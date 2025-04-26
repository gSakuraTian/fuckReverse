PUBLIC Decrypt_2
.code
extern memcpy : proc        ; 声明外部函数
Decrypt_2  PROC

	push rbp
	sub rsp, 50h
	mov qword ptr [rsp+40h], 0FFFFFFFFFFFFFFFEh
	mov r13, r8
	mov r9, rcx
	mov r10, rdx
	mov qword ptr [rsp+8], r9	;存储
	mov qword ptr [rsp+10h], r10
	xor r12b, r12b
	xor r15d, r15d
	mov r14d, r15d
	mov dword ptr [rsp+20h], r15d
	mov esi, r15d
	mov dword ptr [rsp+24h], r15d
	
Decr_while:
	cmp esi, r13d
	jae Decr_end
	mov r8d, esi
	add r8, r9
	mov ebx, r15d
	mov dword ptr [rsp+30h], ebx
	mov edi, r15d
	mov dword ptr [rsp+2Ch], r15d
	mov ecx, r15d
	mov dword ptr [rsp+34h], ecx

Decr_1:
	mov eax, edi
	movzx edx, byte ptr [rax+r8]
	inc edi
	mov dword ptr [rsp+2Ch], edi
	mov eax, edx
	and eax, 7Fh
	shl eax, cl
	or ebx, eax
	mov dword ptr [rsp+30h], ebx
	add ecx, 7
	mov dword ptr [rsp+34h], ecx
	test dl, dl
	js Decr_1
	mov dword ptr [rsp+98h], edi
	add esi, edi
	mov dword ptr [rsp+24h], esi
	test r12b, r12b
	je Decr_2
	mov edi, r14d
	add rdi, r10
	mov ecx, ebx
	xor eax, eax
	rep stosb
	add r14d, ebx
	mov dword ptr [rsp+20h], r14d
	jmp Decr_3

Decr_2:
	mov r8d, ebx
	mov edx, esi
	add rdx, r9
	mov ecx, r14d
	add rcx, r10
	call memcpy
	add r14d, ebx
	mov dword ptr [rsp+20h], r14d
	add esi,ebx
	mov dword ptr [rsp+24h], esi
	mov r9, qword ptr [rsp+8]
	mov r10, qword ptr [rsp+10h]

Decr_3:
	xor r12b, 1
	jmp Decr_while

Decr_end:
	mov rax, qword ptr [rsp+10h]
	add rsp, 50h
	pop rbp
	ret

Decrypt_2  ENDP
END