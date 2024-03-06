    .include data_model.h
    .cdecls C, LIST, "msp430.h"
    .cdecls C, LIST
    %{
        #include "FreeRTOS.h"
    %}

    .global snapshot

    .def snapshotReg
    .def restoreReg

    .text
; ==========================================================
; snapshotSRAM
; ==========================================================
snapshotReg: .asmfunc

    dint
    nop

    mov_x       sp,     &(snapshot + 4)
    mov_x       sr,     &(snapshot + 8)
    mov_x       r3,     &(snapshot + 12)
    mov_x       r4,     &(snapshot + 16)
    mov_x       r5,     &(snapshot + 20)
    mov_x       r6,     &(snapshot + 24)
    mov_x       r7,     &(snapshot + 28)
    mov_x       r8,     &(snapshot + 32)
    mov_x       r9,     &(snapshot + 36)
    mov_x       r10,    &(snapshot + 40)
    mov_x       r11,    &(snapshot + 44)
    mov_x       r12,    &(snapshot + 48)
    mov_x       r13,    &(snapshot + 52)
    mov_x       r14,    &(snapshot + 56)
    mov_x       r15,    &(snapshot + 60)

    mov_x       pc,     &snapshot ; Program starts from here after restore.

    ret_x
    .endasmfunc

; ==========================================================
; restoreSRAM
; ==========================================================
restoreReg: .asmfunc

    dint
    nop

    mov_x       &(snapshot + 4),    sp

    nop
    mov_x       &(snapshot + 8),    sr
    nop

    mov_x       &(snapshot + 12),   r3
    mov_x       &(snapshot + 16),   r4
    mov_x       &(snapshot + 20),   r5
    mov_x       &(snapshot + 24),   r6
    mov_x       &(snapshot + 28),   r7
    mov_x       &(snapshot + 32),   r8
    mov_x       &(snapshot + 36),   r9
    mov_x       &(snapshot + 40),   r10
    mov_x       &(snapshot + 44),   r11
    mov_x       &(snapshot + 48),   r12
    mov_x       &(snapshot + 52),   r13
    mov_x       &(snapshot + 56),   r14
    mov_x       &(snapshot + 60),   r15

    mov_x       &snapshot,          pc

    ret_x
    .endasmfunc

    .end
