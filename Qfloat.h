#pragma once
#include <iostream>

using namespace std;

class Qfloat
{
private:
	char value[16];
public:
	Qfloat();
	~Qfloat();
};

void ScanQfloat(Qfloat&);
void PrintQfloat(Qfloat);
Qfloat BinToDec(bool* bit);
bool* DecToBin(Qfloat x);