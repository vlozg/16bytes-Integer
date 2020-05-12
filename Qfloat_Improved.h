/*

Qfloat_Improved.h là thư viện khai báo kiểu dữ liệu số thực 128bit

và chứa các hàm/phương thức/toán tử phục vụ cho việc cài đặt Qfloat

Đây là phiên bản thứ 2 của Qfloat, cải tiến hơn về thuật toán

giúp sử dụng tiết kiệm bộ nhớ, và tăng tốc độ xử lý

Chú ý khi sử dụng tránh dùng cùng lúc với Qfloat.h là phiên bản 1

*/

#ifndef _QFLOAT_H_
#define _QFLOAT_H_
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

#ifndef SIZE
#define SIZE 16
#endif

#ifndef HEX_SIZE
#define HEX_SIZE 32
#endif

#ifndef BIT_RANGE
#define BIT_RANGE 128
#endif

#ifndef MAX_VALUE_BIT
#define MAX_VALUE_BIT 16
#endif

#ifndef FOUR_BIT
#define FOUR_BIT 4
#endif

#define KNUMBER 16383 // Số thừa K
#define EXPONENT_BIT 15	// Số bit mũ
#define SIGNIFICANT_BIT 112	// Số bit định trị
using namespace std;

class Qfloat
{
private:
	char value[16];

public:
	Qfloat();
	Qfloat(const Qfloat& src);
	Qfloat(const string& src);	//Note done
	~Qfloat();

	bool GetBit(int pos) const;
	void SetBit(int pos, bool bit);
	void SetBit(bool bit);

	const Qfloat Negate() const;
	bool IsNegative() const;

	bool IsZero() const;
	bool IsNaN() const;
	bool IsInfinity() const;
	bool IsNumber() const;

	const Qfloat operator+(const Qfloat& src) const;
	const Qfloat operator-(const Qfloat& src) const;
	const Qfloat operator*(const Qfloat& src) const;//
	const Qfloat operator/(const Qfloat& src) const;//
	const Qfloat operator%(const Qfloat& src) const;//

	const Qfloat operator&(const Qfloat& src) const;
	const Qfloat operator|(const Qfloat& src) const;
	const Qfloat operator^(const Qfloat& src) const;
	const Qfloat operator~() const;
	const Qfloat operator>>(const int& number) const;
	const Qfloat operator<<(const int& number) const;
	const Qfloat RotateLeft(int number) const;
	const Qfloat RotateRight(int number) const;

	Qfloat& operator=(const Qfloat&);
	Qfloat& operator=(const string& number);

	bool operator<(const Qfloat& src) const;
	bool operator>(const Qfloat& src) const;
	bool operator<=(const Qfloat& src) const;
	bool operator>=(const Qfloat& src) const;
	bool operator==(const Qfloat& src) const;

	string BinStr() const;//
	string DecStr() const;//
};

namespace qfloat
{
bool ReadDecString(string, Qfloat &);
void ScanQfloat(Qfloat &);
void PrintQfloat(Qfloat);
Qfloat BinToDec(bool *bit);
bool *DecToBin(Qfloat x);

bool CheckMinus(char first);
bool CheckNumber(char input);
bool CheckOne(string input);
bool CheckDecimalPoint(char input);
void NormalizeNumber(string &number);
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
void DeleteExcessiveZero(string &);
bool CheckAllChar(string, char);
bool *StringToBool(string);

Qfloat BinStrToDec(string bin);

void PrintBinary(bool *);
} // namespace qfloat

#endif