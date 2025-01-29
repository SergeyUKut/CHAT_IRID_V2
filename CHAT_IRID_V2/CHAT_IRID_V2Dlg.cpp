
// CHAT_IRID_V2Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "CHAT_IRID_V2.h"
#include "CHAT_IRID_V2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnCbnSelchangeComPort();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}



void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUT_OPPORT, &CCHATIRIDV2Dlg::OnBnClickedButOpport)
	ON_CBN_SELCHANGE(IDC_COM_PORT, &CAboutDlg::OnCbnSelchangeComPort)
END_MESSAGE_MAP()


// Диалоговое окно CCHATIRIDV2Dlg



CCHATIRIDV2Dlg::CCHATIRIDV2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT_IRID_V2_DIALOG, pParent)
	, str(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCHATIRIDV2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_PORT, comPort);
	DDX_Control(pDX, IDC_COM_BITRATE, comBiteRate);
	DDX_Control(pDX, IDC_COM_BITN, comBitn);
	DDX_Control(pDX, IDC_COM_PARY, comPary);
	DDX_Control(pDX, IDC_COM_STOPB, comStopBit);
	DDX_Control(pDX, IDC_ED_SEND, edSend);
	DDX_Control(pDX, IDC_LI_RECEIV, liReceiv);
	DDX_Control(pDX, IDC_BUT_OPPORT, btPort);
	DDX_LBString(pDX, IDC_LI_RECEIV, str);
}

BEGIN_MESSAGE_MAP(CCHATIRIDV2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()

//	ON_CBN_SELCHANGE(IDC_COM_STOPB, &CCHATIRIDV2Dlg::OnCbnSelchangeComStopb)
	ON_BN_CLICKED(IDC_BUT_OPPORT, &CCHATIRIDV2Dlg::OnBnClickedButOpport)
//	ON_LBN_SELCHANGE(IDC_LI_RECEIV, &CCHATIRIDV2Dlg::OnLbnSelchangeLiReceiv)
	ON_BN_CLICKED(IDC_BUT_SEND, &CCHATIRIDV2Dlg::OnBnClickedButSend)
	ON_BN_CLICKED(IDC_BUT_CLEAR, &CCHATIRIDV2Dlg::OnBnClickedButClear)
	ON_EN_CHANGE(IDC_ED_SEND, &CCHATIRIDV2Dlg::OnEnChangeEdSend)
END_MESSAGE_MAP()


// Обработчики сообщений CCHATIRIDV2Dlg

BOOL CCHATIRIDV2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CCHATIRIDV2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CCHATIRIDV2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CCHATIRIDV2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Поток приема данных
 UINT StreamData(LPVOID pParam) {
	CCHATIRIDV2Dlg* ChatDlg = (CCHATIRIDV2Dlg*)pParam; //Получение дескриптора основного класса
	int iInDat = 0, iInOldDat = 0;
	while (ChatDlg->cSerial.IsOpened())  // цикл пока открыто соединение
	{
		iInDat = ChatDlg->cSerial.WaitLngData(); //Проверка кол-ва данных в буфере приема
		if (iInDat != 0) 
		{
			if (iInDat != iInOldDat)  //Проверка именения кол-ва данных в буфере
			{   
				BYTE* buffer = new BYTE[iInDat]; // выделение места под буфер приёма
				iInDat = ChatDlg->cSerial.ReadData(buffer, iInDat); 
				if (iInDat > 0)
				//	ChatDlg->MessageBoxA((CString)buffer);
					ChatDlg->InDATA(buffer, iInDat); //Переход на обработку и вывод
				
				iInDat = iInOldDat = 0;
				
				delete[] buffer;
			}
			else {
				iInDat = iInOldDat;
				Sleep(10);
				//delete[] buffer;
			}
		}
		else
			Sleep(10);
		 

		
	}
	//if (!ChatDlg->cSerial.IsOpened()) { AfxEndThread(0, 1); }
	AfxEndThread(0, 1);
	return 0;

}
//Открытие закрытие порта

afx_msg void CCHATIRIDV2Dlg:: OnBnClickedButOpport()
{
	if (!cSerial.IsOpened()) 
	{
		CString strPort, strBiteRate, strBitN;
		comPort.GetWindowTextA(strPort); // получение названия порта
		comBiteRate.GetWindowTextA(strBiteRate);//Получение скорости
		comBitn.GetWindowTextA(strBitN);
		int iPary = comPary.GetCurSel();
		int iStopB = comStopBit.GetCurSel();
		if (cSerial.OpenPort(strPort, atoi(strBiteRate), atoi(strBitN), iPary, iStopB)) 
		{
				btPort.SetWindowText("Закрыть");//вывод в кнопку приоткрытии порта
				comPort.EnableWindow(false); //блокировка списка параметров
				comBiteRate.EnableWindow(false);
				comBitn.EnableWindow(false);
				comPary.EnableWindow(false);
				comStopBit.EnableWindow(false);
				AfxBeginThread(StreamData, this); //Запуск потока
			}


	}  else {
		cSerial.ClosePort();
		btPort.SetWindowText("Открыть");//вывод в кнопку закрытии порта
		comPort.EnableWindow(true); //Разблокировка списка параметров
		comBiteRate.EnableWindow(true);
		comBitn.EnableWindow(true);
		comPary.EnableWindow(true);
		comStopBit.EnableWindow(true);
	      }
	 
}


// Обработка принятых байт
void CCHATIRIDV2Dlg::InDATA(BYTE* buffer, int nLen)
{
	CString sDATA;
	for (int i = 0; i < nLen; i++)
		sDATA += buffer[i];
	//this->MessageBoxA((CString)buffer);
	liReceiv.AddString(sDATA); //ввод данных в список
	delete[] buffer;
}


//void CCHATIRIDV2Dlg::OnLbnSelchangeLiReceiv()
//{
	// TODO: добавьте свой код обработчика уведомлений
//}

//передача в порт
void CCHATIRIDV2Dlg::OnBnClickedButSend()
{
	CString sOutData;

	edSend.GetWindowText(sOutData);
	int iLen = sOutData.GetLength();
	BYTE* buffer = new BYTE[iLen];
	
	for (int i = 0; i < iLen; i++)
		buffer[i] =  sOutData[i];
	int iTX = cSerial.SendData(buffer, iLen);
	if (iTX = iLen)
		//this->MessageBoxA((CString)buffer);
	delete[] buffer;
	if (iTX != iLen)
		this->MessageBoxA("Не удалось передать");

	

	
}


void CCHATIRIDV2Dlg::OnBnClickedButClear()
{
	liReceiv.ResetContent();
}


void CAboutDlg::OnCbnSelchangeComPort()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CCHATIRIDV2Dlg::OnEnChangeEdSend()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}
