ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL TAKE_INP
CALL QUANT_ENC
CALL LED_DISP
HERE: SJMP HERE
ORG 130H
// *****************
DELAY_8s:
	push 00h
	mov r0, #160
	h5: acall delay_50ms
	djnz r0, h5
	pop 00h
	ret

DELAY_4s:
	push 00h
	mov r0, #80
	h4: acall delay_50ms
	djnz r0, h4
	pop 00h
	ret

delay_50ms:
	push 00h
	mov r0, #50
	h3: acall delay_1ms
	djnz r0, h3
	pop 00h
	ret

delay_1ms:
	push 00h
	mov r0, #4
	h2: acall delay_250us
	djnz r0, h2
	pop 00h
	ret

delay_250us:
	push 00h
	mov r0, #244
	h1: djnz r0, h1
	pop 00h
	ret
    
TAKE_INP:

MOV P1, #1Fh
ACALL DELAY_8s
MOV A, P1
ANL A, #0Fh
SWAP A
MOV R1, A

MOV P1, #2Fh
ACALL DELAY_8s
MOV A, P1
ANL A, #0FH
ORL A, R1
MOV 70H, A


MOV P1, #3Fh
ACALL DELAY_8s
MOV A, P1
ANL A, #0Fh
SWAP A
MOV R1, A

MOV P1, #4Fh
ACALL DELAY_8s
MOV A, P1
ANL A, #0FH
ORL A, R1
MOV 71H, A


MOV P1, #5Fh
ACALL DELAY_8s
MOV A, P1
ANL A, #0Fh
SWAP A
MOV R1, A

MOV P1, #6Fh
ACALL DELAY_8s
MOV A, P1
ANL A, #0FH
ORL A, R1
MOV 72H, A


MOV P1, #7Fh
ACALL DELAY_8s
MOV A, P1
ANL A, #0Fh
SWAP A
MOV R1, A

MOV P1, #8Fh
ACALL DELAY_8s
MOV A, P1
ANL A, #0FH
ORL A, R1
MOV 73H, A

RET

QUANT_ENC:
MOV R0, #70H


loop:
CLR C
MOV A, @R0
SUBB A, #40H
JC less_than_64

CLR C
MOV A, @R0
SUBB A, #80H
JC less_than_128

CLR C
MOV A, @R0
SUBB A, #0C0H
JC less_than_192

CLR C
MOV A, @R0
JMP greater_than_192

quant_enc_loop:
INC R0
CJNE R0, #74H, loop

RET


less_than_64:
MOV @R0, #10h
JMP quant_enc_loop

less_than_128:
MOV @R0, #20h
JMP quant_enc_loop

less_than_192:
MOV @R0, #40h
JMP quant_enc_loop

greater_than_192:
MOV @R0, #80h
JMP quant_enc_loop



LED_DISP:
MOV R0, #70H

led:
MOV P1, @R0
ACALL DELAY_4s
INC R0
CJNE R0, #74H, led
SJMP LED_DISP

RET
END 