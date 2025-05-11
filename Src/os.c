 
 #include "os.h"

 tcb_ thread_pool[THREAD_POOL_SIZE];
 tcb_ *execution_queue;
 tcb_ *current_thread;
 tcb_ *next_thread;
 
 volatile unsigned long int total_tasks;
 unsigned long int current_sp;
 unsigned long int next_sp;
 unsigned long int *sp;
 
 
 /*
  * Enables all interrupts
  */
 void enable_interrupts() {
     // Enables all interrupts
     __asm("CPSIE I");
 }
 
 /*
  * Disables all interrupts
  */
 void dissable_interrupts() {
     // Disables all interrupts
     __asm("CPSID I");
 }
   
 void PendSV_Handler() {
     __asm("CPSID I");
     __asm("PUSH  {r4-r11}");
 
     if (current_thread == NULL) {
         current_thread = execution_queue;
         current_sp = (unsigned long int)(current_thread->sp);
         __asm("LDR R10, =current_sp");
         __asm("LDR SP,[R10,#0x00]");
         __asm("POP {R4-R11}");
         __asm("CPSIE I");
         return;
     }
 
     if (current_thread->next == NULL) {
         next_thread = execution_queue;
     } else {
         next_thread = current_thread->next;
     }
 
     current_sp = (unsigned long int)&current_thread->sp;
     __asm("LDR r10, =current_sp");
     __asm("LDR r11, [r10]");
     __asm("STR sp,[r11,#0x00]");
 
     next_sp = (unsigned long int)(next_thread->sp);
     __asm("LDR r10, =next_sp");
     __asm("LDR sp,[r10,#0x00]");
     current_thread = next_thread;
 
     __asm("POP {r4-r11}");
     __asm("CPSIE I");
 }
 
 static void add_to_execution_queue(tcb_ *tcb) {
     tcb->next = execution_queue;
     execution_queue = tcb;
 }
 
 
 /*
  * Creates a Thread for a function provided and adds it into execution queue
  */
 void create_thread(function task) {
     dissable_interrupts();
 
     unsigned long int *sp;
     tcb_ *tcb = &thread_pool[total_tasks];  // Get the Next free TCB
 
     sp   = (unsigned long int *)((unsigned long int*)&(tcb->stack[TASK_STACK_SIZE]));
 
     *(--sp) = (1U << 24);  // Set thumb bit of XPSR
     *(--sp) = (unsigned long int)task;  // PC points to the task
 
     for (int i=0; i <= 13; i++)
         *(--sp) = i;
 
     *sp = 0xDEADBEEF;
 
     // Get the stack pointer for current task
     tcb->sp = sp;
 
     add_to_execution_queue(tcb);
     total_tasks ++;
 
     enable_interrupts();
 }
 
