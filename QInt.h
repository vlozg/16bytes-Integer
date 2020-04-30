#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "QNum.h"
#include <iostream>
#include <string>

#define SIZE 16
#define BIT_RANGE 128
#define MAX_VALUE_BIT 16
#define FOUR_BIT 4
using namespace std;

class QInt
{
private:
	char value[SIZE] = { 0 };
public:
	bool GetBit(int i);
	void SetBit(int i, bool bit);

	void Input(string);
	void Output();

	QInt ComplementTwo();

	//các hàm số học
	QInt operator+(QInt);
	QInt operator-(QInt);
	QInt operator*(QInt);
	QInt operator/(QInt);

	//các hàm bitwise
	QInt RotateLeft(int number);
	QInt RotateRight(int number);
	QInt operator&(QInt number);
	QInt operator|(QInt number);
	QInt operator^(QInt number);
	QInt operator~();
	QInt operator>>(int number);
	QInt operator<<(int number);


	QInt operator=(const QInt&);
	
	//các hàm so sánh
	bool operator<(const QInt&);
	bool operator>(const QInt&);
	bool operator<=(const QInt&);
	bool operator>=(const QInt&);
	bool operator==(const QInt&);

	bool IsNegative();
	int MostSignificantBit();

	QInt();
	QInt(string);
};

void ScanQInt(QInt& x);		//Cau a
void PrintQInt(QInt x);		//Cau b
bool* DecToBin(QInt x);		//Cau c
QInt BinToDec(bool* bit);	//Cau d
char* BinToHex(bool* bit);	//Cau e
char* DecToHex(QInt x);		//Cau f


char BinToHexChar(string num);
string HexToBinChar(char hex);

void OutputBin(bool* bin);
void OutputHex(char* hex);

bool* HexToBin(char* hex);
QInt HexToDec(char* hex);

