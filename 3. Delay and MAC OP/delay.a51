ORG 0H
LJMP MAIN

ORG 100H
MAIN:
    MOV P1, #01H       
    CALL DELAY_1s      
    MOV P1, #00H       
HERE: 
    SJMP HERE          

ORG 130H
// *****************

DELAY_1s:
    MOV R1, #100       
D_LOOP:
    ACALL delay_10ms   
    DJNZ R1, D_LOOP    
    RET                


delay_10ms:
    PUSH 00H           
    MOV R0, #40       
h2: 
    ACALL delay_250us  
    DJNZ R0, h2        
    POP 00H            
    RET               


delay_250us:
    PUSH 00H           
    MOV R0, #244       
h1: 
    DJNZ R0, h1        
    POP 00H            
    RET                

END
