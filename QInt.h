#pragma once
#include <iostream>
#include <string>

using namespace std;

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
