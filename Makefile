CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -c -g
LFLAGS = -mcpu=cortex-m4 -nostdlib -mthumb -Wl,-Map=main.map -T main.ld
all : startup.o main.o
	$(CC) $(LFLAGS) -o main.elf main.o startup.o 

startup : startup.c
	$(CC) $(CFLAGS) startup.c

main : main.c
	$(CC) $(CFLAGS) main.c
	
clean:
	rm -f *.o *.elf *.map
	#del /Q *.o *.elf *.map
flash: 
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program main.elf verify reset exit"

debug:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

gdb:
	arm-none-eabi-gdb main.elf
	

