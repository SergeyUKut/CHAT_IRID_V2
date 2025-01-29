#include "pch.h"
#include"afxwin.h"
#include "ClassSerial.h"
//Конструктор
  ClassSerial::ClassSerial(void)
    :bOpened(false) 
{
    hComDev = NULL;
     
}
//Деконструк
ClassSerial::~ClassSerial(void)
{

}

// Открытие порта
BOOL ClassSerial::OpenPort(CString nPort, DWORD nBaund, BYTE nBite, BYTE nPary, BYTE nSbite)
{
    if (bOpened) //proverka otkrytia
        return bOpened;
    hComDev = CreateFile(nPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
       if (hComDev == NULL) //Проверка успеха создания порта
         return FALSE; 
   memset(&sOverRead, 0, sizeof(OVERLAPPED)); //Очистка сруктуры чтения
   memset(&sOverWrite, 0, sizeof(OVERLAPPED)); //Очистка сруктуры записи
   sOverRead.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
   sOverWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
   COMMTIMEOUTS ComTimeOut; //Структура тайаутов компорта
   ComTimeOut.ReadIntervalTimeout = MAXDWORD;
   ComTimeOut.ReadTotalTimeoutMultiplier = 0;
   ComTimeOut.ReadTotalTimeoutConstant = 0;
   ComTimeOut.WriteTotalTimeoutMultiplier = 0;
   ComTimeOut.WriteTotalTimeoutConstant = 5000;
   SetCommTimeouts(hComDev, &ComTimeOut);
   DCB sDCB; //структура настроек порта
   sDCB.DCBlength = sizeof(DCB);
   GetCommState (hComDev, &sDCB);
   sDCB.BaudRate = nBaund;
   sDCB.ByteSize = nBite;
   sDCB.Parity = nPary;
   sDCB.StopBits = nSbite;
   if (!SetCommState(hComDev, &sDCB) || (!SetupComm(hComDev, 10000, 10000)) || (sOverRead.hEvent == NULL) || (sOverWrite.hEvent == NULL) )
   {
       DWORD dwError = GetLastError();//Получение последней ошибки
       if (sOverRead.hEvent != NULL)
           CloseHandle(sOverRead.hEvent);//Закрытие дискриптора чтения
       if (sOverWrite.hEvent != NULL)
           CloseHandle(sOverWrite.hEvent);//закрытие дискриптора Записи
       CloseHandle(hComDev); //Закрытие соединения
       return FALSE;

   }
   bOpened = TRUE;
   return TRUE;
}


// Закрытие порта
BOOL ClassSerial::ClosePort(void)
{
    if ((!bOpened || hComDev) == NULL)
        return TRUE;
    if (sOverRead.hEvent != NULL)
        CloseHandle(sOverRead.hEvent);//Закрытие дискриптора чтения
    if (sOverWrite.hEvent != NULL)
        CloseHandle(sOverWrite.hEvent);//закрытие дискриптора Записи
      
    bOpened = FALSE;
    hComDev = NULL;
    return TRUE;
}


// Чтение данных из порта
int ClassSerial::ReadData(BYTE* buffer, int LimitBuffer)
{
    if ((!bOpened || hComDev) == NULL)
    return 0;
    DWORD dwError;
    COMSTAT ComStat;
    ClearCommError(hComDev, &dwError, &ComStat);
    if (!ComStat.cbInQue)
         return 0;
    DWORD dwByteRead = ComStat.cbInQue;
    if (LimitBuffer < (int)dwByteRead)
        dwByteRead = (DWORD)LimitBuffer;
  BOOL bReadStatus =  ReadFile(hComDev, buffer, dwByteRead, &dwByteRead, &sOverRead);
  if (!bReadStatus) 
  {
      if (GetLastError() == ERROR_IO_PENDING) 
      {
          WaitForSingleObject(sOverRead.hEvent, 2000);
          return (int)dwByteRead;
      }
      return 0;
  }

  return (int)dwByteRead;


}


// Передача в порт
int ClassSerial::SendData(BYTE* buffer, int nLen)
{
    if ((!bOpened || hComDev) == NULL)
        return 0;

    DWORD dwWrByte;
    BOOL bWrState = WriteFile(hComDev, buffer, nLen, &dwWrByte, &sOverWrite);
    if (!bWrState && (GetLastError() == ERROR_IO_PENDING)) {
        if (WaitForSingleObject(sOverWrite.hEvent, 100))
            dwWrByte = 0;
        else {
            GetOverlappedResult(hComDev, &sOverWrite, &dwWrByte, FALSE);
            sOverWrite.Offset += dwWrByte;
        }
     }

    return dwWrByte;
}


// Проверка данных в приемном буфере
int ClassSerial::WaitLngData()
{
    if ((!bOpened || hComDev) == NULL)
        return 0;

    DWORD dwError;
    COMSTAT ComStat;
    ClearCommError(hComDev, &dwError, &ComStat);

    return (int)ComStat.cbInQue;
}


// Проверка открытия порта
BOOL ClassSerial::IsOpened()
{
    // TODO: Добавьте сюда код реализации.
    return bOpened;
}
