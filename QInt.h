#pragma once
#include <iostream>
#include <string>

using namespace std;

class QInt
{
private:
	char val[16] = { 0 };
public:
	bool GetBit(int i);
	void SetBit(int i);	//Ham chi bat bit tu 0 -> 1, muon set bit 0 thi no phai la 0 truoc do

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
string PlusNumber(string n1, string n2);
bool checkNumber(string number);
void normalizeNumber(string& number);