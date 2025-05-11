/* GNU linker script for STM32F407 (cortex-M4)*/

MEMORY 
{
	sram (rwx) : ORIGIN = 0x20000000, LENGTH = 128K /* SRAM 128 KB*/
	flash (rx) : ORIGIN = 0x08000000, LENGTH = 1M   /* Flash memory 1024KB*/
}

_estack = ORIGIN(sram) + LENGTH(sram);

SECTIONS
{
    /* Interrupt vector table in flash */
   .isr_vectors :  
   {
    . = ALIGN(4);
    KEEP(*(.isr_vectors)) 
   }>flash 
   
   .text :
   {
    . = ALIGN(4);
    *(.text*)
    *(rodata*)
    . = ALIGN(4);
    _etext = .;
   }>flash 
   
   .data :
   {
    . = ALIGN(4);
    _sdata = .;      /* Start of data in SRAM */
    *(.data*)      /* Initialized data */
    . = ALIGN(4);
    _edata = .;     /* End of data in SRAM */
   }>sram AT >flash
   
  /* Uninitialized data (BSS) in SRAM */
  .bss :
  {
      . = ALIGN(4);
      _sbss = .;         /* Start of BSS */
      *(.bss*)           /* Uninitialized data */
      *(COMMON)          /* Common uninitialized data */
      . = ALIGN(4);
      _ebss = .;         /* End of BSS */
  } > sram

  /* Discard unused sections */
  /DISCARD/ :
  {
      *(.ARM.exidx*)     /* Exception unwinding (not needed for Cortex-M3) */
      *(.comment)        /* Comments */
      *(.note*)          /* Notes */
  }
   
}