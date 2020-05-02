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
	int length;
public:
	Qfloat();
	~Qfloat();
	bool GetBit(int);
	void SetBit(int, bool);
	int GetLength();
	void SetLength(int);
};

bool ReadDecString(string, Qfloat&);
void ScanQfloat(Qfloat&);
void PrintQfloat(Qfloat);
Qfloat BinToDec(bool* bit);
bool* DecToBin(Qfloat x);

void ReadFile();

bool CheckMinus(char first);
bool CheckNumber(char input);
bool CheckOne(string input);
bool CheckDecimalPoint(char input);
void NormalizeNumber(string& number);
string DivideByTwo(string number);
string DivideOne(string number);
string IntegerDecToBin(string number);
string FractionalDecToBin(string number);
string FractionalBinToDec(string bin);
string IntegerBinToDec(string bin);
string MultiplyByTwo(string number);
string MultiplyByFive(string number);
void PowOfTwo(string pow[128]);
void PowOfFive(string pow[128]);
void PowOfTwoMinus(string pow[128]);
string SumNumbers(string n1, string n2);
string SumFractionals(string n1, string n2);
void DeleteExcessiveZero(string&);
void PrintBinary(Qfloat x);
bool CheckAllChar(string, char);
bool* StringToBool(string);
