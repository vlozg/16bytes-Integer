// NumBtnHandle.cpp
//	
//	File thiết lập các hàm xử lý event
//	
//	khi người dùng nhấn nút số
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//Xuất kết quả ra screen
void CCalculatorDlg::GetResultOutput()
{
	if (mode == 2)
	{
		ActiveInput = iOutput.BinStr().c_str();
		PassiveInput1 = iOutput.DecStr().c_str();
		PassiveInput2 = iOutput.HexStr().c_str();
	}
	else if (mode == 10)
	{
		ActiveInput = iOutput.DecStr().c_str();
		PassiveInput1 = iOutput.BinStr().c_str();
		PassiveInput2 = iOutput.HexStr().c_str();
	}
	else
	{
		ActiveInput = iOutput.HexStr().c_str();
		PassiveInput1 = iOutput.BinStr().c_str();
		PassiveInput2 = iOutput.DecStr().c_str();
	}
}

void CCalculatorDlg::OnBnClickedBtnequal()
{
	PreCalc(prevOpr);	//Tính toán lần cuối

	GetResultOutput();

	prevOpr = '=';
	isEmptyInput = true;
	UpdateData(0);
}

//Xóa 1 số bên phải ra khỏi active input
void CCalculatorDlg::PopInput()
{
	if (ActiveInput.GetLength() > 1)
	{
		//Nếu active input nhiều hơn 1 số thì xóa bên phải
		ActiveInput.Delete(ActiveInput.GetLength()-1);
	}
	else
	{
		//Còn 1 số thì reset về 0, không để chuỗi input rỗng
		ActiveInput = "0";
	}
}

void CCalculatorDlg::OnBnClickedBtnbackspace()
{
	PopInput();
	UpdateAllData();
}

//Xóa sạch mọi dữ liệu
void CCalculatorDlg::OnBnClickedBtnclear()
{
	ResetInput(1);
	iInput = "0";
	iOutput = "0";
	prevOpr = NULL;
	isEmptyInput = false;
	UpdateData(0);
}


void CCalculatorDlg::OnBnClickedBtnPassive2()
{
	if (mode == 16)
	{
		ChangeMode_Dec();
	}
	else
	{
		ChangeMode_Hex();
	}
}


void CCalculatorDlg::OnBnClickedBtnPassive1()
{
	if (mode == 2)
	{
		ChangeMode_Dec();
	}
	else
	{
		ChangeMode_Bin();
	}
}

//Hoạt động tương tự như nút số
//đảo dấu số đang hiện trên input màn hình
//số preCalc không bị ảnh hưởng
void CCalculatorDlg::OnBnClickedBtnchangesign()
{
	//Nếu mới bấm calc xong thì sẽ reset lại về trạng thái đầu tiên 
	if (prevOpr == '=' && isEmptyInput)
	{
		prevOpr = NULL;
		iInput = iOutput;
		iOutput = "0";
	}
	
	//Đảo dấu input
	iInput = iInput.ComplementTwo();
	
	//Xuất input ra màn hình
	if (mode == 2)
	{
		ActiveInput = iInput.BinStr().c_str();
		PassiveInput1 = iInput.DecStr().c_str();
		PassiveInput2 = iInput.HexStr().c_str();
	}
	else if (mode == 10)
	{
		ActiveInput = iInput.DecStr().c_str();
		PassiveInput1 = iInput.BinStr().c_str();
		PassiveInput2 = iInput.HexStr().c_str();
	}
	else
	{
		ActiveInput = iInput.HexStr().c_str();
		PassiveInput1 = iInput.BinStr().c_str();
		PassiveInput2 = iInput.DecStr().c_str();
	}

	isEmptyInput = false;	//Đánh dấu đã nhận input số

	UpdateData(0);
}