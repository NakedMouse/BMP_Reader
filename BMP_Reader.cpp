#pragma warning (disable:4996)
#pragma pack(2)
#include <iostream>
#include <fstream>
using namespace std;
#define BYTE unsigned char

//struct存在以4或8为标志进行字节对齐，需要用pack（2）限定对齐系数大小
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
	ifstream file(fileIn,ios::in|ios::binary);
	if (file.fail()) {
		cout << "File Error" << endl;
		return;
	}
	file.read(reinterpret_cast <char*>(&fileHader), 14);

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

