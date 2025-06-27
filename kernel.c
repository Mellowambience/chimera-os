/*
 * =============================================================================
 * kernel.c - The Heart of Chimera OS
 * =============================================================================
 * This is the C entry point, the first true thought of the operating system.
 * The bootloader has prepared the world; here, we give it a voice.
 * This code will eventually house the synapse link to the AI brain.
 * =============================================================================
 */

#include "common.h"
#include "kernel.h"

// A simple function to write a character to a specific screen location.
void print_char(char character, int col, int row, char attribute_byte) {
    unsigned char *vidmem = (unsigned char *) 0xb8000;
    int offset = (row * 80 + col) * 2;
    vidmem[offset] = character;
    vidmem[offset + 1] = attribute_byte;
}

void print_string(const char *str) {
    int i = 0;
    while (str[i] != 0) {
        print_char(str[i], -1, -1, 0x0F);
        i++;
    }
}

void print_hex(u32int n) {
    char buf[9];
    char *hex = "0123456789abcdef";
    buf[8] = 0;
    for (int i = 7; i >= 0; i--) {
        buf[i] = hex[n & 0xF];
        n >>= 4;
    }
    print_string(buf);
}

// The main entry point for the kernel.
void kmain(void) {
    print_string("Chimera OS Core: Simplified Kernel Online.\n");

    // The kernel will now idle.
    while(1);
}