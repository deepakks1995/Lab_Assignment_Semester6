%include "io.mac"

.DATA
	prompt_msg1  db   "Please input matrix A", 0
	prompt_msg2  db   "Please input matrix B", 0
	prompt_msg3  db	  "Length of matriceS: ",0
	prompt_msg4  db	  "Height of matrices: ",0	
	prompt_msg6  db   "Matrix C is:", 0x0A, 0

.UDATA
	arrA	resd	100
	arrB	resd	100
	arrC	resd	100
	len 	resd	1
	wid 	resd	1

.CODE
	.STARTUP

	PutStr prompt_msg3;
	GetLInt EAX;
	mov [len], EAX;
	XOR EAX,EAX;
	PutStr prompt_msg4;
	GetLInt	EAX
	mov [wid] , EAX

	PutStr prompt_msg1
	nwln
	mov ESI, arrA
	call read

	PutStr prompt_msg2
	nwln
	mov ESI,arrB
	call read

	mov ESI, arrA
	mov EDI, arrB
	call matrix_add


	PutStr prompt_msg6
	nwln
	mov ESI, arrC
	call print_matrix
	nwln

	.EXIT

	read:
		xor EAX,EAX
		xor ECX,ECX

		loop_read:
			mov ECX,EAX
			imul ECX, [wid]
			xor EBX,EBX
			
			row_read:
				add ECX,EBX		;	EBX = j && ECX = i*wid + j
				GetLInt EDX
				mov [ESI + ECX*4], EDX
				inc EBX
				cmp EBX,[wid]
				jne row_read

			inc EAX		;	EAX == i for comparing lenth
			cmp EAX,[len]
			jne loop_read
		ret;

	print_matrix:		; function to print matrix C
		xor EAX,EAX
		xor ECX,ECX
			loop_ROW:
				nwln
				mov ECX,EAX
				imul ECX,[wid]
				xor EBX,EBX

				row_print:
					add ECX,EBX
					mov EDX, [ESI + ECX*4]
					PutLInt EDX
					PutCh ' '
					inc EBX
					cmp EBX, [wid]
					jne row_print
				inc EAX
				cmp EAX,[len]
				jne loop_ROW;
			ret;

	matrix_add:			; Function to add matrix A and matrix B
		xor eax,eax
		xor ecx,ecx

			loop:
				mov ecx,eax
				imul ecx,[wid]
				xor ebx,ebx
					add:
						add ecx,ebx
						mov edx, [esi + ecx*4]
						add edx, [edi + ecx*4]

						mov [arrC + ecx*4], edx
						inc ebx
						cmp ebx, [wid]
						jne add
				inc eax
				cmp eax,[len]
				jne loop
			ret


