#include "QInt.h"

/*Calculate sum of 2 bits using half-adder algorithm
Input: first bit A, secoond bit B, carrier bit C*/
bool HalfAdder(bool A, bool B, bool& C)
{
	C = A & B;
	return A ^ B;
}

/*Calculate sum of 2 bits using full-adder algorithm
Input: first bit A, secoond bit B, previous carrier bit prevC
Output: returns sum 2 bit, remainder bit into carrier bit prevC*/
bool FullAdder(bool A, bool B, bool& prevC)
{
	bool C, newC; //carrier bits
	bool sum = HalfAdder(A, B, C); //C is now remainder bit
	sum = HalfAdder(sum, prevC, newC);
	prevC = C | newC;
	return sum;
}

//Return QInt complement two
QInt QInt::ComplementTwo()
{
	QInt complement;
	int i;
	for (i = 15;i >= 0;i--)
	{
		complement.val[i] = 255 - val[i];
	} //Complement one
	cout << endl;
	for (i = 15;i >= 0;i--)
	{
		complement.val[i] = val[i] + 1; 
		if (complement.val[i] == 0) //if overflow
			continue; 
		else
			break;
	}
	return complement;
}

//Calculate sum of 2 QInt
QInt QInt::operator +(QInt number)
{
	QInt product;
	bool carrierBit = 0;
	for (int i = 0;i < 128;i++)
	{
		bool firstBit = this->GetBit(127 - i);
		bool secondBit = number.GetBit(127 - i);
		bool newBit = FullAdder(firstBit, secondBit, carrierBit); 
		if (newBit) //if new bit is 1 then set it in value
			product.SetBit(127 - i);
	}
	return product;
}


//Calculate subtraction of 2 QInt
QInt QInt::operator -(QInt number)
{
	return (*this) + number.ComplementTwo(); //turns number into two's complement then sum
}