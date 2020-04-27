#include "QInt.h"

//Lấy bit tại vị trí thứ i
bool QInt::GetBit(int pos)
{
	if (pos > 127 || pos < 0) return 0;
    char mask = 1 << (pos%8);   //Mặt nạ đánh dấu bit cần lấy
    return (value[pos/8] & mask);
}

//Set bit
// bit: bit cần set
// pos : vị trí cần set
void QInt::SetBit(int pos, bool bit)
{
    if (pos > 127) return;

    char mask = 1 << (pos%8);   //Mặt nạ đánh dấu bit cần sửa

    if (bit == 1){
        value[pos/8] |= mask;   //OR với mask để bật bit
    } else {
        value[pos/8] &= ~mask;  //Đảo mask và AND để tắt bit
    }

}

//Chuỗi Dec -> Chuỗi Bin -> QInt
void QInt::Input(string number)
{
	string bin = DecToBinStr(number);			//Chuỗi Dec number -> Chuỗi Bin bin
	for (int i = 0; i < 128; i++)
	{					
		if (bin[i] == '1')					// Set bit 1 tại vị trí i
		{
			SetBit(i, 1);
		}

	}
}

//	QInt --> chuỗi Bin --> chuỗi Dec
void QInt::Output() 
{
	string bin = "";
	string result = "0";
	QInt temp = *this;	//Biến tạm lưu dãy bit

	bool negative = GetBit(0);	//Xét bit dấu
	if (negative == true)
	{
		temp = this->ComplementTwo();	//Nếu là số âm thì khi lấy bù 2 sẽ trả lại số dương
	}

	for (int i = 0; i < 128; i++)	// QInt --> chuỗi Bin
	{
		char c = temp.GetBit(i) + '0';
		bin += c;
	}

	string pow[128] = { "" };
	PowOfTwo(pow);					//	Lập thành các lũy thừa của số 2

	for (int i = 0; i < 128; i++)	
	{
		if (bin[127 - i] == '1')
		{
			result = SumNumbers(result, pow[i]);	//	Cộng theo công thức: 2^x1 + 2^x2 + 2^x3 +...
		}
	}

	//Kết quả trả về số thập phân ở dạng chuỗi
	if (negative)
	{
		result = "-" + result;
	}
	cout << result;
}

//Chuyen day bit thanh day bool
//Neu k xai nua thi phai delete[] bool
//Lấy bit từ x -> dãy bool 128 phần tử
bool* DecToBin(QInt x)
{
	bool* bit = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		bit[i] = x.GetBit(i);	
	}
	return bit;
}

//Set các phần tử của bin vào QInt
//bin cần có 128 phần tử
QInt BinToDec(bool* bin)	
{
	QInt result;

	for (int i = 0; i < 128; i++)
	{
		if (bin[i] == 1)
		{
			result.SetBit(i, 1);
		}
	}
	return result;
}

QInt::QInt()
{
	for (int i = 0; i < 16; i++)
	{
		value[i] = 0;
	}
}

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

//	Chuỗi dec number -> chuỗi bin (128 kí tự)
string DecToBinStr(string number)	
{
	bool positive = true;
	if (number[0] == '-')
	{
		positive = false;
		number.erase(0, 1);
	}

	int last_index = number.length() - 1;
	string temp = number;	//temp lưu lại kết quả sau các phép chia 2
	string bin = "";	
	//			LÀM NHƯ CÔNG THỨC:
	//CHIA NUMBER CHO 2, LẤY SỐ DƯ THÊM VÀO PHÍA TRƯỚC KẾT QUẢ
	//THỰC HIỆN LIÊN TỤC CHO ĐẾN KHI SỐ BỊ CHIA LÀ 0
	//NẾU KẾT QUẢ CHƯA ĐỦ 128 BIT, CHÈN CÁC SỐ 0 VÀO TRƯỚC

	while (temp != "0")
	{
		last_index = temp.length() - 1;			
		int r = (temp[last_index] - '0') % 2;	//Chữ số cuối cùng chia dư cho 2 --> bit
		temp = DivideByTwo(temp);				//Chia liên tục cho 2
		char c = r + '0';
		bin = c + bin;							
	}
	for (int i = bin.length(); i < 128; i++)	//Chèn các số 0 vào trước kết quả
	{
		bin = "0" + bin;
	}

	if (positive == false)	//Nếu là số âm thì phải chuyển chuỗi bit về bù 2
	{
		for (int i = 0; i < 128; i++)	//Bù 1
		{
			if (bin[i] == '0') {
				bin[i] = '1';
			}
			else {
				bin[i] = '0';
			}
		}
		int carry = 1; //biến nhớ cộng 1 bit
		for (int i = 127; i >= 0; i--)
		{
			int s = bin[i] - '0' + carry;
			if (s > 1)
			{
				bin[i] = '0';
				carry = 1;
			}
			else if(s == 1)
			{
				bin[i] = '1';
				carry = 0;
			}
			else
			{
				bin[i] = '0';
				carry = 0;
			}
		}

	}
	return bin;
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
		complement.value[i] = 255 - value[i];
	} //Complement one
	for (i = 15; i >= 0; i--)
	{
		complement.value[i] += 1;
		if (complement.value[i] == 0) //if overflow
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
			product.SetBit(127 - i, 1);
	}
	return product;
}


//Calculate subtraction of 2 QInt
QInt QInt::operator -(QInt number)
{
	return (*this) + number.ComplementTwo(); //turns number into two's complement then sum
}

//Nhập vào số thập phân ở dạng chuỗi
void ScanQInt(QInt& x)
{
	string number;
	getline(cin, number);
	NormalizeNumber(number);	//
	if (CheckNumber(number) == false)
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

//Xuất ở dạng thập phân
void PrintQInt(QInt x)
{
	x.Output();
}
