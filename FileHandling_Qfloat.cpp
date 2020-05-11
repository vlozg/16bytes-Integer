#include "FileHandling.h"

using namespace qfloat;

//Hàm đọc file 
void qfloat::ReadFile(string input, string output)
{
	Qfloat number;

	//tạo file txt output mới
	freopen(output.c_str(), "w", stdout);
	fclose(stdout);

	freopen(input.c_str(), "rt", stdin);
	while (!cin.eof()) {
		string p1 = ""; //chứa số đầu tiên để xác định hệ để xử lý
		string p2 = ""; //chứa số thứ 2 để xác định hệ chuyển
		string inputNumber;
		getline(cin, inputNumber); //lấy cả dòng 

		int space = 0; //biến dùng để đếm số dấu cách trong dòng

		//đếm số dấu cách trong string
		for (int i = 0; i < inputNumber.length(); i++) {
			if (inputNumber[i] == ' ') {
				space++;
			}
		}

		//lấy p1
		int e = 0; //biến đếm số kí tự của p1
		for (int i = 0;; i++) {
			if (inputNumber[i] == ' ') {
				break;
			}
			p1 += inputNumber[i];
			e++;
		}
		inputNumber.erase(inputNumber.begin(), inputNumber.begin() + e + 1); //xóa p1 và dấu cách

		//lấy p2
		if (space == 2) { //có 2 dấu cách
			e = 0;
			for (int i = 0;; i++) {
				if (inputNumber[i] == ' ') {
					break;
				}
				p2 += inputNumber[i];
				e++;
			}
			inputNumber.erase(inputNumber.begin(), inputNumber.begin() + e + 1); //xóa p2 và dấu cách
		}

		//xử lý p1 p2 để scan
		if (p1 == "2") {
			bool* binary = StringToBool(inputNumber);
			if (p2 == "") { //nhập hệ 2 xuất hệ 2
				freopen(output.c_str(), "a", stdout);
				PrintBinary(binary);
				cout << endl;
				fclose(stdout);
			}
			else { //nhập hệ 2 xuất hệ 10
				freopen(output.c_str(), "a", stdout);
				number = BinToDec(binary);
				PrintQfloat(number);
				cout << endl;
				fclose(stdout);
			}
		}
		else {
			ReadDecString(inputNumber, number); //đọc và lưu vào Qfloat
			if (p2 == "") { //nhập hệ 10 xuất hệ 10
				freopen(output.c_str(), "a", stdout);
				PrintQfloat(number);
				cout << endl;
				fclose(stdout);
			}
			else { //nhập hệ 10 xuất hệ 2
				freopen(output.c_str(), "a", stdout);
				bool* binary = DecToBin(number);
				PrintBinary(binary);
				cout << endl;
				fclose(stdout);
			}
		}
	}
	fclose(stdin);
}