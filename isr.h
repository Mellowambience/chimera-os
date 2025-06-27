/*
 * =============================================================================
 * isr.h - Interrupt Service Routines (ISRs) and IDT definitions
 * =============================================================================
 * This file defines the structure for interrupt gates and the Interrupt
 * Descriptor Table (IDT). It also declares the functions for installing
 * interrupt handlers.
 * =============================================================================
 */

#ifndef ISR_H
#define ISR_H

#include "common.h"

// Define the structure for an IDT entry (Interrupt Gate)
struct idt_entry {
    u16int base_low;  // The lower 16 bits of the address to jump to when this interrupt fires.
    u16int sel;       // Kernel segment selector.
    u8int  always0;   // This must always be zero.
    u8int  flags;     // Flags: type and attributes, DPL, P.
    u16int base_high; // The upper 16 bits of the address to jump to.
} __attribute__((packed));

// Define the structure for the IDT pointer
struct idt_ptr {
    u16int limit; // The upper 16 bits of all selector limits.
    u32int base;  // The address of the first idt_entry structure.
} __attribute__((packed));

// Declare the IDT itself, and the IDT pointer.
extern struct idt_entry idt[256];
extern struct idt_ptr idt_p;

// This exists in `isr.s` and is used to load the IDT.
extern void idt_load();

// IRQ definitions
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47


// Function to install a single IDT entry.
void idt_set_gate(u8int num, u32int base, u16int sel, u8int flags);

// Function to install the IDT.
void idt_install();

// These are the assembly ISRs defined in `isr.s`.
// They are extern because they are called from C, but defined in assembly.
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// IRQ handlers (hardware interrupts)
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

// Structure for registers pushed by the ISR assembly stub.
// This is how the C handler receives the CPU state.
struct registers {
    u32int ds;                                     // Data segment selector
    u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    u32int int_no, err_code;                       // Interrupt number and error code (if applicable)
    u32int eip, cs, eflags, useresp, ss;           // Pushed by the processor automatically.
};

// This is the main C interrupt handler.
void isr_handler(struct registers regs);

// A generic handler for IRQs.
void irq_handler(struct registers regs);

// Function to install a custom IRQ handler.
typedef void (*isr_t)(struct registers);
void register_interrupt_handler(u8int n, isr_t handler);

#endif // ISR_H
