#include <stdint.h>
#include "stm32f407xx.h"  // CMSIS header for STM32F4 series

/* Symbols from linker script */
extern uint32_t _estack;
extern uint32_t _etext, _sdata, _edata;
extern uint32_t _sbss, _ebss;

extern int main(void);
extern void Reset_Handler(void);
void Default_Handler(void);         /* Default handler for unused IRQs */

// Cortex-M core exception handlers
void NMI_Handler(void)               __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)           __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)          __attribute__((weak, alias("Default_Handler")));

// STM32F407 Peripheral IRQ Handlers (0–81)
void WWDG_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void EXTI2_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream0_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream1_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream2_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream3_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream4_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream5_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream6_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void ADC_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void CAN1_TX_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void CAN1_RX0_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void CAN1_RX1_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void TIM4_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void USART3_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void OTG_FS_WKUP_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void TIM8_BRK_TIM12_IRQHandler(void)__attribute__((weak, alias("Default_Handler")));
void TIM8_UP_TIM13_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_TRG_COM_TIM14_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream7_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void FSMC_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void SDIO_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void TIM5_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void SPI3_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void UART4_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void UART5_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void TIM7_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void ETH_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void ETH_WKUP_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void CAN2_TX_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void CAN2_RX0_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void CAN2_RX1_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void CAN2_SCE_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void USART6_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void OTG_HS_EP1_OUT_IRQHandler(void)__attribute__((weak, alias("Default_Handler")));
void OTG_HS_EP1_IN_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_HS_WKUP_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void OTG_HS_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void DCMI_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void CRYP_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void HASH_RNG_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void FPU_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));

// Vector table with 98 entries
void (* const vector_table[98])(void) __attribute__((section(".isr_vectors"))) = {
    (void (*)(void))((uint32_t)&_estack),    // 0: Initial Stack Pointer
    Reset_Handler,                // 1: Reset
    NMI_Handler,                  // 2
    HardFault_Handler,            // 3
    MemManage_Handler,            // 4
    BusFault_Handler,             // 5
    UsageFault_Handler,           // 6
    0, 0, 0, 0,                   // 7–10 Reserved
    SVC_Handler,                  // 11
    DebugMon_Handler,             // 12
    0,                            // 13 Reserved
    PendSV_Handler,               // 14
    SysTick_Handler,              // 15
    // IRQ 0–81
    WWDG_IRQHandler,
    PVD_IRQHandler,
    TAMP_STAMP_IRQHandler,
    RTC_WKUP_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler,
    EXTI0_IRQHandler,
    EXTI1_IRQHandler,
    EXTI2_IRQHandler,
    EXTI3_IRQHandler,
    EXTI4_IRQHandler,
    DMA1_Stream0_IRQHandler,
    DMA1_Stream1_IRQHandler,
    DMA1_Stream2_IRQHandler,
    DMA1_Stream3_IRQHandler,
    DMA1_Stream4_IRQHandler,
    DMA1_Stream5_IRQHandler,
    DMA1_Stream6_IRQHandler,
    ADC_IRQHandler,
    CAN1_TX_IRQHandler,
    CAN1_RX0_IRQHandler,
    CAN1_RX1_IRQHandler,
    CAN1_SCE_IRQHandler,
    EXTI9_5_IRQHandler,
    TIM1_BRK_TIM9_IRQHandler,
    TIM1_UP_TIM10_IRQHandler,
    TIM1_TRG_COM_TIM11_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM4_IRQHandler,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    I2C2_EV_IRQHandler,
    I2C2_ER_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    USART3_IRQHandler,
    EXTI15_10_IRQHandler,
    RTC_Alarm_IRQHandler,
    OTG_FS_WKUP_IRQHandler,
    TIM8_BRK_TIM12_IRQHandler,
    TIM8_UP_TIM13_IRQHandler,
    TIM8_TRG_COM_TIM14_IRQHandler,
    TIM8_CC_IRQHandler,
    DMA1_Stream7_IRQHandler,
    FSMC_IRQHandler,
    SDIO_IRQHandler,
    TIM5_IRQHandler,
    SPI3_IRQHandler,
    UART4_IRQHandler,
    UART5_IRQHandler,
    TIM6_DAC_IRQHandler,
    TIM7_IRQHandler,
    DMA2_Stream0_IRQHandler,
    DMA2_Stream1_IRQHandler,
    DMA2_Stream2_IRQHandler,
    DMA2_Stream3_IRQHandler,
    DMA2_Stream4_IRQHandler,
    ETH_IRQHandler,
    ETH_WKUP_IRQHandler,
    CAN2_TX_IRQHandler,
    CAN2_RX0_IRQHandler,
    CAN2_RX1_IRQHandler,
    CAN2_SCE_IRQHandler,
    OTG_FS_IRQHandler,
    DMA2_Stream5_IRQHandler,
    DMA2_Stream6_IRQHandler,
    DMA2_Stream7_IRQHandler,
    USART6_IRQHandler,
    I2C3_EV_IRQHandler,
    I2C3_ER_IRQHandler,
    OTG_HS_EP1_OUT_IRQHandler,
    OTG_HS_EP1_IN_IRQHandler,
    OTG_HS_WKUP_IRQHandler,
    OTG_HS_IRQHandler,
    DCMI_IRQHandler,
    CRYP_IRQHandler,
    HASH_RNG_IRQHandler,
    FPU_IRQHandler
};

/* Reset Handler */
void Reset_Handler(void)
{
    // Copy initialized data from flash to SRAM
    uint32_t *src = &_etext;
    uint32_t *dest = &_sdata;
    while (dest < &_edata)
    {
        *dest++ = *src++;
    }

    // Zero initialize the .bss section
    dest = &_sbss;
    while (dest < &_ebss)
    {
        *dest++ = 0U;
    }

    // Call the application's entry point
    main();

    // If main returns, loop forever
    while (1);
}

/* Default Handler */
void Default_Handler(void)
{
    __asm volatile(
        "BKPT #0\n" // Break into debugger
      );
    while (1);
}


// System Initialization: Basic Clock Setup
void SystemInit(void)
{
    // Configure the HSI as the system clock (16 MHz)
    RCC->CR |= RCC_CR_HSION;   // Enable HSI oscillator
    while (!(RCC->CR & RCC_CR_HSIRDY));  // Wait for HSI to stabilize
    RCC->CFGR &= ~RCC_CFGR_SW;  // Set HSI as system clock
    RCC->CFGR |= RCC_CFGR_SW_HSI;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); // Wait for system clock to switch to HSI
}