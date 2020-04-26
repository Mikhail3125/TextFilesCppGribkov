#pragma once
///<Library>
#include <io.h>
#include <process.h> /* for getpid() and the exec..() family */
#include <direct.h>
#include <fcntl.h>		/* open() and O_XXX flags */
#include <sys/stat.h>	/* S_IXXX flags */
#include <sys/types.h>	/* mode_t */
#include <Windows.h>
#include <stdio.h> 
#include <conio.h>
#include <process.h> 
#include <stdlib.h> 
#include <iostream>
#include<fstream>
#include<string>
#include<ctime>
#include <iostream>
#include <sstream> // для stringstream

#pragma warning(disable : 4996)

void BaseLevelTask();
void MidleLevelTask();
///<UsidFunctions> 

void HardLevelTask();

double* gauss(double** a, double* y, int n);

void swap(double& a, double& b);

void sysout(double** a, double* y, int n);

void WorkFile(char* FileName, char* FileNameSecond, int Count_MatsOrVectors,
				int row, int col);

int BlockWriteFile(char* FileName, const char* Mode_Open_File,  //поматрично записывает в файл с именем String, открытый в режиме Mode, k матриц размерности nxm.
	unsigned count_matrix, unsigned row, unsigned col);

double* InitMatrix(unsigned,  //возвращает указатель на участок динамической памяти размером n*m*sizeof(int), содержимым которого является матрица, заполненная числом l+1.
	unsigned, unsigned);

double* FreeMemory(unsigned, unsigned);//возвращает указатель на участок динамической памяти размером n*m*sizeof(int) для хранения динамической матрицы размерности nxm.

void DisplayFile(const char*, const char*, unsigned, unsigned);//поматрично выводит на экран содержимое файла с именем String, открытый в режиме Mode

void DisplayMatrix(double*, unsigned, unsigned); //выводит на экран содержимое динамической памяти размером n*m*sizeof(int) по адресу Pointer

void FillNewFileUnwantedMatrix(char* FileName1, char* FileName2, unsigned set_pos, unsigned count_matrix, unsigned row, unsigned col);//Заполняет 3ий фыйл лишними матрицами из второго

void DeleteUnwantedMatrixOfFile(char* String, unsigned position, unsigned n, unsigned m);

///<\UsidFunctions>

