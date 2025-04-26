PUBLIC Decrypt_3
.code
Decrypt_3  PROC

	push rbp
	sub rsp, 60h
	mov r14, rcx
	mov rcx, rdx
	mov ebx, dword ptr [r8+1Ch]
	shr bx, 3
	movzx r13d, bx
	mov esi, dword ptr [r8+14h]
	mov dword ptr [rsp+4], esi
	mov r8d, dword ptr [r8+10h]
	mov dword ptr [rsp+8], r8d
	mov dword ptr [rsp+30h], 0
	imul r13d, r8d
	xor r12, r12
	mov rsi, r12
	mov rdx, r12
	mov rax, r12

Decr_while:
	mov dword ptr [rsp+34h], eax
	cmp eax, dword ptr [rsp+4]
	jge Decr_end
	mov edi, edx
	mov dword ptr [rsp+3Ch], edx
	mov r15d, r12d
	mov dword ptr [rsp+44h], r12d

Decr_6:
	cmp r15d, r8d 
	jge Decr_1
	test eax, eax
	jne Decr_2
	test r15d, r15d
	jne Decr_3
	movzx r10d, r12w
	mov word ptr [rsp+20h], r12w

Decr_5:
	cmp r10w, bx
	jae Decr_4
	movzx r9d, r10w
	lea eax, qword ptr [r9+rsi]
	movzx r8d, byte ptr [rax+r14]
	lea eax, qword ptr [r9+rdi]
	mov byte ptr [rax+rcx], r8b
	inc r10w
	mov word ptr [rsp+20h], r10w
	jmp Decr_5

Decr_3:
	movzx r11d, r12w
	mov word ptr [rsp+24h], r12w

Decr_7:
	cmp r11w, bx
	jae Decr_4
	movzx r10d, r11w
	movzx eax, bx
	mov edx, r10d
	sub edx, eax
	add edx, edi
	lea eax, qword ptr [r10+rsi]
	movzx r9d, byte ptr [rdx+rcx]
	add r9b, byte ptr [rax+r14]
	lea eax, qword ptr [r10+rdi]
	mov byte ptr [rax+rcx], r9b
	inc r11w
	mov word ptr [rsp+24h], r11w
	jmp Decr_7

Decr_2:
	test r15d, r15d
	jne Decr_9
	movzx r11d, r12w
	mov word ptr [rsp+28h], r12w

Decr_10:
	cmp r11w, bx
	jae Decr_4
	movzx r10d, r11w
	mov r8d, r10d
	sub r8d, r13d
	add r8d, edi
	lea eax, qword ptr [r10+rsi]
	movzx r9d, byte ptr [r8+rcx]
	add r9b, byte ptr [rax+r14]
	lea eax, qword ptr [r10+rdi]
	mov byte ptr [rax+rcx], r9b
	inc r11w
	mov word ptr [rsp+28h], r11w
	jmp Decr_10

Decr_9:
	movzx r10d, r12w
	mov word ptr [rsp+2Ch], r12w

Decr_8:
	cmp r10w, bx
	jae Decr_4
	movzx r9d, r10w
	movzx eax, bx
	mov edx, r9d
	sub edx, eax
	add edx, edi
	movzx r8d, byte ptr [rdx+rcx]
	mov eax, r9d
	sub eax, r13d
	add eax, edi
	movzx edx,byte ptr [rax+rcx]
	add r8d, edx
	shr r8d, 1
	lea eax, qword ptr [r9+rsi]
	add r8b, byte ptr [rax+r14]
	lea eax, qword ptr [r9+rdi]
	mov byte ptr [rax+rcx], r8b
	inc r10w
	mov word ptr [rsp+2Ch], r10w
	jmp Decr_8

Decr_4:
	movzx eax, bx
	add edi, eax
	mov dword ptr [rsp+3Ch], edi
	add esi, eax
	mov dword ptr [rsp+40h], edi
	inc r15d
	mov dword ptr [rsp+44h], r15d
	mov eax, dword ptr [rsp+34h]
	mov r8d, dword ptr [rsp+8]
	jmp Decr_6

Decr_1:
	mov edx, dword ptr [rsp+30h]
	add edx, r13d
	mov dword ptr [rsp+30h], edx
	inc eax
	jmp Decr_while

Decr_end:
	mov rax, rcx
	add rsp, 60h
	pop rbp
	ret

Decrypt_3  ENDP
END