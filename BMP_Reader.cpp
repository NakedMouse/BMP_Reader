#pragma warning (disable:4996)
#pragma pack(2)
#include <iostream>
#include <fstream>
using namespace std;

//struct存在以4或8为标志进行字节对齐，需要用pack（2）限定对齐系数大小
struct FileHader {
	unsigned short	bfType;
	unsigned long	bfSize;
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned long	bfOffBits;
}fileHader;

struct InfoHader {
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
}infoHader;

struct ColorTable {
	unsigned char*	colorData;
}clrTable;

struct Image {
	unsigned char*	imageData;
	unsigned long	width;
	unsigned long	height;
	unsigned int	channels;
}imageDatas;


void main()
{
	string fileIn = "resources//lena_24bit.bmp";
	ifstream file(fileIn,ios::in|ios::binary);
	if (file.fail()) {
		cout << "File Error" << endl;
		return;
	}
	file.read(reinterpret_cast <char*>(&fileHader), 14);
	file.read((char*)& infoHader, 40);

	unsigned char* dataBuf = NULL;

	//无colorTable情况
	if (fileHader.bfOffBits == 54) {
		unsigned int width = infoHader.biWidth;
		unsigned int height = infoHader.biHeight;
		unsigned int channels = infoHader.biBitCount / 8;
		unsigned int length = width * height * channels;

		if (dataBuf = (unsigned char*)malloc(length * sizeof(char))) {
			memset(dataBuf, 0, length * sizeof(char));
		}
		else {
			cout << "Malloc Error" << endl;
			return;
		}
		imageDatas.channels = channels;
		imageDatas.width = width;
		imageDatas.height = height;
		file.read((char*)dataBuf, length * sizeof(char));
		imageDatas.imageData = dataBuf;
		//cout << dataBuf[0] - NULL << endl;
	}
	else {

	}

	
	//输出文件
	string fileOut = "resources//1.txt";
	FILE* fout = fopen(fileOut.c_str(), "w+");
	for (unsigned int i = 0; i <= (int)imageDatas.width * imageDatas.height * 3; i+=3) {
		if (i % (500*3) == 0 && i!=0) fprintf(fout, "\n");
		fprintf(fout, "(%X %X %X)   ", imageDatas.imageData[i], imageDatas.imageData[i + 1], imageDatas.imageData[i + 2]);
	}
	//fout << nNum << "," << str << std::endl;
	//fprintf(fout, "%.3f  %.3f  %.6f\n", j * p.h, l * p.h, u[40][l][j]);
	fclose(fout);
	file.close();
}

