#include "QInt.h"

bool QInt::GetBit(int i)
{
	return (val[i / 8] >> (7 - (i % 8))) & 1;
}

void QInt::SetBit(int i)
{
	val[i / 8] = val[i / 8] | (1 << (7 - (i % 8)));
}

void QInt::Input(string number)
{
	string bin = DecToBinStr(number);			//bin se la dang binary cua number
	for (int i = 0; i < 128; i++)
	{					
		if (bin[i] == '1')					// set bit 1 tai vi tri i
		{
			SetBit(i);
		}

	}
}

//	Tu QInt --> chuoi Bin --> chuoi Dec
void QInt::Output() 
{
	string bin = "";
	string result = "0";
	QInt temp = *this;	//Luu so bu 2 neu can

	bool negative = GetBit(0);
	if (negative == true)
	{
		temp = this->ComplementTwo();
	}

	for (int i = 0; i < 128; i++)	// QInt --> chuoi bin
	{
		char c = temp.GetBit(i) + '0';
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
	if (negative)
	{
		result = "-" + result;
	}
	cout << result;
}

//Chuyen day bit thanh day bool
//Neu k xai nua thi phai delete[] bool
bool* DecToBin(QInt x)
{
	bool* bit = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		bit[i] = x.GetBit(i);	//Gan bit tu QInt vao mang bit tren
	}
	return bit;
}

//Chi dung khi mang bin co du 128 phan tu
QInt BinToDec(bool* bin)	
{
	QInt result;

	for (int i = 0; i < 128; i++)
	{
		if (bin[i] == 1)
		{
			result.SetBit(i);
		}
	}
	return result;
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



void normalizeNumber(string& number)
{
	while (number[0] == '0' || number[0] == ' ')	//Delete all the '0' and the space in front of number
	{
		number = number.erase(0,1);
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

//Chia chuoi dec cho 2
string DivideByTwo(string number)	
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

//	Chuyen chuoi dec --> chuoi bin (co 128 ki tu)
string DecToBinStr(string number)	
{
	bool positive = true;
	if (number[0] == '-')
	{
		positive = false;
		number.erase(0, 1);
	}

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

	if (positive == false)	//Neu la so am thi chuyen sang bu 2
	{
		for (int i = 0; i < 128; i++)	//Bu 1
		{
			if (bin[i] == '0') {
				bin[i] = '1';
			}
			else {
				bin[i] = '0';
			}
		}
		int c = 1; //bien nho cho viec cong 1 bit
		for (int i = 127; i >= 0; i--)
		{
			int s = bin[i] - '0' + c;
			if (s > 1)
			{
				bin[i] = '0';
				c = 1;
			}
			else if(s == 1)
			{
				bin[i] = '1';
				c = 0;
			}
			else
			{
				bin[i] = '0';
				c = 0;
			}
		}

	}
	return bin;
}


//Nhan chuoi dec cho 2
string MultiplyByTwo(string number)	
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

//Luy thua cua 2
void PowOfTwo(string pow[128])	
{
	//		Ket qua se luu vao mang string pow co 128 phan tu
	//
	//		--> nen khoi tao mang nay truoc khi bat dau hay luu o ngoai file ???
	//
	//
	pow[0] = "1";
	for (int i = 1; i < 128; i++)
	{
		pow[i] = MultiplyByTwo(pow[i - 1]);	//So dang sau thi bang so dang truoc x 2
	}
}

//Cong 2 chuoi so dec (only for output)
string PlusNumber(string n1, string n2)		
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


//Tra ve True neu la so nguyen
//Tra ve False neu nguoc lai
bool checkNumber(string number)
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
	for (i = 15; i >= 0; i--)
	{
		complement.val[i] = 255 - val[i];
	} //Complement one
	for (i = 15; i >= 0; i--)
	{
		complement.val[i] += 1;
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
	for (int i = 0; i < 128; i++)
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

//Tao mang chuoi cho user nhap vao
void ScanQInt(QInt& x)
{
	string number;
	getline(cin, number);
	normalizeNumber(number);
	if (checkNumber(number) == false)
	{
		//Do something
		cout << "Khong phai so";
		return;
	}
	else
	{
		x.Input(number);
	}

}

void PrintQInt(QInt x)
{
	x.Output();
}
