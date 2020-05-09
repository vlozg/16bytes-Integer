#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "QNum.h"
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
	QInt operator%(QInt);

	//các hàm bitwise
	QInt RotateLeft(int number);
	QInt RotateRight(int number);
	QInt operator&(QInt number);
	QInt operator|(QInt number);
	QInt operator^(QInt number);
	QInt operator~();
	QInt operator>>(int number);
	QInt operator<<(int number);
	QInt operator>>(QInt number);
	QInt operator<<(QInt number);
	QInt RotateLeft(QInt number);
	QInt RotateRight(QInt number);


	QInt operator=(const QInt&);
	QInt operator=(string number);
	
	//các hàm so sánh
	bool operator<(const QInt&);
	bool operator>(const QInt&);
	bool operator<=(const QInt&);
	bool operator>=(const QInt&);
	bool operator==(const QInt&);

	bool IsNegative();
	
	int ModBy128();	//Hỗ trợ shift bit với qint

	QInt();
	QInt(string);

	//Hàm hỗ trợ giao diện
	string DecStr();
	string HexStr();
	string BinStr();
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
QInt BinStrToDec(string binStr);

bool* HexToBin(char* hex);
QInt HexToDec(char* hex);

