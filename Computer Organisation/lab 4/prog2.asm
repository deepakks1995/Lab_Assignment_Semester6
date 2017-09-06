
%include "io.mac"

extern read
extern printf
extern exit

.DATA
	cache times 32 dw -1
	PriorityCounter times 32 dw 0
	hit	dw 0
	miss dw 0
	str1 db "Hit:: " ,0
	str3 db "hit",0
	str4 db "Hit Rate : ",0
	str5 db "Miss Rate: ",0
	str6 db "2-way Set Associative Cache: ",0
	count dw 0
	total dw 500

.UDATA
	number resw 1

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
    	jne start     	
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
	pusha					;pushing all registers on stack
	mov edx,0
	mov ax,[number]
	mov bx,4
	div bx

	mov edx,0
	mov cx,ax				;memory block no stored  in cx
	mov bx,16
	div bx
	
	cmp cx,[cache+edx*4]
	je hit1
	cmp cx,[cache+edx*4+2]
	je hit2

	mov bx,[miss]
	inc bx
	mov [miss],bx				;miss no increased
	mov bx,[PriorityCounter+edx*4]
	cmp bx,0
	je miss1
	mov [cache+edx*4],cx
	mov bx,0
	mov [PriorityCounter+edx*4],bx
	
	mov bx,1
	mov [PriorityCounter+edx*4+2],bx
	jmp exit5

	miss1:
		mov [cache+edx*4+2],cx
		mov bx,1
		mov [PriorityCounter+edx*4],bx
		mov bx,0
		mov [PriorityCounter+edx*4+2],bx
		jmp exit5		
	
	hit1:

		mov bx,0
		mov [PriorityCounter+edx*4],bx
		mov bx,1
		mov [PriorityCounter+edx*4+2],bx
		mov bx,[hit]
		inc bx
		mov [hit],bx
		jmp exit5

	hit2:
		mov bx,1
		mov [PriorityCounter+edx*4],bx
		mov bx,0
		mov [PriorityCounter+edx*4+2],bx
		mov bx,[hit]
		inc bx
		mov [hit],bx
	

	exit5:
		popa	
		ret				
