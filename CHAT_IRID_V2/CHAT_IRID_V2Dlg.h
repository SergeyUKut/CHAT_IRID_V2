
// CHAT_IRID_V2Dlg.h: файл заголовка
//

#pragma once
#include "afxwin.h"
#include "ClassSerial.h"
#include <cstring>
#include <memory>

// Диалоговое окно CCHATIRIDV2Dlg
class CCHATIRIDV2Dlg : public CDialogEx
{
// Создание
public:
	CCHATIRIDV2Dlg(CWnd* pParent = nullptr);	// стандартный конструктор
	
	afx_msg void OnBnClickedButOpport();
	//void InDATA(std::unique_ptr<BYTE[]> buffer, int nLen);
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_IRID_V2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComPort();
	/*afx_msg void OnCbnSelchangeCombo2();
	
	afx_msg void OnCbnSelchangeCombo7();
	afx_msg void OnCbnSelchangeCombo4();*/
	// Выбор прота
	CComboBox comPort;
	// Выбор скорости
	CComboBox comBiteRate;
	// Выбор битности
	CComboBox comBitn;
	// Выбор четности
	CComboBox comPary;
	CComboBox comStopBit;
	afx_msg void OnCbnSelchangeComStopb();
	// Поле ввода для передачи
	CEdit edSend;
	//IEMI
	CStatic IN_IMEI;
	// Поле ввода принятых данных
	CListBox liReceiv;
	ClassSerial cSerial; 
	//CAboutDlg CAboutDlg;
//	afx_msg void OnBnClickedButOpport();
	// Кнопка открытия/закрытия порта
	CButton btPort;
	// Обработка принятых байт
	void InDATA(std::unique_ptr<BYTE[]> buffer, int nLen);
	void InSTATIC(std::unique_ptr<BYTE[]> buffer, int nLen);
//	afx_msg void OnLbnSelchangeLiReceiv();
	afx_msg void OnBnClickedButSend();
	afx_msg void OnBnClickedButClear();
	afx_msg void OnEnChangeEdSend();
	CString str;
	
};
