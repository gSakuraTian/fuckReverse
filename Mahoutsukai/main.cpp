#include "main.h"

struct Header
{
    char sign[0xC];
    DWORD fileNum;
}header;

struct File_properties
{
    char fileName[0x60];
    DWORD offset;
    DWORD dataNum;
    char tmp[0x18];
}file_properties;

int unPack(LPCTSTR filePath)
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
    ReadFile(pFile, &header, 0x10, &nByt, NULL);

    DWORD data_baseAddr = (header.fileNum * sizeof(File_properties))+ sizeof(Header);

    if (!(strncmp(header.sign, "HUNEXGGEFA10", 0xC)))
    {
        DWORD currentPosition;
        char* Buf = NULL;

        while (header.fileNum)
        {
            ReadFile(pFile, &file_properties, 0x80, &nByt, NULL);
            //��ȡ��ǰƫ��
            currentPosition = SetFilePointer(pFile, 0, NULL, FILE_CURRENT);

            SetFilePointer(pFile, data_baseAddr + file_properties.offset, NULL, FILE_BEGIN);

            Buf = (char*)malloc(file_properties.dataNum);
            ReadFile(pFile, Buf, file_properties.dataNum, &nByt, NULL);

            //��Ѱ��׺��
            int i = 0;
            char* Format;
            while (true)
            {
                if (file_properties.fileName[i] == '.')
                {
                    Format = file_properties.fileName + i + 1;
                    break;
                }
                i++;
            }

            std::string fileName = file_properties.fileName;

            if (!(strncmp(Format, "cbg", 3)))
                CBG(Buf, file_properties.dataNum, fileName);


            free(Buf);
            SetFilePointer(pFile, currentPosition, NULL, FILE_BEGIN);
            header.fileNum = header.fileNum - 1;
        }
    }

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
    LPCTSTR filePath = _T("D:\\Galgame\\data00000.hfa");
    TCHAR* dirName = ExtractFileName(filePath);

    Py_Initialize();

    _mkdir(dirName);
    _chdir(dirName);
    unPack(filePath);

    Py_Finalize();

	return 0;
}