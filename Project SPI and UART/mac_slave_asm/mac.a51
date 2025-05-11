; File: mac.a51
; Performs MAC = a1*b1 + a2*b2 + a3*b3

; File: mac.a51
; Performs MAC = a1*b1 + a2*b2 + a3*b3 (8-bit result only)

PUBLIC MAC_NUMS
EXTRN DATA (a1, a2, a3, b1, b2, b3)
EXTRN DATA (mac_result)

CSEG AT 100h

MAC_NUMS:
    ; Clear accumulator
    MOV A, #00H

    ; First product: a1 * b1
    MOV R0, A          ; Clear sum
    MOV A, a1
    MOV B, b1
    MUL AB
    ADD A, R0          ; Add to sum
    MOV R0, A

    ; Second product: a2 * b2
    MOV A, a2
    MOV B, b2
    MUL AB
    ADD A, R0
    MOV R0, A

    ; Third product: a3 * b3
    MOV A, a3
    MOV B, b3
    MUL AB
    ADD A, R0

    ; Final 8-bit result
    MOV mac_result, A
    RET

END
