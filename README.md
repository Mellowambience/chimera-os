# Project Chimera OS

## The AI-Core Operating System

Project Chimera is an ambitious endeavor to build a foundational operating system with deep AI integration at its core. Unlike traditional operating systems where AI is merely an application, Chimera OS aims to leverage AI for fundamental OS decisions, including resource management, task scheduling, and user interaction.

## Current Status

**Under active development.**

Currently, the project has successfully established a basic bootloader and a minimal kernel capable of displaying text. The development environment and build process are set up, and the project is moving towards implementing core OS functionalities with AI integration in mind.

## Key Features (Planned/In Progress)

*   **Hybrid Architecture:** A lean microkernel (the "Heart") handles low-level hardware, while an AI layer (the "Brain") provides strategic decision-making.
*   **Conversational Interface:** Future goal to allow natural language interaction with the OS.
*   **AI-Powered Resource Management:** AI will guide process scheduling and memory allocation.
*   **Modular Design:** Built with extensibility in mind for future features.

## Building Chimera OS

To build Chimera OS, you will need the following tools installed on your system:

*   `nasm` (Netwide Assembler)
*   `x86_64-elf-gcc` (GCC Cross-Compiler for i386-elf target)
*   `qemu` (QEMU Emulator)

If you are on macOS, you can install these using Homebrew:

```bash
brew install nasm x86_64-elf-gcc qemu
```

Once the tools are installed, navigate to the `chimera_os` directory and run the following commands:

```bash
# Clean up previous build artifacts
rm -f *.o *.bin *.img

# Assemble the bootloader
nasm -f bin boot.s -o boot.bin

# Assemble the ISR stubs
nasm -f elf32 isr.s -o isr_asm.o

# Compile C files
x86_64-elf-gcc -m32 -ffreestanding -c kernel.c -o kernel.o
x86_64-elf-gcc -m32 -ffreestanding -c isr.c -o isr_c.o
x86_64-elf-gcc -m32 -ffreestanding -c keyboard.c -o keyboard.o
x86_64-elf-gcc -m32 -ffreestanding -c io.c -o io.o

# Link all object files into the kernel binary
x86_64-elf-ld -m elf_i386 -T linker.ld kernel.o isr_asm.o isr_c.o keyboard.o io.o -o kernel.bin

# Create a blank 1.44MB floppy disk image
dd if=/dev/zero of=floppy.img bs=1024 count=1440

# Copy bootloader to the floppy image
dd if=boot.bin of=floppy.img bs=512 count=1 conv=notrunc

# Copy kernel to the floppy image
dd if=kernel.bin of=floppy.img bs=512 seek=1 conv=notrunc
```

## Running Chimera OS in QEMU

After building, you can run Chimera OS using QEMU:

```bash
qemu-system-i386 -fda floppy.img
```

If you encounter issues with QEMU not booting, ensure your QEMU installation is correct and try explicitly setting the boot device:

```bash
qemu-system-i386 -fda floppy.img -boot a
```

## Contributing

Contributions are welcome! Please feel free to open issues or pull requests on the GitHub repository.