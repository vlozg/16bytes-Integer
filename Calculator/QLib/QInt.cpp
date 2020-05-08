#include "QInt.h"

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
void ScanQInt(QInt& x)
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
void PrintQInt(QInt x)
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

	QInt result("-1"); //kết quả là số lần trừ
	while (!(divisor.IsNegative())) //lặp khi số bị chia >= 0
	{
		divisor = divisor - number;
		result = result + QInt("1");
	}

	if (negative1 ^ negative2) //2 số trái dấu
		result = result.ComplementTwo();

	return result;
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
	QInt newnum(number);
	return newnum;
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

/*
====================================
		HỖ TRỢ GIAO DIỆN
====================================
*/

string QInt::DecStr()	//Copy từ output, nhưng trả về string
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
	return result;
}

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
	return result;
}