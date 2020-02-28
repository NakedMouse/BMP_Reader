#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	string fileIn = "//file/2.bmp";
	ifstream file(fileIn,binaty);

	//输出文件
	string fileOut = "//file/1.txt";
	FILE* fout = fopen(fileOut.c_str(), "w+");
	fprintf(fout, "aa");
	//fout << nNum << "," << str << std::endl;
	//fprintf(fout, "%.3f  %.3f  %.6f\n", j * p.h, l * p.h, u[40][l][j]);
	fclose(fout);
}

