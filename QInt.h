#pragma once
#include <iostream>
#include <string>

using namespace std;

class QInt
{
private:
	char val[16] = { 0 };
public:
	void input(string);
	void output();

	QInt();
};

bool getBit(char data, int i, int size);
void setBit(char& data, int i, int size);
string divideByTwo(string number);
string decToBin(string number);
string multiplyWithTwo(string number);
void powOfTwo(string pow[128]);
string plusNumber(string n1, string n2);
