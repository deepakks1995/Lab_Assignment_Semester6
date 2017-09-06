%include "io.mac"

	.DATA
		msg1	db	"Please enter the string : ",0
		msg2	db	"Length of String: ",0
		msg3	db	"Encrypted String: ",0	
		msg4	db	"Terminate the Program[Y/N] ",0
		msg5	db	"Invalid Input! ",0
		msg6	db	"Exiting.............",0

	.UDATA
		string1 resb	80
		strlen	resb	1
		check	resb	1
		string2	resb	2

	.CODE
		.STARTUP
			
		loop:
			nwln
			PutStr	msg1
			GetStr	string1
			nwln
			
			call getLength
			PutStr msg2
			PutInt [strlen]
			nwln
			nwln	

			mov esi,string1
			mov edi,string1
			mov eax , [strlen]
		
			call solve
			PutStr msg3
			PutStr string1
			nwln
			nwln
			
			PutStr msg4
			GetStr string2
			cmp byte [string2] , 'Y'
			je	terminate
			cmp byte [string2] , 'y'
			je	terminate
			cmp byte [string2] , 'N'
			je	loop
			cmp byte [string2] , 'n'
			je	loop
			PutStr msg5

		terminate:
			nwln
			PutStr msg6
			nwln
			
		.EXIT
;.......................................................................



;.......................................................................
;Function to calculate length of string
;.......................................................................
	getLength:
		mov ebx,string1
		mov eax,ebx
		
		top:	
			cmp byte [eax],0
			jz done
			inc eax
			jmp top
		
		done:
			sub eax,ebx
			mov [strlen],eax		; strlen contains length of string
			ret
;.......................................................................
;.......................................................................



;.......................................................................
;Function to generate Encrypted String
;.......................................................................
	GenerateString:
		
		solve:
			cmp eax,0
			je end
			dec eax
		
			lodsb
			mov byte [check],'0'
		
			cmp al,'0'
			je	cmp0
		
			cmp al,'1'
			je	cmp1
		
			cmp al,'2'
			je	cmp2
		
			cmp al,'3'
			je	cmp3
		
			cmp al,'4'
			je	cmp4
		
			cmp al,'5'
			je	cmp5
		
			cmp al,'6'
			je	cmp6
		
			cmp al,'7'
			je	cmp7
		
			cmp al,'8'
			je	cmp8
		
			cmp al,'9'
			je	cmp9
		
			cmp byte [check],'0'
			je char
		
			jmp solve
		
		char:
			inc edi
			jmp solve
		
		cmp0:
			mov al,'4'
			mov byte [check],'1'
			stosb
			jmp solve
		
		cmp1:
			mov al,'6'
			mov byte [check],'1'
			stosb
			jmp solve
		
		cmp2:
			mov al,'9'
			mov byte [check],'1'
			stosb
			jmp solve
		
		cmp3:
			mov al,'5'
			mov byte [check],'1'
			stosb
			jmp solve
		
		cmp4:
			mov al,'0'
			mov byte [check],'1'
			stosb
			jmp solve
		
		cmp5:
			mov al,'3'
			mov byte [check],'1'
			stosb
			jmp solve
		
		cmp6:
			mov al,'1'
			mov byte [check],'1'
			stosb
			jmp solve
		
		cmp7:
			mov al,'8'
			mov byte [check],'1'
			stosb
			jmp solve
		
		cmp8:
			mov al,'7'
			mov byte [check],'1'
			stosb
			jmp solve
		
		cmp9:
			mov al,'2'
			mov byte [check],'1'
			stosb
			jmp solve	
		
		end:
			ret
;.......................................................................
;.......................................................................
