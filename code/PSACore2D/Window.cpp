#include "Window.h"

HWND g_wnd;
RECT g_rectClient;
Window* g_window = nullptr;

Window::Window()
{
	g_window = this;
}

LRESULT CALLBACK WndProc(
	HWND wnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	_ASSERT(g_window);
	return g_window->MsgProc(wnd, msg, wParam, lParam);
}

LRESULT Window::MsgProc(
	HWND wnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
#ifdef _DEBUG
	msgList.push_back(msg);
#endif // _DEBUG
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(wnd, msg, wParam, lParam);
}

BOOL Window::InitInstance(const WCHAR* title, UINT width, UINT height)
{
	_wndStyle = WS_OVERLAPPEDWINDOW;
	RECT rect = { 0, 0, LONG(width), LONG(height) };
	AdjustWindowRect(&rect, _wndStyle, FALSE);

#ifdef _DEBUG
	msgList.clear();
#endif

	_wnd = CreateWindowW(
		L"window1",
		title,
		_wndStyle,
		0, 0,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr, nullptr,
		_instance, nullptr);

	if (!_wnd) return FALSE;

	GetWindowRect(_wnd, &_rectWindow);
	GetClientRect(_wnd, &_rectClient);
	_clientWidth = _rectClient.right - _rectClient.left;
	_clientHeight = _rectClient.bottom - _rectClient.top;

	g_wnd = _wnd;
	g_rectClient = _rectClient;

	CentreWindow();
	ShowWindow(_wnd, SW_SHOW);
	return TRUE;
}

void Window::CentreWindow()
{
	UINT screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	UINT screenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	UINT cx = UINT((screenWidth - (_rectWindow.right - _rectWindow.left)) * 0.5f);
	UINT cy = (UINT)((screenHeight - (_rectWindow.bottom - _rectWindow.top)) * 0.5f);

	MoveWindow(_wnd, cx, cy,
		_rectWindow.right - _rectWindow.left,
		_rectWindow.bottom - _rectWindow.top,
		true);
}

ATOM Window::MyRegisterClass()
{
	/*
		WNDCLASSEX contains window class information
		  1) cbSize:		 size of structure in bytes

		  2) style:			 class style in UINT
							 HREDRAW - redraw entire window if width of client area changes
							 VREDRAW - redraw entire window if height of client area changes

		  3) lpfnWndProc:	 pointer to the window procedure

		  4) cbClsExtra:	 number of extra bytes to allocate the window-class struture
							 initialised to zero by system

		  5) cbWndExtra:	 number of extra bytes to allocate the window instance
							 initialised to zero by system

		  6) hInstance:		 handle to the instance containing the window procedure for the class

		  7) hIcon:			 handle to large class icon
							 to use predefined icons, set hInstance param to NULL and LpIconName
							 param to MAKEINTRESOURCE(value) - value: IDI_ERROR, IDI_WARNING...

		  8) hCursor:		 handle to class cursor
							 if set to NULL, shape must be set every time mouse moves to window

		  9) hbrBackground:	 handle to class background brush
							 can be a handle to the brush used for painting
							 or be a colour value that is converted to a HBRUSH type

		  10) lpszMenuName:	 pointer to character string specifying the name of class menu
							 to use integer as menu, use MAKEINTRESOURCE macro

		  11) lpszClassName: pointer to string specifying the window class name

		  12) hIconSm:		 handle to small icon shown in taskbar/titlebar
	*/

	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));

	wcex.cbSize			 = sizeof(WNDCLASSEX);
	wcex.style			 = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance		 = _instance;
	wcex.hbrBackground	 = CreateSolidBrush(RGB(0, 0, 0));
	wcex.lpszClassName	 = L"window1"; 
	wcex.lpfnWndProc	 = WndProc;   
	wcex.hCursor		 = LoadCursorFromFileW(L"../../resource/pink.cur");//LoadCursor(nullptr, IDC_ARROW);

	return RegisterClassEx(&wcex);
}

bool Window::SetWindow(HINSTANCE instance, const WCHAR* title, UINT width, UINT height)
{
	_instance = instance;
	WORD ret = MyRegisterClass();

	if (!InitInstance(title, width, height)) return FALSE;
	return TRUE;
}

/*
void Window::CheckLiveObjects()
{
	HMODULE dxgiDebugDll = GetModuleHandleW(L"dxgidebug.dll");
	decltype(&DXGIGetDebugInterface) GetDebugInterface =
		reinterpret_cast <decltype(&DXGIGetDebugInterface)>
		(GetProcAddress(dxgiDebugDll, "DXGIGetDebugInterface"));

	IDXGIDebug* debug;
	GetDebugInterface(IID_PPV_ARGS(&debug));

	OutputDebugStringW(L"Starting Live Direct3D Object Dump:\r\n");
	debug->ReportLiveObjects(DXGI_DEBUG_D3D11, DXGI_DEBUG_RLO_DETAIL);
	OutputDebugStringW(L"Completed Live Direct3D Object Dump.\r\n");

	debug->Release();
}
*/

bool Window::Run()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
#ifdef GAMECORE
		else
		{
			return true;
		}
#endif		
	}
	return false;
}