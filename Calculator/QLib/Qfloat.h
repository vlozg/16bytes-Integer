#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

class Qfloat
{
private:
	char value[16] = {0};
public:
	void SetBit(int pos, bool bit);
	bool GetBit(int pos);
};

void ScanQfloat(Qfloat&);
void PrintQfloat(Qfloat);
Qfloat BinToDecF(bool* bit);
bool* DecToBin(Qfloat x);