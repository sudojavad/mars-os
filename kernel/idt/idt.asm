idt_init:
      ; IDT
      mov rdi, IDT

      ; IDT entry for interrupt 0
      mov rax, handle_0 ; holds offset of the handler
      ; the offset is divided into three parts in the IDT entry
      mov [rdi], ax ; copy the lower 16 bits of the offset to the location that rdi points to
      shr rax, 16 ; shift offset in rax rightward by 16 bits. then the bits 16 to 31 are in ax
      mov [rdi+6], ax ; copy the bits 16 to 31 of the offset to the second part, which is at the 7th byte in the entry
      shr rax, 16 ; now bits 32 to 63 are in eax
      mov [rdi+8], eax ; copy the value in eax to the third part of the offset

      ; IDT entry for the timer
      ; vector number of the timer is set to 32 in PIC
      ; so the address of entry is base of IDT + 32 * 16
      ; Note: each entry in 64-bit takes up 16-byte space
      mov rax, handle_timer ; holds offset of the timer
      add rdi, 32*16 ; to make it point to the timer entry
      mov [rdi], ax
      shr rax, 16
      mov [rdi+6], ax
      shr rax, 16
      mov [rdi+8], eax

      lidt [IDT_PTR] ; load IDT

      ret


IDT:
      %rep 256
            dw 0
            dw 8 ; the code segment descriptor that we currently use
            db 0
            ; attributes field
            db 0x8E ; D=1 DPL=00 TYPE=01110 -> 10001110
            dw 0
            dd 0
            dd 0
      %endrep

IDT_LEN: equ $-IDT

IDT_PTR:
      dw IDT_LEN-1
      dq IDT