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

void CCalculatorDlg::OnBnClickedBtnequal()
{
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


void CCalculatorDlg::OnBnClickedBtnclear()
{
	hisActiveInput = "";
	hisPassiveInput1 = "";
	hisPassiveInput2 = "";
	ResetInput();
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
