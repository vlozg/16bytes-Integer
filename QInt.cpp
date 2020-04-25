#include "QInt.h"

bool getBit(char data, int i, int size)
{
	return (data >> (size - 1 - i)) & 1;
}

void setBit(char& data, int i, int size)
{
	data = data | (1 << (size - 1 - i));
}

void normalizeNumber(string& number)
{
	/*
		- Detecting those are not number
		- Detecting negative number
	*/
	while (number[0] == '0')	//Delete all the '0' in front of number
	{
		number = number.erase(0,1);
	}
	if (number.empty())	//Add '0' in case the number above is just 0
	{
		number += '0';
	}
}


string divideByTwo(string number)
{
	string result = "";

	string temp = "";

	int q = 0;
	int len = number.length();
	int p = 0;

	for (int i = 0; i < len; i++)
	{
		temp += number[i];

		if (temp.length() == 1)
		{
			p = temp[0] - '0';
			q = p / 2;
			result += q + '0';
			temp.clear();

			temp += (p - q * 2) + '0';
			if (temp[0] == '0') temp.clear();
		}
		else
		{
			p = (temp[1] - '0' + (temp[0] - '0') * 10);
			q = p / 2;
			result += q + '0';
			temp.clear();

			temp += (p - q * 2) + '0';
			if (temp[0] == '0') temp.clear();
		}	
	}
	normalizeNumber(result);
	return result;
}

string decToBin(string number)
{
	int last_index = number.length() - 1;
	string temp = number;
	string bin = "";
	
	while (temp != "0")
	{
		last_index = temp.length() - 1;
		int r = (temp[last_index] - '0') % 2;
		temp = divideByTwo(temp);
		char c = r + '0';
		bin = c + bin;
	}
	for (int i = bin.length(); i < 128; i++)
	{
		bin = "0" + bin;
	}
	return bin;
}


void QInt::input(string number)
{
	//getline(cin, number);
	//...
	//Check the number
	//...
	string bin = decToBin(number);
	for (int i = 0; i < 128; i++)
	{
		int K = i / 8;
		int k = i % 8;
		if (bin[i] == '1')
		{
			setBit(val[K], k, 8);
		}
	
	}
}

void QInt::output() //just for test
{
	string result = "";
	for (int i = 0; i < 128; i++)
	{
		char c = getBit(val[i / 8], i % 8, 8) + '0';
		result += c;
	}
	normalizeNumber(result);
	cout << result;
}

QInt::QInt()
{
	for (int i = 0; i < 16; i++)
	{
		val[i] = 0;
	}
}

string multiplyWithTwo(string number)	//Nhan chuoi dec cho 2
{
	string result = "";
	int number_len = number.length();
	int mem = 0;

	for (int i = number_len - 1; i >= 0; i--)
	{
		int m = (number[i] - '0') * 2 + mem;

		mem = m / 10;

		char c = m % 10 + '0';
		result = c + result;
	}
	if (mem > 0)
	{
		result = char(mem + '0') + result;
	}
	return result;
}

void powOfTwo(string pow[128])	//Luy thua cua 2
{
	pow[0] = "1";
	for (int i = 1; i < 128; i++)
	{
		pow[i] = multiplyWithTwo(pow[i - 1]);
	}
}

string plusNumber(string n1, string n2)		//Cong 2 chuoi so dec
{
	string result = "";
	string longer = "";
	int max = 0, min = 0;
	if (n1.length() > n2.length())
	{
		min = n2.length();
		max = n1.length();
		longer = n1;
	}
	else
	{
		min = n1.length();
		max = n2.length();
		longer = n2;
	}


	int mem = 0;
	for (int i = 0; i < min; i++)
	{
		int s = (n1[i] - '0') + (n2[i] - '0') + mem;

		mem = s / 10;

		char c = s % 10 + '0';
		result = c + result;
	}
	for (int i = min; i < max; i++)
	{
		int s = (longer[i] - '0') + mem;

		mem = s / 10;

		char c = s % 10 + '0';
		result = c + result;
	}
	if (mem > 0)
	{
		result = char(mem + '0') + result;
	}
	return result;
}
