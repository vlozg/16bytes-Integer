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
}

//Đưa active input vào history và tính toán
//Parameter:
//- Opr: ký tự dấu được đưa vào
void CCalculatorDlg::PushHistoryInput(char Opr)
{
	//Đưa input vào history
	hisActiveInput += ActiveInput;
	hisPassiveInput1 += PassiveInput1;
	hisPassiveInput2 += PassiveInput2;

	//Đưa dấu vào history
	hisActiveInput += Opr;
	hisPassiveInput1 += Opr;
	hisPassiveInput2 += Opr;
}

//Lấy active input ra và thực hiện tính toán
void CCalculatorDlg::PreCalc(char Opr)
{
	switch (Opr)
	{
	case '+':	//Plus
		break;
	case '-':	//Minus
		break;
	case '*':	//Multiply
		break;
	case '/':	//Division
		break;
	case '&':	//And
		break;
	case '|':	//Or
		break;
	case '^':	//Xor
		break;
	case '~':	//Not
		break;
	case '<':	//Left Shift
		break;
	case '>':	//Right Shift
		break;
	case '[':	//Left Rotate
		break;
	case ']':	//Right Rotate
		break;
	default:
		break;
	}
}

void CCalculatorDlg::OnBnClickedBtndot()
{
	// TODO: Add your control notification handler code here
}

//Xử lý khi nhấn nút +
void CCalculatorDlg::OnBnClickedBtnplus()
{
	PushHistoryInput('+');	//Cập nhật history

	PreCalc(prevOpr);	//Tính toán các opr có trước (nếu có)
	prevOpr = '+';	//Đưa dấu vào hàng đợi
	ResetInput();
	UpdateData(0);
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