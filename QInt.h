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
	QInt operator+(QInt);
	QInt operator-(QInt);
	QInt operator*(QInt);
	QInt operator/(QInt);

	QInt operator=(const QInt&);
	bool operator<(const QInt&);
	bool operator>(const QInt&);
	bool operator<=(const QInt&);
	bool operator>=(const QInt&);
	bool operator==(const QInt&);

	QInt operator>>(int number);
	QInt operator<<(int number);


	bool IsNegative();
	int MostSignificantBit();

	QInt();
	QInt(string);
};


void ScanQInt(QInt& x);		//Cau a
void PrintQInt(QInt x);		//Cau b
bool* DecToBin(QInt x);		//Cau c
QInt BinToDec(bool* bit);	//Cau d



string DivideByTwo(string number);
string DecToBinStr(string number);	//Ham nay moi sua ten do nha! (DecToBin -> DecToBinStr)
string MultiplyByTwo(string number);
void PowOfTwo(string pow[128]);
string SumNumbers(string n1, string n2);
bool CheckNumber(string number);
void NormalizeNumber(string& number);

