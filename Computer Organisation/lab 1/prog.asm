%include "io.mac"
	
	.DATA
		msg1	db	"Please enter the number : ",0
		msg2	db	"Total Sum of above numbers: ",0
		msg3	db	"Enter total number of numbers: ",0
		msg4	db	"Quotient: ",0
		msg5	db	"Remainder: ",0
	.UDATA
		number1	resd	1
	
	.CODE
		.STARTUP
		PutStr msg3	; request total numbers
		GetInt DX	; DX = total number
		mov CX,DX
		mov AX,0
		loop:
			PutStr msg1	;
			GetInt BX	;
			add AX,BX	;
			dec DX		;
			jnz loop
		nwln
		PutStr msg2
		PutInt AX
	
		nwln
		mov DX,0
		div CX
		PutStr msg4
		PutInt AX
		nwln 
		PutStr msg5
		PutInt DX
		nwln
		done:
		.EXIT

			
