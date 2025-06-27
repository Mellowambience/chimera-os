/*
 * =============================================================================
 * io.h - Port I/O functions
 * =============================================================================
 * This file declares functions for interacting with hardware ports.
 * =============================================================================
 */

#ifndef IO_H
#define IO_H

#include "common.h"

u8int inb(u16int port);
void outb(u16int port, u8int data);

#endif // IO_H
