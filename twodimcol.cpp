#include <windows.h>
#include <gl\gl.h>

const char mainWndClassName[] = "GLWindow";

void paint() {
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glEnd();

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_PAINT:
		paint();
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

class MyGL {
	HINSTANCE hInstance;
	WNDCLASS wc;
	HWND hWnd;
	HDC hDC;
	HGLRC hRC;
public:
	MyGL(HINSTANCE hInst, int nCmdShow) {
		hInstance = hInst;
		
		memset(&wc, 0, sizeof(wc));
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = mainWndClassName;
		if (!RegisterClass(&wc))
			throw "RegisterClass failed";
	
		if (!(hWnd = CreateWindow(mainWndClassName, NULL, WS_OVERLAPPEDWINDOW,
			0, 0, 800, 600, NULL, NULL, hInstance, NULL)));
			throw "CreateWindow failed";
		if (!(hDC = GetDC(hWnd)))
			throw "GetDC failed";
		
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(pfd));
		pfd.nSize        = sizeof(pfd);
		pfd.nVersion     = 1;
		pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType   = PFD_TYPE_RGBA;
		pfd.cColorBits   = 32;
		pfd.iLayerType   = PFD_MAIN_PLANE;
		int format;
		if (!(format = ChoosePixelFormat( hDC, &pfd )))
			throw "ChoosePixelFormat failed";
		
		if (!SetPixelFormat( hDC, format, &pfd ))
			throw "SetPixelFormat failed";
		

		if (!(hRC = wglCreateContext(hDC)))
			throw "wglCreateContext failed";
		if (!wglMakeCurrent(hDC, hRC))
			throw "wglMakeCurrent failed";
		
		ShowWindow(hWnd, nCmdShow);

	}
	
	~MyGL() {
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRC);
		ReleaseDC(hWnd, hDC);
		DestroyWindow(hWnd);
		UnregisterClass(mainWndClassName, hInstance);
	}
	void loop() {
		MSG msg;
		while(GetMessage(&msg, hWnd, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}	

	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MyGL* myGL;
	try {
		myGL = new MyGL(hInstance, nCmdShow);
	} catch (char* e) {
		MessageBox(NULL, e, NULL, MB_OK);
		delete myGL;
		return 0;
	}

	myGL->loop();
	
	delete myGL;
	return 0;
}
