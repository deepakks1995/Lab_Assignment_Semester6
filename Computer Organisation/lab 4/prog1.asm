
%include "io.mac"

extern read
extern printf
extern exit
.DATA

	cache times 32 dw -1
	hit	dw 0
	miss dw 0
	str1 db "Hit:: " ,0
	str3 db "hit",0
	str4 db "Hit Rate : ",0
	str5 db "Miss Rate: ",0
	str6 db "Direct Access Cache: ",0
	count dw 0
	total dw 500

.UDATA
	number resw 1


;section .data
 ; format db "%d", 10, 0
;section .text

.CODE

.STARTUP
	call start


	start:	
		je end
   		call  read     
    	mov [number], eax
   		call calmisshitrate
   		mov ebx, [count]
		inc ebx
		mov [count], ebx
		mov bx, [total]
		cmp [count],bx
    	jne start     ; exit(0)	

	end:
		PutStr str6
		nwln
		PutStr str4
		PutInt [hit] 
		nwln
		PutStr str5
		PutInt [miss]
		nwln
.EXIT

calmisshitrate:
	pusha				;pushing all registers on stack
	mov edx,0			
	mov ax,[number]	
	mov bx,4
	div bx

	mov edx,0
	mov cx,ax			;memory block no stored in cx
	mov bx,32
	div bx
	
	cmp cx,[cache+edx*2]	;comparing old and required values
	je hitt
	mov ebx,[miss]			
	inc ebx
	mov [miss],ebx			
	mov [cache+edx*2],cx	;new address stored in cache
	jmp exit4
	
	hitt:					;hit		
		mov ebx,[hit]
		inc ebx				
		mov [hit],ebx

	exit4:
		popa	
		ret	