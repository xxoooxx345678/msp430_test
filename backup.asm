	.include data_model.h
	.cdecls C,LIST,"msp430.h"
	.cdecls C,LIST
	%{
		#include <stdint.h>
		#include "FreeRTOS.h"
	%}



    .global __bss__
    .global __bssEnd__
    .global __data__
    .global __dataEnd__
    .global __stack__
    .global __stackEnd__
	.global backup_buffer
	.global reg_buffer
	.global pc_buffer
	.global sp_buffer

	.def vPortBackupASM
	.def vPortRestoreASM
	.def vPortShutdownASM


;-----------------------------------------------------------

PUSH_SECTION_START_END .macro
    ; push.w  #__stack__
    ; push.w  #__stackEnd__
    push.w  #__data__
    push.w  #__dataEnd__
    push.w  #__bss__
    push.w  #__bssEnd__
    .endm
;-----------------------------------------------------------


DST     .set r10
SRC     .set r9
LEN     .set r8
SECT    .set r5


;-----------------------------------------------------------
	.text
;-----------------------------------------------------------
;
; Backup stack ,registers
;
	.align 2

vPortBackupASM: .asmfunc
    ; Now the SR is stacked we can disable interrupts.
    dint
	nop

	; Push registers R2 - R15 to stack.
	push.w	sr 			; Push R2		; sr is 16-bit register
	pushm_x  #13, r15	; Push R3 - R15


	; backup register
	mov_x r3, 	reg_buffer
	mov_x r4, 	(reg_buffer+4)
	mov_x r5, 	(reg_buffer+8)
	mov_x r6, 	(reg_buffer+12)
	mov_x r7, 	(reg_buffer+16)
	mov_x r8, 	(reg_buffer+20)
	mov_x r9, 	(reg_buffer+24)
	mov_x r10, 	(reg_buffer+28)
	mov_x r11, 	(reg_buffer+32)
	mov_x r12, 	(reg_buffer+36)
	mov_x r13, 	(reg_buffer+40)
	mov_x r14, 	(reg_buffer+44)
	mov_x r15, 	(reg_buffer+48)
	mov_x sr, 	(reg_buffer+52)


; 	movx.w  #backup_buffer,   DST      ; DST = backup_buffer
; 	movx.a  sp,         0(DST) ; DST[0] = SP
; 	add		#4,			DST
; 	; SRAM --------------------------------------------------------------
;     PUSH_SECTION_START_END
; 	mov     #2,         SECT    ; Section = 3

; BACKUP_SRAM
;     pop.w   LEN
;     pop.w   SRC
;     sub.w   SRC,        LEN     ; Length = __xxxEnd__ - __xxx__
; WAIT
; 	movx.b  @SRC+,      0(DST)  ; Write 1st word
;     inc     DST                 ; Point to next words
;     dec     LEN
;     jnz     WAIT                ; Loop while Length > 0

;     dec     SECT
;     jnz     BACKUP_SRAM         ; Loop while Section > 0

CHECKPOINT
	; Restore registers from stack.
	popm_x #13, r15			; pop R3 - R15
	pop.w sr


	;backup pc,sp
	mov_x sp, &sp_buffer
	mov_x pc, &pc_buffer


	ret_x
	.endasmfunc
;-----------------------------------------------------------

;
; Restore stack, registers
;

	.align 2
vPortRestoreASM: .asmfunc
	dint
	nop

; 	movx.w  #backup_buffer,  SRC  ; SRC = asmSRAM
; 	; Restore SP  ---------------------------------------------
; 	movx.a  0(SRC),    sp      ; SP = asmSRAM[0]
; 	add		#4,			SRC

; 	; Restore SRAM  -------------------------------------------
;     PUSH_SECTION_START_END
;     mov     #2,     SECT        ; Section = 3

; RESTORE_SRAM
;     pop.w   LEN
;     pop.w   DST
;     sub.w   DST,    LEN         ; Length = __xxxEnd__ - __xxx__
;     rra.w   LEN                 ; Length /= 2

; L1  movx.w  @SRC+,  0(DST)      ; *DST = *(SRC++)
;     incd    DST                 ; Point to next words
;     dec     LEN
;     jnz     L1                  ; Loop while Length > 0

;     dec     SECT
;     jnz     RESTORE_SRAM        ; Loop while Section > 0


	; restore register
	mov_x reg_buffer, r3
	mov_x (reg_buffer+4), r4
	mov_x (reg_buffer+8), r5
	mov_x (reg_buffer+12), r6
	mov_x (reg_buffer+16), r7
	mov_x (reg_buffer+20), r8
	mov_x (reg_buffer+24), r9
	mov_x (reg_buffer+28), r10
	mov_x (reg_buffer+32), r11
	mov_x (reg_buffer+36), r12
	mov_x (reg_buffer+40), r13
	mov_x (reg_buffer+44), r14
	mov_x (reg_buffer+48), r15
	nop
	mov_x (reg_buffer+52), sr
	nop

	;clear LOCKLPM5 bit in the PM5CTL0 register
	bic.b #LOCKLPM5, &PM5CTL0_L


	;move pc,sp
	mov_x &sp_buffer, sp
	mov_x &pc_buffer, pc



	.endasmfunc
;--------------------------------------------------------------

;
; Enter LPM4.5, press RESET button to wakeup
;

	.align 2
vPortShutdownASM: .asmfunc
	dint
	nop
	mov.b #PMMPW_H, &PMMCTL0_H
	bis.b #PMMREGOFF, &PMMCTL0_L
	bic.b #SVSHE, &PMMCTL0_L
	mov.b #000h, &PMMCTL0_H
	bis #CPUOFF+OSCOFF+SCG0+SCG1, SR
	.endasmfunc
;---------------------------------------------------------------

	.end
