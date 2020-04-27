﻿#include "QInt.h"

//	------------------------------------------------------
//	------------------------------------------------------
//	----------------- HAM HO TRO -------------------------
//	------------------------------------------------------
//	------------------------------------------------------


//Xóa số 0 và space phía trước số thập phân
//Xóa space phía sau số thập phân
void NormalizeNumber(string& number)
{
	while (number[0] == '0' || number[0] == ' ')	//Delete all the '0' and the space in front of number
	{
		number = number.erase(0, 1);
	}
	if (number.empty())	//Add '0' in case the number above is just 0
	{
		number += '0';
	}
	while (number[number.length() - 1] == ' ')	//Delete all the space behind number
	{
		number = number.erase(number.length() - 1, 1);
	}

}

//Trả về chuỗi thập phân của number/2
string DivideByTwo(string number)
{
	// Thực hiện phép chia như cấp 1

	string result = "";

	string temp = "";	//Chuỗi dùng để trích từng số để chia

	int q = 0;	//Thương của phép chia từng số (là 1 phần của result)
	int len = number.length();
	int p = 0;	//p -> dạng int của temp

	//		CÁCH CHIA:
	//	ĐƯA TỪNG CHỮ SỐ VÀO TEMP
	//	SAU ĐỐ CHUYỂN TEMP TỪ DẠNG CHUỖI SANG P DẠNG SỐ
	//	DÙNG P / 2 = Q, NẾU CÓ DƯ THÌ CỘNG SỐ DƯ VÀO TEMP Ở DẠNG CHUỖI
	//	TIẾP TỤC CHO ĐÉN KHI HẾT TẤT CẢ CHỮ SỐ CỦA SÓ BỊ CHIA

	for (int i = 0; i < len; i++)
	{
		temp += number[i];	//	Thêm từng chữ số vào temp

		if (temp.length() == 1)
		{
			p = temp[0] - '0';
			q = p / 2;			//	q la ket qua cua phep chia
			result += q + '0';	//	dua q vao ket qua
			temp.clear();		//	Xóa temp cho đợt chia tiếp theo

			temp += (p - q * 2) + '0';	//	Nếu còn dư thì đưa vào temp

			if (temp[0] == '0')	// Nếu không dư thì xóa
			{
				temp.clear();
			}
		}
		else	//	Nếu temp có 2 chữ số
		{
			p = (temp[1] - '0' + (temp[0] - '0') * 10);	//	VD: "12" -> 12
			q = p / 2;									//	q la ket qua cua phep chia
			result += q + '0';							//	dua q vao ket qua
			temp.clear();								//	Xoa temp di

			temp += (p - q * 2) + '0';					//	Dua so du con lai vao temp
			if (temp[0] == '0')							//	Neu temp van chi co 0 thi xoa luon
			{
				temp.clear();
			}
		}
	}
	NormalizeNumber(result);	//Có nhiệm vụ xóa số 0 phía trước
	return result;
}

//	Chuỗi dec number -> mảng bin (128 phần tử)
bool* DecToBinStr(string number)
{
	bool positive = true;
	if (number[0] == '-')
	{
		positive = false;
		number.erase(0, 1);
	}

	int last_index = number.length() - 1;
	string temp = number;	//temp lưu lại kết quả sau các phép chia 2

	//			LÀM NHƯ CÔNG THỨC:
	//CHIA NUMBER CHO 2, LẤY SỐ DƯ THÊM VÀO PHÍA TRƯỚC KẾT QUẢ
	//THỰC HIỆN LIÊN TỤC CHO ĐẾN KHI SỐ BỊ CHIA LÀ 0
	//NẾU KẾT QUẢ CHƯA ĐỦ 128 BIT, CHÈN CÁC SỐ 0 VÀO TRƯỚC

	bool* result = new bool[BIT_RANGE];
	int pos = BIT_RANGE - 1;

	while (temp != "0")
	{
		last_index = temp.length() - 1;
		int r = (temp[last_index] - '0') % 2;	//Chữ số cuối cùng chia dư cho 2 --> bit
		temp = DivideByTwo(temp);				//Chia liên tục cho 2
		result[pos] = r;
		pos--;
	}
	while (pos >= 0)	//Thêm 0 vào phía trước
	{
		result[pos] = 0;
		pos--;
	}

	if (positive == false)	//Nếu là số âm thì phải chuyển chuỗi bit về bù 2
	{
		for (int i = 0; i < BIT_RANGE; i++)	//Bù 1
		{
			result[i] = 1 - result[i];
		}
		int carry = 1; //biến nhớ cộng 1 bit
		for (pos = 127; pos >= 0; pos--)		//Bù 2
		{
			int s = int(result[pos]) + carry;
			if (s > 1)
			{
				result[pos] = 0;
				carry = 1;
			}
			else if (s == 1)
			{
				result[pos] = 1;
				carry = 0;
			}
			else
			{
				result[pos] = 0;
				carry = 0;
			}
		}

	}
	return result;
}


//Chuỗi number x 2
string MultiplyByTwo(string number)
{
	string result = "";
	int number_len = number.length();
	int carry = 0;	//Bien nho

	for (int i = number_len - 1; i >= 0; i--)
	{
		int m = (number[i] - '0') * 2 + carry;	//m la ket qua cua phep nhan cua 2 voi tung chu so cua number

		carry = m / 10;	//mem se ghi nho chu so dau tien neu m >= 10

		char c = m % 10 + '0';	//c se luu chu so cuoi cung cua m duoi dang char
		result = c + result;	//dua c vao truoc chuoi ket qua da co
	}
	if (carry > 0)
	{
		//Neu van con bien nho sau khi nhan 2 cho tat chu so, them bien nho vao truoc chuoi ket qua
		result = char(carry + '0') + result;
	}
	return result;
}

//Lũy thừa của 2
void PowOfTwo(string pow[BIT_RANGE])
{
	//		Ket qua se luu vao mang string pow co 128 phan tu
	//
	//		--> nen khoi tao mang nay truoc khi bat dau hay luu o ngoai file ???
	//
	//
	pow[0] = "1";
	for (int i = 1; i < BIT_RANGE; i++)
	{
		pow[i] = MultiplyByTwo(pow[i - 1]);	//So dang sau thi bang so dang truoc x 2
	}
}

//Cộng 2 chuỗi dec --> chuỗi sum dec
string SumNumbers(string n1, string n2)
{
	string result = "";
	string longer = "", shorter = "";	//longer se luu chuoi so co nhieu chu so hon, shorter nguoc lai
	int small = 0, large = 0;	//small se luu do dai chuoi ngan hon, large luu do dai cua chuoi dai hon
	if (n1.length() > n2.length())
	{
		small = n2.length();
		large = n1.length();
		longer = n1;
		shorter = n2;
	}
	else
	{
		small = n1.length();
		large = n2.length();
		longer = n2;
		shorter = n1;
	}

	// --> Cong nhu kieu dat tinh roi tinh o cap 1 :)))

	int carry = 0;	//Cong co nho

	int i = 0, j = 0;

	for (i = small - 1, j = large - 1; i >= 0; i--, j--)
	{
		int s = (shorter[i] - '0') + (longer[j] - '0') + carry; //Lay 2 ki tu cung don vi cong voi nhau va cong them bien nho

		carry = s / 10;			//Bien nho la chu so dang truoc cua s

		char c = s % 10 + '0';	//Luu hang don vi cua s o dang char
		result = c + result;	//Them vao ket qua da co
	}
	while (j >= 0)
	{
		int s = (longer[j] - '0') + carry;	// Cong cac chu so con lai cho mem

		carry = s / 10;

		char c = s % 10 + '0';
		result = c + result;

		j--;
	}
	if (carry > 0)
	{
		result = char(carry + '0') + result;	// Them mem vao truoc chuoi neu con
	}
	return result;
}


//Tra ve True neu la so nguyen
//Tra ve False neu nguoc lai
bool CheckNumber(string number)
{
	int i = 0;
	if (number[i] == '+' || number[i] == '-')
	{
		i++;
	}

	while (i < number.length())
	{
		if (number[i] < '0' || number[i] > '9')
		{
			return 0;
		}
		i++;
	}
	return 1;
}