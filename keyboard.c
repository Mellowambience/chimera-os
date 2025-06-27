/*
 * =============================================================================
 * keyboard.c - Keyboard Driver Implementation
 * =============================================================================
 * This file contains the implementation of the keyboard driver. It handles
 * IRQ1, reads scancodes from the keyboard controller, and translates them
 * into ASCII characters that can be printed to the screen.
 * =============================================================================
 */

#include "keyboard.h"
#include "isr.h"
#include "kernel.h"

// Scancode to ASCII mapping for a US keyboard layout.
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
  '9', '0', '-', '=', '\b', /* Backspace */
  '\t',         /* Tab */
  'q', 'w', 'e', 'r',   /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,          /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
  '\'', '`',   0,        /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',            /* 49 */
  'm', ',', '.', '/',   0,              /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

// The main keyboard handler.
void keyboard_handler(struct registers regs) {
    unsigned char scancode;

    // Read from the keyboard's data buffer
    scancode = inb(0x60);

    // If the top bit of the byte we read is set, that means that a key has just been released
    if (scancode & 0x80) {
        // You can use this one to see if the user released the shift, alt, or control keys...
    } else {
        // Here, a key was just pressed. Please note that if you hold a key down, you will get repeated key press interrupts.
        // Just to prove you can see the keyboard working, we'll print the scancode to the screen.
        print_char(kbdus[scancode], -1, -1, 0x0F);
    }
}

// Function to install the keyboard handler.
void keyboard_install() {
    register_interrupt_handler(IRQ1, &keyboard_handler);
}