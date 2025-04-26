PUBLIC clacSize 
.code
clacSize PROC
        mov edi, DWORD PTR [rcx + 10h + 12]
        shr edi, 3
        mov eax, DWORD PTR [rcx + 10h + 4]
        imul edi, eax
        imul edi, DWORD PTR [rcx + 10h]
        mov eax, edi
        ret
clacSize ENDP
END