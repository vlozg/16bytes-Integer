#pragma once
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

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

void ScanQInt(QInt& x);
void PrintQInt(QInt x);	
bool* DecToBin(QInt x);	
QInt BinToDec(bool* bit);

char* BinToHex(bool* bit); 
char* DecToHex(QInt x); 



string DivideByTwo(string number);
string DecToBinStr(string number);	//Ham nay moi sua ten do nha! (DecToBin -> DecToBinStr)
string MultiplyByTwo(string number);
void PowOfTwo(string pow[128]);
string SumNumber(string n1, string n2);
bool CheckNumber(string number);
void NormalizeNumber(string& number);
char BinToHexChar(string num);
