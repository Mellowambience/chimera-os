/*
 * =============================================================================
 * kernel.h - Main Kernel Definitions
 * =============================================================================
 * This file contains the main definitions for the kernel, including function
 * prototypes for printing and port I/O.
 * =============================================================================
 */

#ifndef KERNEL_H
#define KERNEL_H

#include "common.h"
#include "io.h"

void print_char(char character, int col, int row, char attribute_byte);
void print_string(const char *str);
void print_hex(u32int n);

u8int inb(u16int port);
void outb(u16int port, u8int data);

#endif // KERNEL_H
