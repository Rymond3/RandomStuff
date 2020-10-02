/*-----------------------------------------------------------------
**
**  File:
**    pract3b.asm  
**
**    Introduction to Computers
**    Dpto. de Arquitectura de Computadores y Automática
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Goal:
**    Implement a program that sorts a vector, A, of positive integers, of length N
**    and stores the result in vector B
**	  The program must use the function "max" implemented in prac3a.
**
**  Design notes:
**
**---------------------------------------------------------------*/

.global start
.extern _stack

.EQU N, 8

.data
A:         .word 7,3,25,4,75,100,1,1	@ Vector to be sorted

.bss
B:         .space N*4			@ Sorted vector
ind:       .space 4				@ variable "ind" of the C code


.text
/* This program sorts a vector, A, of positive integers, of length N
   and stores the result in vector B */

start:
            ldr sp, =_stack		@ initialize the SP with the address provided in the linker script
			mov	fp, #0			@ initialize the FP
			ldr r6, =A
			ldr r8, =B
			mov r4, #0			@index j
for_loop:
			cmp r4, #N
			bge exit_for
			mov r0, r6
			bl max
			mov r5, r0
			ldr r7, [r6, r5, lsl #2]
			str r7, [r8, r4, lsl #2]
			mov r9, #0
			str r9, [r6, r5, lsl #2]
			add r4, r4, #1
			b for_loop
exit_for:
			b .
max:
			push {r4-r8, fp}
			add fp, sp, #4 * 5
			mov r4, r0
			mov r5, #0			@index i
			mov r6, #0			@max_candidate
			ldr r7, =ind
max_for_loop:
			cmp r5, #N
			bge	exit_max_for
			ldr r8, [r4, r5, lsl #2]
			cmp r8, r6
			ble smaller
			mov r6, r8
			str r5, [r7]
smaller:
			add r5, r5, #1
			b	max_for_loop
exit_max_for:
			ldr r0, [r7]
			sub fp, sp, #4 * 5
			pop {r4-r8, fp}
			mov pc, lr
.end


