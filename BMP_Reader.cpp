#pragma warning (disable:4996)
#include <iostream>
#include <fstream>
using namespace std;
#define BYTE unsigned char

struct FileHader {
	unsigned short	bfType;
	unsigned long	bfSize;
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned long	bfOffBits;
}fileHader;

struct InforHader {
	unsigned long	biSize;
	unsigned long	biWidth;
	unsigned long	biHeight;
	unsigned short	biPlanes;
	unsigned short	biBitCount;
	unsigned long	biCompression;
	unsigned long	biSizeImage;
	unsigned long	biXperlsPerMeter;
	unsigned long	biYperlsPerMeter;
	unsigned long	biClrUsed;
	unsigned long	biCleImportant;
}inforHader;

struct ColorTable {
	char* colorData;
}clrTable;

struct Image {
	char* imageData;
	unsigned long	width;
	unsigned long	height;
	unsigned int	channels;
}imageDatas;


void main()
{
	string fileIn = "D:\\WorkSpace\\TsetFile\\img\\lena_24bit.bmp";
	FILE* file = fopen(fileIn.c_str(),"rb");
	
	if (file==NULL) {
		cout << "File Open Error" << endl;
		return ;
	}
	
	BYTE szBuf[256] = { 0 };
	int intBuf[256] = { 0 };
	//fread(szBuf, 1, 54, file);	//将前54个字节读入szBuf再进行处理
	fread(fileHader, 1, 14, file);


	for (int i = 0; i < 54; i++) {
		intBuf[i] = (int)(szBuf[i] - NULL);
		cout << intBuf[i] << endl;
	}

	char* dataBuf = NULL;


	//file.close();
	////输出文件
	//string fileOut = "//file/1.txt";
	//FILE* fout = fopen(fileOut.c_str(), "w+");
	//fprintf(fout, "aa");
	////fout << nNum << "," << str << std::endl;
	////fprintf(fout, "%.3f  %.3f  %.6f\n", j * p.h, l * p.h, u[40][l][j]);
	//fclose(fout);
}

