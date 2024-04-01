    .include data_model.h
    .cdecls C, LIST, "msp430.h"
    .cdecls C, LIST
    %{
        #include "FreeRTOS.h"
    %}

    .global snapshot_asm 

    .def snapshotReg
    .def restoreReg

    .text
; ==========================================================
; snapshotSRAM
; ==========================================================
snapshotReg: .asmfunc

    dint
    nop

    pushm_x     #13,    r15     ; Push R3 - R15
    push_x      sr              ; Push R2

    mov_x       &snapshot_asm,  r9
    
    mov_x       @sp+,     8(r9)
    mov_x       @sp+,    12(r9) 
    mov_x       @sp+,    16(r9) 
    mov_x       @sp+,    20(r9) 
    mov_x       @sp+,    24(r9) 
    mov_x       @sp+,    28(r9) 
    mov_x       @sp+,    32(r9) 
    mov_x       @sp+,    36(r9) 
    mov_x       @sp+,    40(r9) 
    mov_x       @sp+,    44(r9) 
    mov_x       @sp+,    48(r9) 
    mov_x       @sp+,    52(r9) 
    mov_x       @sp+,    56(r9) 
    mov_x       @sp+,    60(r9) 

    mov_x        sp,     4(r9)
    mov_x        pc,     0(r9)

    ret_x
    .endasmfunc

; ==========================================================
; restoreSRAM
; ==========================================================
restoreReg: .asmfunc

    dint
    nop

    mov_x       &snapshot_asm, r9
    push_x      r9

;    push_x       0(r9)       
    push_x       4(r9)
    push_x      60(r9)
    push_x      56(r9)
    push_x      52(r9)
    push_x      48(r9)
    push_x      44(r9)
    push_x      40(r9)
    push_x      36(r9)
    push_x      32(r9)
    push_x      28(r9)
    push_x      24(r9)
    push_x      20(r9)
    push_x      16(r9)
    push_x      12(r9)
    push_x       8(r9)

    popm_x      #14, r15
    mov_x       @sp, sp

    ret_x
    .endasmfunc

    .end
