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

void CCalculatorDlg::OnBnClickedBtnnum0()
{
	*ActiveInput += "0";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum1()
{
	*ActiveInput += "1";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum2()
{
	*ActiveInput += "2";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum3()
{
	*ActiveInput += "3";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum4()
{
	*ActiveInput += "4";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum5()
{
	*ActiveInput += "5";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum6()
{
	*ActiveInput += "6";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum7()
{
	*ActiveInput += "7";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum8()
{
	*ActiveInput += "8";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum9()
{
	*ActiveInput += "9";
	UpdateInput();
}

void CCalculatorDlg::OnBnClickedBtnnuma()
{
	*ActiveInput += "A";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnumb()
{
	*ActiveInput += "B";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnumc()
{
	*ActiveInput += "C";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnumd()
{
	*ActiveInput += "D";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnume()
{
	*ActiveInput += "E";
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnumf()
{
	*ActiveInput += "F";
	UpdateInput();
}
