; =============================================================================
; isr.s - Low-Level Interrupt Service Routine Stubs
; =============================================================================
; This file contains the assembly stubs for handling interrupts. Each stub
; saves the processor state, calls the main C handler, and then restores
; the state. This is the bridge between raw hardware signals and our C kernel.
; =============================================================================

[bits 32]

; This macro creates a common ISR stub.
%macro ISR_NOERRCODE 1
[global isr%1]
isr%1:
    cli          ; Disable interrupts.
    push byte 0  ; Push a dummy error code.
    push byte %1 ; Push the interrupt number.
    jmp isr_common_stub
%endmacro

; This macro creates an ISR stub for interrupts that push an error code.
%macro ISR_ERRCODE 1
[global isr%1]
isr%1:
    cli
    ; Error code is already on the stack.
    push byte %1
    jmp isr_common_stub
%endmacro

; This macro creates a common IRQ stub.
%macro IRQ 2
[global irq%1]
irq%1:
    cli
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro

; --- CPU Exception ISRs ---
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_ERRCODE   17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_ERRCODE   30
ISR_NOERRCODE 31

; --- Hardware IRQs ---
IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

; Common ISR stub
extern isr_handler
extern irq_handler
extern idt_p

isr_common_stub:
    pusha        ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
    mov ax, ds   ; Lower 16-bits of ds register
    push eax     ; save the data segment descriptor

    mov ax, 0x10 ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop ebx      ; reload the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa         ; Pops edi,esi,ebp,esp,ebx,edx,ecx,eax
    add esp, 8   ; Cleans up the pushed error code and ISR number
    sti          ; Re-enable interrupts
    iret         ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

; Common IRQ stub
irq_common_stub:
    pusha
    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irq_handler

    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa
    add esp, 8
    sti
    iret

; Function to load the IDT
[global idt_load]
idt_load:
    lidt [idt_p]
    ret
