#include "QInt.h"

bool QInt::GetBit(int i)
{
	return GetBitAll(val[i / 8], i % 8, 8);
}

void QInt::SetBit(int i)
{
	SetBitAll(val[i / 8], i % 8, 8);
}

void QInt::Input(string number)
{
	//getline(cin, number);

	//...
	//Check the number (not a number or negative)
	//...

	string bin = DecToBin(number);			//bin se la dang binary cua number
	for (int i = 0; i < 128; i++)
	{
		int K = i / 8;						// K la vi tri cua i trong mang val
		int k = i % 8;						// k la vi tri cua i trong phan tu val[K]
		if (bin[i] == '1')					// set bit 1 tai vi tri co bit 1, cac bit khac phai mac dinh la bit 0 truoc do
		{
			SetBitAll(val[K], k, 8);
		}

	}
}

void QInt::Output() 
{
	
	//	Tu QInt --> chuoi Bin --> chuoi Dec
	
	string bin = "";
	string result = "0";
	for (int i = 0; i < 128; i++)	// QInt --> chuoi bin
	{
		char c = GetBitAll(val[i / 8], i % 8, 8) + '0';
		bin += c;
	}

	string pow[128] = { "" };
	PowOfTwo(pow);					//	Lap thanh cac so luy thua cua 2

	//	------------------WARNING-------------------
	//	--------CHUA XU LI BIT DAU, SO BU 2 --------
	//	--------------------------------------------
	for (int i = 0; i < 128; i++)	
	{
		if (bin[127 - i] == '1')
		{
			result = PlusNumber(result, pow[i]);	//	Cong lai theo kieu 2^x1 + 2^x2 + 2^x3 + ...
		}
	}

	//	Ket qua tra ve dang chuoi o so thap phan
	cout << result;
}


bool* QInt::DecToInt()
{
	bool* bit = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		bit[i] = GetBitAll(val[i / 8], i % 8, 8);	//Gan bit tu QInt vao mang bit tren
	}
	return bit;
}

void QInt::BinToDec(bool* bin)	//Chi dung khi mang bin co du 128 phan tu
{
	for (int i = 0; i < 16; i++)	//Dem ve dang mac dinh
	{
		val[i] = 0;
	}

	for (int i = 0; i < 128; i++)
	{
		int K = i / 8;
		int k = i % 8;
		if (bin[i] == '1')
		{
			SetBitAll(val[K], k, 8);
		}

	}
}

QInt::QInt()
{
	for (int i = 0; i < 16; i++)
	{
		val[i] = 0;
	}
}

//	------------------------------------------------------
//	------------------------------------------------------
//	----------------- HAM HO TRO -------------------------
//	------------------------------------------------------
//	------------------------------------------------------

bool GetBitAll(char data, int i, int size)
{
	return (data >> (size - 1 - i)) & 1;
}

void SetBitAll(char& data, int i, int size)
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


string DivideByTwo(string number)	//Chia chuoi dec cho 2
{
	// Thuc hien nhu phep chia o cap 1

	string result = "";	//Ket qua

	string temp = "";	//Chuoi luu tung chu so dung de chia

	int q = 0;	//La thuong cua phep chia tung chu so (la 1 phan cua result)
	int len = number.length();
	int p = 0;	//La temp nhung o dang so

	//		CACH CHIA:
	//	DUA TUNG CHU SO TU TRAI SANG VAO TEMP
	//	SAU DO CHUYEN TEMP TU DANG CHUOI SANG P DANG SO
	//	DUNG P / 2 = Q, NEU CO DU THI CONG SO DU VAO TEMP O DANG CHUOI
	//	TIEP TUC CHO DEN KHI HET TAT CA CHU SO CUA SO BI CHIA

	for (int i = 0; i < len; i++)
	{
		temp += number[i];	//	Them vao tung chu so vao temp

		if (temp.length() == 1)	//Neu temp chi co 1 chu so
		{
			p = temp[0] - '0';	//	Chuyen temp thanh p o dang so
			q = p / 2;			//	q la ket qua cua phep chia
			result += q + '0';	//	dua q vao ket qua
			temp.clear();		//	Xoa temp di

			temp += (p - q * 2) + '0';	//	Dua so du con lai vao temp

			if (temp[0] == '0')	//	Neu temp van chi co 0 thi xoa luon
			{
				temp.clear();
			}
		}
		else	//	Neu temp co 2 chu so (chi khac o tren cach chuyen sang p)
		{
			p = (temp[1] - '0' + (temp[0] - '0') * 10);	//	Chuyen temp co 2 chu so sang p
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
	normalizeNumber(result);	//Co nhiem vu xoa cac so 0 o phia truoc 
	return result;
}

string DecToBin(string number)	//	Chuyen chuoi dec --> chuoi bin (co 128 ki tu)
{
	int last_index = number.length() - 1;
	string temp = number;	//temp luu ket qua cua chuoi sau cac phep chia 2
	string bin = "";	//Chuoi ket qua binary
	
	//			LAM NHU CONG THUC:
	//CHIA SO NUMBER CHO 2, LAY SO DU THEM VAO DANG TRUOC KET QUA
	//THUC HIEN LIEN TUC CHO DEN KHI SO BI CHIA LA 0
	//NEU BIN VAN CHUA DU 128 KI TU, CHEN CAC SO 0 VAO

	while (temp != "0")
	{
		last_index = temp.length() - 1;			//Trich chu so cuoi cung de xem so do chia co du hay khong
		int r = (temp[last_index] - '0') % 2;	//r se la so du (0 hoac 1)
		temp = DivideByTwo(temp);				//temp mang ket qua sau khi chia 2
		char c = r + '0';
		bin = c + bin;							//Them so du do vao truoc ket qua da co
	}
	for (int i = bin.length(); i < 128; i++)	//Chen cac so 0 vao cho du 128 bit
	{
		bin = "0" + bin;
	}
	return bin;
}




string MultiplyWithTwo(string number)	//Nhan chuoi dec cho 2
{
	string result = "";
	int number_len = number.length();
	int mem = 0;	//Bien nho

	for (int i = number_len - 1; i >= 0; i--)
	{
		int m = (number[i] - '0') * 2 + mem;	//m la ket qua cua phep nhan cua 2 voi tung chu so cua number

		mem = m / 10;	//mem se ghi nho chu so dau tien neu m >= 10

		char c = m % 10 + '0';	//c se luu chu so cuoi cung cua m duoi dang char
		result = c + result;	//dua c vao truoc chuoi ket qua da co
	}
	if (mem > 0)
	{
		//Neu van con bien nho sau khi nhan 2 cho tat chu so, them bien nho vao truoc chuoi ket qua
		result = char(mem + '0') + result;
	}
	return result;
}

void PowOfTwo(string pow[128])	//Luy thua cua 2
{
	//		Ket qua se luu vao mang string pow co 128 phan tu
	//
	//		--> nen khoi tao mang nay truoc khi bat dau hay luu o ngoai file ???
	//
	//
	pow[0] = "1";
	for (int i = 1; i < 128; i++)
	{
		pow[i] = MultiplyWithTwo(pow[i - 1]);	//So dang sau thi bang so dang truoc x 2
	}
}

string PlusNumber(string n1, string n2)		//Cong 2 chuoi so dec (only for output)
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
	
	int mem = 0;	//Cong co nho

	int i = 0, j = 0;

	for (i = small - 1, j = large - 1; i >= 0; i--, j--)
	{
		int s = (shorter[i] - '0') + (longer[j] - '0') + mem; //Lay 2 ki tu cung don vi cong voi nhau va cong them bien nho

		mem = s / 10;			//Bien nho la chu so dang truoc cua s

		char c = s % 10 + '0';	//Luu hang don vi cua s o dang char
		result = c + result;	//Them vao ket qua da co
	}
	while (j >= 0)
	{
		int s = (longer[j] - '0') + mem;	// Cong cac chu so con lai cho mem

		mem = s / 10;

		char c = s % 10 + '0';
		result = c + result;

		j--;
	}
	if (mem > 0)
	{
		result = char(mem + '0') + result;	// Them mem vao truoc chuoi neu con
	}
	return result;
}
