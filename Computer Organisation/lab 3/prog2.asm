
%include "io.mac"

.DATA
    prompt_msg1  db   "Please input string A  ", 0
    prompt_msg2  db   "Please input string B   ", 0
    found_msg  	 db   "B is a substring of A, from index ", 0
    not_found_msg   	 db	  "B is not a substring of A.  ", 0

.UDATA 
    A resb 100
    B resd 100
    lenA resd 1
    lenB resd 1
    pos  resd 1
    diff resd 1

.CODE
      .STARTUP
      
    PutStr prompt_msg1
        GetStr A
        PutStr prompt_msg2
        GetStr B
        call str_str
        cmp dword[pos], -1 ; EBX stores index of result
        je not_found
        jmp found
    
    strlen:				;;	length in EAX, input in EBX
    	mov EAX, EBX
      
      nextchar: 
      	cmp byte[EAX], 0
      	je finished
      	inc EAX
      	jmp nextchar
      
      finished:
      	sub EAX, EBX
      	ret
    
    str_str:			;; A in ESI, B in EDI
    	mov dword[pos], -1
    	mov EBX, A
    	call strlen
    	mov [lenA], EAX
    	mov [diff], EAX
    	mov EBX, B
    	call strlen
    	cmp EAX, [lenA]
    	jg not_found
    	mov [lenB], EAX
    	sub [diff], EAX
    	
    	mov ESI, A
    	xor AL, AL
    	    	
    	next:
    		mov EDI, B 
    		cmp byte[ESI], 0
    		je end
    		mov DL, byte[B]
    		cmp byte[ESI], DL
    		je first_match
    		inc ESI
    		jmp next 
    		
    	first_match:
    		push ESI
    		xor ECX, ECX
    		inc ECX
    		inc ESI
    		inc EDI
    		mov AL, byte[ESI]
    		mov BL, byte[EDI]
    		cmp BL, 0
    		je end
    		cmp AL, BL
    		je continue
    		pop ESI
    		inc ESI
    		jmp next
    		
    	continue:
    		inc ECX
    		cmp ECX, [lenB]
    		je end
    		inc ESI
    		inc EDI
    		mov AL, byte[ESI]
    		cmp byte[EDI], AL
    		je continue
    		inc ESI
    		jmp next
    	
    	end:
    		cmp byte[ESI], 0
    		je not_found   
    		pop ESI
    		sub ESI, A
    		inc ESI
    		mov dword[pos], ESI
    		ret    	    	    	
    			      			   
    	
    not_found:
    	PutStr not_found_msg
    	jmp done
    
    found:
    	PutStr found_msg
    	PutLInt dword[pos]
    	nwln

	done:
      .EXIT
