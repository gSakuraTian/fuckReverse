#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

struct Data
{
    CHAR sign[4];
    DWORD size;
    char* Buf;
};

void PackSec5(const char* filePath)
{
    HANDLE hFind;
    WIN32_FIND_DATA findData;
    char filename[5];
    // ������ǰĿ¼�µ������ļ�����Ŀ¼
    hFind = FindFirstFile(filePath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cout << "�޷���Ŀ¼" << std::endl;
    }
    
    do {

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            continue;
        if(!(strncmp(findData.cFileName, "SEC5", 4)))
            continue;
        if(!(strncmp(findData.cFileName, "ENDS", 4)))
            continue;

        HANDLE pFile;
        pFile = CreateFile(findData.cFileName, GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,        
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        if (pFile == INVALID_HANDLE_VALUE)
        {
            printf("open file error!\n");
            CloseHandle(pFile);
        }

        DWORD fileSize = GetFileSize(pFile, NULL);
        DWORD nByt;
        CHAR* fileBuf;

        fileBuf = new char[fileSize];
        ReadFile(pFile, fileBuf, fileSize, &nByt, NULL);

        if (!(strncmp(findData.cFileName, "CODE", 4)))
        {
            unsigned char key = 0;
            for (unsigned int i = 0; i < fileSize; i++)
            {
                fileBuf[i] ^= key;
                key += (unsigned char)(fileBuf[i] + 0x12);
            }
        }
        CloseHandle(pFile);

        memcpy(filename, findData.cFileName, 4);
        filename[4] = '\0';
        FILE* dst = fopen(filename, "wb");
        //д���־
        fwrite(&findData.cFileName, 4, 1, dst);
        fflush(dst);

        //д���ļ���С
        fwrite(&fileSize, 4, 1, dst);
        fflush(dst);

        //д������
        fwrite(fileBuf, fileSize, 1, dst);
        fclose(dst);

        delete[]fileBuf;
        
    } while (FindNextFile(hFind, &findData));

    FindClose(hFind);

}

int main()
{   
    const char* command = "D:\\Galgame\\SEC5";
    //���ĵ�ǰ����Ŀ¼
    SetCurrentDirectory(command);

    PackSec5("*");

    system("copy /b SEC5 + RTFC + OPTN + CZIT + VARS + VARA + EXPL + CODE + RESR + ENDS katakoi.sec5");
    
}