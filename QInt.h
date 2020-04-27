#pragma once
#include <iostream>
#include <string>
#define SIZE 16
#define BIT_RANGE 128
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
	void RotateLeft(int number);
	void RotateRight(int number);
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

char* BinToHex(bool* bit);
char* DecToHex(QInt x);

string DivideByTwo(string number);
bool* DecToBinStr(string number);	//Ham nay moi sua ten do nha! (DecToBin -> DecToBinStr)
string MultiplyByTwo(string number);
void PowOfTwo(string pow[BIT_RANGE]);
string SumNumbers(string n1, string n2);
bool CheckNumber(string number);
void NormalizeNumber(string& number);

char BinToHexChar(string num);
