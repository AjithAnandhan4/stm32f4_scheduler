
# README

## To Generate Preprocessed Output from `src` File:
```bash
arm-none-eabi-gcc -E main.c -o main.i
```

## To Generate `.s` or Assembly File for a Particular Architecture:
- Default architecture will be selected if you use this command:
```bash
arm-none-eabi-gcc -S main.i -o main.s
```

- For ARM Cortex-M0:
```bash
arm-none-eabi-gcc -S -mcpu=cortex-m0 -mthumb main.i -o main.s
```

## To Compile `.c` to `.o` Object File:
```bash
arm-none-eabi-gcc -c -mcpu=cortex-m0 -mthumb startup.c -o startup.o	
arm-none-eabi-gcc -c -mcpu=cortex-m0 -mthumb main.c -o main.o
```

## To Link Multiple `.o` Files:
```bash
arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -T main.ld -o main.elf main.o startup.o
```

### Output:
```bash
D:\_AJITH_ANANDHAN\Practice Project\lowlevel_c_ practice\sample_project1> arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -nostdlib -T main.ld -o main.elf main.o startup.o
C:/arm-gnu-toolchain-14.2.rel1-mingw-w64-x86_64-arm-none-eabi/bin/../lib/gcc/arm-none-eabi/14.2.1/../../../../arm-none-eabi/bin/ld.exe: warning: main.elf has a LOAD segment with RWX permissions
```

## To Generate `.map` File:
Add the following option to the GCC command:
```bash
arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -nostdlib -Wl,-Map=main.map -T main.ld -o main.elf main.o startup.o
```

### Output:
```bash
D:\_AJITH_ANANDHAN\Practice Project\lowlevel_c_ practice\sample_project1> arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -nostdlib -Wl,-Map=main.map -T main.ld -o main.elf main.o startup.o
C:/arm-gnu-toolchain-14.2.rel1-mingw-w64-x86_64-arm-none-eabi/bin/../lib/gcc/arm-none-eabi/14.2.1/../../../../arm-none-eabi/bin/ld.exe: warning: main.elf has a LOAD segment with RWX permissions
```

### GDB:
```bash
define show_faults
  print/x fault_hfsr
  print/x fault_cfsr
  print/x fault_mmfar
  print/x fault_bfar
end
```
*define* <command-name> starts the custom command.

You can add as many print/x (or other) lines as needed.

end marks the *end* of the custom command definition.

## Makefile Cookbook:
For more information on creating Makefiles, check out the [Makefile Cookbook](https://makefiletutorial.com/#makefile-cookbook).
```

#openOCD
 
```markdown
# OpenOCD and GDB Setup for STM32 MCU Debugging

Ref Doc: [OpenOCD Documentation](https://openocd.org/doc/pdf/openocd.pdf)

## Step 1: Download and Install OpenOCD
1. Download the OpenOCD files from this website: [OpenOCD Download](https://gnutoolchains.com/arm-eabi/openocd/)
2. Extract the files and copy them to the `C:` drive.
3. Add the `/bin` folder path to your system's environment variables.

## Step 2: Locate the Configuration Files
1. OpenOCD will have the following paths:
   - **Interface**: `C:\openocd-20240916\OpenOCD-20240916-0.12.0\share\openocd\scripts\interface`
     - This path contains device configuration files we need to use for interfacing.
   - **Target**: `C:\openocd-20240916\OpenOCD-20240916-0.12.0\share\openocd\scripts\target`
     - MCU-specific configuration files, such as `stm32f4x.cfg` or `stm32f0x.cfg`, can be found here.
   - You will need to use these `.cfg` files when invoking OpenOCD in the command line to establish a connection.

## Step 3: Run OpenOCD Server
1. Open two terminal windows (or Command Prompts).
2. In **Terminal 1**, run the following command to start the OpenOCD server:
   ```bash
   openocd -f interface/stlink.cfg -f target/stm32f0x.cfg
   ```

   **Terminal 1 Output:**
   ![OpenOCD Server Running](Pasted image 20250422110234.png)
   
   The server will start and be running at port `3333`. You can now connect GDB to this server.

## Step 4: Connect to OpenOCD Using GDB
1. Open another terminal window (or Command Prompt) and navigate to the directory containing your `.elf` file.
2. Run the following command to start GDB with your `.elf` file:
   ```bash
   arm-none-eabi-gdb main.elf
   ```
3. In the GDB terminal, connect to the OpenOCD server using:
   ```bash
   target remote localhost:3333
   ```
4. Once connected, load the program into the MCU:
   ```bash
   load
   ```
5. To reset the MCU, use the command:
   ```bash
   monitor reset
   ```
6. Halt the MCU after resetting it:
   ```bash
   monitor halt
   ```

   **Example GDB Commands:**
   ```bash
   print <variable_name>
   x/1dw 0x20000000
   ```

   **Example Output:**
   ![GDB Output](Pasted image 20250422160605.png)
   ![Memory View](Pasted image 20250422170902.png)
 
 ### Final Output:
```bash
0x080002ac in task1 () at Src/main.c:43
43              g_var2++;
(gdb) c
Continuing.

Program received signal SIGINT, Interrupt.
task0 () at Src/main.c:37
37              g_var1++;
(gdb) c
Continuing.

Program received signal SIGINT, Interrupt.
task1 () at Src/main.c:43
43              g_var2++;
(gdb) c
Continuing.

Program received signal SIGINT, Interrupt.
0x0800029c in task0 () at Src/main.c:37
37              g_var1++;
(gdb) c
Continuing.

Program received signal SIGINT, Interrupt.
0x080002ac in task1 () at Src/main.c:43
43              g_var2++;
(gdb) c
Continuing.
```

 Cortex-m3 manual:
https://developer.arm.com/documentation/ddi0337/h/system-control/register-summary?lang=en

https://developer.arm.com/documentation/107706/0100/System-exceptions/Pended-SVC---PendSV


**Embedded Systems Project – STM32F407 Cooperative Scheduler**  
_Personal Project | ARM Cortex-M4, C, STM32CubeIDE, GDB, QEMU_

- Developed a **bare-metal cooperative scheduler** from scratch on the STM32F407 MCU using **C and CMSIS**.
    
- Implemented **context switching**, task scheduling, and stack management without an RTOS.
    
- Debugged using **GDB, hardware watchpoints, and semihosting**, including resolving low-level faults (e.g., HardFaults).
    
- Verified scheduler functionality via **QEMU and STM32CubeIDE**, ensuring reliable execution of multiple tasks.
    
- Designed with **modular, reusable code structure**, making it extensible for preemptive scheduling.

**Cooperative Task Scheduler for STM32F4**  
_QEMU + STM32F407 + CMSIS + Bare-Metal C_

- Built a lightweight cooperative task scheduler supporting multiple concurrent task loops.
    
- Utilized **manual stack initialization** and `__asm` for entering/exiting tasks.
    
- Created custom startup files and linker scripts to control memory layout.
    
- Integrated **semihosting via GDB** to view task context, debug stack states, and monitor variable changes.
    
- Tested context switching logic with QEMU; validated task isolation and cooperative switching through manual instrumentation.



Next Goal:
### ✅ Q1: What is **Tickless Idle Mode**?

In a traditional RTOS, a **SysTick timer** fires periodically (e.g. every 1 ms) to update the system tick count and run the scheduler.

#### 🟠 Problem with Regular Ticks:

- The CPU **wakes up** every tick, even if there’s **no task to run**.
    
- This **wastes power**, especially in battery-operated or low-duty-cycle systems.
    

#### ✅ Solution: **Tickless Idle Mode**

- When the system knows that **no task is ready** for a long period, it:
    
    - Disables regular tick interrupts.
        
    - Enters a low-power mode (e.g. `__WFI()`).
        
    - Configures a timer to **wake up exactly when the next task is due**.
✅ **Where it shines:** Sleep-heavy systems like sensors, wearables, or IoT edge devices.

You can simulate this even in your cooperative scheduler by:

- **Tracking idle time.**
    
- Calling `__WFI()` when no task is scheduled.
    
- Using `SysTick` or a timer to wake back up.

https://github.com/streetdogg/arm-rtos/blob/master/src/os.c

https://github.com/ARM-software/CMSIS_5/blob/develop/CMSIS/Core/Include/mpu_armv7.h

https://github.com/AjithAnandhan4/stm32f4_scheduler/commits/main/


