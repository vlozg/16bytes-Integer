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
	UpdateData(1);
	if (ActiveInput == "0" || isEmptyInput)
	{
		ActiveInput = bInput;
		
		//Nếu mới bấm dấu = thì sẽ reset về lại input mới
		if (prevOpr == '=')
		{
			prevOpr = NULL;
			iOutput = "0";
		}
	}
	else
	{
		ActiveInput += bInput;
	}
	isEmptyInput = false;	//Đánh dấu đã nhận input số
}


void CCalculatorDlg::OnBnClickedBtnnum0()
{
	AddInput('0');
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnum1()
{
	AddInput('1');
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnum2()
{
	AddInput('2'); 
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnum3()
{
	AddInput('3');
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnum4()
{
	AddInput('4');
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnum5()
{
	AddInput('5');
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnum6()
{
	AddInput('6');
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnum7()
{
	AddInput('7');
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnum8()
{
	AddInput('8');
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnum9()
{
	AddInput('9');
	UpdateAllData();
}

void CCalculatorDlg::OnBnClickedBtnnuma()
{
	AddInput('A');
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnumb()
{
	AddInput('B');
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnumc()
{
	AddInput('C');
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnumd()
{
	AddInput('D');
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnume()
{
	AddInput('E');
	UpdateAllData();
}


void CCalculatorDlg::OnBnClickedBtnnumf()
{
	AddInput('F');
	UpdateAllData();
}
