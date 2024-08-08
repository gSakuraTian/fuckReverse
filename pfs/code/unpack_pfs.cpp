#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <direct.h>
#include <string.h>

#pragma pack(1)
struct Header
{
    char sign[3];
    DWORD offset;
    DWORD file_num;
}header;


struct Data
{
    /*char* file_name = NULL;*/
    DWORD zero;
    DWORD offset;
    DWORD size;
}data;

int ReadFilePfs(LPCTSTR filePath)
{
    HANDLE pFile;

    pFile = CreateFile(filePath, GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,        //���Ѵ��ڵ��ļ� 
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (pFile == INVALID_HANDLE_VALUE)
    {
        printf("open file error!\n");
        CloseHandle(pFile);
        return 0;
    }

    DWORD nByt;

    ReadFile(pFile, &header, sizeof(Header), &nByt, NULL);

    if ((strncmp(header.sign, "pf8.", 3)))
        return 0;


    DWORD key[0x14] = { 0x9E, 0x84, 0x66, 0x30, 0x42, 0x6B, 0xAC, 0xCB, 0xAF, 0x57,
        0x78, 0x22, 0xA0, 0xE5, 0xEA, 0xB4, 0x5C, 0x3F, 0xED, 0x14 };
    
    DWORD currentPosition;
    char* Buf = NULL;


    while (header.file_num > 0)
    {
        DWORD file_path_len = 0;
        char* file_path = NULL;

        ReadFile(pFile, &file_path_len, sizeof(file_path_len), &nByt, NULL);
        file_path = (char*)malloc(file_path_len + 1);
        ReadFile(pFile, file_path, file_path_len, &nByt, NULL);
        file_path[file_path_len] = 0;

        //�����ļ�����
        LPCTSTR lastBackslash = _tcsrchr(_T(file_path), _T('\\'));
        if (lastBackslash == NULL) {
            lastBackslash = file_path; // ���û�з�б�ܣ�ʹ�������ַ���
        }
        else {
            lastBackslash++; // �ƶ�����б�ܺ�����ַ�
        }
        int len = strlen(lastBackslash);
        int dir_len = file_path_len - len - 1;

        if (dir_len > 0)
        {
            std::string dir;
            for (size_t i = 0; i < dir_len; i++)
            {
                dir += file_path[i];
                if (file_path[i] == '\\')
                    dir += '\\';
            }
            std::string command = "mkdir " + dir + " 2>nul";
            system(command.c_str());
        }
            

        ReadFile(pFile, &data, sizeof(Data), &nByt, NULL);

        //��ȡ��ǰƫ��
        currentPosition = SetFilePointer(pFile, 0, NULL, FILE_CURRENT);

        //��ȡ����
        SetFilePointer(pFile, data.offset, NULL, FILE_BEGIN);
        Buf = (char*)malloc(data.size);
        ReadFile(pFile, Buf, data.size, &nByt, NULL);



        int esi = 0;
        for (size_t i = 0; i < data.size; i++)
        {
            Buf[i] = Buf[i] ^ key[esi];

            int eax = esi + 1;
            esi = 0;
            if (eax < 0x14) {  
                esi = eax;
            }
        }

        FILE* dst = fopen(file_path, "wb");
        fwrite(Buf, data.size, 1, dst);
        fclose(dst);

        SetFilePointer(pFile, currentPosition, NULL, FILE_BEGIN);
        free(file_path);
        free(Buf);
        header.file_num -= 1;
    }

    return 0;
}

TCHAR* ExtractFileName(LPCTSTR filePath) {
    static TCHAR result[MAX_PATH];

    // �ҵ����һ����б��
    LPCTSTR lastBackslash = _tcsrchr(filePath, _T('\\'));
    if (lastBackslash == NULL) {
        lastBackslash = filePath; // ���û�з�б�ܣ�ʹ�������ַ���
    }
    else {
        lastBackslash++; // �ƶ�����б�ܺ�����ַ�
    }

    // �ҵ����һ�����
    LPCTSTR lastDot = _tcsrchr(lastBackslash, _T('.'));

    if (lastDot == NULL) {
        // ���û���ҵ���ţ���������ʣ���ַ���
        _tcscpy_s(result, MAX_PATH, lastBackslash);
    }
    else {
        // ���㲻������չ�����ļ�������
        size_t length = lastDot - lastBackslash;
        _tcsncpy_s(result, MAX_PATH, lastBackslash, length);
        result[length] = _T('\0'); // ȷ���ַ�����ȷ��ֹ
    }

    return result;
}

int main()
{
	LPCTSTR filePath = _T("D:\\Galgame\\sakuranotoki.pfs");
    TCHAR* fileName = ExtractFileName(filePath);

    _mkdir(fileName);
    _chdir(fileName);

    ReadFilePfs(filePath);

    std::cout << "complete" << std::endl;
}