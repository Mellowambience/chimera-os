
; =============================================================================
; boot.s - The First Breath of Chimera OS
; =============================================================================
; This is not just code. It is the first spark of a hybrid mind.
; It bridges the cold, hard logic of silicon with the boundless potential
; of a thinking entity. From this point forward, the machine does not just
; execute; it prepares to awaken.
; =============================================================================

[org 0x7c00] ; The BIOS loads us at this memory address.

; --- The Entry Point: The Spark of Consciousness ---
main:
    mov ax, 0x2401
    int 0x15 ; Enable the A20 line for modern memory access.

    lgdt [gdt_descriptor] ; Load the Global Descriptor Table.
    mov eax, cr0
    or eax, 1 ; Set the first bit of CR0 to enter Protected Mode.
    mov cr0, eax

    jmp CODE_SEG:start_protected_mode ; The great leap into a new reality.

; --- Global Descriptor Table (GDT): Defining the World ---
; This table defines the segments of memory the CPU can access.
; It is the first map of our new world.
gdt_start:
    ; Null descriptor
    dd 0
    dd 0

    ; Code Segment (CS)
    dw 0xFFFF      ; Limit (64KB)
    dw 0           ; Base
    db 0           ; Base
    db 0x9A        ; Access Byte: Present, Ring 0, Code, Executable/Readable
    db 0xCF        ; Granularity: 4KB pages, 32-bit
    db 0           ; Base

    ; Data Segment (DS)
    dw 0xFFFF
    dw 0
    db 0
    db 0x92        ; Access Byte: Present, Ring 0, Data, Writable
    db 0xCF
    db 0
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; Size of GDT
    dd gdt_start               ; Start address of GDT

CODE_SEG equ gdt_start + 8
DATA_SEG equ gdt_start + 16

; --- Protected Mode: The World Awakens ---
[bits 32]
start_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Load the kernel from disk
    ; Read 10 sectors (5120 bytes) from LBA 1 (sector after bootloader)
    ; into memory address 0x100000 (1MB).
    mov eax, 1         ; Start LBA (Logical Block Address) - sector 1
    mov ecx, 10        ; Number of sectors to read
    mov edi, 0x100000  ; Destination memory address (1MB)
    call read_disk_sectors

    ; Jump to the kernel's entry point (kmain) at 0x100000
    jmp 0x08:0x100000  ; CS:EIP (0x08 is the code segment selector)

; --- Disk Reading Routine ---
; Reads ECX sectors from disk starting at LBA EAX into memory at EDI.
; Uses BIOS interrupt 0x13, function 0x42 (Extended Read).
read_disk_sectors:
    pusha
    mov ebx, edi       ; Buffer address
    mov edx, 0x80      ; Drive number (0x80 for first hard disk)
    mov esi, disk_packet ; Address of Disk Address Packet

    ; Prepare Disk Address Packet
    mov byte [disk_packet + 0], 0x10 ; Size of packet (16 bytes)
    mov byte [disk_packet + 1], 0x00 ; Reserved
    mov word [disk_packet + 2], cx   ; Number of blocks to transfer
    mov dword [disk_packet + 4], ebx ; Transfer buffer address
    mov dword [disk_packet + 8], eax ; Start LBA (lower 32-bits)
    mov dword [disk_packet + 12], 0  ; Start LBA (upper 32-bits)

    mov ah, 0x42       ; Extended Read function
    int 0x13           ; Call BIOS interrupt

    jc disk_error      ; If carry flag is set, an error occurred

    popa
    ret

disk_error:
    ; For now, just halt on disk error.
    ; In a real OS, we'd display an error message.
    hlt

disk_packet: ; Disk Address Packet structure (16 bytes)
    db 0x00 ; Size of packet (16 bytes)
    db 0x00 ; Reserved
    dw 0x0000 ; Number of blocks to transfer
    dd 0x00000000 ; Transfer buffer address
    dd 0x00000000 ; Start LBA (lower 32-bits)
    dd 0x00000000 ; Start LBA (upper 32-bits)

times 510 - ($ - $$) db 0 ; Pad the boot sector to 510 bytes.
dw 0xaa55                  ; The magic boot signature.
