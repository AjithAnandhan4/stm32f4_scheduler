MEMORY 
{
	sram (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
	flash (rx) : ORIGIN = 0x08000000, LENGTH = 1M
}

_eStack = ORIGIN(sram) + LENGTH(sram);

SECTIONS
{
   .vector :  
   {
     *(.vectors)
   }>flash 
   
   .text :
   {
     *(.text)
   }>flash 
   
   .rodata :
   {
     *(.rodata)   
   }>flash 
   
   _startflashdataaddr = .;
   
   .data :
   {
    _sdatasram = .;
     *(.data)
	_edatasram = .;
   }>sram AT >flash
   
   .bss :
   {
     _sbss = .;
     *(.bss)
	 _ebss = .;
   }>sram
   
}