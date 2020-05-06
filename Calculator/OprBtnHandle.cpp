// OprBtnHandle.cpp
//	
//	File thiết lập các hàm xử lý event
//	
//	khi người dùng nhấn nút dấu
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////
//
//	CÁCH THỨC HOẠT ĐỘNG
//
//	Khi người dùng nhấn nút dấu, active input sẽ được
//
//	đưa vào history và active input sẽ được reset về 0
//
////////////////////////////////////////////////

//Reset input screen
void CCalculatorDlg::ResetInput() 
{
	ActiveInput = "0";
	PassiveInput1 = "0";
	PassiveInput2 = "0";
	UpdateData(0);
}

void CCalculatorDlg::OnBnClickedBtndot()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnplus()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnminus()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnmultiply()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtndivision()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnand()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnor()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnxor()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnnot()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnrightsihft()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnleftshift()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnrolright()
{
	// TODO: Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedBtnrolleft()
{
	// TODO: Add your control notification handler code here
}