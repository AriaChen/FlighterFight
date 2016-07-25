#include <Windows.h>

// 全局变量
HINSTANCE hinst;
#define TRANSE_BK_COLOR RGB (255,255,255)

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL SpeedUp(HWND hwnd);
BOOL RegisterFlighterClass();
BOOL CreateFlighterWindow();

LONG APIENTRY FlighterWndProc(
	//主窗口例程
	HWND hwnd, //
	UINT msg, // 消息
	WPARAM wParam, // 消息参数
	LPARAM lParam); // 消息参数

BOOL RegisterFlighterClass() 
{
	WNDCLASS wc;
	HWND hwnd;

	MSG msg;
	int fGotMessage;

	wc.style = CS_HREDRAW | CS_VREDRAW; 
	wc.lpfnWndProc = FlighterWndProc;  
	wc.cbClsExtra = 0; 
	wc.cbWndExtra = 0;  
	wc.hInstance = hinst; 
	wc.hIcon = NULL;   
	wc.hCursor = LoadCursor(NULL, IDC_HAND);   
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(TRANSE_BK_COLOR); 
	wc.lpszMenuName = NULL;  
	wc.lpszClassName = "Flighter_Class"; 
	 // Register the window class. 

	if (!RegisterClass(&wc))
	{
		// 窗口注册失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return FALSE;
	}
	// 窗口注册成功，继续运行。
	return TRUE;
}

BOOL CreateFlighterWindow()
{
	HWND hwndFlighter;
	hwndFlighter = CreateWindowEx(
		WS_EX_LAYERED | WS_EX_TOPMOST,
		"Flighter_Class",         // 窗口类名，必须是已经注册了的窗口类
		"",                   // title-bar string 
		WS_POPUP | WS_VISIBLE,  // 窗口的style，这个表示为top-level window 
		CW_USEDEFAULT,                  // 窗口水平位置default horizontal POINT 
		CW_USEDEFAULT,                  // 窗口垂直位置default vertical POINT 
		CW_USEDEFAULT,        // 窗口宽度 default width 
		CW_USEDEFAULT,        // 窗口高度 default height 
		(HWND)NULL,           // 父窗口句柄 no owner window 
		(HMENU)NULL,          // 窗口菜单的句柄 use class menu 
		hinst,            // 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);        // 指向附加数据的指针 no window-creation data 

	if (!hwndFlighter)
	{
		// 窗口创建失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return FALSE;
	}
	// 窗口创建成功，继续运行。

	if (!SetLayeredWindowAttributes(
		hwndFlighter, TRANSE_BK_COLOR,
		255, LWA_COLORKEY | LWA_ALPHA))
	{

	};
	ShowWindow(hwndFlighter, SW_SHOW);

	// 刷新窗口，向窗口发送一个WM_PAINT消息，使得窗口进行重绘。
	UpdateWindow(hwndFlighter);
	return TRUE;
}

int WINAPI WinMain(
	HINSTANCE hinstance, // 程序实例句柄，在程序运行，进程创建后，由操作系统向应用程序传入
	HINSTANCE hPrevInstance, // 父进程的程序实例句柄
	LPSTR lpCmdLine,  // 命令行参数，地位和作用类似C语言main函数参数argc和argv,但是没有按空格进行切分
	int nCmdShow)   // 用于指明窗口是否需要显示的参数。
{

	WNDCLASS wc;
	// 窗口句柄，hwnd变量是主窗口的句柄，这个程序中只用到了一个窗口。
	HWND hwnd;

	MSG msg;
	int fGotMessage;

	hinst = hinstance;

	// Fill in the window class structure with parameters that describe the main window. 

	wc.style = CS_HREDRAW | CS_VREDRAW;  // 窗口类的样式，这里设置的样式表示窗口在大小变化是需要重绘
	wc.lpfnWndProc = MainWndProc;  // 一个函数指针，这个函数用来处理窗口消息。
	wc.cbClsExtra = 0;  // no extra class memory 
	wc.cbWndExtra = 0;  // no extra window memory 
	wc.hInstance = hinstance;  // handle to instance 
	wc.hIcon = LoadIcon(NULL,  // hIcon成员用来指定窗口的图标
		IDI_APPLICATION);   // 这里直接使用LoadIcon函数加载了一个系统预定义的图标，开发人员可也可以自己创建图标。
	wc.hCursor = LoadCursor(NULL, // Cursor是鼠标光标，这里是设定了鼠标光标的样式。
		IDC_HAND);   // 直接使用LoadCursor API函数载入了一个系统预定义的光标样式，还有IDC_CROSS,IDC_HAND等样式 
	wc.hbrBackground = (HBRUSH)GetStockObject( // GetStockObject的功能是加载一个系统预定义（在栈中）的GDI对象，
		WHITE_BRUSH);  // 这里加载的是一个白色的画刷，有关画刷和GDI对象，详见GDI说明。
	wc.lpszMenuName = "MainMenu";  // 窗口的菜单的资源名。
	wc.lpszClassName = "MainWClass"; // 给窗口类起一个名字，在创建窗口时需要这个名字。

									 // Register the window class. 

	if (!RegisterClass(&wc))
	{
		// 窗口注册失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}
	// 窗口注册成功，继续运行。


	// Create the main window. 

	hwnd = CreateWindow(
		"MainWClass",        // 窗口类名，必须是已经注册了的窗口类
		"飞机大战 ~\(^o^)/~ ε=ε=ε=(~￣▽￣)",    // title-bar string 
		WS_OVERLAPPEDWINDOW, // 窗口的style，这个表示为top-level window 
		400,        // 窗口水平位置default horizontal POINT 
		200,        // 窗口垂直位置default vertical POINT 
		CW_USEDEFAULT,        // 窗口宽度 default width 
		CW_USEDEFAULT,        // 窗口高度 default height 
		(HWND)NULL,         // 父窗口句柄 no owner window 
		(HMENU)NULL,        // 窗口菜单的句柄 use class menu 
		hinstance,           // 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);      // 指向附加数据的指针 no window-creation data 

	if (!hwnd)
	{
		// 窗口创建失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}

	// 窗口创建成功，继续运行。

	// 显示窗口，WinMain函数的nCmdShow参数在这里发挥作用，一般都设置为SW_SHOW：
	//Activates the window and displays it in its current size and position.
	ShowWindow(hwnd, nCmdShow);

	// 刷新窗口，向窗口发送一个WM_PAINT消息，使得窗口进行重绘。
	UpdateWindow(hwnd);


	// 以下进入消息循环。获取消息--翻译消息--分配消息（由窗口的消息处理函数来处理消息）
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0
		&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

HBITMAP hbmpSky;

LONG APIENTRY MainWndProc(
	//主窗口例程
	HWND hwnd, //
	UINT msg, // 消息
	WPARAM wParam, // 消息参数
	LPARAM lParam) // 消息参数
{
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	RECT rect;
	// 注意，是switch-case, 每次这个函数被调用，只会落入到一个case中。
	switch (msg)
	{
		// 当窗口被创建时，收到的第一个消息就是WM_CREATE，
		// 一般收到这个消息处理过程中，可以用来进行一些初始化的工作
	case WM_CREATE:
		hbmpSky = LoadImage(NULL, "sky.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (hbmpSky == NULL)
		{
			MessageBox(hwnd, "位图未找到", "ERROR!", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		if (RegisterFlighterClass())
		{
			CreateFlighterWindow();
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, hbmpSky);
		GetClientRect(hwnd, &rect);
		StretchBlt(hdc, rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top,
			hdcMem, 0, 0, 1536, 864, SRCCOPY);
		DeleteDC(hdcMem);
		SelectObject(hdc, hbmpSky);
		EndPaint(hwnd, &ps);
		break;

	case WM_TIMER:

		break;

	case WM_LBUTTONDOWN:

		break;

	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}

HBITMAP hbmpFlighter;

LONG APIENTRY FlighterWndProc(
	//主窗口例程
	HWND hwnd, //
	UINT msg, // 消息
	WPARAM wParam, // 消息参数
	LPARAM lParam) // 消息参数
{
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	RECT rect;
	// 注意，是switch-case, 每次这个函数被调用，只会落入到一个case中。
	switch (msg)
	{
		// 当窗口被创建时，收到的第一个消息就是WM_CREATE，
		// 一般收到这个消息处理过程中，可以用来进行一些初始化的工作
	case WM_CREATE:
		MoveWindow(hwnd, 100, 100, 300, 140, TRUE);
		hbmpFlighter = LoadImage(NULL, "飞机.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (hbmpFlighter == NULL)
		{
			MessageBox(hwnd, "位图未找到", "ERROR!", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, hbmpFlighter);
		GetClientRect(hwnd, &rect);
		StretchBlt(hdc,
			rect.left,
			rect.top,
			rect.right - rect.left,
			rect.bottom - rect.top,
			hdcMem,
			0, 0, 1300, 1002,
			SRCCOPY);
		DeleteDC(hdcMem);
		SelectObject(hdc, hbmpFlighter);
		EndPaint(hwnd, &ps);
		break;

	case WM_TIMER:

		break;

	case WM_LBUTTONDOWN:

		break;

	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}