#include <iostream>
#include <string>

using namespace std;

bool bit[128] = { 0,1,0,1,0,1,0,0, 0,1,1,0, 1,0,0,0, 0,1,1,0, 0,0,0,1, 0,1,1,1, 0,1,0,0,
0,1,0,1, 0,1,0,0, 0,1,1,0, 1,0,0,0, 0,1,1,0, 0,0,0,1, 0,1,1,1, 0,1,0,0,
0,1,0,1, 0,1,0,0, 0,1,1,0, 1,0,0,0, 0,1,1,0, 0,0,0,1, 0,1,1,1, 0,1,0,0, 
0,1,0,1,0,1,0,0, 0,1,1,0, 1,0,0,0, 0,1,1,0, 0,0,0,1, 0,1,1,1, 0,1,0,0, };

bool getBit(char data, int i, int size)
{
	return (data >> (size - 1 - i)) & 1;
}

void setBit(char& data, int i, int size)
{
	data = data | (1 << (size - 1 - i));
}

void NormalizeNumber(string& number)
{
	/*
		- Detecting those are not number
		- Detecting negative number
	*/
	while (number[0] == '0')	//Delete all the '0' in front of number
	{
		number = number.erase(0, 1);
	}
	if (number.empty())	//Add '0' in case the number above is just 0
	{
		number += '0';
	}
}

char BinToHexChar(string num) {
	if (num == "0000") return '0';
	if (num == "0001") return '1';
	if (num == "0010") return '2';
	if (num == "0011") return '3';
	if (num == "0100") return '4';
	if (num == "0101") return '5';
	if (num == "0110") return '6';
	if (num == "0111") return '7';
	if (num == "1000") return '8';
	if (num == "1001") return '9';
	if (num == "1010") return 'A';
	if (num == "1011") return 'B';
	if (num == "1100") return 'C';
	if (num == "1101") return 'D';
	if (num == "1110") return 'E';
	if (num == "1111") return 'F';
	return '\0';
}

string DivideByTwo(string number)
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
	NormalizeNumber(result);
	return result;
}

string DecToBin(string number)
{
	int last_index = number.length() - 1;
	string temp = number;
	string bin = "";

	while (temp != "0")
	{
		last_index = temp.length() - 1;
		int r = (temp[last_index] - '0') % 2;
		temp = DivideByTwo(temp);
		char c = r + '0';
		bin = c + bin;
	}
	for (int i = bin.length(); i < 128; i++)
	{
		bin = "0" + bin;
	}
	return bin;
}


#define BIT_RANGE 128
#define FOUR_BIT 4

class QInt {
private:
	char value[16];
public:
	//hàm chuyển đổi từ mảng binary sang mảng hex
	char* BinToHex(bool* bit) {
		string hexString = "";
		string subString = ""; // khởi tạo sub string để hỗ trợ trong việc chuyển đổi 
		char hexCode; // hex code cho mỗi 4 bit

		int fourBitCount = FOUR_BIT; // biến đếm 4 bit 1 lần 

		//cứ mỗi 4 bit kế tiếp nhau ta đổi nó qua hệ 16
		for (int i = 0; i < BIT_RANGE; i++) {
			
			//chưa đủ 4 bit thì gán thêm vào substring
			subString += char(bit[i] + '0');
			fourBitCount--;
			// đủ 4 bit thì chuyển qua Hex
			if (fourBitCount == 0){
				fourBitCount = FOUR_BIT;
				hexCode = BinToHexChar(subString);
				hexString += hexCode;
				subString = "";
			}
		}
		char *result = new char[hexString.length() + 1];
		strcpy(result, hexString.c_str());
		return result;
	};

	char* DecToHex(QInt x) {

	}
};

int main() {
	QInt a;
	for (int i = 0; i < 128; i++) {
		cout << bit[i];
	}
	cout << endl;
	cout << a.BinToHex(bit) << endl;
	system("pause");

}