#include "QInt.h"

/*Tổng 2 bit dùng half adder
Input: bit A, bit B, bit nhớ C*/
bool HalfAdder(bool A, bool B, bool& C)
{
	C = A & B;
	return A ^ B;
}

/*Tính tổng 2 bit dùng full-adder
Input: bit A, bit B, carrier bit prevC
Output: trả về tổng 2 bit, bit nhớ được đưa vào prevC*/
bool FullAdder(bool A, bool B, bool& prevC)
{
	bool C, newC; //các bit nhớ
	bool sum = HalfAdder(A, B, C); //C bit nhớ
	sum = HalfAdder(sum, prevC, newC);
	prevC = C | newC;
	return sum;
}


//Output: dạng bù 2 của QInt
QInt QInt::ComplementTwo()
{
	QInt complement;
	int i;
	for (i = SIZE - 1;i >= 0;i--)
	{
		complement.val[i] = 255 - val[i];
		//chuyển thành số bù 1: 
		//255 - 1 số 8 bit sẽ ra số nhị phân có các bit đảo ngược của số đó
	}
	cout << endl;
	for (i = SIZE - 1;i >= 0;i--)
	{
		complement.val[i] += 1; //+1 tuần tự vào từng block
		if (complement.val[i] == 0) //nếu tràn số thì tiếp tục +1 vào block kế tiếp
			continue;
		else
			break;
	}
	return complement;
}

QInt QInt::operator +(QInt number)
{
	QInt product;
	bool carrierBit = 0;
	for (int i = 0;i < BIT_RANGE;i++)
	{
		bool firstBit = this->GetBit(BIT_RANGE - i - 1);
		bool secondBit = number.GetBit(BIT_RANGE - i - 1);
		bool newBit = FullAdder(firstBit, secondBit, carrierBit);
		if (newBit) //nếu bit 1 thì set bit
			product.SetBit(BIT_RANGE - i - 1);
	}
	return product;
}

QInt QInt::operator -(QInt number)
{
	return (*this) + number.ComplementTwo(); //chuyển number về dạng bù 2 rồi cộng
}

QInt QInt::operator=(const QInt& number)
{
	if (this == &number) //nếu gán cho chính nó
		return *this;
	for (int i = 0;i < SIZE;i++) //copy giá trị
	{
		this->val[i] = number.val[i];
	}
	return *this;
}

bool QInt::operator<(const QInt& number)
{
	QInt A = *this, B = number; //biến tạm để so sánh
	bool negative1 = A.IsNegative();
	bool negative2 = B.IsNegative();
	if (negative1 && !negative2) //số hiện tại âm, số number dương
		return true;
	if (!negative1 && negative2) //số hiện tại dương, số number âm
		return false;
	
	if (negative1 && negative2) //cả 2 số cùng âm
	{
		A = A.ComplementTwo();
		B = B.ComplementTwo();
	}

	int msb1 = A.MostSignificantBit(); //most significant bit(msb) của số hiện tại
	int msb2 = B.MostSignificantBit(); //most significant bit(msb) của number

	if (msb1 > msb2) //nếu số hiện tại < number 
	{
		if (!negative1) //nếu cả 2 số dương
			return true;
		else
			return false;
	}
	else if (msb1 < msb2)
	{
		if (!negative1) //nếu cả 2 số dương
			return false;
		else
			return true;
	}
	else
	{
		for (int i = msb1;i < BIT_RANGE;i++)
		{
			//nếu bit tại vị trí i của số này = 1 còn number = 0
			if (A.GetBit(i) && !B.GetBit(i))
			{
				if (!negative1) //nếu cả 2 số dương
					return false;
				else
					return true;
			}
			//ngược lại
			else if (!A.GetBit(i) && B.GetBit(i))
			{
				if (!negative1) //nếu cả 2 số dương
					return true;
				else
					return false;
			}
		}
	}
	return false;
}

bool QInt::operator<=(const QInt& number)
{
	return true;
}

bool QInt::operator>(const QInt& number)
{
	return true;
}

bool QInt::operator>=(const QInt& number)
{
	return true;
}

bool QInt::operator==(const QInt& number)
{
	for (int i = 0;i < SIZE;i++)
	{
		if (val[i] != number.val[i])
			return false;
	}
	return true;
}

/*Hàm kiểm tra số âm.
Output: là số âm thì True, ngược lại False
*/
bool QInt::IsNegative()
{
	return this->GetBit(0);
}


/*
Hàm trả về vị trí bit có giá trị lớn nhất.
*/
int QInt::MostSignificantBit()
{
	for (int i = 0;i < SIZE;i++)
	{
		if (val[i] != 0)
		{
			int j;
			if (i == 0)
				j = 1;
			else
				j = 0; //nếu block 0 thì check từ bit 1, còn lại thì check từ bit 0
			for (;j < 8;j++)
			{
				if (this->GetBit(i * 8 + j)) //trả về vị trí bit 1 đầu tiên
					return i;
			}
		}
	}
	return 0; //số 0
}