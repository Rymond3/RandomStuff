/*-----------------------------------------------------------------
**
**  File:
**    pract1b.asm  
**
**    Introduction to Computers
**    Dpto. de Arquitectura de Computadores y Automática
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Goal:
**    Divide 2 numbers by means of itereative subtractions
**
**  Design notes: C = A/B (integer division)
**
**---------------------------------------------------------------*/

.global start

.data
A: 		.word 86
B: 		.word 8

.bss
C:		.space 4

.text
start:	MOV 	R0, #0			@R0 = 0
		LDR 	R3, =A			@R3 <-- Address of A
		LDR 	R4, =B			@R4 <-- Address of B
		LDR 	R1, [R3]		@R1 <-- Value of A
		LDR		R2, [R4]		@R2 <-- Value of B
while:	CMP		R1, R2			@Compare R1 and R2 (R1 - R2)
		BLT		exit			@If R1 less than R2 branch to exit
		SUB		R1, R1, R2		@R1 = R1 - R2
		ADD		R0, R0, #1		@R0 = R0 + 1
		B		while			@Return to the while loop
exit:	LDR		R5, =C			@R5 <-- Address of C
		STR		R0, [R5]		@Value of R0 --> C
		B		.				@Infinite loop
		.end
