.586 
.model flat, stdcall
includelib kernel32.lib 
includelib libucrt.lib 

ExitProcess PROTO : DWORD 
GetStdHandle Proto : DWORD 
SetConsoleTitleA PROTO : DWORD
WriteConsoleA PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD 
wout PROTO pstr : DWORD, _size : DWORD 
intToString PROTO number : DWORD, pstr : DWORD 

.stack 4096 
.const 
	emptstr DB 0
	Lit_0	 	DB 19,10,114,101,116,117,114,110,101,100,32,102,114,111,109,32,70,76,69,78	 
	Lit_1	 	DWORD 16777215
	Lit_2	 	DB 1,102	 
	Lit_3	 	DB 29,72,101,108,108,111,33,63,58,60,62,123,125,40,41,61,46,45,43,42,44,59,32,37,35,87,111,114,108,100	 
	Lit_4	 	DWORD 5
	Lit_5	 	DWORD 1
	Lit_6	 	DWORD 1000
	Lit_7	 	DB 7,10,99,104,49,32,61,32	 
	Lit_8	 	DB 7,10,115,116,114,32,61,32	 
	Lit_9	 	DB 1,10	 
	Lit_10	 	DB 11,10,115,116,114,32,108,101,110,32,61,32	 
	Lit_11	 	DB 1,10	 
	Lit_12	 	DB 13,10,68,82,97,110,100,111,109,32,121,32,61,32	 
	Lit_13	 	DB 13,10,82,97,110,100,111,109,32,121,121,32,61,32	 
	Lit_14	 	DB 1,10	 
	Lit_15	 	DWORD 64
	Lit_16	 	DB 10,10,109,97,116,104,32,120,32,61,32	 
	Lit_17	 	DB 1,10	 
	Lit_18	 	DWORD 5
	Lit_19	 	DWORD 7
	Lit_20	 	DB 5,10,120,32,61,32	 
	Lit_21	 	DB 1,10	 
	Lit_22	 	DB 15,76,111,111,112,32,73,115,32,67,111,109,105,110,103,10	 
	Lit_23	 	DWORD 5
	Lit_24	 	DWORD 1
	Lit_25	 	DB 4,121,32,61,32	 
	Lit_26	 	DB 1,10	 
	Lit_27	 	DB 11,76,111,111,112,32,69,110,100,101,100,10	 
	Lit_28	 	DB 13,97,108,109,111,115,116,32,101,110,100,46,46,46	 
	Lit_29	 	DB 6,10,103,103,119,112,10	 
	Lit_30	 	DB 1,10	 
	Lit_31	 	DB 7,10,47,69,78,68,47,10	 

.data 
	numberSize DWORD 0
	strResult byte 11 dup(' ')
	seed DWORD 0
	tmp DWORD 0
	c_i	 DWORD 0
	g_i	 DWORD 0
	z_i	 DWORD 0
	ch1_i	 DWORD 0
	str_i	 DWORD 0
	len_i	 DWORD 0
	x_i1	 DWORD 0
	sh_i	 DWORD 0
	y_i1	 DWORD 0
	yy_i	 DWORD 0

.code

stringlen PROC strptr: DWORD
	mov esi, [strptr]
	xor eax, eax
loop_len:
	mov dl, [esi]
	cmp dl, 9
	jbe done
	inc esi
	inc eax
	jmp loop_len
done:
	dec eax
	ret
stringlen ENDP

SRandom PROC
	push edx
	push ecx
	mov eax, [seed]
	or eax, eax
	jnz nn
	rdtsc
	xor eax, edx
	mov [seed], eax
nn:
	xor edx, edx
	mov ecx, 12773
	div ecx
	mov ecx, eax
	mov eax, 16807
	mul edx
	mov edx, ecx
	mov ecx, eax
	mov eax, 2836
	mul edx
	sub ecx, eax
	xor edx, edx
	mov eax, ecx
	mov [seed], ecx
	mov ecx, 100000
	div ecx
	mov eax, edx
	pop ecx
	pop edx
	ret
SRandom ENDP

DRandom PROC rmin: DWORD,rmax: DWORD
	push edx
	push ecx
	mov ecx, rmax
	sub ecx, rmin
	inc ecx
	call SRandom
	xor edx, edx
	div ecx
	mov eax, edx
	add eax, rmin
	pop ecx
	pop edx
	ret
DRandom ENDP

wout PROC  pstr : DWORD, _size : DWORD
	push eax
	INVOKE GetStdHandle, -11
	INVOKE WriteConsoleA, eax, pstr, _size, 0, 0
	pop eax
	ret
wout ENDP

intToString PROC number: DWORD, pstr: DWORD
	push eax
	push ebx
	push ecx
	push edi
	push esi
	mov esi, OFFSET strResult
	mov ecx, sizeof strResult
	mov al, ' '
CLEARSTR:
	mov [esi], al
	inc esi
	LOOP CLEARSTR
	mov edi, pstr
	mov esi, 0
	cdq
	mov eax, number
	mov ebx, 10
	div ebx
plus :
	push dx
	inc esi
	test eax, eax
	jz fin
	cdq
	div ebx
	jmp plus
fin :
	mov ecx, esi
write :
	pop bx 
	add bl, '0'
	mov[edi], bl
	inc edi
	loop write
	mov ecx, sizeof strResult
	mov esi, OFFSET strResult
COUNTER :
	mov al, [esi]
	cmp al, 32
	jz IC
	inc numberSize
IC :
	inc esi
	LOOP COUNTER
	pop esi
	pop edi
	pop ecx
	pop ebx
	pop eax
	ret
intToString ENDP

flen_f PROC 
	push OFFSET Lit_0
	pop eax
	ret
flen_f ENDP

fstr_f PROC b_i : DWORD 
	push 	Lit_1
	pop g_i
	push b_i
	pop eax
	ret
fstr_f ENDP

fch_f PROC 
	push OFFSET Lit_2
	pop eax
	ret
fch_f ENDP

math_f PROC x_i : DWORD , y_i : DWORD 
	push x_i
	push y_i
	pop ebx 
	pop eax 
	ADD eax, ebx
	push eax
	pop z_i
	push z_i
	pop eax
	ret
math_f	ENDP

main PROC
	call fch_f
	push eax 
	pop ch1_i
	push OFFSET Lit_3
	pop str_i
	push str_i
	call stringlen
	push eax
	pop len_i
	push 	Lit_4
	pop x_i1
	call flen_f
	push eax 
	pop sh_i
	push 	Lit_6
	push 	Lit_5
	call DRandom
	push eax
	pop y_i1
	push 100000
	push 0
	call DRandom
	push eax
	pop yy_i
	mov edi, sh_i
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	mov edi, OFFSET Lit_7
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	mov edi, ch1_i	
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	mov edi, OFFSET Lit_8
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	mov edi, str_i
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	mov edi, OFFSET Lit_9
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	mov edi, OFFSET Lit_10
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	INVOKE intToString, len_i, ADDR strResult
	INVOKE wout, ADDR strResult, numberSize
	mov numberSize, 0
	mov edi, OFFSET Lit_11
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	mov edi, OFFSET Lit_12
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	INVOKE intToString, y_i1, ADDR strResult
	INVOKE wout, ADDR strResult, numberSize
	mov numberSize, 0
	mov edi, OFFSET Lit_13
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	INVOKE intToString, yy_i, ADDR strResult
	INVOKE wout, ADDR strResult, numberSize
	mov numberSize, 0
	mov edi, OFFSET Lit_14
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	push x_i1
	push 	Lit_15
	call math_f
	push eax 
	pop x_i1
	mov edi, OFFSET Lit_16
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	INVOKE intToString, x_i1, ADDR strResult
	INVOKE wout, ADDR strResult, numberSize
	mov numberSize, 0
	mov edi, OFFSET Lit_17
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	push x_i1
	push 	Lit_18
	pop ebx 
	pop eax 
	mov cl, bl
	shl eax, cl
	push eax
	pop x_i1
	push 	Lit_19
	pop y_i1
	mov edi, OFFSET Lit_20
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	INVOKE intToString, x_i1, ADDR strResult
	INVOKE wout, ADDR strResult, numberSize
	mov numberSize, 0
	mov edi, OFFSET Lit_21
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	mov edi, OFFSET Lit_22
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	mov ecx, Lit_23
LOOP0 :
	mov tmp, ecx
	push y_i1
	push 	Lit_24
	pop ebx 
	pop eax 
	mov cl, bl
	shl eax, cl
	push eax
	pop y_i1
	mov edi, OFFSET Lit_25
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	INVOKE intToString, y_i1, ADDR strResult
	INVOKE wout, ADDR strResult, numberSize
	mov numberSize, 0
	mov edi, OFFSET Lit_26
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	mov ecx, tmp
	loop LOOP0
	mov edi, OFFSET Lit_27
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	push OFFSET Lit_28
	call fstr_f
	push eax 
	pop sh_i
	mov edi, OFFSET Lit_29
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	mov edi, sh_i
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	mov edi, OFFSET Lit_30
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	mov edi, OFFSET Lit_31
	mov al, [edi]
	inc edi
	INVOKE wout, edi, al
	push 0
call ExitProcess
main ENDP
end main 