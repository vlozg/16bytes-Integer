#include "QInt.h"

//Calculate sum of 2 bits using half-adder algorithm
//Input: first bit A, secoond bit B, carrier bit C
bool HalfAdder(bool A, bool B, bool& C)
{
	C = A & B;
	return A ^ B;
}

//Calculate sum of 2 bits using full-adder algorithm
//Input: first bit A, secoond bit B, previous carrier bit prevC
bool FullAdder(bool A, bool B, bool& prevC)
{
	bool C, newC; //carrier bits
	bool sum = HalfAdder(A, B, C); //C is now remainder bit
	sum = HalfAdder(sum, prevC, newC);
	prevC = C | newC;
	return sum;
}

//Calculate sum
QInt QInt::operator +(QInt number)
{
	QInt product;
	bool carrierBit = 0;
	for (int i = 0;i < 128;i++)
	{
		bool firstBit = this.getBit(127 - i);
		bool secondBit = number.getBit(127 - i);
		bool newBit = FullAdder(firstBit, secondBit, carrierBit);
		product.setBit(newBit, 127 - i);
	}
	return product;
}


//Calculate subtraction
QInt QInt::operator -(QInt number)
{
	number.Complement2(); //turns number into complement 2
	return this + number;
}