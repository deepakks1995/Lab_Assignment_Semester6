%include "io.mac"

;.......................................................................
	.DATA
		msg1	db	"Please enter the string : ",0
		msg2	db	"Length of String: ",0
		msg3	db	"String is a Palindrome ",0	
		msg4	db	"Terminate the Program[Y/N] ",0
		msg5	db	"Invalid Input! ",0
		msg6	db	"Exiting.............",0
		msg7	db	"String is not a Palindrome ",0

	.UDATA
		string1 resb	80
		strlen	resb	1
		string2	resb	2

	.CODE
		.STARTUP
		while:	
			nwln
			PutStr	msg1
			GetStr	string1
			nwln
			
			call getLength
			PutStr msg2
			PutInt [strlen]
			nwln
			nwln

			call Check_Palindrome

			PutStr msg4
			GetStr string2
			cmp byte [string2] , 'Y'
			je	terminate1
			cmp byte [string2] , 'y'
			je	terminate1
			cmp byte [string2] , 'N'
			je	while
			cmp byte [string2] , 'n'
			je	while
			PutStr msg5

		terminate1:
			nwln
			PutStr msg6
			nwln
		.EXIT	
;.......................................................................



;.......................................................................
;Funtion to check for palindromes
;.......................................................................
	Check_Palindrome:
			mov eax,string1
			mov ebx, [strlen]
			add eax, ebx
			dec eax
			xor ebx, ebx
			mov ebx , string1

		start:
			cmp ebx,eax
			jle check
			jmp palin

		check:
			mov dl, byte[eax]
			cmp byte[ebx], dl
			jne nonpalin
			inc ebx
			dec eax
			jmp start

		palin:
			nwln
			PutStr msg3
			nwln
			jmp end

		nonpalin:
			nwln
			PutStr msg7
			nwln
			jmp end

		end:
			ret
;.......................................................................
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
