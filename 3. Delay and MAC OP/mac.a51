ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL MAC
HERE: SJMP HERE
ORG 130H
// *****************
MAC:
// MAC OPERATION, CALL THE ADDITION SUBROUTINE USING "CALL ADD16"
	MOV A, 70H
	MOV B, 73H
    MUL AB               
    MOV R1, A             
    MOV R2, B             

    ; a2 * b2
    MOV A, 71H             
    MOV B, 74H            
    MUL AB                
    CALL ADD16           
    ; a3 * b3
    MOV A, 72H             
    MOV B, 75H            
    MUL AB                
    CALL ADD16   
	
	MOV 50H, R3           
    MOV 51H, R2            
    MOV 52H, R1             

    RET                    

ADD16:
    
    ADD A, R1              
    MOV R1, A              
    MOV A, B               
    ADDC A, R2       
    MOV R2, A             
                        
	MOV A,#00h
    ADDC A,R3
	MOV R3,A
	RET
END