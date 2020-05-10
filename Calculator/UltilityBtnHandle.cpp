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

	ResetInput(0);

	prevOpr = '=';
	isEmptyInput = true;
	UpdateDisplay();
}

//Xóa 1 số bên phải ra khỏi active input
void CCalculatorDlg::PopInput()
{
	if (ActiveInput.GetLength() <= 1 || isEmptyInput)
	{
		//Còn 1 số thì reset về 0, không để chuỗi input rỗng
		ActiveInput = "0";
	}
	else
	{
		//Nếu active input nhiều hơn 1 số thì xóa bên phải
		ActiveInput.Delete(ActiveInput.GetLength() - 1);
	}
}

void CCalculatorDlg::OnBnClickedBtnbackspace()
{
	PopInput();

	//Dù có input hay không
	//sửa số tức là muốn thêm input mới
	isEmptyInput = false;

	UpdateAllData();
}

//Xóa sạch mọi dữ liệu
void CCalculatorDlg::OnBnClickedBtnclear()
{
	ResetInput(1);
	iInput = "0";
	iOutput = "0";
	ReadDecString("0", fInput);
	prevOpr = NULL;
	isEmptyInput = false;
	UpdateDisplay();
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

//Hoạt động tương tự như nút số
//đảo dấu số đang hiện trên input màn hình
//số preCalc không bị ảnh hưởng
void CCalculatorDlg::OnBnClickedBtnchangesign()
{
	//Nếu mới bấm calc xong thì sẽ reset lại về trạng thái đầu tiên 
	if (prevOpr == '=' && isEmptyInput)
	{
		prevOpr = NULL;
		iInput = iOutput;
		iOutput = "0";
	}
	
	//Đảo dấu input
	iInput = iInput.ComplementTwo();
	
	CString DecOutput; 
	CString HexOutput;

	DecOutput = iInput.DecStr().c_str();
	HexOutput = iInput.HexStr().c_str();
	/*
	//Hot fix for unexplainable error occur
	if (DecOutput[0] == '-')
	{
		DecOutput.Remove('-');
		DecOutput += '-';
	}
	if (HexOutput[0] == '-')
	{
		HexOutput.Remove('-');
		HexOutput += '-';
	}
	*/
	//Xuất input ra màn hình
	if (mode == 2)
	{
		ActiveInput = iInput.BinStr().c_str();
		PassiveInput1 = DecOutput;
		PassiveInput2 = HexOutput;
	}
	else if (mode == 10)
	{
		ActiveInput = DecOutput;
		PassiveInput1 = iInput.BinStr().c_str();
		PassiveInput2 = HexOutput;
	}
	else
	{
		ActiveInput = HexOutput;
		PassiveInput1 = iInput.BinStr().c_str();
		PassiveInput2 = DecOutput;
	}

	isEmptyInput = false;	//Đánh dấu đã nhận input số

	UpdateDisplay();
}