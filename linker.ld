/*
 * linker.ld - The Blueprint of Memory
 * This file tells the linker how to construct the final OS image,
 * placing the bootloader's code first, followed by our kernel.
 */

OUTPUT_FORMAT(elf32-i386)
ENTRY(main)

SECTIONS
{
    . = 0x100000; /* Load the kernel at 1MB */

    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}
