#pragma once
class ClassSerial
{
public:
	ClassSerial(void);
	~ClassSerial(void);
	// �������� �����
	BOOL OpenPort(CString nPort, DWORD nBaund, BYTE nBite, BYTE nPary, BYTE nSbite);
	// �������� �����
	BOOL ClosePort();
	// ������ ������ �� �����
	int ReadData(BYTE* buffer, int LimitBuffer);
	// �������� � ����
	int SendData(BYTE* buffer, int nLen);
	// �������� ������ � �������� ������
	int WaitLngData();
	// �������� �������� �����
	BOOL IsOpened();
	// ���� ��������
	
	BOOL bOpened;
protected:
	// ���������� ���������� ����������
	HANDLE hComDev;
	OVERLAPPED sOverRead, sOverWrite; //��������� ������������ ������ � ������
};

