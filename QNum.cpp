#include "QInt.h"

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

string HexToBinChar(char hex) {
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
char* DecToHex(QInt x) {
	bool* binConvert = DecToBin(x);
	return BinToHex(binConvert);
}


//Chuyen day bit thanh day bool
//Có khởi tạo, nhớ delete
//Lấy bit từ x -> dãy bool 128 phần tử
bool* DecToBin(QInt x)
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
QInt BinToDec(bool* bin)
{
	QInt result;

	for (int i = 0; i < BIT_RANGE; i++)
	{
		result.SetBit(i, bin[i]);
	}
	return result;
}

//Xuất bin
void OutputBin(bool* bin)	
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
void OutputHex(char* hex)
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
bool* HexToBin(char* hex)
{
	string bin_str = "";
	bool* bin = new bool[128];


	int len = strlen(hex);
	for (int i = 0; i < len; i++)
	{
		bin_str += HexToBinChar(hex[i]);
	}
	for (int i = 0; i < bin_str.length(); i++)
	{
		bin[i] = bin_str[i] - '0';
	}

	return bin;
}


QInt HexToDec(char* hex)
{
	bool* bin = HexToBin(hex);
	QInt a;
	a = BinToDec(bin);
	return a;
}

