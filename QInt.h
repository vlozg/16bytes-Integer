#pragma once
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

/*
	Define của Duy
*/
#define BIT_RANGE 128
#define MAX_VALUE_BIT 16
#define FOUR_BIT 4

class QInt
{
private:
	char value[16] = { 0 };
public:
	bool GetBit(int pos);
	void SetBit(int pos, bool bit);

	void Input(string);
	void Output();

	QInt();

	QInt ComplementTwo();
	QInt operator+(QInt number);
	QInt operator-(QInt number);
	QInt operator&(QInt number);
	QInt operator|(QInt number);
	QInt operator^(QInt number);
	QInt operator~();
	QInt operator<<(int number);
	QInt operator>>(int number);

	void RotateLeft(int number);
	void RotateRight(int number);
};

void ScanQInt(QInt& x);		//Cau a
void PrintQInt(QInt x);		//Cau b
bool* DecToBin(QInt x);		//Cau c
QInt BinToDec(bool* bit);	//Cau d

char* BinToHex(bool* bit); //cau e
char* DecToHex(QInt x); // cau f



string DivideByTwo(string number);
string DecToBinStr(string number);	//Ham nay moi sua ten do nha! (DecToBin -> DecToBinStr)
string MultiplyByTwo(string number);
void PowOfTwo(string pow[128]);
string SumNumber(string n1, string n2);
bool checkNumber(string number);
void normalizeNumber(string& number);
char BinToHexChar(string num);
