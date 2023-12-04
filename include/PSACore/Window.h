#pragma once
#include "Std.h"

class Window
{
public:
	HINSTANCE	_instance	= nullptr;
	HWND		_wnd		= nullptr;
public:
	RECT		_rectWindow		= { 0,0,0,0 };
	RECT		_rectClient		= { 0,0,0,0 };
	DWORD		_wndStyle		= 0;
	UINT		_clientWidth	= 0;
	UINT		_clientHeight	= 0;
#ifdef _DEBUG
	std::vector<UINT>	msgList;
#endif
public:
	bool				SetWindow(HINSTANCE, const WCHAR*, UINT w=1024, UINT h=768);
	ATOM				MyRegisterClass();
	BOOL				InitInstance(const WCHAR*, UINT, UINT);
	virtual bool		Run();
	void				CentreWindow();
	virtual LRESULT		MsgProc(HWND, UINT, WPARAM, LPARAM);
public:
	//void CheckLiveObjects();
public:
	Window();
};

                                                       