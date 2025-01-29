#pragma once
class ClassSerial
{
public:
	ClassSerial(void);
	~ClassSerial(void);
	// Открытие порта
	BOOL OpenPort(CString nPort, DWORD nBaund, BYTE nBite, BYTE nPary, BYTE nSbite);
	// Закрытие порта
	BOOL ClosePort();
	// Чтение данных из порта
	int ReadData(BYTE* buffer, int LimitBuffer);
	// Передача в порт
	int SendData(BYTE* buffer, int nLen);
	// Проверка данных в приемном буфере
	int WaitLngData();
	// Проверка открытия порта
	BOOL IsOpened();
	// Флаг открытия
	
	BOOL bOpened;
protected:
	// Дискриптор созданного устройства
	HANDLE hComDev;
	OVERLAPPED sOverRead, sOverWrite; //Структуры асинхронного чтения и записи
};

