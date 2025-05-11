; File: add.a51
; Adds num1 and num2 and stores result in result (all in internal RAM)

PUBLIC ADD_NUMS

EXTRN DATA (num1, num2, result)   ; Declare external variables
;define global variables stored in internal RAM using data in C, and access them in assembly using their addresses
CSEG AT 100h

ADD_NUMS:
    MOV A, num1
    ADD A, num2
    MOV result, A
    RET

END
