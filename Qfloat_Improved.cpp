#include "Qfloat_Improved.h"

using namespace qfloat;

/*
Khởi tạo Qfloat với toàn bộ bit = 0 và độ dài -1
*/
Qfloat::Qfloat()
{
	for (int i = 0; i < SIZE; i++) 
	{
		value[i] = 0;
	}
}

//	Constructor với Qfloat
Qfloat::Qfloat(const Qfloat& src)
{
	*this = src;
}

//	Constructor với string
Qfloat::Qfloat(const string& src)
{
	
}

Qfloat::~Qfloat()
{
}

/*
Lấy giá trị bit tại vị trí bất kì
Parameter:
- pos: vị trí bit cần lấy
*/
bool Qfloat::GetBit(int pos) const
{
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
void Qfloat::SetBit(int pos, bool bit) 
{
	if (pos > 127) return;

	char mask = 1 << (pos % 8);   //Mặt nạ đánh dấu bit cần sửa

	if (bit == 1) {
		value[pos / 8] |= mask;   //OR với mask để bật bit
	}
	else {
		value[pos / 8] &= ~mask;  //Đảo mask và AND để tắt bit
	}
}

/*
Set toàn bộ bit về 1 giá trị
Parameter:
- bit: giá trị set
*/
void Qfloat::SetBit(bool bit) 
{
	for (int i = 0; i < SIZE; i++)
		this->value[i] = 255;
}

//	Lấy số đảo dấu
const Qfloat Qfloat::Negate() const
{
	Qfloat res(*this);
	res.SetBit(0,1);
	return res;
}

//	Kiểm tra số âm.
bool Qfloat::IsNegative() const
{
	return this->GetBit(0);
}

//	Kiểm tra số không.
bool Qfloat::IsZero() const
{
	//Bỏ qua bit dấu, kết quả sai khi tồn tại bit 1
	for (int i = 1; i < BIT_RANGE; i++)
		if (this->GetBit(i)) return false;
	
	return true;
}

//	Kiểm tra có phải số.
bool Qfloat::IsNaN() const
{
	int i;
	//Bỏ qua bit dấu, kết quả sai khi exponent tồn tại bit 0
	for (i = 1; i < EXPONENT_BIT + 1; i++)
		if (!this->GetBit(i)) return false;

	//Kết quả đúng khi significant tồn tại bit 1
	for (; i < BIT_RANGE; i++)
		if (this->GetBit(i)) return true;

	return false;	//Significant toán bit 0 là infinity
}

//	Kiểm tra vô cực.
bool Qfloat::IsInfinity() const
{
	int i;
	//Bỏ qua bit dấu, kết quả sai khi exponent tồn tại bit 0
	for (i = 1; i < EXPONENT_BIT + 1; i++)
		if (!this->GetBit(i)) return false;
		
	//Kết quả sai khi significant tồn tại bit 1
	for (; i < BIT_RANGE; i++)
		if (this->GetBit(i)) return false;

	return true;
}

//	Kiểm tra có phải số hợp lệ
bool Qfloat::IsNumber() const
{
	return (!(this->IsInfinity() || this->IsNaN()));
}

/*Tổng 2 bit dùng half adder
Input: bit A, bit B, bit nhớ C
Output: bit tổng và kết quả nhớ lưu vào C*/
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

/*Tính tổng 2 số thực theo cách của số nguyên 128bit
Input: số thực num1, num2 và product là kết quả phép cộng
Output: true nếu tràn bit và ngược lại*/
bool Adder_128bit(const Qfloat& num1, const Qfloat& num2, Qfloat& product){
	bool carrierBit = 0;
	bool firstBit, secondBit, newBit;
	bool isSignExpected = ~(num1.GetBit(0) ^ num2.GetBit(0));	//Dấu của phép toán có xác định trước được không

	//Tính toán chừa bit dấu
	for (int i = 0; i < BIT_RANGE; i++)
	{
		firstBit = num1.GetBit(BIT_RANGE - i - 1);
		secondBit = num2.GetBit(BIT_RANGE - i - 1);
		newBit = FullAdder(firstBit, secondBit, carrierBit);
		product.SetBit(BIT_RANGE - i - 1, newBit);
	}

	return (isSignExpected & (num1.GetBit(0) ^ product.GetBit(0)));
}

//	Output: dạng bù 2 của số nguyên 128bit
Qfloat& ComplementTwo(Qfloat& src)
{
	src = ~src;	//Đảo bit

	//Lấy số nguyên 1
	Qfloat num1;
	num1.SetBit(BIT_RANGE-1, 1);

	//Lấy bù 2
	Adder_128bit(src, num1, src);
	return src;
}

//	Lấy phần Exponent
const Qfloat ExponentExtract(const Qfloat& src)
{
	Qfloat mask;
	mask.SetBit(1);	//Reset mask
	mask = mask << SIGNIFICANT_BIT;	//Remove significant
	mask.SetBit(0,0);	//Remove sign bit
	return (src & mask);
}

//	Lấy phần Significant và đẩy lên đầu và chừa 2 chỗ bit dấu và bit định trị mạc định
const Qfloat SignificantExtract(const Qfloat& src)
{
	Qfloat res;
	res = (src << (EXPONENT_BIT + 1)) >> 2;
	
	//Nếu phần mũ khác 0
	//-> Đây là số chuẩn
	//-> Thêm 1 bit định trị mặc định vào
	if (!ExponentExtract(src).IsZero())
		res.SetBit(1,1);
	
	return res;
}

//	Toán tử cộng
const Qfloat Qfloat::operator+(const Qfloat& src) const
{
	if (!this->IsNumber() || !src.IsNumber())
		return Qfloat("NaN");

	Qfloat res;

	//Lấy exponent bit
	Qfloat exp1, exp2;
	exp1 = ExponentExtract(*this);
	exp2 = ExponentExtract(src);

	//Lấy significant bit
	Qfloat frac1, frac2;
	frac1 = SignificantExtract(*this);
	frac2 = SignificantExtract(src);

	//Cân bằng exponent
	Qfloat expInterval;
	expInterval.SetBit(EXPONENT_BIT, 1);
	int expDelta = 0;
	bool isMixNormal = exp1.IsZero() ^ exp2.IsZero();	//Case: subnormal + normal
	if (isMixNormal) 
		expDelta--;

	//Tính chênh lệch exponent, nếu chênh lệch lớn hơn 112 bit thì return số còn lại
	bool biasNum1 = exp1 < exp2;	//Bên nào bị lệch
	while (exp1 < exp2 && expDelta <= SIGNIFICANT_BIT){
		Adder_128bit(exp1, expInterval, exp1);	//Tăng exp
		expDelta++;
	}
	if (expDelta > SIGNIFICANT_BIT)
		return src;

	while (exp1 > exp2 && expDelta <= SIGNIFICANT_BIT){
		Adder_128bit(exp2, expInterval, exp2);	//Tăng exp
		expDelta++;
	}
	if (expDelta > SIGNIFICANT_BIT)
		return (*this);

	//Dịch significant theo số chênh exponent
	if (biasNum1)
		frac1 = frac1 >> expDelta;
	else
		frac2 = frac2 >> expDelta;

	//Lấy bù 2 nếu gặp số âm
	if (this->IsNegative())
		ComplementTwo(frac1);
	if (src.IsNegative())
		ComplementTwo(frac2);

	//Nếu dịch xong có số bằng 0 thì return số còn lại
	if (frac1.IsZero())
		return src;
	else if (frac2.IsZero())
		return (*this);

	bool isOverflow = Adder_128bit(frac1, frac2, res);

	if (res.IsZero() && !isOverflow)
		return res;

	if (isOverflow)
	{
		//Dịch số
		res = res >> 1;
		res.SetBit(0, !res.GetBit(1));	//Tràn số thì bit dấu sẽ ngược với bit đầu
		//Tăng exp
		Adder_128bit(exp1, expInterval, exp1);
	}

	//Xử lý exponent đề phòng exponent tràn số
	exp1.SetBit(0,0);	//Xóa bit dấu của
	if (exp1.IsZero())
		//Tràn số
		return Qfloat("0");

	bool resSign = res.GetBit(0);	//Lưu lại dấu
	if (resSign)	//Số âm thì lấy bù 2 
		ComplementTwo(res);

	//Chuẩn hóa số
	ComplementTwo(expInterval);

	//Nếu bit thứ 2 là 0 
	//	(vị trí được chừa dành cho 
	//	bit đầu mặc định của định dạng số thực) 
	//thì liên tục chuẩn hóa
	//cho đến khi tìm được bit số 1 vào vị trí đó
	while (!res.GetBit(1) && !exp1.IsZero() && !res.IsZero())
	{
		res = res << 1;
		//Giảm exp
		Adder_128bit(exp1, expInterval, exp1);
	}

	//Chuẩn hóa thất bại
	if (res.IsZero())
		return Qfloat("0");

	res = (res << 2) >> (EXPONENT_BIT + 1);	//Đưa significant xuống
	res = res | exp1;	//Set bit exponent, exponent của res ban đầu luôn là 0
	res.SetBit(0,resSign);

	return res;
}

//	Toán tử trừ
const Qfloat Qfloat::operator-(const Qfloat& src) const
{
	//Đảo dấu rồi cộng
	return ((*this) + src.Negate());
}
/*
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
	choice = true: number làm toán hạng 1
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
*/

//	Chuyển dạng bias sang dạng bù 2
const Qfloat BiasToNorm(const Qfloat& src)
{

}

//	Toán tử nhân
const Qfloat Qfloat::operator*(const Qfloat& src) const
{
	if (this->IsZero() || src.IsZero())
		return Qfloat("0");

	Qfloat res;

	//Lấy exponent bit
	Qfloat exp1, exp2;
	exp1 = ExponentExtract(*this);
	exp2 = ExponentExtract(src);

	//Lấy significant bit
	Qfloat frac1, frac2;
	frac1 = SignificantExtract(*this);
	frac2 = SignificantExtract(src);

	//Cộng exponent
	Adder_128bit(exp1, exp2, res);
	
	//Trừ bias
	Qfloat bias;
	bias.SetBit(EXPONENT_BIT, 1);
	bias.SetBit(0,1);
	bias.SetBit(1,1);

	bool isMixNormal = exp1.IsZero() ^ exp2.IsZero();	//Case: subnormal + normal
	if (isMixNormal) 
		expDelta--;

	//Set bit 1 mặc định cho số chuẩn
	if (!exp1.IsZero())
		frac1.SetBit(1,1);
	if (!exp2.IsZero())
		frac2.SetBit(1,1);

	//Tính chênh lệch exponent, nếu chênh lệch lớn hơn 112 bit thì return số còn lại
	bool biasNum1 = exp1 < exp2;	//Bên nào bị lệch
	while (exp1 < exp2 && expDelta <= SIGNIFICANT_BIT){
		Adder_128bit(exp1, expInterval, exp1);	//Tăng exp
		expDelta++;
	}
	if (expDelta > SIGNIFICANT_BIT)
		return src;

	while (exp1 > exp2 && expDelta <= SIGNIFICANT_BIT){
		Adder_128bit(exp2, expInterval, exp2);	//Tăng exp
		expDelta++;
	}
	if (expDelta > SIGNIFICANT_BIT)
		return (*this);

	//Dịch significant theo số chênh exponent
	if (biasNum1)
		frac1 = frac1 >> expDelta;
	else
		frac2 = frac2 >> expDelta;

	//Lấy bù 2 nếu gặp số âm
	if (this->IsNegative())
		ComplementTwo(frac1);
	if (src.IsNegative())
		ComplementTwo(frac2);

	//Nếu dịch xong có số bằng 0 thì return số còn lại
	if (frac1.IsZero())
		return src;
	else if (frac2.IsZero())
		return (*this);

	bool isOverflow = Adder_128bit(frac1, frac2, res);

	if (res.IsZero() && !isOverflow)
		return res;

	if (isOverflow)
	{
		//Dịch số
		res = res >> 1;
		res.SetBit(0, !res.GetBit(1));	//Tràn số thì bit dấu sẽ ngược với bit đầu
		//Tăng exp
		Adder_128bit(exp1, expInterval, exp1);
	}

	//Xử lý exponent đề phòng exponent tràn số
	exp1.SetBit(0,0);	//Xóa bit dấu của
	if (exp1.IsZero())
		//Tràn số
		return Qfloat("0");

	bool resSign = res.GetBit(0);	//Lưu lại dấu
	if (resSign)	//Số âm thì lấy bù 2 
		ComplementTwo(res);

	//Chuẩn hóa số
	ComplementTwo(expInterval);

	//Nếu bit thứ 2 là 0 
	//	(vị trí được chừa dành cho 
	//	bit đầu mặc định của định dạng số thực) 
	//thì liên tục chuẩn hóa
	//cho đến khi tìm được bit số 1 vào vị trí đó
	while (!res.GetBit(1) && !exp1.IsZero() && !res.IsZero())
	{
		res = res << 1;
		//Giảm exp
		Adder_128bit(exp1, expInterval, exp1);
	}

	//Chuẩn hóa thất bại
	if (res.IsZero())
		return Qfloat("0");

	res = (res << 2) >> (EXPONENT_BIT + 1);	//Đưa significant xuống
	res = res | exp1;	//Set bit exponent, exponent của res ban đầu luôn là 0
	res.SetBit(0,resSign);

	return res;
}

//	Toán tử AND
const Qfloat Qfloat::operator&(const Qfloat& src) const
{
	Qfloat res;

	for (int i = 0; i < MAX_VALUE_BIT; i++) {
		res.value[i] = this->value[i] & src.value[i];
	}

	return res;
}

//	Toán tử OR
const Qfloat Qfloat::operator|(const Qfloat& src) const
{
	Qfloat res;

	for (int i = 0; i < MAX_VALUE_BIT; i++) {
		res.value[i] = this->value[i] | src.value[i];
	}

	return res;
}

//	Toán tử XOR
const Qfloat Qfloat::operator^(const Qfloat& src) const
{
	Qfloat res;

	for (int i = 0; i < MAX_VALUE_BIT; i++) {
		res.value[i] = this->value[i] | src.value[i];
	}

	return res;
}

//	Toán tử NOT
const Qfloat Qfloat::operator~() const
{
	Qfloat res;

	for (int i = 0; i < MAX_VALUE_BIT; i++) {
		res.value[i] = ~(this->value[i]);
	}

	return res;
}

//	Toán tử shift right
const Qfloat Qfloat::operator>>(const int& number) const
{
	//Số bé hơn 0 thì kết quả giữ nguyên
	if (number <= 0)
		return *this;
	//Vượt quá bit range thì kết quả bằng 0
	if (number >= BIT_RANGE)
		return Qfloat("0");

	Qfloat res;

	for (int i = BIT_RANGE - 1; i >= number; i--)
	{
		res.SetBit(i, this->GetBit(i - number));
		res.SetBit(i - number, 0);
	}
	return res;
}

//	Toán tử shift left
const Qfloat Qfloat::operator<<(const int& number) const
{
	//Số bé hơn 0 thì kết quả giữ nguyên
	if (number <= 0)
		return *this;
	//Vượt quá bit range thì kết quả bằng 0
	if (number >= BIT_RANGE)
		return Qfloat("0");

	Qfloat res;

	for (int i = 0; i < BIT_RANGE - number; i++)
	{
		res.SetBit(i, this->GetBit(i + number));
		res.SetBit(i + number, 0);
	}
	return res;
}

//	Toán tử xoay bit bên trái
const Qfloat Qfloat::RotateLeft(int number) const
{
	//Số âm hoặc bộ số của 128 thì giữ nguyên
	if (number <= 0 || (number%BIT_RANGE == 0)) 
		return *this;
	
	number %= BIT_RANGE;
	Qfloat res;
	
	res = (*this) << number;	//Đẩy phần đuôi lên
	res = res | ((*this) >> (BIT_RANGE - number));	//Đẩy phần đầu xuống và set bit vào

	return res;
}

//	Toán tử xoay bit bên phải
const Qfloat Qfloat::RotateRight(int number) const
{
	//Số âm hoặc bộ số của 128 thì giữ nguyên
	if (number <= 0 || (number%BIT_RANGE == 0)) 
		return *this;
	
	number %= BIT_RANGE;
	Qfloat res;
	
	res = (*this) >> number;	//Đẩy phần đầu xuống
	res = res | ((*this) << (BIT_RANGE - number));	//Đẩy phần đuôi lên và set bit vào

	return res;
}

//	Toán tử gán cơ bản
Qfloat& Qfloat::operator=(const Qfloat& src)
{
	if (this == &src) //nếu gán cho chính nó
		return *this;

	//copy giá trị
	for (int i = 0; i < SIZE; i++) 
	{
		this->value[i] = src.value[i];
	}

	return *this;
}

//	Toán tử gán trực tiếp với string
Qfloat& Qfloat::operator=(const string& src)
{
	*this = Qfloat(src);
	return *this;
}

//	Toán tử so sánh bé hơn
bool Qfloat::operator<(const Qfloat& src) const
{
	bool negative1 = this->IsNegative();
	bool negative2 = src.IsNegative();

	if (negative1 && !negative2) //số hiện tại âm, số number dương
		return true;
	if (!negative1 && negative2) //số hiện tại dương, số number âm
		return false;
	
	for (int i = 1; i < BIT_RANGE; i++)
	{
		//Nếu bit tại vị trí i của this > src
		if (this->GetBit(i) && !src.GetBit(i))
		{
			if (!negative1) //nếu cả 2 số dương
				return false;
			else
				return true;
		}
		//ngược lại
		else if (!(this->GetBit(i)) && src.GetBit(i))
		{
			if (!negative1) //nếu cả 2 số dương
				return true;
			else
				return false;
		}
	}

	//Trường hợp bằng nhau
	return false;
}

//	Toán tử so sánh lớn hơn
bool Qfloat::operator>(const Qfloat& src) const
{
	bool negative1 = this->IsNegative();
	bool negative2 = src.IsNegative();

	if (negative1 && !negative2) //số hiện tại âm, số number dương
		return true;
	if (!negative1 && negative2) //số hiện tại dương, số number âm
		return false;
	
	for (int i = 1; i < BIT_RANGE; i++)
	{
		//Nếu bit tại vị trí i của this > src
		if (this->GetBit(i) && !src.GetBit(i))
		{
			if (!negative1) //nếu cả 2 số dương
				return true;
			else
				return false;
		}
		//ngược lại
		else if (!(this->GetBit(i)) && src.GetBit(i))
		{
			if (!negative1) //nếu cả 2 số dương
				return false;
			else
				return true;
		}
	}

	//Trường hợp bằng nhau
	return false;
}

//	Toán tử so sánh bé hơn hoặc bằng
bool Qfloat::operator<=(const Qfloat& src) const
{
	return (*this == src || *this < src);
}

//	Toán tử so sánh lớn hơn hoặc bằng
bool Qfloat::operator>=(const Qfloat& src) const
{
	return (*this == src || *this > src);
}

//	Toán tử so sánh bằng
bool Qfloat::operator==(const Qfloat& src) const
{
	for (int i = 0; i < SIZE; i++)
	{
		if (value[i] != src.value[i])
			return false;
	}
	return true;
}

/*
Chuyển các bit trong Qfloat thành string
*/
string Qfloat::BinStr() const
{
	string result = "";

	if (GetBit(0) == 0) {
		result += '0';
	}
	else {
		result += '1';
	}	//lấy bit dấu
	result += " ";
	for (int i = 1; i < 16; i++) {
		if (GetBit(i) == 0) {
			result += '0';
		}
		else {
			result += '1';
		}	//lấy 15 bit Exponent
	}
	result += ' ';
	for (int i = 16; i < 128; i++) {
		if (GetBit(i) == 0) {
			result += '0';
		}
		else {
			result += '1';
		}	//lấy cái bit Significand
	}
	return result;
}

/*
Chuyển Qfloat dưới dạng thập phân thành string
*/
string Qfloat::DecStr() const
{
	string result = "";
	string Exponent, Significand;

	//xét bit đầu tiên để xét dấu
	if (GetBit(0) == 1) {
		result += '-';
	}

	//lấy 15 bit tiếp theo ra làm phần exponent
	for (int i = 1; i < 16; i++) {
		if (GetBit(i) == 1) {
			Exponent += '1';
		}
		else {
			Exponent += '0';
		}
	}

	//lấy các bit còn lại để xét significand
	for (int i = 16; i < 128; i++) {
		if (GetBit(i) == 1) {
			Significand += '1';
		}
		else {
			Significand += '0';
		}
	}

	/*Kiểm tra Exponent và Significand để check các số đặc biệt*/
	if (CheckAllChar(Exponent, '0')) {
		if (CheckAllChar(Significand, '0')) { //nếu Ex và Si đều toàn 0 => số 0
			result = "0";
			return result;
		}
		else { //nếu Ex toàn 0 và Sig khác 0 thì là số không thể chuẩn hóa
			//Exponent toàn bộ bit  0
			for (int i = 0; i < Exponent.length(); i++) {
				Exponent[i] = '0';
			}

			//Significand toàn 1
			for (int i = 0; i < Significand.length(); i++) {
				Significand[i] = '1';
			}
		}
	}
	if (CheckAllChar(Exponent, '1')) {
		if (CheckAllChar(Significand, '0')) { //nếu Ex và Si toàn 1 => số vô cùng
			//Exponent toàn bộ bit 1 bit cuối 0
			result = "infinity";
			return result;
		}
		else { //nếu Ex toàn 1 và Si khác 1 => số báo lỗi
			result = "NaN";
			return result;
		}
	}

	//Tính toán để ra E
	Exponent = IntegerBinToDec(Exponent);
	int E = stoi(Exponent);
	E = E - KNUMBER;

	//Lấy lại phần nguyên ban đầu
	string integerDigits;
	if (E >= 0) {
		integerDigits = "1";
		int i = 0;
		if (E < 112) {
			for (i = 0; i < E; i++) { //chạy 112 bit của Significand
				integerDigits += Significand[i];
			}
			if (integerDigits.length() > 1) {
				Significand.erase(Significand.begin(), Significand.begin() + E);
			}
		}
		else {
			for (i = 0; i < 112; i++) { //chạy 112 bit của Significand
				integerDigits += Significand[i];
			}
			while (i < E) { // E > 112 nên thêm 0 vào integerDigits
				integerDigits += '0';
				i++;
			}
			Significand.erase(Significand.begin(), Significand.end());
		}
	}
	else if (E <= -KNUMBER) { //TH Exponent toàn 0 và Significand khác 0 => đưa về 0....Fx2^-126
		result = "0.";
		for (int i = 0; i < 23; i++) {
			result += '0'; //thêm 23 số 0
		}
		result += "*2^(-126)";
		return result;
	}
	else if (E < 0) {
		Significand = '1' + Significand;
		int i = 0;
		for (i = E + 1; i < 0; i++) {
			Significand = '0' + Significand;	//thêm vào các bit 0
		}
		integerDigits = "0";
	}

	integerDigits = IntegerBinToDec(integerDigits);
	result = result + integerDigits;

	//lấy lại phần thập phân ban đầu
	string fractionalDigits = FractionalBinToDec(Significand);
	if (fractionalDigits.length() > 0) {
		fractionalDigits.erase(fractionalDigits.begin(), fractionalDigits.begin() + 1); //xóa số 0
	}
	result += fractionalDigits;

	//so sánh độ dài ban đầu và kết quả để làm tròn
	int initialLength = 100/*length*/;
	if (initialLength > 0) {
		if (initialLength < result.length()) {
			//xóa các kí tự dư
			while (result.length() > initialLength) {
				result.pop_back();
				fractionalDigits.pop_back();
			}

			string addIn = "0."; //phần sẽ được cộng thêm vào kết quả
			while (addIn.length() < fractionalDigits.length()) {
				addIn += '0';//thêm số không
			}
			addIn += '1';
			fractionalDigits = '0' + fractionalDigits;

			fractionalDigits = SumFractionals(fractionalDigits, addIn); //lấy phần thập phân + 0.(0...00)1
			DeleteExcessiveZero(fractionalDigits); //xóa số 0 dư

			if (fractionalDigits[0] == '1') { //nếu kết quả lớn hơn 1
				SumNumbers(integerDigits, "1"); //+ thêm 1 vào phần nguyên
			}
			fractionalDigits.erase(fractionalDigits.begin(), fractionalDigits.begin() + 1); //xóa dấu .

			result = integerDigits + fractionalDigits;
		}
	}
	return result;
}

//hàm scan từ string lưu vào Qfloat
bool qfloat::ReadDecString(string input, Qfloat& output)
{
	//set tất cả bit của input về 0 tránh TH trùng
	for (int i = 0; i < 128; i++) {
		output.SetBit(i, 0);
	}

	string temp = input;

	//khởi tạo mảng gồm các số 2 mũ n
	string pow2[128], powminus2[128];
	PowOfTwo(pow2);
	PowOfFive(powminus2);

	//nếu string không có gì thì stop
	if (temp.length() == 0) {
		return false;
	}

	//lấy độ dài số nhập vào
	/*output.SetLength(temp.length());*/

	//kiểm tra dấu
	if (CheckMinus(temp[0])) {
		output.SetBit(0, 1);	//có dấu - thì set bit đầu tiên thành 1
		temp.erase(temp.begin(), (temp.begin() + 1));	//xong xóa char dấu
	}

	//Đưa phần số nguyên sang 1 string mới
	string integerDigits;
	int k;

	//chạy tới khi gặp dấu .
	for (k = 0; k < temp.length(); k++) {
		if (CheckNumber(temp[k])) {
			integerDigits += temp[k];	//nếu là số thì đưa vô string integerDigits
		}
		else {
			if (CheckDecimalPoint(temp[k])) {
				break;	//nếu là dấu . thì break
			}
			else {
				return false;	//nếu là kí tự lạ thì stop
			}
		}
	}

	//nếu phần nguyên hay thập phân vượt qua giới hạn thì set số infinity
	//giới hạn của phần nguyên là (2^128)-1; của phần thập phân là 2^-128
	if ((integerDigits.length() > pow2[127].length()) || (temp.length() > powminus2[127].length())) {
		for (int i = 1; i < 16; i++) { //set Exponent toàn bit 1
			output.SetBit(i, 1);
		}
		for (int i = 16; i < 128; i++) { //set Significand toàn 0
			output.SetBit(i, 0);
		}
		return true;
	}

	//xóa phần nguyên khỏi string đầu
	temp.erase(temp.begin(), (temp.begin() + k));
	if (temp.length() == 1) {
		temp.erase(temp.begin(), temp.end());	//chỉ còn 1 phần tử thì đó là dấu . nên xóa luôn
	}

	//chuyển phần nguyên sang binary
	integerDigits = IntegerDecToBin(integerDigits);
	//chuyển phần thập phân sang binary
	temp = FractionalDecToBin(temp);

	// tính E bằng cách dời từng bit từ phần nguyên sang phần thập phân
	// (từ phải qua trái) tới khi chỉ còn 1 bit 1
	// nếu integerDigits = 0 thì dời sang phải đến khi qua khỏi số 1
	int e = 0;
	char tempBit;	//lưu bit chuyển
	if (integerDigits == "") {	//nếu phần nguyên = 0 thì dời sang phải
		//nếu temp không có gì luôn => input là số 0
		if (CheckAllChar(temp, '0')) {
			return true;
		}
		for (int i = 0;; i++) {
			if (temp[i] == '1') {
				tempBit = temp[i];
				integerDigits += tempBit;
				e--;
				break;
			}
			else {
				tempBit = temp[i];
				integerDigits += tempBit;
			}
			e--;
		}
		//xóa e bit đầu của temp (chứa significand)
		for (int i = e; i < 0; i++) {
			temp.erase(temp.begin(), temp.begin() + 1);
		}
	}
	else {	//ngược lại dời qua trái
		for (int i = integerDigits.length() - 1; i > 0; i--) {
			tempBit = integerDigits[i];
			temp = tempBit + temp;
			e++;
		}
	}

	e += KNUMBER;	// cộng E với số thừa K để ra Exponent
	string E = to_string(e);
	E = IntegerDecToBin(E);	//chuyển E sang binary

	//Kiểm tra độ dài đủ 15 bit, thiếu thì thêm 0 vào đầu
	if (E.length() > 15) {
		E.erase(E.begin() + 15, E.end());
	}
	else if (E.length() < 15) {
		E = "0" + E;
	}

	// Xài các string integerDigits, temp (đang chứa phần thập phân)
	// và E để đưa vô Qfloat

	// Phần Exponent
	int l = 1;
	for (int i = 0; i < 15; i++) {
		if (E[i] == '1') {
			output.SetBit(l, 1);
		}
		l++;
	}
	//Phần định trị
	l = 16;
	for (int i = 0; i < temp.length(); i++) {
		if (temp[i] == '1') {
			output.SetBit(l, 1);
		}
		l++;
	}
	return true;
}

//hàm nhập string từ console
void qfloat::ScanQfloat(Qfloat& input) {
	string temp;
	getline(cin, temp);
	ReadDecString(temp, input);
}

//hàm xuất Qfloat dưới dạng thập phân
void qfloat::PrintQfloat(Qfloat input)
{
	string result = "";
	string Exponent, Significand;

	//xét bit đầu tiên để xét dấu
	if (input.GetBit(0) == 1) {
		result += '-';
	}

	//lấy 15 bit tiếp theo ra làm phần exponent
	for (int i = 1; i < 16; i++) {
		if (input.GetBit(i) == 1) {
			Exponent += '1';
		}
		else {
			Exponent += '0';
		}
	}

	//lấy các bit còn lại để xét significand
	for (int i = 16; i < 128; i++) {
		if (input.GetBit(i) == 1) {
			Significand += '1';
		}
		else {
			Significand += '0';
		}
	}

	/*Kiểm tra Exponent và Significand để check các số đặc biệt*/
	if (CheckAllChar(Exponent, '0')) {
		if (CheckAllChar(Significand, '0')) { //nếu Ex và Si đều toàn 0 => số 0
			cout << "0";
			return;
		}
		else { //nếu Ex toàn 0 và Sig khác 0 thì là số không thể chuẩn hóa
			//Exponent toàn bộ bit  0
			for (int i = 0; i < Exponent.length(); i++) {
				Exponent[i] = '0';
			}

			//Significand toàn 1
			for (int i = 0; i < Significand.length(); i++) {
				Significand[i] = '1';
			}
		}
	}
	if (CheckAllChar(Exponent, '1')) {
		if (CheckAllChar(Significand, '0')) { //nếu Ex và Si toàn 1 => số vô cùng
			//Exponent toàn bộ bit 1 bit cuối 0
			cout << "infinity";
			return;
		}
		else { //nếu Ex toàn 1 và Si khác 1 => số báo lỗi
			cout << "NaN";
			return;
		}
	}

	//Tính toán để ra E
	Exponent = IntegerBinToDec(Exponent);
	int E = stoi(Exponent);
	E = E - KNUMBER;

	//Lấy lại phần nguyên ban đầu
	string integerDigits;
	if (E >= 0) {
		integerDigits = "1";
		int i = 0;
		if (E < 112) {
			for (i = 0; i < E; i++) { //chạy 112 bit của Significand
				integerDigits += Significand[i];
			}
			if (integerDigits.length() > 1) {
				Significand.erase(Significand.begin(), Significand.begin() + E);
			}
		}
		else {
			for (i = 0; i < 112; i++) { //chạy 112 bit của Significand
				integerDigits += Significand[i];
			}
			while (i < E) { // E > 112 nên thêm 0 vào integerDigits
				integerDigits += '0';
				i++;
			}
			Significand.erase(Significand.begin(), Significand.end());
		}
	}
	else if (E <= -KNUMBER) { //TH Exponent toàn 0 và Significand khác 0 => đưa về 0....Fx2^-126
		result = "0.";
		for (int i = 0; i < 23; i++) {
			result += '0'; //thêm 23 số 0
		}
		result += "*2^(-126)";
		cout << result;
		return;
	}
	else if (E < 0) {
		Significand = '1' + Significand;
		int i = 0;
		for (i = E + 1; i < 0; i++) {
			Significand = '0' + Significand;	//thêm vào các bit 0
		}
		integerDigits = "0";
	}

	integerDigits = IntegerBinToDec(integerDigits);
	result = result + integerDigits;

	//lấy lại phần thập phân ban đầu
	string fractionalDigits = FractionalBinToDec(Significand);
	if (fractionalDigits.length() > 0) {
		fractionalDigits.erase(fractionalDigits.begin(), fractionalDigits.begin() + 1); //xóa số 0
	}
	result += fractionalDigits;

	//so sánh độ dài ban đầu và kết quả để làm tròn
	int initialLength = 100/*input.GetLength()*/;
	if (initialLength > 0) {
		if (initialLength < result.length()) {
			//xóa các kí tự dư
			while (result.length() > initialLength) {
				result.pop_back();
				fractionalDigits.pop_back();
			}

			string addIn = "0."; //phần sẽ được cộng thêm vào kết quả
			while (addIn.length() < fractionalDigits.length()) {
				addIn += '0';//thêm số không
			}
			addIn += '1';
			fractionalDigits = '0' + fractionalDigits;

			fractionalDigits = SumFractionals(fractionalDigits, addIn); //lấy phần thập phân + 0.(0...00)1
			DeleteExcessiveZero(fractionalDigits); //xóa số 0 dư

			if (fractionalDigits[0] == '1') { //nếu kết quả lớn hơn 1
				SumNumbers(integerDigits, "1"); //+ thêm 1 vào phần nguyên
			}
			fractionalDigits.erase(fractionalDigits.begin(), fractionalDigits.begin() + 1); //xóa dấu .

			result = integerDigits + fractionalDigits;
		}
	}
	cout << result;
}

/*
Đổi số thực từ dãy nhị phân sang thập phân lưu trữ trong Qfloat
Parameter:
- bit: dãy nhị phân 128bit
*/
Qfloat qfloat::BinToDec(bool* bit) {
	Qfloat res; //Lưu kết quả trả về

	for (int i = 0; i < 128; i++) {
		res.SetBit(i, bit[i]);
	}
	return res;
}

/*
Đổi số thực từ dạng thập phân trong Qfloat sang dãy nhị phân 128bit
Parameter:
- x: số thực 128bit
*/
bool* qfloat::DecToBin(Qfloat x) {
	bool* res = new bool[128];  //Lưu kết quả trả về

	for (int i = 0; i < 128; i++) {
		res[i] = x.GetBit(i);
	}

	return res;
}


/*--------Dưới đây là các hàm bổ trợ---------*/

//Kiểm tra dấu trừ
bool qfloat::CheckMinus(char first) {
	return first == 45;
}

//Kiểm tra xem char có phải là số không
bool qfloat::CheckNumber(char input) {
	if (input >= 48 && input <= 57) {
		return true;
	}
	return false;
}

//Kiểm tra string có phải bằng 1
bool qfloat::CheckOne(string input) {
	for (int i = 2; i < input.length(); i++) {
		if (input[i] != '0') {
			return false;
		}
	}
	return true;
}

//Kiểm tra dấu .
bool qfloat::CheckDecimalPoint(char input) {
	return input == 46;
}

//Xóa các số 0 đứng đầu chuỗi
void qfloat::NormalizeNumber(string& number)
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

//Lấy string chia 2
string qfloat::DivideByTwo(string number)	//Chia chuoi dec cho 2
{
	// Thuc hien nhu phep chia o cap 1

	string result = "";	//Ket qua

	string temp = "";	//Chuoi luu tung chu so dung de chia

	int q = 0;	//La thuong cua phep chia tung chu so (la 1 phan cua result)
	int len = number.length();
	int p = 0;	//La temp nhung o dang so

	//		CACH CHIA:
	//	DUA TUNG CHU SO TU TRAI SANG VAO TEMP
	//	SAU DO CHUYEN TEMP TU DANG CHUOI SANG P SANG SO
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
	NormalizeNumber(result);	//Co nhiem vu xoa cac so 0 o phia truoc 
	return result;
}

//Chia 1 cho chuỗi
string qfloat::DivideOne(string number) {
	string result = "0.";
	string temp = number;

	int q = 0;	//Là số chia
	int p = 0;	//Là thương
	int r = 10;
	int s = 1;	//số dư

	q = stoi(number);	//chuyển chuỗi về dạng số
	while (s != 0) {
		p = r / q;
		if (p == 0) {
			result += '0';
			s = r - 0;
		}
		else {
			result += p + '0';
			s = r - (p * q);
		}
		r *= 10;
	}

	return result;
}

//Chuyển chuỗi số nguyên sang binary
string qfloat::IntegerDecToBin(string number)
{
	if (number.length() == 0) {
		return "";
	}
	int lastIndex = number.length() - 1;
	string temp = number;	//temp luu ket qua cua chuoi sau cac phep chia 2
	string bin = "";	//Chuoi ket qua binary

	//			LAM NHU CONG THUC:
	//CHIA SO NUMBER CHO 2, LAY SO DU THEM VAO DANG TRUOC KET QUA
	//THUC HIEN LIEN TUC CHO DEN KHI SO BI CHIA LA 0

	while (temp != "0")
	{
		lastIndex = temp.length() - 1;			//Trich chu so cuoi cung de xem so do chia co du hay khong
		int r = (temp[lastIndex] - '0') % 2;	//r se la so du (0 hoac 1)
		temp = DivideByTwo(temp);				//temp mang ket qua sau khi chia 2
		char c = r + '0';
		bin = c + bin;							//Them so du do vao truoc ket qua da co
	}
	return bin;
}

//Chuyển chuỗi số thập phân sang binary
string qfloat::FractionalDecToBin(string number) {

	if (number.length() == 0) {
		return "";
	}
	number = '0' + number;
	string bin = "";
	string temp = number;	//temp để lưu kết quả các lần nhân
	char c;

	/*	Nhân 2 đến khi kết quả = 1 thì dừng lại
		Nếu kết quả > 1 lấy 1, < 1 lấy 0 */

	while (bin.length() < 112)
	{
		temp = MultiplyByTwo(temp);	//temp mang kết quả sau khi nhân 2
		if (temp[0] == '1') {
			if (CheckOne(temp)) {
				bin = bin + '1';
				return bin;	//kết quả bằng 1 thì thêm 1 vào bin rồi end
			}
			else {
				c = '1';	//kết quả lớn hơn 1 thì lấy 1
				temp.erase(temp.begin(), (temp.begin() + 1));
				temp = '0' + temp;	//lấy kết quả trừ 1 (ở đây là đổi char đầu thành 0)
			}
		}
		else {
			c = '0';	//kết quả < 0 nên lấy 0
		}
		bin += c;	//Thêm số đã chọn vào kết quả
	}
	return bin;
}

//Chuyển chuỗi binary sang chuỗi thập phân
string qfloat::IntegerBinToDec(string bin) {
	string number = "0";
	int binLength = bin.length();

	string pow[128];
	PowOfTwo(pow);	//khởi tạo chuỗi có các số 2 mũ n

	if (bin.length() < 128) {
		for (int i = 0; i < bin.length(); i++)
		{
			if (bin[bin.length() - 1 - i] == '1')
			{
				number = SumNumbers(number, pow[i]);	//	Cong lai theo kieu 2^x1 + 2^x2 + 2^x3 + ...
			}
		}
	}
	else
	{
		for (int i = 0; i < 128; i++)
		{
			if (bin[128 - 1 - i] == '1')
			{
				number = SumNumbers(number, pow[i]);	//	Cong lai theo kieu 2^x1 + 2^x2 + 2^x3 + ...
			}
		}
	}

	return number;
}

//chuyển phần thập phân binary sang thập phân
string qfloat::FractionalBinToDec(string bin) {
	string number = "";

	string pow[128];
	PowOfTwoMinus(pow);	//khởi tạo chuỗi có các số 2 mũ -n

	pow[0] = "0.0";
	for (int i = 0; i < bin.length(); i++)
	{
		if (bin[i] == '1')
		{
			number = SumFractionals(number, pow[i + 1]);	//	Cộng theo kiểu 2^-1 + 2^-2 + ...
		}
	}

	return number;
}

//Lấy chuỗi nhân 2
string qfloat::MultiplyByTwo(string number)
{
	string result = "";
	int number_len = number.length();
	int mem = 0;	//biến nhớ khi nhân

	for (int i = number_len - 1; i >= 0; i--)
	{
		//kiểm tra nếu gặp dấu phẩy
		if (number[i] == '.') {
			result = number[i] + result;
		}
		else {
			int m = (number[i] - '0') * 2 + mem;

			mem = m / 10;

			char c = m % 10 + '0';
			result = c + result;
		}
	}

	//đưa số nhớ cuối cùng vào đầu kết quả
	if (mem > 0)
	{
		result = char(mem + '0') + result;
	}
	return result;
}

//Lấy chuỗi nhân 5
string qfloat::MultiplyByFive(string number)
{
	string result = "";
	int number_len = number.length();
	int mem = 0;	//biến nhớ khi nhân

	for (int i = number_len - 1; i >= 0; i--)
	{
		//kiểm tra nếu gặp dấu phẩy
		if (number[i] == '.') {
			result = number[i] + result;
		}
		else {
			int m = (number[i] - '0') * 5 + mem;

			mem = m / 10;

			char c = m % 10 + '0';
			result = c + result;
		}
	}

	//đưa số nhớ cuối cùng vào đầu kết quả
	if (mem > 0)
	{
		result = char(mem + '0') + result;
	}
	return result;
}

//Tạo mảng 2 mũ n
void qfloat::PowOfTwo(string pow[128])
{
	pow[0] = "1";
	for (int i = 1; i < 128; i++)
	{
		pow[i] = MultiplyByTwo(pow[i - 1]);
	}
}

//Tạo mảng 5 mũ n
void qfloat::PowOfFive(string pow[128])
{
	pow[0] = "1";
	for (int i = 1; i < 128; i++)
	{
		pow[i] = MultiplyByFive(pow[i - 1]);
	}
}

/*
	Tạo mảng 2^-n
	Đầu tiên tạo mảng các số 5^n
	Vì các số 2^-n là 0.(00..0)5^n - với phần sau thập phân có n chữ số
*/
void qfloat::PowOfTwoMinus(string pow[128])
{
	string five[128];
	PowOfFive(five);	//khởi tạo mảng các số 5 mũ n

	pow[0] = "1";
	for (int i = 1; i < 128; i++)
	{
		pow[i] = five[i];
		while (pow[i].length() < i) {
			pow[i] = '0' + pow[i];
		}
		pow[i] = "0." + pow[i];
	}
}

//Cộng 2 chuỗi số thập phân
string qfloat::SumNumbers(string n1, string n2)
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

//Cộng 2 chuỗi có dạng 0.(...)
string qfloat::SumFractionals(string n1, string n2) {
	string result = "";
	string longer = "", shorter = "";	//longer se luu chuoi so co nhieu chu so hon, shorter nguoc lai
	int small = 0, large = 0;

	//phân biệt xem chuỗi nào dài hơn
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

	//thêm số 0 vào đuôi chuỗi ngắn hơn cho bằng chuỗi dài
	while (small < large) {
		shorter += '0';
		small++;
	}

	int carry = 0;	//Cong co nho

	int i = 0, j = 0;

	for (i = small - 1, j = large - 1; i >= 0; i--, j--)
	{
		if (shorter[i] == '.') {
			result = '.' + result;
			continue;
		}
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

//xóa số 0 đứng cuối chuỗi
void qfloat::DeleteExcessiveZero(string& input)
{
	for (int i = input.length(); i >= 0; i--) {
		if (input[i] == '0') {
			input.pop_back();
			i++;
		}
		else {
			break;
		}
	}
}

//xuất ra binary từ mảng bool
void qfloat::PrintBinary(bool* bit) {
	cout << bit[0] << " ";

	for (int i = 1; i < 16; i++) {
		cout << bit[i];
	}
	cout << " ";

	for (int i = 16; i < 128; i++) {
		cout << bit[i];
	}
}

/*
Hàm kiểm tra xem string có phải toàn là 1 char nào đó không
	Input: string và char a
	Output: true nếu string chứa toàn char a
*/
bool qfloat::CheckAllChar(string input, char a)
{
	for (int i = 0; i < input.length(); i++) {
		if (input[i] != a) {
			return false;
		}
	}
	return true;
}

//Hàm đọc string lưu vào mảng bool
bool* qfloat::StringToBool(string input)
{
	bool* res = new bool[128];  //Lưu kết quả trả về
	int i = 0;

	for (i = 0; i < input.length(); i++) {
		if (input[i] == '1') {
			res[i] = 1;
		}
		else {
			res[i] = 0;
		}
	}
	while (i < 128) {
		res[i] = 0;
		i++;
	}
	return res;
}

//Chuyển chuỗi nhị phân chuẩn IEEE về Qfloat
//(có khả năng tự chuẩn hóa nếu chuỗi không đủ độ dài)
Qfloat qfloat::BinStrToDec(string bin)
{
	int len = bin.length();
	while (len < 128)
	{
		bin = "0" + bin;
		len++;
	}
	while (len > 128)
	{
		bin.erase(0,1);
		len--;
	}
	bool* binArr = StringToBool(bin);
	Qfloat result;
	result = BinToDec(binArr);
	if (binArr != NULL)
		delete[] binArr;
	return result;
}
