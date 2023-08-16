#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	HINSTANCE inst,
	HINSTANCE prevInst,
	PSTR cmdLine,
	int cmdShow
) {
	static char appName[] = "Hello";
	HWND window;
	MSG message;
	WNDCLASSEX windowClass;

	windowClass.cbSize = sizeof(windowClass);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = inst;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = appName;
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&windowClass);

	window = CreateWindowW(
		appName,
		L"Hello",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		inst,
		NULL,
	);

	ShowWindow(window, cmdShow);
	UpdateWindow(window);

	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

LRESULT CALLBACK WindowProc(HWND wind, UINT msg, WPARAM wpar, LPARAM lpar) {
	HDC hdc;
	PAINTSTRUCT paintStruct;
	RECT rect;

	switch (msg) {
	case WM_PAINT:
		hdc = BeginPaint(wind, &paintStruct);
		GetClientRect(wind, &rect);
		DrawTextW(hdc, L"Hey, listen!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(wind, &paintStruct);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(wind, msg, wpar, lpar);
}