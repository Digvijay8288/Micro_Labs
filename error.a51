/* Following code finds GCD of the two numbers saved at memory locations 50h and 51h and stores result at location 52h*/
ORG 0H
LJMP MAIN
ORG 100H
MAIN:

CALL GCD
HERE: SJMP HERE
ORG 130H
GCD:
MOV 50H , #1BH
MOV 51H , #0FH
MOV A , 50H
MOV B , 51H

S: 		SUBB A , B 
		JC HERE1
		JZ HERE2
		MOV R2 , B
		CJNE R2 , #00H , S 
		JMP ENDING

HERE1: 	CPL A
		INC A      
HERE2:	XRL A , B
		XRL B , A
		XRL A , B
		MOV R2,  B
		CJNE R2 , #00H , S
		JMP ENDING
ENDING:
		MOV 52H , A
Y:		MOV A , #0F0H
X:		MOV P1,A
		DEC A
		CJNE A , #00H , X
		JMP Y
RET
END 