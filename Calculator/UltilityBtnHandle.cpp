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
