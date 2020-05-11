#include "QInt.h"

using namespace qint;

/*
Lấy giá trị bit tại vị trí bất kì
Parameter:
- pos: vị trí bit cần lấy
*/
bool QInt::GetBit(int pos) {
	if (pos > 127 || pos < 0) return 0;
	char mask = 1 << (pos % 8);   //Mặt nạ đánh dấu bit cần lấy
	return (value[pos / 8] & mask);
}


/*
Set bit tại vị trí bất kì
Parameter:
- pos: vị trí set
- bit: giá trị set
*/
void QInt::SetBit(int pos, bool bit) {
	if (pos > 127) return;

	char mask = 1 << (pos % 8);   //Mặt nạ đánh dấu bit cần sửa

	if (bit == 1) {
		value[pos / 8] |= mask;   //OR với mask để bật bit
	}
	else {
		value[pos / 8] &= ~mask;  //Đảo mask và AND để tắt bit
	}
}

//Chuỗi Dec -> Chuỗi Bin -> QInt
void QInt::Input(string number)
{
	bool* bin = DecToBinStr(number);			//Chuỗi Dec number -> Chuỗi Bin bin
	for (int i = 0; i < BIT_RANGE; i++)
	{					
		SetBit(i, bin[i]);

	}
}

//	QInt --> mảng Bin --> chuỗi Dec
void QInt::Output() 
{
	bool *bin = new bool[BIT_RANGE];
	string result = "0";
	QInt temp = *this;	//Biến tạm lưu dãy bit (để không làm thay đổi *this) 

	bool negative = GetBit(0);	//Xét bit dấu
	if (negative == true)
	{
		temp = this->ComplementTwo();	//Nếu là số âm thì khi lấy bù 2 sẽ trả lại số dương
	}

	for (int i = 0; i < BIT_RANGE; i++)	// QInt --> mảng Bin
	{
		bin[i] = temp.GetBit(i);
	}

	string pow[BIT_RANGE] = { "" };
	PowOfTwo(pow);					//	Lập thành các lũy thừa của số 2

	for (int i = 0; i < BIT_RANGE; i++)	
	{
		if (bin[BIT_RANGE - 1 - i])
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


QInt::QInt()
{
	for (int i = 0; i < SIZE; i++)
	{
		value[i] = 0;
	}
}

QInt::QInt(string number)
{
	this->Input(number);
}

//Nhập vào số thập phân ở dạng chuỗi
//Nếu có lỗi thì x vẫn giữ nguyên giá trị trước đó
void qint::ScanQInt(QInt& x)
{
	string number;
	getline(cin, number);
	NormalizeNumber(number);	//
	if (CheckNumber(number) == false)
	{
		//Do something
		cout << "Khong phai so hoac tran so!";
		return;
	}
	else
	{
		x.Input(number);
	}

}

//Xuất ở dạng thập phân
void qint::PrintQInt(QInt x)
{
	x.Output();
}

//Hàm dịch phải n bit 
QInt QInt::operator>>(int number) {
	if (number <= 0) return *this;
	else {
		if (number > BIT_RANGE) {
			number = BIT_RANGE;
		}
		bool FirstBit = (*this).GetBit(BIT_RANGE - 1);
		QInt res;
		for (int i = BIT_RANGE; i >= number; i--)
			res.SetBit(i, (*this).GetBit(i - number));
		for (int i = number - 1; i >= 0; i--)
			res.SetBit(i, 0);

		return res;
	}
}

QInt QInt::operator>>(QInt number) 
{
	//Nếu number lớn hơn 127 thì kết quả luôn là 0
	if (number >= QInt("128"))
	{
		return QInt("0");
	}

	QInt res = *this >> number.ModBy128();
	return res;
}

// Hàm dịch trái n bit
QInt QInt::operator<<(int number) {
	if (number <= 0) return *this;
	else
	{
		if (number > BIT_RANGE) {
			number = BIT_RANGE;
		}
		QInt res;
		//gán vị trí đầu tiên theo vị trí từ number
		for (int i = 0; i < BIT_RANGE - number; i++)
		{
			res.SetBit(i, (*this).GetBit(i + number));
			/*print(res, i, (*this).GetBit(i + number));
			if (i == 111)
				continue;*/
		}
		for (int i = BIT_RANGE - number; i <= BIT_RANGE; i++)
			res.SetBit(i, 0);
		
		return res;
	}
}

QInt QInt::operator<<(QInt number) {
	//Nếu number lớn hơn 127 thì kết quả luôn là 0
	if (number >= QInt("128"))
	{
		return QInt("0");
	}
	
	QInt res = *this << number.ModBy128();
	return res;
}


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
	for (i = SIZE - 1; i >= 0; i--)
	{
		complement.value[i] = 255 - value[i];
		//chuyển thành số bù 1: 
		//255 - 1 số 8 bit sẽ ra số nhị phân có các bit đảo ngược của số đó
	}
	complement = complement + QInt("1");
	return complement;
}

QInt QInt::operator +(QInt number)
{
	QInt product;
	bool carrierBit = 0;
	for (int i = 0; i < BIT_RANGE; i++)
	{
		bool firstBit = this->GetBit(BIT_RANGE - i - 1);
		bool secondBit = number.GetBit(BIT_RANGE - i - 1);
		bool newBit = FullAdder(firstBit, secondBit, carrierBit);
		product.SetBit(BIT_RANGE - i - 1, newBit);
	}
	return product;
}

QInt QInt::operator -(QInt number)
{
	return (*this) + number.ComplementTwo(); //chuyển number về dạng bù 2 rồi cộng
}

//Phép nhân 2 số dương
QInt Multiplication(QInt A, QInt B)
{
	QInt result;
	for (int i = BIT_RANGE - 1; i >= 1; i--)
	{
		if (B.GetBit(i) == 1)
		{
			result = result + (A << (BIT_RANGE - 1 - i));
		}
	}
	return result;
}


QInt QInt::operator *(QInt number)
{
	QInt result; //kết quả
	QInt A = *this, B = number; //biến tạm
	bool negative1 = A.IsNegative();
	bool negative2 = B.IsNegative();
	//chuyển 2 số về dương
	if (negative1)
		A = A.ComplementTwo();
	if (negative2)
		B = B.ComplementTwo();
	/*lấy số lớn hơn làm toán hạng thứ nhất
	choice = false: *this làm toán hạng 1
	choice = true: number làm toán hạng 1*/
	bool choice = false;
	if (number > * this)
		choice = true;
	if (choice)
		result = Multiplication(B, A);
	else
		result = Multiplication(A, B);

	if (negative1 ^ negative2) //2 số trái dấu
		result = result.ComplementTwo();

	return result;
}


QInt QInt::operator/(QInt number)
{
	if (number == QInt("0"))
		return QInt("0");	//Chia cho 0
	QInt divisor = *this;
	bool negative1 = divisor.IsNegative();
	bool negative2 = number.IsNegative();
	//chuyển 2 số về dương
	if (negative1)
		divisor = divisor.ComplementTwo();
	if (negative2)
		number = number.ComplementTwo();

	QInt remainder("0"); //kết quả là số dư
	for (int i = 0; i < BIT_RANGE; i++)
	{
		//Đưa 1 số hạng xuống xét
		remainder = remainder << 1;
		remainder.SetBit(BIT_RANGE - 1, divisor.GetBit(0));
		divisor = divisor << 1;

		//Lấy những số hạng đang xét trừ cho số bị chia
		remainder = remainder - number;

		if (remainder.IsNegative())
		{
			//Nếu số hạng đang xét không đủ lớn thì bỏ qua
			remainder = remainder + number;
		}
		else
		{
			//Nếu đúng thì tăng số hạng của kết quả tại vị trí chia lên 1
			divisor.SetBit(BIT_RANGE - 1, 1);
		}
		
	}

	if (negative1 ^ negative2) //2 số trái dấu
		divisor = divisor.ComplementTwo();

	return divisor;
}

QInt QInt::operator%(QInt number)
{
	if (number == QInt("0"))
		return QInt("0");	//Chia cho 0
	QInt divisor = *this;
	bool negative1 = divisor.IsNegative();
	bool negative2 = number.IsNegative();
	//chuyển 2 số về dương
	if (negative1)
		divisor = divisor.ComplementTwo();
	if (negative2)
		number = number.ComplementTwo();

	QInt remainder("0"); //kết quả là số dư
	for (int i = 0; i < BIT_RANGE; i++)
	{
		//Đưa 1 số hạng xuống xét
		remainder = remainder << 1;
		remainder.SetBit(BIT_RANGE - 1, divisor.GetBit(0));
		divisor = divisor << 1;

		//Lấy những số hạng đang xét trừ cho số bị chia
		remainder = remainder - number;

		if (remainder.IsNegative())
		{
			//Nếu số hạng đang xét không đủ lớn thì bỏ qua
			remainder = remainder + number;
		}
		else
		{
			//Nếu đúng thì tăng số hạng của kết quả tại vị trí chia lên 1
			divisor.SetBit(BIT_RANGE - 1, 1);
		}
		
	}

	if (negative1) //Nếu số bị chia âm thì số dư âm
		remainder = remainder.ComplementTwo();

	return remainder;
}

QInt QInt::operator=(const QInt& number)
{
	if (this == &number) //nếu gán cho chính nó
		return *this;
	for (int i = 0; i < SIZE; i++) //copy giá trị
	{
		this->value[i] = number.value[i];
	}
	return *this;
}

QInt QInt::operator =(string number)
{
	(*this).Input(number);
	return *this;
}

/*
================================
		CÁC TOÁN TỬ SO SÁNH
=================================
*/

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

	
	for (int i = 1; i < BIT_RANGE; i++)
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
	return false;
}

bool QInt::operator<=(const QInt& number)
{
	return (*this == number || *this < number);
}

bool QInt::operator>(const QInt& number)
{
	QInt A = *this, B = number; //biến tạm để so sánh
	bool negative1 = A.IsNegative();
	bool negative2 = B.IsNegative();
	if (negative1 && !negative2) //số hiện tại âm, số number dương
		return false;
	if (!negative1 && negative2) //số hiện tại dương, số number âm
		return true;

	if (negative1 && negative2) //cả 2 số cùng âm
	{
		A = A.ComplementTwo();
		B = B.ComplementTwo();
	}

	for (int i = 1; i < BIT_RANGE; i++)
	{
		//nếu bit tại vị trí i của số này = 1 còn number = 0
		if (A.GetBit(i) && !B.GetBit(i))
		{
			if (!negative1) //nếu cả 2 số dương
				return true;
			else
				return false;
		}
		//ngược lại
		else if (!A.GetBit(i) && B.GetBit(i))
		{
			if (!negative1) //nếu cả 2 số dương
				return false;
			else
				return true;
		}
	}
	return false;
}

bool QInt::operator>=(const QInt& number)
{
	return (*this == number || *this > number);
}

bool QInt::operator==(const QInt& number)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (value[i] != number.value[i])
			return false;
	}
	return true;
}

/*
================================
	CÁC TOÁN TỬ BITWISE
=================================
*/


/*
	Xoay trái n bit bằng cách dịch n bit sang trái và lưu các bit bị văng ra khỏi
	mảng rồi gán lại vào sau
*/
QInt QInt::RotateLeft(int number) {
	QInt res = *this;
	//xét nhưng TH không cần xoay
	if (number <= 0 && number >= BIT_RANGE - 1) {
		return *this;
	}
	else {
		bool* tempBit = new bool[number]; // mảng chứa các bit bị dịch ra khỏi mảng
		for (int i = 0; i < number; i++) {
			tempBit[i] = (res).GetBit(i);
		}
		// dịch trái number bit
		res = res << number;
		//gán lại bit đã lưu ra phía sau
		int j = 0;
		for (int i = BIT_RANGE - number; i < BIT_RANGE; i++) {
			res.SetBit(i, tempBit[j]);
			j++;
		}

	}
	return res;
}

QInt QInt::RotateLeft(QInt number) {
	QInt res = this->RotateLeft(number.ModBy128());
	return res;
}

/*
	Xoay phải n bit cách làm như trên
*/
QInt QInt::RotateRight(int number) {
	QInt res = *this;
	//xét nhưng TH không cần xoay
	if (number <= 0 && number >= BIT_RANGE - 1) {
		return *this;
	}
	else {
		bool* tempBit = new bool[number]; // mảng chứa các bit bị dịch ra khỏi mảng
		int j = 0;
		for (int i = BIT_RANGE - number; i < BIT_RANGE; i++) {
			tempBit[j] = res.GetBit(i);
			j++;
		}
		// dịch phải number bit
		res = res >> number;
		//gán lại bit đã lưu ra phía trước
		j = 0;
		for (int i = 0; i < number; i++) {
			res.SetBit(i, tempBit[j]);
			j++;
		}
	}
	return res;
}

QInt QInt::RotateRight(QInt number) {
	QInt res = this->RotateRight(number.ModBy128());
	return res;
}

//Hàm trả về kết quả khi 2 kiểu dữ liệu QInt & nhau
QInt QInt::operator &(QInt number) {
	QInt result; // kết quả trả về

	for (int i = 0; i < MAX_VALUE_BIT; i++) {
		// res là kết quả của phép & giữa 2 QInt
		result.value[i] = (*this).value[i] & number.value[i];
	}

	return result;
}

//Hàm trả về kết quả khi 2 kiểu dữ liệu QInt | nhau
QInt QInt::operator |(QInt number) {
	QInt result; // kết quả trả về

	for (int i = 0; i < MAX_VALUE_BIT; i++) {
		// res là kết quả của phép | giữa 2 bit
		result.value[i] = (*this).value[i] | number.value[i];
	}

	return result;
}

//Hàm trả về kết quả khi 2 kiểu dữ liệu QInt ^ nhau
QInt QInt::operator ^(QInt number) {
	QInt result; // kết quả trả về

	for (int i = 0; i < MAX_VALUE_BIT; i++) {
		// res là kết quả của phép ^ giữa 2 QInt
		result.value[i] = (*this).value[i] ^ number.value[i];
	}

	return result;
}

//Hàm trả về kết quả khi 2 kiểu dữ liệu QInt ~ nhau
QInt QInt::operator ~() {
	QInt result; // kết quả trả về

	for (int i = 0; i < MAX_VALUE_BIT; i++) {
		// res là kết quả của phép ~ giữa 2 QInt
		result.value[i] = ~(*this).value[i];
	}

	return result;
}

/*
================================
		CÁC HÀM BỔ TRỢ
=================================
*/


/*Hàm kiểm tra số âm.
Output: là số âm thì True, ngược lại False*/
bool QInt::IsNegative()
{
	return this->GetBit(0);
}

//Hàm trả về kết quả int của số QInt khi mod với 128
//Hỗ trợ dùng trong toán tử shift bit giữa 2 số QInt
int QInt::ModBy128()
{
	QInt remainder = *this % QInt("128");	//Lấy số dư
	int result = 0;

	//Đổi về số dương
	bool isNegative = remainder.IsNegative();
	if (isNegative)
		remainder = remainder.ComplementTwo();

	//Áp dụng công thức số hạng tổng quát
	for (int i = 0; i < 9; i++)
	{
		if (remainder.GetBit(BIT_RANGE - 1 - i))
			result += pow(2,i);
	}
	
	if (isNegative) result *= -1;	//Nếu số âm thì trả kết quả âm

	return result;
}

/*
====================================
		HỖ TRỢ GIAO DIỆN
====================================
*/

//Chuyển về chuỗi thập phân (phục vụ in ra màn hình)
string QInt::DecStr()
{
	bool* bin = new bool[BIT_RANGE];
	string result = "0";
	QInt temp = *this;	//Biến tạm lưu dãy bit (để không làm thay đổi *this) 

	bool negative = GetBit(0);	//Xét bit dấu
	if (negative == true)
	{
		temp = this->ComplementTwo();	//Nếu là số âm thì khi lấy bù 2 sẽ trả lại số dương
	}

	for (int i = 0; i < BIT_RANGE; i++)	// QInt --> mảng Bin
	{
		bin[i] = temp.GetBit(i);
	}

	string pow[BIT_RANGE] = { "" };
	PowOfTwo(pow);					//	Lập thành các lũy thừa của số 2

	for (int i = 0; i < BIT_RANGE; i++)
	{
		if (bin[BIT_RANGE - 1 - i])
		{
			result = SumNumbers(result, pow[i]);	//	Cộng theo công thức: 2^x1 + 2^x2 + 2^x3 +...
		}
	}

	//Kết quả trả về số thập phân ở dạng chuỗi
	if (negative)
	{
		result = "-" + result;
	}
	return result;
}

//Chuyển về chuỗi thập lục phân (phục vụ in ra màn hình)
string QInt::HexStr()
{
	char* hex = DecToHex(*this);
	string result = "";
	bool flag = false;
	for (int i = 0; i < strlen(hex); i++)
	{
		if (flag == false && hex[i] == '0')
		{
			continue;
		}
		else
		{
			flag = true;
		}
		result += hex[i];
	}
	if (result == "") result = "0";
	return result;
}

//Chuyển về chuỗi nhị phân (phục vụ in ra màn hình)
string QInt::BinStr()
{
	bool* bin = DecToBin(*this);
	string result = "";
	bool flag = false; //flag để xóa số 0 đầu
	for (int i = 0; i < BIT_RANGE; i++)
	{
		if (bin[i] == 0 && flag == false)
			continue;
		if (bin[i])
			flag = true;
		result += (bin[i] + '0');
	}
	if (result == "") result = "0";
	return result;
}

QInt qint::BinStrToDec(string binStr){
	bool bin[128] = {0};
	for (int i = binStr.length() - 1, j = BIT_RANGE -1; i >=0; i--, j--)
	{
		if (binStr[i] == '1') 
			bin[j] = 1;
		else if (binStr[i] != '0')
			return QInt("0");	//Xuất hiện ký tự lạ -> nhập thất bại
	}
	return BinToDec(bin);
}

//	------------------------------------------------------
//	------------------------------------------------------
//	----------------- HAM HO TRO -------------------------
//	------------------------------------------------------
//	------------------------------------------------------


//Xóa số 0 và space phía trước số thập phân
//Xóa space phía sau số thập phân
void qint::NormalizeNumber(string& number)
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
string qint::DivideByTwo(string number)
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
bool* qint::DecToBinStr(string number)
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

	while (temp != "0" && pos >= 0)				//pos >= 0 tránh stackoverflow
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
string qint::MultiplyByTwo(string number)
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
void qint::PowOfTwo(string pow[BIT_RANGE])
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
string qint::SumNumbers(string n1, string n2)
{
	string result = "";
	string longer = "", shorter = "";	//longer se luu chuoi so co nhieu chu so hon, shorter nguoc lai
	int smallLen = 0, largeLen = 0;	//smallLen se luu do dai chuoi ngan hon, largeLen luu do dai cua chuoi dai hon
	if (n1.length() > n2.length())
	{
		smallLen = n2.length();
		largeLen = n1.length();
		longer = n1;
		shorter = n2;
	}
	else
	{
		smallLen = n1.length();
		largeLen = n2.length();
		longer = n2;
		shorter = n1;
	}

	// --> Cong nhu kieu dat tinh roi tinh o cap 1 :)))

	int carry = 0;	//Cong co nho

	int i = 0, j = 0;

	for (i = smallLen - 1, j = largeLen - 1; i >= 0; i--, j--)
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
bool qint::CheckNumber(string number)
{
	int i = 0;
	if (number[i] == '+' || number[i] == '-')
	{
		i++;
	}

	int len = number.length();	//Chặn người dùng nhập quá nhiều (40 kí tự trở lên)

	//Chỉ khi nhập nhiều kí tự mới phát hiện được
	//Nếu nhập số MAX + 1 or MIN - 1 hoặc số có cùng số chữ số thì vẫn chạy (nhưng k có lỗi)
	if (len - i >= 40)
	{
		return false;
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


/*
	Hàm chuyển đổi 4bit binary -> kí tự hex
*/
char qint::BinToHexChar(string num) {
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

string qint::HexToBinChar(char hex) {
	if (hex == '0') return "0000";
	if (hex == '1') return "0001";
	if (hex == '2') return "0010";
	if (hex == '3') return "0011";
	if (hex == '4') return "0100";
	if (hex == '5') return "0101";
	if (hex == '6') return "0110";
	if (hex == '7') return "0111";
	if (hex == '8') return "1000";
	if (hex == '9') return "1001";
	if (hex == 'A') return "1010";
	if (hex == 'B') return "1011";
	if (hex == 'C') return "1100";
	if (hex == 'D') return "1101";
	if (hex == 'E') return "1110";
	if (hex == 'F') return "1111";
	return "\0";
}


/*
	Hàm chuyển đổi chuỗi bool* dạng binary -> chuỗi char* dạng hex

*/
char* qint::BinToHex(bool* bit) {
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
		if (fourBitCount == 0) {
			fourBitCount = FOUR_BIT;
			hexCode = BinToHexChar(subString);
			hexString += hexCode;
			subString = "";
		}
	}
	char* result = new char[hexString.length() + 1];
	strcpy(result, hexString.c_str());
	return result;
};

/*
	Hàm chuyển đổi từ QInt Dec -> Char *hex
*/
char* qint::DecToHex(QInt x) {
	bool* binConvert = DecToBin(x);
	return BinToHex(binConvert);
}


//Chuyen day bit thanh day bool
//Có khởi tạo, nhớ delete
//Lấy bit từ x -> dãy bool 128 phần tử
bool* qint::DecToBin(QInt x)
{
	bool* bit = new bool[BIT_RANGE];
	for (int i = 0; i < BIT_RANGE; i++)
	{
		bit[i] = x.GetBit(i);
	}
	return bit;
}

//Set các phần tử của bin vào QInt
//bin cần có 128 phần tử
QInt qint::BinToDec(bool* bin)
{
	QInt result;

	for (int i = 0; i < BIT_RANGE; i++)
	{
		result.SetBit(i, bin[i]);
	}
	return result;
}

//Xuất bin
void qint::OutputBin(bool* bin)	
{
	bool flag = false; //flag để xóa số 0 đầu
	for (int i = 0; i < BIT_RANGE; i++)
	{
		if (bin[i] == 0 && flag == false)
			continue;
		if (bin[i])
			flag = true;
		cout << bin[i];
	}
}

//Xuất hex
void qint::OutputHex(char* hex)
{
	bool flag = false; //flag để xóa sổ 0 đầu
	int len = strlen(hex);
	for (int i = 0; i < len; i++)
	{
		if (hex[i] == '0' && flag == false)
			continue;
		if (hex[i] != '0')
			flag = true;
		cout << hex[i];
	}

}

//Tạo chuỗi bin từ hex
bool* qint::HexToBin(char* hex)
{
	string bin_str = "";
	bool* bin = new bool[BIT_RANGE];
	memset(bin, 0, BIT_RANGE*sizeof(*bin));

	int len = strlen(hex);
	for (int i = 0; i < len; i++)
	{
		bin_str += HexToBinChar(hex[i]);
	}
	for (int i = bin_str.length() - 1, j = BIT_RANGE - 1; i >= 0; i--, j--)
	{
		bin[j] = bin_str[i] - '0';
	}

	return bin;
}

//Chuyển đổi chuỗi thập lục phân sang thập phân QInt lưu trữ
QInt qint::HexToDec(char* hex)
{
	bool* bin = HexToBin(hex);
	QInt a;
	a = BinToDec(bin);
	return a;
}