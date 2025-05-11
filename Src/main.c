#include "stm32f407xx.h"  // CMSIS header for STM32F4 series
#include "system_stm32f4xx.h"
#include "os.h"

#define SYSTICK_LOAD    SysTick->LOAD
#define SYSTICK_VAL     SysTick->VAL
#define SYSTICK_CTRL    SysTick->CTRL
#define ICSR            SCB->ICSR
#define SHPR2           SCB->SHP[10]  // For SysTick_IRQn priority
#define SHPR3           SCB->SHP[11]  // For PendSV_IRQn priority

// func proto
void GPIO_Init(void);

volatile uint32_t g_var1 = -1;
volatile uint32_t g_var2 = -1;
volatile uint32_t g_tick_cntr = 0;

// Debug variables for HardFault
volatile uint32_t fault_hfsr = 0;
volatile uint32_t fault_cfsr = 0;
volatile uint32_t fault_mmfar = 0;
volatile uint32_t fault_bfar = 0;

uint32_t *task0_sp;
uint32_t *task1_sp;

// Ensure stack arrays are 8-byte aligned
__attribute__((aligned(8))) uint32_t task0_stack[64];
__attribute__((aligned(8))) uint32_t task1_stack[64];

volatile uint32_t current_task = 0;

// Simple tasks
void task0(void) {
    while (1) {
        g_var1++;
    }
}

void task1(void) {
    while (1) {
        g_var2++;
    }
}

// Initialize a task stack with proper alignment
void init_task_stack(uint32_t **stack_addr, void (*task_func)(void)) {
    uint32_t *sp = *stack_addr + 64; // Point to the end of the stack
    
    // Ensure 8-byte alignment
    sp = (uint32_t*)((uint32_t)sp & ~0x7);
    // Reserve space for full exception frame (16 registers: R0-R3, R12, LR, PC, xPSR, R4-R11)
    sp -= 16;

    // Hardware-saved registers
    sp[15] = 0x01000000;         // xPSR (Thumb bit set)
    sp[14] = ((uint32_t)task_func) | 1; // PC (Task entry point)
    sp[13] = 0xFFFFFFFD;          // LR (return to Thread mode using PSP)
    sp[12] = 0;                   // R12
    sp[11] = 0;                   // R3
    sp[10] = 0;                   // R2
    sp[9]  = 0;                   // R1
    sp[8]  = 0;                   // R0
    // Manually saved registers (R4-R11)
    sp[7]  = 0;                   // R11
    sp[6]  = 0;                   // R10
    sp[5]  = 0;                   // R9
    sp[4]  = 0;                   // R8
    sp[3]  = 0;                   // R7
    sp[2]  = 0;                   // R6
    sp[1]  = 0;                   // R5
    sp[0]  = 0;                   // R4

    *stack_addr = sp; // Save the new stack pointer
}

void SysTick_Handler(void) {
    g_tick_cntr++;
    if (g_tick_cntr % 1 == 0) { // Every 1ms
        ICSR |= (1 << 28); // Trigger PendSV
    }
    if (g_tick_cntr % 1000 == 0) // Blink every second
    {
        // Toggle LED (PD12)
        //GPIOD->ODR |= GPIO_ODR_OD12;
    }
}

// PendSV Handler (minimal context switch)
__attribute__((naked)) void PendSV_Handler(void) {
  GPIOD->ODR |= GPIO_ODR_OD12;
  #if 1
    __asm volatile(
        "MRS r0, psp\n"             // Get current PSP
        "BIC r0, r0, #7\n"         // Ensure 8-byte alignment
        "STMDB r0!, {r4-r11}\n"     // Save high registers
        "LDR r1, =current_task\n"
        "LDR r2, [r1]\n"
        "CMP r2, #0\n"
        "BEQ save_task0\n"

        // Save task1_sp
        "LDR r3, =task1_sp\n"
        "STR r0, [r3]\n"
        "B load_task\n"

        "save_task0:\n"
        // Save task0_sp
        "LDR r3, =task0_sp\n"
        "STR r0, [r3]\n"

        "load_task:\n"
        // Toggle task
        "LDR r1, =current_task\n"
        "LDR r2, [r1]\n"
        "EOR r2, r2, #1\n"
        "STR r2, [r1]\n"

        "CMP r2, #0\n"

        "BEQ load_task0\n"

        // Load task1_sp
        "LDR r3, =task1_sp\n"
        "LDR r0, [r3]\n"
        "B restore\n"

        "load_task0:\n"
        // Load task0_sp
        "LDR r3, =task0_sp\n"
        "LDR r0, [r3]\n"

        "restore:\n"
        "LDMIA r0!, {r4-r11}\n"     // Restore high registers
        "MSR psp, r0\n"             // Restore PSP
        "BX lr\n"                   // Return from exception
    );
    #endif
}


void init_systick(void) {
    // Assuming 168 MHz system clock -> 1 ms = 168000 ticks
    SysTick->LOAD = 168000 - 1;  // Adjust if different clock
    SysTick->VAL = 0;
    SysTick->CTRL = 0x07; // Enable SysTick, use system clock, enable interrupt
}

void set_interrupt_priorities(void) {
    NVIC_SetPriority(SysTick_IRQn, 2);
    NVIC_SetPriority(PendSV_IRQn, 3);
}

int main(void) {
    // Disable interrupts during setup
    __asm volatile("CPSID i\n");

    task0_sp = task0_stack;
    task1_sp = task1_stack;

    // Initialize task stacks
   init_task_stack(&task0_sp, task0);
   init_task_stack(&task1_sp, task1);

    // Initialize system clock and peripherals
    SystemInit();

    // Set interrupt priorities
    set_interrupt_priorities();

    // Initialize SysTick
    init_systick();

    GPIO_Init();
#if 0
    // Start first task (Task0)
    __asm volatile(
        "LDR r0, =task0_sp\n"
        "LDR r0, [r0]\n"
        "BIC r0, r0, #7\n"         // Ensure 8-byte alignment
        "MSR psp, r0\n"            // Set PSP to task0 stack
        "MOVS r0, #2\n"            // CONTROL = 0x2 -> Use PSP, unprivileged mode
        "MSR CONTROL, r0\n"
        "ISB\n"
        "CPSIE i\n"                // Re-enable interrupts
    );
#endif
__asm volatile(
  "LDR r0, =task0_sp\n"
  "LDR r0, [r0]\n"
  "BIC r0, r0, #7\n"         // Ensure 8-byte alignment
  "MSR psp, r0\n"            // Set PSP to task0 stack
  "MOVS r0, #2\n"            // CONTROL = 0x2 -> Use PSP, unprivileged mode
  "MSR CONTROL, r0\n"
  "ISB\n"
  "CPSIE i\n"                // Re-enable interrupts
  "LDR r0, =task0\n"
  "BX r0\n"                  // Jump to task0
);

// create_thread(task0);
// create_thread(task1);

    while (1) {
        // Main loop idle
    }
}

// HardFault Handler (for debugging)
void HardFault_Handler(void) {
    fault_hfsr = *(volatile uint32_t*)0xE000ED2C; // HFSR
    fault_cfsr = *(volatile uint32_t*)0xE000ED28; // CFSR
    fault_mmfar = *(volatile uint32_t*)0xE000ED34; // MMFAR
    fault_bfar = *(volatile uint32_t*)0xE000ED38; // BFAR
   // __asm volatile("BKPT #0\n");
    while (1);
}


// Configure GPIO for LED
void GPIO_Init(void)
{
    // Enable GPIO clock for Port D (where the onboard LED is connected)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    
    // Set pin PD12 as output
    GPIOD->MODER |= GPIO_MODER_MODE12_0;  // Output mode
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT_12;  // Push-pull
    GPIOD->OSPEEDR |= GPIO_OSPEEDR_OSPEED12;  // High speed
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD12;  // No pull-up, no pull-down
}