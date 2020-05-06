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


void CCalculatorDlg::OnBnClickedBtnbackspace()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnclear()
{
	// TODO: Add your control notification handler code here
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
