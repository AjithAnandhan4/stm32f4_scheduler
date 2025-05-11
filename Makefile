# Compiler and flags
CC      = arm-none-eabi-gcc
CFLAGS  = -mcpu=cortex-m4 -mthumb -c -g -I./Inc
LFLAGS  = -mcpu=cortex-m4 -mthumb -nostdlib -Wl,-Map=build/main.map -T main.ld

# Sources and objects
SRCS    = Src/startup.c Src/main.c Src/os.c
OBJS    = build/startup.o build/main.o build/os.o
TARGET  = build/main.elf

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

# Compilation
build/%.o: Src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) $< -o $@

# Clean build
clean:
	rm -rf build/*


# Flash firmware
flash: $(TARGET)
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(TARGET) verify reset exit"

# Debug using OpenOCD
debug:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

# Launch GDB
gdb: $(TARGET)
	arm-none-eabi-gdb $(TARGET)

.PHONY: all clean flash debug gdb
