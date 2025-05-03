 ORG 0H
 LJMP MAIN
 ORG 100H
 MAIN:
 CALL ADD16
 HERE: SJMP HERE 
 ORG 130H
	 
 ADD16:
   
 
 MOV 74H, #00H
 MOV 75H, #00H
 MOV 76H, #00H
 ;Load and add the lower bytes
 MOV A,71H
 ADD A,73H
 MOV 76H,A
 JC ADD_MSB
 ;No carry 
 MOV A,70H
 ADD A,72H
 MOV 75H, A
 RET
 ;Carry case 
 ADD_MSB:
 MOV A,70H
 ADDC A, 72H
 MOV 75H, A
 
 ;carry to z16 (MSB of result)
 MOV A,#00H
 ADDC A,#00H
 MOV 74H,A
 
 RET
 END