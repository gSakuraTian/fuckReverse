#include "main.h"

struct DataSign
{
	char sign[0x10];
	DWORD width;
	DWORD height;
	DWORD num1;
	DWORD channels;
	char tmp[0x10];
	DWORD offset;
}datasign;

extern "C" DWORD clacSize(DataSign* dSign);
extern "C" char* Decrypt(char* data, char* asm_Buf, char* asm_Buf_2, DWORD key, DWORD size);
extern "C" char* Decrypt_2(char* decryptData, char* asm_Buf_3, DWORD size);
extern "C" char* Decrypt_3(char* decryptData, char* asm_Buf_3, DataSign* dSign);

std::string to_hex_string(const char* data, size_t len) {
	static const char hex_digits[] = "0123456789abcdef";
	std::string hex;
	hex.reserve(len * 2);
	for (size_t i = 0; i < len; ++i) {
		unsigned char byte = static_cast<unsigned char>(data[i]);
		hex.push_back(hex_digits[byte >> 4]);
		hex.push_back(hex_digits[byte & 0x0F]);
	}
	return hex;
}

void CBG(char* Buf, DWORD dataNum, std::string fileName)
{
	memcpy(&datasign, Buf, sizeof(DataSign));
	DWORD r12d;
	char* data = Buf;

	if (datasign.offset >= 0X34)
	{
		DWORD val8 = datasign.channels;
		val8 >>= 3;
		DWORD eax = val8;

		DWORD val5 = datasign.width;
		DWORD ecx = val5 * eax;

		DWORD val7 = datasign.num1;
		eax = val7 * ecx;

		DWORD val6 = datasign.height;
		DWORD remainder = val6 % val7;
		DWORD quotient = val6 / val7;
		DWORD rounded = (val6 - 1 + val7) / val7;
		r12d = rounded;

	}
	DWORD size;
	char* temp = Buf;
	for (int i = 1; i <= r12d; i++)
	{
		DWORD offset;
		char* temp;
		temp = Buf + (0x30 + (i-1) * 4 );
		memcpy(&offset, temp, 4);
		data = Buf + offset;
		memcpy(&size, data, 4);

	}
	
	data += 4;

	DWORD dwBytes = clacSize(&datasign);

	char* asm_Buf = NULL;
	asm_Buf = (char*)malloc(0x400 + 0x1ff * 0x18 + 0x70);
	memset(asm_Buf, 0, 0x400 + 0x1ff * 0x18 + 0x70);

	//存储Decrypt1后数据
	char* asm_Buf_2 = NULL;
	asm_Buf_2 = (char*)malloc(size);
	memset(asm_Buf_2, 0, size);
	DWORD key = dataNum - datasign.offset - 4;
	char* decryptData = Decrypt(data, asm_Buf, asm_Buf_2, key, size);
	
	//存储Decrypt2后数据
	char* asm_Buf_3 = NULL;
	asm_Buf_3 = (char*)malloc(dwBytes);
	memset(asm_Buf_3, 0, dwBytes);
	char* decryptData_2 = Decrypt_2(decryptData, asm_Buf_3, size);

	//存储Decrypt3后数据
	char* asm_Buf_4 = NULL;
	asm_Buf_4 = (char*)malloc(dwBytes);
	memset(asm_Buf_4, 0, dwBytes);
	char* hex_data = Decrypt_3(decryptData_2, asm_Buf_4, &datasign);

	
	//int width = datasign.width;
	//int height = datasign.height;
	//int channels = 4;    // RGBA
	DWORD channels = datasign.channels >> 3;

	std::string py_code;
	py_code += "from PIL import Image\n";
	py_code += "def data_to_img(hex_data, width, height, file_name, channels):\n";
	py_code += "    byte_data = bytes.fromhex(hex_data)\n";
	py_code += "    if channels == 4:\n";
	py_code += "        color_mode = \"RGBA\"\n";
	py_code += "    if channels == 3:\n";
	py_code += "        color_mode = \"RGB\"\n";
	py_code += "    try:\n";
	py_code += "        img = Image.frombytes(color_mode, (width, height), byte_data)\n";
	py_code += "        img.save(file_name + \".png\")\n";
	py_code += "    except Exception as e:\n";
	py_code += "        print(f\"error: {file_name}:{e}\")\n";
	py_code += "data_to_img('{HEX_DATA}', {WIDTH}, {HEIGHT}, '{FILE_NAME}', {CHANNELS})\n";

	size_t pos;
	std::string hex_string = to_hex_string(hex_data, dwBytes);
	pos = py_code.find("{HEX_DATA}");
	if (pos != std::string::npos)
		py_code.replace(pos, std::string("{HEX_DATA}").length(), hex_string);

	pos = py_code.find("{WIDTH}");
	if (pos != std::string::npos)
		py_code.replace(pos, std::string("{WIDTH}").length(), std::to_string(datasign.width));

	pos = py_code.find("{HEIGHT}");
	if (pos != std::string::npos)
		py_code.replace(pos, std::string("{HEIGHT}").length(), std::to_string(datasign.height));

	pos = py_code.find("{FILE_NAME}");
	if (pos != std::string::npos)
		py_code.replace(pos, std::string("{FILE_NAME}").length(), fileName);

	pos = py_code.find("{CHANNELS}");
	if (pos != std::string::npos)
		py_code.replace(pos, std::string("{CHANNELS}").length(), std::to_string(channels));

	if (PyRun_SimpleString(py_code.c_str()) != 0) {
		PyErr_Print(); 
	}

	free(asm_Buf_4);
	free(asm_Buf_3);
	free(asm_Buf_2);
	free(asm_Buf);

}