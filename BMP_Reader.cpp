#pragma warning (disable:4996)
#pragma pack(2)
#include <iostream>
#include <fstream>
#include <vector>
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
	unsigned long	l_width;
	unsigned long	height;
	unsigned int	channels;
	unsigned int	length;
}imageDatas;

void printData();
void getGrayHistogram();
void transToGray();

void main()
{
	//string fileIn = "resources//lena_low_8bit.bmp";
	string fileIn = "resources//lena_low_24bit.bmp";
	ifstream file(fileIn, ios::in | ios::binary);
	if (file.fail()) {
		cout << "File Error" << endl;
		return;
	}
	file.read(reinterpret_cast <char*>(&fileHader), 14);
	file.read((char*)& infoHader, 40);

	unsigned char* dataBuf = NULL;
	unsigned int channels = infoHader.biBitCount / 8;
	unsigned int length = infoHader.biSizeImage;
	if (dataBuf = (unsigned char*)malloc(length)) {
		memset(dataBuf, 0, length );
	}
	else {
		cout << "Malloc Error" << endl;
		return;
	}
	imageDatas.channels = channels;
	imageDatas.width = infoHader.biWidth;
	imageDatas.l_width = (imageDatas.width * imageDatas.channels + 3) / 4 * 4;
	imageDatas.height = infoHader.biHeight;
	imageDatas.length = imageDatas.l_width * imageDatas.height;

	//无colorTable情况
	if (fileHader.bfOffBits == 54) {
		file.seekg(fileHader.bfOffBits);
		file.read((char*)dataBuf, length );
		imageDatas.imageData = dataBuf;
		//cout << dataBuf[0] - NULL << endl;
	}
	else {
		unsigned char* clrBuf;
		if (clrBuf = (unsigned char*)malloc(fileHader.bfOffBits - 54)) {
			memset(clrBuf, 0, fileHader.bfOffBits - 54);
		}
		else {
			cout << "ClrBuf Error" << endl;
		}
		file.read((char*)clrBuf, fileHader.bfOffBits - 54);
		clrTable.colorData = clrBuf;

		file.seekg(fileHader.bfOffBits);
		file.read((char*)dataBuf, length);
		imageDatas.imageData = dataBuf;
	}
	file.close();

	//将数组打印到txt上
	printData();
	getGrayHistogram();
	transToGray();

}


void printData() {
	//输出文件
	string fileOut = "resources//data.txt";
	FILE* fout = fopen(fileOut.c_str(), "w+");
	
	unsigned int pixel_width = imageDatas.width;
	unsigned int fixNum = imageDatas.l_width - imageDatas.width * imageDatas.channels;
	for (unsigned int h = 0, w = 0, i = 0; h < imageDatas.height; h++) {
		for (w = 0; w < pixel_width * imageDatas.channels; w++) {
			fprintf(fout, "%2.2X  ", imageDatas.imageData[h * imageDatas.l_width + w]);
		}
		for (int j = 0; j < fixNum; j++) {
			fprintf(fout, "%2.2X  ", imageDatas.imageData[h * imageDatas.l_width + w  + j]);
		}
		fprintf(fout, "\n");
	}
	//fout << nNum << "," << str << std::endl;
	//fprintf(fout, "%.3f  %.3f  %.6f\n", j * p.h, l * p.h, u[40][l][j]);
	fclose(fout);
}

//计算灰度直方图并打印到GrayHistogram.txt
void getGrayHistogram() {
	if (imageDatas.channels != 1) {
		cout << "Not Gray BMP , Can Not Get Gray Histogram" << endl;
		return;
	}

	unsigned int grayHistoGram[256] = { 0 };
	
	for (unsigned int i = 0; i < imageDatas.length; i++) {
		int index = (int)(imageDatas.imageData[i] - NULL);
		grayHistoGram[index]++;
	}

	string fileOut = "resources//GrayHistogram.txt";
	FILE* fout = fopen(fileOut.c_str(), "w+");
	for (int i = 0; i < 256; i++) {
		//if (i % 10 == 0 && i != 0) fprintf(fout, "\n");
		fprintf(fout, "%.3d,%.4d\n", i, grayHistoGram[i]);
	}

	fclose(fout);
}

//将24位真彩色转换为灰度图像并打印到txt
void transToGray() {
	if (imageDatas.channels != 3) {
		cout << "Is Not 24Bit Image , Can not Transfer TO Gray Image" << endl;
		return;
	}

	unsigned int length = imageDatas.length;
	//Gray = (R*299 + G*587 + B*114 + 500) / 1000 转换算法
	unsigned char* gray;
	unsigned int pixel_width = imageDatas.width;
	unsigned int gray_l_width = (pixel_width + 3) / 4 * 4;
	unsigned int gray_length = imageDatas.height * gray_l_width;

	if (gray = (unsigned char*)malloc(gray_length)) {
		memset(gray, 0, gray_length);
	}
	else {
		cout << "Gray memorry error" << endl;
		return;
	}

	unsigned int fixNum = gray_l_width - pixel_width;
	for (unsigned int h = 0, w = 0, i = 0; h < imageDatas.height / 2; h++) {
		unsigned char charTemp;
		unsigned int temp;
		for (w = 0, i = 0; w < pixel_width; w++) {
			unsigned int R = (unsigned int)imageDatas.imageData[h * imageDatas.l_width + i];
			unsigned int G = (unsigned int)imageDatas.imageData[h * imageDatas.l_width + i + 1];
			unsigned int B = (unsigned int)imageDatas.imageData[h * imageDatas.l_width + i + 2];
			i += 3;
			temp = (R * 299 + G * 587 + B * 144 + 500) / 1000;
			charTemp = (unsigned char)(0xff & temp);
			gray[h * gray_l_width + w] = charTemp;
		}

		//补位
		charTemp = 0xff;
		for (unsigned int j = 0; j < fixNum; j++) {
			gray[h * gray_l_width + w + j] = charTemp;
		}
	}

	//文件输出
	string fileOut = "resources\\TransData.txt";
	FILE* fout = fopen(fileOut.c_str(), "w+");
	fprintf(fout, "Trans Image Datas \n");
	for (unsigned int h = 0; h < imageDatas.height / 2; h++) {
		for (unsigned int w = 0; w < gray_l_width; w++) {
			fprintf(fout, "%2.X  ", gray[h * gray_l_width + w]);
		}
		fprintf(fout, "\n");
	}

	
	fixNum = imageDatas.l_width - pixel_width * 3;
	unsigned int height = imageDatas.height / 2;
	for (unsigned int h = height, w = 0, i = 0; h < imageDatas.height; h++) {
		for (w = 0, i = 0; w < pixel_width; w++) {
			unsigned int R = (unsigned int)imageDatas.imageData[h*imageDatas.l_width+i];
			unsigned int G = (unsigned int)imageDatas.imageData[h * imageDatas.l_width + i + 1];
			unsigned int B = (unsigned int)imageDatas.imageData[h * imageDatas.l_width + i + 2];
			i += 3;
			fprintf(fout, "(%2.2X %2.2X %2.2X) ", R, G, B);
		}
		for (int j = 0; j < fixNum; j++) {
			//gray[h * gray_l_width + w + j] = charTemp;
			fprintf(fout, "%2.2X  ", imageDatas.imageData[h * imageDatas.l_width + w * imageDatas.channels + j]);
		}
		fprintf(fout, "\n");
	}
	fclose(fout);
	return;
}