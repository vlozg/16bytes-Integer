#pragma once
#include <iostream>
#include <string>

#define SIZE 16
#define HEX_SIZE 32
#define BIT_RANGE 128
#define MAX_VALUE_BIT 16
#define FOUR_BIT 4
using namespace std;


string DivideByTwo(string number);
bool* DecToBinStr(string number);	
string MultiplyByTwo(string number);
void PowOfTwo(string pow[BIT_RANGE]);
string SumNumbers(string n1, string n2);
bool CheckNumber(string number);
void NormalizeNumber(string& number);
