/*-----------------------------------------------------------------
**  for (i=0; i<N; i++) {
**  aux = A[i]+B[N-1-i];
**    if (aux < 0)
**    	aux = 0-aux;
**    C[i] = aux;
**    }
**---------------------------------------------------------------*/

.global start
		@ #define N 10
.equ N, 10
.data
@Some values for test purposes (not shown in the HLL pseudo-code)
A: .word 0,1,2,7,-8,4,5,-12,11,-2
B: .word 0,1,2,7,-8,4,5,12,-11,-2
@Reserve space for C (not shown in the HLL pseudo-code)
.bss
C: .space 4*N
.text
start:  LDR R0, =A					@R0 <-- Address of A
		LDR R1, =B					@R1 <-- Address of B
		MOV R2, #0					@R2 (i) = 0
		MOV R4, #N					@R4 = N
		SUB R5, R4, #1				@R5 = N - 1
		MOV R9, #0					@R9 = 0
for:    CMP R2, #N					@Compare R2 (i) and N
        BGE end						@If R2 (i) greater than N, branch to end
        LDR R3, [R0, R2, lsl #2]	@R3 <-- Value of A[i]
        SUB R6, R5, R2				@R6 = R5 (N - 1) - R2 (i)
        LDR R7, [R1, R6, lsl #2]	@R7 <-- Value of B[N - 1 - i]
        ADD R8, R3, R7				@R8 = R3 + R7
        CMP R8, #0					@Compare R8 and 0
        BGE exit					@If R8 positive, branch to exit
        SUB R8, R9, R8				@R8 = - R8 (Make R8 positive)
exit:   LDR R10, =C					@R10 <-- Address of C
		STR R8, [R10, R2, lsl #2]	@Value of R8 --> C[i]
		ADD R2, R2, #1				@R2++ (i++)
		B	for						@Branch back to for
end:
        B .
        .end










