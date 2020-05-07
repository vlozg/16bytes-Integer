
// CalculatorDlg.h : header file
//

#pragma once


// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();

public:
	afx_msg void OnBnClickedBtnnum1();
	afx_msg void OnBnClickedBtnnum2();
	afx_msg void OnBnClickedBtnnum3();
	afx_msg void OnBnClickedBtnnum4();
	afx_msg void OnBnClickedBtnnum5();
	afx_msg void OnBnClickedBtnnum6();
	afx_msg void OnBnClickedBtnnum7();
	afx_msg void OnBnClickedBtnnum8();
	afx_msg void OnBnClickedBtnnum9();
	afx_msg void OnBnClickedBtnchangesign();
	afx_msg void OnBnClickedBtnnum0();
	afx_msg void OnBnClickedBtndot();
	afx_msg void OnBnClickedBtnplus();
	afx_msg void OnBnClickedBtnminus();
	afx_msg void OnBnClickedBtnmultiply();
	afx_msg void OnBnClickedBtndivision();
	afx_msg void OnBnClickedBtnequal();
	afx_msg void OnBnClickedBtnnuma();
	afx_msg void OnBnClickedBtnnumb();
	afx_msg void OnBnClickedBtnnumc();
	afx_msg void OnBnClickedBtnnumd();
	afx_msg void OnBnClickedBtnnume();
	afx_msg void OnBnClickedBtnnumf();
	afx_msg void OnBnClickedBtnand();
	afx_msg void OnBnClickedBtnor();
	afx_msg void OnBnClickedBtnxor();
	afx_msg void OnBnClickedBtnnot();
	afx_msg void OnBnClickedBtnrightsihft();
	afx_msg void OnBnClickedBtnleftshift();
	afx_msg void OnBnClickedBtnrolright();
	afx_msg void OnBnClickedBtnrolleft();
	afx_msg void OnBnClickedBtnbackspace();
	afx_msg void OnBnClickedBtnclear();
	afx_msg void OnBnClickedBtnPassive2();
	afx_msg void OnBnClickedBtnPassive1();

private:
	QInt iOutput, iInput;
	Qfloat fOutput, fOutput;
	char prevOpr = NULL;	//Operator được đưa vào hàng đợi, sẽ được thay thế và tính toán khi input operator mới
	bool isEmptyInput = false;	//Đánh dấu đã input số chưa
	CFont b_Font;
	byte mode = 10;	//Đánh số chế độ: 2=bin 10=dec 16=hex
	void UpdateAllData();
	void ChangeMode_Dec();
	void ChangeMode_Hex();
	void ChangeMode_Bin();
	void ChangeMode_Float();
	void ResetInput();
	void AddInput(char bInput);
	void PopInput();
	void PreCalc(char Opr);
	void HandleOprButton(char Opr);
	CString GetOprSymbol(char Opr);

	CString PassiveInput1;
	CString PassiveInput2;
	CString ActiveInput;

	CEdit t_ActiveInput;
	CEdit t_PassiveInput1;
	CEdit t_PassiveInput2;

	CButton b_Num1;
	CButton b_Num2;
	CButton b_Num3;
	CButton b_Num4;
	CButton b_Num5;
	CButton b_Num6;
	CButton b_Num7;
	CButton b_Num8;
	CButton b_Num9;
	CButton b_Num0;
	CButton b_NumA;
	CButton b_NumB;
	CButton b_NumC;
	CButton b_NumD;
	CButton b_NumE;
	CButton b_NumF;

	CButton b_Equal;
	CButton b_ChangeSign;
	CButton b_Dot;
	CButton b_Del;
	CButton b_Clear;

	CButton b_oprAnd;
	CButton b_oprOr;
	CButton b_oprXor;
	CButton b_oprNot;
	CButton b_oprLeftShift;
	CButton b_oprRightShift;
	CButton b_oprLeftRol;
	CButton b_oprRightRol;

	CButton b_oprPlus;
	CButton b_oprMinus;
	CButton b_oprMultiply;
	CButton b_oprDivision;

	CButton b_Passive1;
	CButton b_Passive2;
};
