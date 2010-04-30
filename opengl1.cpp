#include <math.h>
#include "opengl_common.cpp"

#define M_180_DIV_PI 0.017453

float abssum(float a, float b) {
	if (a >= 0.0 && a + b < 0 ||
		a < 0.0 && a - b > 0.0) return 0.0;
	return a >= 0 ? a + b : a - b;
}

class Camera {
	public: float camx,camy,camz,camr,camq;
	float cavx,cavy,cavz,cavr,cavq;
	float a, b;
	int v;

	Camera() {
		init();
	}
	void init() {
		camx = 0.0;
		camy = 0.0;
		camz = 0.0;
		camq = 0.0;
		camr = 0.0;
		cavx = 0.0;
		cavy = 0.0;
		cavz = 0.0;
		cavq = 0.0;
		cavr = 0.0;
		a = -0.0005;
		b = -0.0005;
		v = 0;
	}
	void switchview() {
		v++;
		switch(v & 0x3) {
		case 0: camq =   0.0; break;
		case 1: camq =  90.0; break;
		case 2: camq = 180.0; break;
		case 3: camq = 270.0; break;
		}
		switch (v >> 2 & 0x3) {
		case 0: camr =   0.0; break;
		case 1: camr =  90.0; break;
		case 2: camr = 180.0; break;
		case 3: camr = 270.0; break;
		}
	}
	void accel() {
		cavx = abssum(cavx, a);
		cavy = abssum(cavy, a);
		cavz = abssum(cavz, a);
		cavq = abssum(cavq, b);
		cavr = abssum(cavr, b);
	}
	void inert() {
		camx += cavx;
		camy += cavy;
		camz += cavz;
		camq += cavq;
		camr += cavr;
		accel();
		checkCam();
	}
	// forward upward right
	void move(float f, float u, float r) {
		float sinr = float(sin(camr * M_180_DIV_PI));
		float cosr = float(cos(camr * M_180_DIV_PI));
		
		float cosq = float(cos(camq * M_180_DIV_PI));
		float sinq = float(sin(camq * M_180_DIV_PI));
		
		cavy += (-f * sinr            + u * cosr) * 0.05;
		cavx += ( f * sinq + r * cosq + u * sinr * sinq) * 0.05;
		cavz += (-f * cosq + r * sinq - u * sinr * cosq) * 0.05;
		
	}
	// horisontal vertical
	void rotate(float h, float v) {
		cavq += h * 0.05;
		cavr += v * 0.05;
	}
	void checkCam() {
		if (this->camx < -10.0f) this->camx = -10.0f;
		if (this->camx > 10.0f) this->camx = 10.0f;
		if (this->camz < -10.0f) this->camz = -10.0f;
		if (this->camz > 10.0f) this->camz = 10.0f;
		if (this->camy < -10.0f) this->camy = -10.0f;
		if (this->camy > 1.0f) this->camy = 1.0f;
		if (this->camq < 0.0f) this->camq = 360.0f;
		if (this->camq > 360.0f) this->camq = 0.0f;
		if (this->camr < 0.0f) this->camr = 360.0f;
		if (this->camr > 360.0f) this->camr = 0.0f;

		if (this->cavx < -1.0f) this->cavx = -1.0f;
		if (this->cavx >  1.0f) this->cavx =  1.0f;
		if (this->cavy < -1.0f) this->cavy = -1.0f;
		if (this->cavy >  1.0f) this->cavy =  1.0f;
		if (this->cavz < -1.0f) this->cavz = -1.0f;
		if (this->cavz >  1.0f) this->cavz =  1.0f;
		if (this->cavq < -1.0f) this->cavq = -1.0f;
		if (this->cavq >  1.0f) this->cavq =  1.0f;
		if (this->cavr < -1.0f) this->cavr = -1.0f;
		if (this->cavr >  1.0f) this->cavr =  1.0f;
	}
};
Camera cam;





void DrawNet(GLfloat size, GLint LinesX, GLint LinesZ) {
	glBegin(GL_LINES);
	for (int xc = 0; xc < LinesX; xc++) {
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
					0.0,
					size / 2.0);
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
					0.0,
					size / -2.0);
	}
	for (int zc = 0; zc < LinesX; zc++) {
		glVertex3f(	size / 2.0,
					0.0,
					-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
		glVertex3f(	size / -2.0,
					0.0,
					-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
	}
	glEnd();
}

void DrawPrism(float x, float y, float z, float yrot, float zrot, float width, float height, float depth) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glRotatef(zrot, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glColor3f(0.5, 0.5, 0.5);
		glVertex3f(-width, -height, -depth); // нижняя
		glVertex3f( width, -height, -depth);
		glVertex3f( width, -height,  depth);
		glVertex3f(-width, -height,  depth);

		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(-width, -height, -depth); // левая
		glVertex3f(-width,  height, -depth);
		glVertex3f(-width,  height,  depth);
		glVertex3f(-width, -height,  depth);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f( width, -height, -depth); // правая
		glVertex3f( width,  height, -depth);
		glVertex3f( width,  height,  depth);
		glVertex3f( width, -height,  depth);

		glColor3f(9.0, 9.0, 0.9);
		glVertex3f(-width,  height, -depth); // верхняя
		glVertex3f( width,  height, -depth);
		glVertex3f( width,  height,  depth);
		glVertex3f(-width,  height,  depth);

	glEnd();
	glPopMatrix();

}
void DrawCoords() {
	glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
	glEnd();
}
void DrawWalls() {
	glColor3f(0.1,0.1,0.1);      // Установим синий цвет только один раз
	glPushMatrix();
	glTranslatef(0.0f,-2.0f,0.0f);          // Сдвиг вправо на 1.5
	DrawNet(20.0f, 30, 30);
	glPopMatrix();

	glColor3f(0.0,0.0,1.0);      // Установим синий цвет только один раз
	glPushMatrix();
	glTranslatef(10.1,8.0,0.0);          // Сдвиг вправо на 1.5
	glRotatef(90.0,0.0,0.0,1.0);
	DrawNet(20.0f, 30, 30);
	glPopMatrix();

	glColor3f(1.0,1.0,0.0);      // Установим синий цвет только один раз
	glPushMatrix();
	glTranslatef(0.0,8.0,-10.1);          // Сдвиг вправо на 1.5
	glRotatef(90.0,1.0,0.0,0.0);
	DrawNet(20.0f, 30, 30);
	glPopMatrix();
}
float distraw(float x1, float y1, float z1, float x2, float y2, float z2) {
	float dx, dy, dz;
	dx = x2 - x1;
	dy = y2 - y1;
	dz = z2 - z1;
	return dx * dx + dy * dy + dz * dz;
}
float dist(float x1, float y1, float z1, float x2, float y2, float z2) {
	return sqrt(distraw(x1, y1, z1, x2, y2, z1));
}
class MassObject {
	public: float mass, x, y, z, q, r, vx, vy, vz, vq, vr, v;
	MassObject(float cmass, float cx, float cy, float cz) {
		mass = cmass;
		x = cx;
		y = cy;
		z = cz;
	}
	void draw() {
		x += vx;
		y += vy;
		z += vz;
		DrawPrism(x, y, z, q, r, 0.1, 0.1, 0.1);
	}
	void gravity(MassObject *o) {
		float dist = distraw(x, y, z, o->x, o->y, o->z);
		float a = o->mass / dist;
		v += a;
		//vx = (x - o->x) * v;
	}
	
};
int DrawGLScene( GLvoid ) {               // Здесь будет происходить вся прорисовка
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );      // Очистить экран и буфер глубины
	glLoadIdentity();              // Сбросить текущую матрицу
	
	glRotatef(cam.camr,1.0f,0.0f,0.0f);
	glRotatef(cam.camq,0.0f,1.0f,0.0f);
	glTranslatef(cam.camx, cam.camy, cam.camz);
	cam.inert();
	DrawCoords();
	DrawWalls();
	DrawPrism(-2.0, 0.0, -2.0, 0.0, 0.0, 1.0, 1.0, 1.0);
	
	return true;                // Прорисовка прошла успешно
}

/*
	GLfloat h=2.0f,v=0.0f,a=-0.00001f;           // Угол для треугольник

	формулы ускорения скорости и высоты, упругий отскок с заданной скоростью
	v = v + a;
	h = h + v;
	if (h < -1.9f) v = 0.006f;
*/

BOOL  done = false;            // Логическая переменная для выхода из цикла

void onKeyDown(int key) {
	switch(key) {
	case VK_ESCAPE: done = true; break;
	case 'W': cam.move(-1.0, 0.0, 0.0); break;
	case 'S': cam.move( 1.0, 0.0, 0.0); break;
	case 'E': cam.move(0.0, 0.0, -1.0); break;
	case 'Q': cam.move(0.0, 0.0,  1.0); break;
	case 'R': cam.move(0.0, -1.0, 0.0); break;
	case 'F': cam.move(0.0,  1.0, 0.0); break;
	case 'A': cam.rotate(-1.0,  0.0); break;
	case 'D': cam.rotate( 1.0,  0.0); break;
	case 'T': cam.rotate( 0.0, -1.0); break;
	case 'G': cam.rotate( 0.0,  1.0); break;
	}
}
void onKeyUp(int key) {
	switch (key) {
	case 'C': cam.switchview(); break;
	}
}




int WINAPI WinMain(  HINSTANCE  hInstance,        // Дескриптор приложения
      HINSTANCE  hPrevInstance,        // Дескриптор родительского приложения
      LPSTR    lpCmdLine,        // Параметры командной строки
      int    nCmdShow ) {       // Состояние отображения окна
	MSG  msg;              // Структура для хранения сообщения Windows
	// Спрашивает пользователя, какой режим экрана он предпочитает
	/*
	if( MessageBox( NULL, "Хотите ли Вы запустить приложение в полноэкранном режиме?",  "Запустить в полноэкранном режиме?", MB_YESNO | MB_ICONQUESTION) == IDNO ) {
		fullscreen = false;          // Оконный режим
	}
	*/
	// Создать наше OpenGL окно
	if( !CreateGLWindow( "OpenGL", 800, 600, 32, fullscreen ) ) {
		return 0;              // Выйти, если окно не может быть создано
	}
	while( !done ) {               // Цикл продолжается, пока done не равно true
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {   // Есть ли в очереди какое-нибудь сообщение?
			if( msg.message == WM_QUIT ) {       // Мы поучили сообщение о выходе?
				done = true;          // Если так, done=true
			} else {             // Если нет, обрабатывает сообщения
				TranslateMessage( &msg );        // Переводим сообщение
				DispatchMessage( &msg );        // Отсылаем сообщение
			}
		} else {               // Если нет сообщений
			// Прорисовываем сцену.
			if( active ) {         // Активна ли программа?
					DrawGLScene();        // Рисуем сцену
					SwapBuffers( hDC );    // Меняем буфер (двойная буферизация)
			}
			/*
			if( keys[VK_F1] ) {         // Была ли нажата F1?
				keys[VK_F1] = false;        // Если так, меняем значение ячейки массива на false
				KillGLWindow();          // Разрушаем текущее окно
				fullscreen = !fullscreen;      // Переключаем режим
				// Пересоздаём наше OpenGL окно
				if( !CreateGLWindow( _T("OpenGL"), 800, 600, 32, fullscreen ) ) {
					return 0;        // Выходим, если это невозможно
				}
			}
			*/
			
		}
		MsgWaitForMultipleObjects(0, NULL, FALSE, 10, QS_ALLINPUT);
		//Sleep(10);
	}
	// Shutdown
	KillGLWindow();                // Разрушаем окно
	return ( msg.wParam );              // Выходим из программы
}

