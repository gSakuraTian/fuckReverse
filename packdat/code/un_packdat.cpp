#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <direct.h>

struct Data
{
    char sign[0x20];
    DWORD offset;
    DWORD cmp;
    DWORD size1;
    DWORD size2;
}data;

struct Header
{
    char sign[8];
    DWORD size1;
    DWORD size2;
}header;

int ReadFilePackDat(LPCTSTR filePath)
{
    HANDLE pFile;

    pFile = CreateFile(filePath, GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,        //打开已存在的文件 
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (pFile == INVALID_HANDLE_VALUE)
    {
        printf("open file error!\n");
        CloseHandle(pFile);
        return 0;
    }

    DWORD nByt;

    ReadFile(pFile, &header, 0x10, &nByt, NULL);

    if (!(strncmp(header.sign, "PACKDAT.", 8)))
    {
        DWORD currentPosition;
        char* Buf = NULL;
        char fname[0x20];

        while (header.size2)
        {
            ReadFile(pFile, &data, 0x30, &nByt, NULL);
            //获取当前偏移
            currentPosition = SetFilePointer(pFile, 0, NULL, FILE_CURRENT);

            SetFilePointer(pFile, data.offset, NULL, FILE_BEGIN);

            //std::cout << std::hex << currentPosition;

            Buf = (char*)malloc(data.size2);
            ReadFile(pFile, Buf, data.size2, &nByt, NULL);

            DWORD tmp = 0;
            __asm
            {
                mov eax, data.size2
                shr eax, 2
                mov ecx, eax
                mov esi, eax
                and ecx, 7
                mov edi, Buf
                add ecx, 8
                shl esi, cl
                xor esi, eax
                mov tmp, eax
            }
            while(tmp > 0)
            {
                __asm
                {
                
                    mov ecx, dword ptr ds : [edi]
                        xor edx, edx
                        xor ecx, esi
                        mov dword ptr ds : [edi] , ecx
                        mov eax, ecx
                        mov ecx, 0x18
                        add edi, 4
                        div ecx
                        mov ecx, 0x20
                        mov eax, esi
                        sub ecx, edx
                        shr eax, cl
                        mov ecx, edx
                        shl esi, cl
                        or esi, eax
                }
                tmp = tmp - 1;
            }
            
            FILE* dst = fopen(data.sign, "wb");
            fwrite(Buf, data.size2, 1, dst);
            fclose(dst);

            free(Buf);

            SetFilePointer(pFile, currentPosition, NULL, FILE_BEGIN);
            header.size2 = header.size2 - 1;
        }

    }

}

TCHAR* ExtractFileName(LPCTSTR filePath) {
    static TCHAR result[MAX_PATH];

    // 找到最后一个反斜杠
    LPCTSTR lastBackslash = _tcsrchr(filePath, _T('\\'));
    if (lastBackslash == NULL) {
        lastBackslash = filePath; // 如果没有反斜杠，使用整个字符串
    }
    else {
        lastBackslash++; // 移动到反斜杠后面的字符
    }

    // 找到最后一个点号
    LPCTSTR lastDot = _tcsrchr(lastBackslash, _T('.'));

    if (lastDot == NULL) {
        // 如果没有找到点号，复制整个剩余字符串
        _tcscpy_s(result, MAX_PATH, lastBackslash);
    }
    else {
        // 计算不包括扩展名的文件名长度
        size_t length = lastDot - lastBackslash;
        _tcsncpy_s(result, MAX_PATH, lastBackslash, length);
        result[length] = _T('\0'); // 确保字符串正确终止
    }

    return result;
}

int main()
{
    LPCTSTR filePath = _T("D:\\Galgame\\system2.dat");
    TCHAR* fileName = ExtractFileName(filePath);

    _mkdir(fileName);
    _chdir(fileName);
    ReadFilePackDat(filePath);
    
}