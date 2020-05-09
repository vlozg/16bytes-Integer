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

//Reset input screen & input memory
//Parameter:
//	- fullReset: reset về 0 hay hiện kết quả preCalc
void CCalculatorDlg::ResetInput(bool fullReset) 
{
	if (fullReset)
	{
		ActiveInput = "0";
		PassiveInput1 = "0";
		PassiveInput2 = "0";
	}
	else
	{
		GetResultOutput();
	}
	iInput = "0";
}

//Lấy ký hiệu dấu
//Parameter
//- Opr: dấu cần lấy chuỗi ký hiệu
CString CCalculatorDlg::GetOprSymbol(char Opr)
{
	CString symbol;
	switch (Opr)
	{
	case '+':	//Plus
		symbol = '+';
		break;
	case '-':	//Minus
		symbol = '-';
		break;
	case '*':	//Multiply
		symbol = '×';
		break;
	case '/':	//Division
		symbol = '÷';
		break;
	case '&':	//And
		symbol = '&';
		break;
	case '|':	//Or
		symbol = '|';
		break;
	case '^':	//Xor
		symbol = '^';
		break;
	case '~':	//Not
		symbol = '~';
		break;
	case '<':	//Left Shift
		symbol = "<<";
		break;
	case '>':	//Right Shift
		symbol = ">>";
		break;
	case '[':	//Left Rotate
		symbol = "RolL";
		break;
	case ']':	//Right Rotate
		symbol = "RolR";
		break;
	default:
		break;
	}
	return symbol;
}
/*
//Đưa active input vào history và tính toán
//Parameter:
//- Opr: ký tự dấu được đưa vào
void CCalculatorDlg::PushHistoryInput(char Opr)
{
	//Tạo dấu để đưa vào màn hình
	CString symbol, prevSymbol;
	symbol = GetOprSymbol(Opr);
	int prevSymbolLength = GetOprSymbol(prevOpr).GetLength();

	if (isEmptyInput == true)
	{
		//Nếu không input số thì chỉ sửa dấu
		hisActiveInput.Delete(hisActiveInput.GetLength() - prevSymbolLength, prevSymbolLength);
		hisPassiveInput1.Delete(hisPassiveInput1.GetLength() - prevSymbolLength, prevSymbolLength);
		hisPassiveInput2.Delete(hisPassiveInput2.GetLength() - prevSymbolLength, prevSymbolLength);
	}
	else
	{
		hisActiveInput += " ";
		hisPassiveInput1 += " ";
		hisPassiveInput2 += " ";

		//Đưa input vào history
		hisActiveInput += ActiveInput;
		hisPassiveInput1 += PassiveInput1;
		hisPassiveInput2 += PassiveInput2;

		hisActiveInput += " ";
		hisPassiveInput1 += " ";
		hisPassiveInput2 += " ";
	}

	//Đưa dấu vào history
	hisActiveInput += symbol;
	hisPassiveInput1 += symbol;
	hisPassiveInput2 += symbol;
}
*/

//Lấy active input ra và thực hiện tính toán
//Parameter
//- Opr: ký tự dấu được đưa vào
void CCalculatorDlg::PreCalc(char Opr)
{
	switch (Opr)
	{
	case '+':	//Plus
		iOutput = iOutput + iInput;
		break;
	case '-':	//Minus
		iOutput = iOutput - iInput;
		break;
	case '*':	//Multiply
		iOutput = iOutput * iInput;
		break;
	case '/':	//Division
		iOutput = iOutput / iInput;
		break;
	case '&':	//And
		iOutput = iOutput & iInput;
		break;
	case '|':	//Or
		iOutput = iOutput | iInput;
		break;
	case '^':	//Xor
		iOutput = iOutput ^ iInput;
		break;
	case '~':	//Not
		iOutput = ~iOutput;
		break;
	case '<':	//Left Shift
		iOutput = iOutput << iInput;
		break;
	case '>':	//Right Shift
		iOutput = iOutput >> iInput;
		break;
	case '[':	//Left Rotate
		iOutput = iOutput.RotateLeft(iInput);
		break;
	case ']':	//Right Rotate
		iOutput = iOutput.RotateRight(iInput);
		break;
	default:	//Không phát hiện dấu trước đó (aka số đầu tiên)
		iOutput = iInput;
		break;
	}
}

//Handle chung cho các event nhấn nút Operator
//Parameter:
//- Opr: ký tự dấu được đưa vào
void CCalculatorDlg::HandleOprButton(char Opr)
{
	//PushHistoryInput(Opr);	//Cập nhật history

	if (isEmptyInput == false)
	{
		PreCalc(prevOpr);	//Tính toán các opr có trước (nếu có)
		ResetInput(0);
	}

	prevOpr = Opr;	//Đưa dấu vào hàng đợi
	isEmptyInput = true;
	UpdateData(0);
}

void CCalculatorDlg::OnBnClickedBtndot()
{
	// TODO: Add your control notification handler code here
}

//Xử lý khi nhấn nút +
void CCalculatorDlg::OnBnClickedBtnplus()
{
	HandleOprButton('+');
}


void CCalculatorDlg::OnBnClickedBtnminus()
{
	HandleOprButton('-');
}


void CCalculatorDlg::OnBnClickedBtnmultiply()
{
	HandleOprButton('*');
}


void CCalculatorDlg::OnBnClickedBtndivision()
{
	HandleOprButton('/');
}


void CCalculatorDlg::OnBnClickedBtnand()
{
	HandleOprButton('&');
}


void CCalculatorDlg::OnBnClickedBtnor()
{
	HandleOprButton('|');
}


void CCalculatorDlg::OnBnClickedBtnxor()
{
	HandleOprButton('^');
}


void CCalculatorDlg::OnBnClickedBtnnot()
{
	HandleOprButton('~');
}


void CCalculatorDlg::OnBnClickedBtnrightsihft()
{
	HandleOprButton('>');
}


void CCalculatorDlg::OnBnClickedBtnleftshift()
{
	HandleOprButton('<');
}


void CCalculatorDlg::OnBnClickedBtnrolright()
{
	HandleOprButton(']');
}


void CCalculatorDlg::OnBnClickedBtnrolleft()
{
	HandleOprButton('[');
}