
// CHAT_IRID_V2.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


//
// Сведения о реализации этого класса: CHAT_IRID_V2.cpp
//

class CCHATIRIDV2App : public CWinApp
{
public:
	CCHATIRIDV2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CCHATIRIDV2App theApp;
