#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

#define KNUMBER 16383	// số thừa K
using namespace std;

class Qfloat
{
private:
	char value[16];
public:
	Qfloat();
	~Qfloat();
	bool GetBit(int);
	void SetBit(int, bool);
	string BinStr();
	string DecStr();
};

bool ReadDecString(string, Qfloat&);
void ScanQfloat(Qfloat&);
void PrintQfloat(Qfloat);
Qfloat BinToDecF(bool* bit);
bool* DecToBin(Qfloat x);

void ReadFileF(string input, string output);

bool CheckMinus(char first);
bool CheckNumber(char input);
bool CheckOne(string input);
bool CheckDecimalPoint(char input);
void NormalizeNumberF(string& number);
string DivideByTwoF(string number);
string DivideOne(string number);
string IntegerDecToBin(string number);
string FractionalDecToBin(string number);
string FractionalBinToDec(string bin);
string IntegerBinToDec(string bin);
string MultiplyByTwoF(string number);
string MultiplyByFive(string number);
void PowOfTwoF(string pow[128]);
void PowOfFive(string pow[128]);
void PowOfTwoMinus(string pow[128]);
string SumNumbersF(string n1, string n2);
string SumFractionals(string n1, string n2);
void DeleteExcessiveZero(string&);
void PrintBinary(bool*);
bool CheckAllChar(string, char);
bool* StringToBool(string);
Qfloat BinStrToDecF(string bin);
