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
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnbackspace()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnclear()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnhex()
{
	ActiveInput = &HexInput;
}


void CCalculatorDlg::OnBnClickedBtnbin()
{
	ActiveInput = &BinInput;
}
