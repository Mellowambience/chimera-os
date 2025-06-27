/*
 * =============================================================================
 * io.c - Port I/O functions implementation
 * =============================================================================
 * This file implements functions for interacting with hardware ports.
 * =============================================================================
 */

#include "io.h"

// Read a byte from a port
u8int inb(u16int port) {
    u8int ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

// Write a byte to a port
void outb(u16int port, u8int data) {
    __asm__ __volatile__("outb %0, %1" : : "a"(data), "dN"(port));
}
