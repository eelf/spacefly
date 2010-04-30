#include <windows.h>

LPCTSTR wcName = "R";
HWND label1;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow) {
    WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
    wc.style          = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc    = WndProc;
    wc.hInstance      = hInstance;
    wc.hbrBackground  = (HBRUSH) COLOR_BACKGROUND;
	wc.hCursor		  = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon		  = LoadIcon((HINSTANCE) NULL, IDI_APPLICATION);
    wc.lpszClassName  = wcName;

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "RegisterClass failed", NULL, 0);
        return 1;
    }

    HWND hWnd = CreateWindow(
        wcName,
        NULL,
        WS_OVERLAPPED,
        CW_USEDEFAULT, CW_USEDEFAULT,
        320, 180,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd) {
        MessageBox(NULL, "CreateWindow failed", NULL, 0);
        return 1;
    }
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        //TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
	case WM_CREATE:
		label1 = CreateWindow("static", NULL, WS_CHILD | WS_VISIBLE,
			0, 0, 60, 20,
			hWnd, (HMENU) 1, (HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_KEYUP:
		if (wParam == 27)
		    PostQuitMessage(0);
		CHAR str[20];
		wsprintf(str, "%d %x", wParam, wParam);
		SetWindowText(label1, str);
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}
