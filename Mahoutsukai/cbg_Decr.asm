PUBLIC Decrypt 
.code

Decrypt  PROC
    mov r15, rcx    ;data
    mov r13d, [rsp+8]   ;size  

    sub rsp, 80h
    mov qword ptr [rsp+8], rdx    ;asm_Buf
    mov [rsp+10h], r15    ;data
    mov [rsp+18h], r8    ;asm_Buf_2
    mov [rsp+20h], rbp    

    mov r12d, r9d
    xor r14d, r14d
    mov ebx, r14d
    xor r10d, r10d
    xor edx, edx
    

start_processing:      
    cmp r10d, 100h
    jae calc_sec
    mov r11d, ebx
    add r11, r15
    mov r9d, r14d
    mov r8d, r14d
    mov ecx, r14d

calc:
    mov eax, r8d
    movzx edx, byte ptr [rax+r11]
    inc r8d
    mov eax,edx
    and eax,7Fh
    shl eax,cl
    or r9d,eax
    add ecx, 7
    test dl, dl 
    js calc
    mov eax, r10d
    mov qword ptr [rsp+70h], rbp
    mov rbp, qword ptr [rsp+8]
    mov dword ptr [rbp+rax*4+70h],r9d
    mov rbp, qword ptr [rsp+70h]
    add ebx, r8d
    inc r10d
    jmp start_processing

calc_sec:           
    mov [rsp+68h], rbx
    mov [rsp+60h], r14
    mov edi, 1FFh

    mov qword ptr [rsp+70h], rbp
    mov rbp, qword ptr [rsp+8]
    lea rsi, qword ptr [rbp+470h]
    mov rbp, qword ptr [rsp+70h]

    

assign:
    mov rax, rdi
    dec rdi
    test rax, rax
    je decrypt_1
    mov rcx, rsi
    mov byte ptr [rcx],0
    mov rax,rcx
    mov dword ptr [rcx+4],0
    mov byte ptr [rcx+8],0
    mov qword ptr [rcx+12],0FFFFFFFFFFFFFFFFh
    mov dword ptr [rcx+14h],0FFFFFFFFh
    add rsi, 18h
    jmp assign

decrypt_1:

    mov qword ptr [rsp+70h], rbp
    mov rbp, qword ptr [rsp+8]
    lea rdx, qword ptr [rbp+70h]
    lea rcx, qword ptr [rbp+470h]
    mov rbp, qword ptr [rsp+70h]

    xor r15d, r15d
    mov rdi, rcx
    add rcx, 1Ch
    mov r8d, 80h

fill_data:      
    mov eax, dword ptr [rdx]
    lea rdx, qword ptr [rdx+8]
    mov dword ptr [rcx-18h], eax
    lea rcx, qword ptr [rcx+30h]
    mov eax, dword ptr [rdx-4]
    mov dword ptr [rcx-30h], eax
    sub r8, 1
    jne fill_data
    mov r9d, 100h
    mov ebp, r15d
    mov edx, r9d
    mov rax, rdi

fill_while:         
    mov ecx, dword ptr [rax+4]
    test ecx, ecx
    je fill
    mov byte ptr [rax], 1
    add ebp, ecx

fill:       
    add rax, 18h 
    sub rdx, 1
    jne fill_while
    lea r14, qword ptr [rdi+1810h]

woh_10:
    mov esi, r15d
    mov qword ptr [rsp+58h],0FFFFFFFFFFFFFFFFh
    mov r11d, r15d

woh_8:
    mov eax, r15d
    test r9d, r9d
    je woh_1
    mov rcx, rdi

woh_3:
    cmp byte ptr [rcx], r15b
    jne woh_2
    inc eax
    add rcx, 18h
    cmp eax, r9d
    jb woh_3
    jmp woh_1

woh_2:
    mov ecx, r11d
    mov dword ptr [rsp+rcx*4+58h], eax

woh_1:
    lea ebx, qword ptr [r11+1]
    mov edx, ebx
    cmp ebx, r9d
    jae woh_4
    lea rcx, qword ptr [rbx+rbx*2]
    lea r8, qword ptr [rdi+rcx*8]

woh_6:
    cmp byte ptr [r8], r15b
    je woh_5
    mov eax, r11d
    lea r10,qword ptr [rsp+58h]
    lea r10,qword ptr [r10+rax*4]
    mov eax,dword ptr [r10]
    lea rcx, qword ptr [rax+rax*2]
    mov eax, dword ptr [rdi+rcx*8+4]
    cmp dword ptr [r8+4], eax
    jae woh_5
    mov dword ptr [r10], edx

woh_5:
    inc edx
    add r8, 18h
    cmp edx, r9d
    jb woh_6

woh_4:
    mov eax, r11d
    mov ecx, dword ptr [rsp+rax*4+58h]
    cmp ecx, 0FFFFFFFFh
    je woh_7
    lea rcx, qword ptr [rcx+rcx*2]
    mov byte ptr [rdi+rcx*8], r15b
    mov dword ptr [rdi+rcx*8+12], r9d
    mov byte ptr [rdi+rcx*8+8], r11b
    mov r11d, ebx
    add esi,dword ptr [rdi+rcx*8+4]
    cmp ebx, 2
    jb woh_8

woh_7:
    mov ecx, dword ptr [rsp+58h]
    mov dword ptr [r14], ecx
    mov ecx, dword ptr [rsp+5Ch]
    mov dword ptr [r14+4], ecx
    mov byte ptr [r14-10h],1
    mov dword ptr [r14-12],esi
    mov byte ptr [r14-8],0FFh
    cmp esi, ebp
    jae woh_9
    inc r9d
    add r14,18h
    cmp r9d, 1FFh
    jb woh_10

woh_9:
    mov rbx, [rsp+68h]
    mov r14, [rsp+60h]
    mov r15, [rsp+10h]
    mov r11, [rsp+18h]
    mov eax, r9d
    mov r10d, eax
    mov dl, 1
    mov byte ptr [rsp+40h], dl
    mov r9d, r14d
    mov dword ptr [rsp+48h], r14d

woh_18:
    cmp ebx, r12d
    je woh_11
    cmp r9d, r13d
    jae woh_11
    mov ecx, r10d
    mov dword ptr [rsp+50h], ecx
    mov r8d, r10d

woh_17:
    cmp r8d, 100h
    jb woh_13
    mov eax, ebx
    test byte ptr [rax+r15], dl
    mov eax, r8d
    lea rcx, qword ptr [rax+rax*2]
    jne woh_14

    mov qword ptr [rsp+70h], rbp
    mov rbp, qword ptr [rsp+8]
    mov ecx, dword ptr [rbp+rcx*8+480h]
    mov rbp, qword ptr [rsp+70h]
    
    jmp woh_15

woh_14:

    mov qword ptr [rsp+70h], rbp
    mov rbp, qword ptr [rsp+8]
    mov ecx, dword ptr [rbp+rcx*8+484h]
    mov rbp, qword ptr [rsp+70h]

woh_15:
    mov r8d, ecx
    mov dword ptr [rsp+50h], ecx
    add dl, dl
    mov byte ptr [rsp+40h], dl
    jne woh_16
    inc ebx
    mov dword ptr [rsp+44h], ebx
    mov dl, 1
    mov byte ptr [rsp+40h], dl

woh_16:
    jmp woh_17
woh_13:
    mov eax, r9d
    mov byte ptr [rax+r11], cl
    inc r9d
    mov dword ptr [rsp+48h], r9d
    jmp woh_18

woh_11:
    cmp dl, 1
    jbe woh_19
    inc ebx
    mov dword ptr [rsp+44h], ebx
    
woh_19:
    mov dword ptr [rsp+50h], r14d
    jmp woh_20
    mov r14d, dword ptr [rsp+50h]

woh_20:
    mov rax, [rsp+18h]
    mov rbp, [rsp+20h]
    add rsp, 80h

    ret
Decrypt  ENDP
END