#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <direct.h>

struct Data
{
    char sign[4];
    unsigned long size;
}data;

void ReadSec5(const char* filePath)
{
    char ch[4];
    char* Buf = NULL;
    char filename[5];

    FILE* fp = fopen(filePath, "rb");
    fread(&data, sizeof(data), 1, fp);

    if (strncmp(data.sign, "SEC5", 4))
        std::cout << "文件格式出错" << std::endl;
    _mkdir("SEC5");
    _chdir("SEC5");

    memcpy(filename, data.sign, 4);
    filename[4] = '\0';
    FILE* dst = fopen(filename, "wb");
    fwrite(&data, sizeof(data), 1, dst);
    fclose(dst);

    while (true)
    {
        fread(&data, sizeof(data), 1, fp);

        Buf = (char*)malloc(data.size);
        fread(Buf, data.size, 1, fp);

        if (!(strncmp(data.sign, "ENDS", 4)))
        {
            memcpy(filename, data.sign, 4);
            filename[4] = '\0';
            FILE* dst = fopen(filename, "wb");
            fwrite(&data, sizeof(data), 1, dst);
            fclose(dst);
            break;
        }
            

        if (!(strncmp(data.sign, "CODE", 4)))
        {
            __asm
            {
                mov edi, Buf
                xor ecx, ecx
                xor esi, esi
                mov edx, 4EB009h
                calc :
                mov al, byte ptr ds : [edi + esi]
                    mov dl, al
                    xor dl, cl
                    add al, 0x12
                    mov byte ptr ds : [edi + esi] , dl
                    add esi, 1
                    add cl, al
                    cmp esi, edx
                    jl calc
            }
        }
        memcpy(filename, data.sign, 4);
        filename[4] = '\0';
        FILE* dst = fopen(filename, "wb");
        fwrite(Buf, data.size, 1, dst);
        free(Buf);
        fclose(dst);
    }


    
}

/*char* Clac(char* fileBuf)
{
    __asm
    {
        mov edi, fileBuf
        xor ecx, ecx
        xor esi, esi
        mov edx, 4EB009h
calc:
        mov al, byte ptr ds:[edi + esi]
        mov dl, al
        xor dl, cl
        add al, 0x12
        mov byte ptr ds : [edi + esi], dl
        add esi, 1
        add cl, al
        cmp esi, edx
        jl calc
    }
    return fileBuf;
}*/


int main()
{
    const char* filePath = "D:\\Galgame\\katakoi.sec5";
    ReadSec5(filePath);
}