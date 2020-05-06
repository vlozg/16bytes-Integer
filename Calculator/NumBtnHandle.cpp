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

////////////////////////////////////////
//
//	CÁCH THỨC NUM BUTTON HOẠT ĐỘNG
//
//	Nếu active input = 0 thì xóa số 0 đi và thêm số mới
//
//	(không để đầu số bằng 0)
//
/////////////////////////////////////////

//Thêm một số vào đuôi active input
//Parameter:
//- bInput: ký tự muốn thêm vào active input
void CCalculatorDlg::AddInput(char bInput)
{
	if (ActiveInput == "0")
	{
		ActiveInput = bInput;
	}
	else
	{
		ActiveInput += bInput;
	}
}


void CCalculatorDlg::OnBnClickedBtnnum0()
{
	AddInput('0');
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum1()
{
	AddInput('1');
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum2()
{
	AddInput('2'); 
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum3()
{
	AddInput('3');
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum4()
{
	AddInput('4');
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum5()
{
	AddInput('5');
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum6()
{
	AddInput('6');
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum7()
{
	AddInput('7');
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum8()
{
	AddInput('8');
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnum9()
{
	AddInput('9');
	UpdateInput();
}

void CCalculatorDlg::OnBnClickedBtnnuma()
{
	AddInput('A');
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnumb()
{
	AddInput('B');
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnumc()
{
	AddInput('C');
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnumd()
{
	AddInput('D');
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnume()
{
	AddInput('E');
	UpdateInput();
}


void CCalculatorDlg::OnBnClickedBtnnumf()
{
	AddInput('F');
	UpdateInput();
}
