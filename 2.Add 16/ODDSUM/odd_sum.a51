ORG 0H
LJMP MAIN          

ORG 100H
MAIN:
    CALL ODDSUM    
HERE:
    SJMP HERE     

ORG 130H
// *****************
ODD:
    
    ANL A, #01H    ; Perform AND with 01H, keeping only the LSB
    JZ EVEN        ; If LSB is 0, jump to EVEN 
    
    RET           

EVEN:
	MOV @R0,#00
    RET            

ODDSUM:
    
    MOV 70H, #00H 

    ; Loop through memory locations 60H to 67H
    MOV R0, #60H   ; Set R0 to point to memory location 60H

CHECK_LOOP:
    MOV A, @R0      
    CALL ODD       

    ; If the number is odd, add it to the sum stored in 70H
    MOV A, 70H     
    ADD A, @R0      
    MOV 70H, A     

    ; Move to the next number in memory (increment R0)
    INC R0         
    MOV A, R0
    CJNE  A, #67H, CHECK_LOOP   
     ; If not, continue checking

    RET            

END
