#include <math.h>
#include "opengl_common.cpp"
#include "camera.cpp"
#include "compaunds.cpp"


Camera cam;

int frames, ticks, tickslast, sleep = 1;
float fps;

const float step = 0.4;
const float size = 0.19;
int cubik[26][5] = {
// ld bruf
/* l 28000 38000
   d 06000 07000
   b 00200 00e00
   r 00100 001c0
   u 00038 00038
   f 00002 00007
*/
	{  1, -1,  1, 0x15, 0x06102},	// frd
	{  0, -1,  1, 0x11, 0x06002},	// fd
	{ -1, -1,  1, 0x35, 0x2e002},	// fdl
	{  1,  0,  1, 0x05, 0x00102},	// fr
	{  0,  0,  1, 0x01, 0x00002},	// f
	{ -1,  0,  1, 0x21, 0x28002},	// fl
	{  1,  1,  1, 0x07, 0x0013a},	// fur
	{  0,  1,  1, 0x03, 0x0003a},	// fu
	{ -1,  1,  1, 0x23, 0x2803a},	// ful

	{  1, -1,  0, 0x14, 0x06100},	// rd
	{  0, -1,  0, 0x10, 0x06000},	// d
	{ -1, -1,  0, 0x30, 0x2e000},	// dl
	{  1,  0,  0, 0x04, 0x00100},	// r
	//{}
	{ -1,  0,  0, 0x20, 0x28000},	// l
	{  1,  1,  0, 0x06, 0x00138},	// ur
	{  0,  1,  0, 0x02, 0x00038},	// u
	{ -1,  1,  0, 0x22, 0x28038},	// ul
	
	{  1, -1, -1, 0x1c, 0x06300},	// rbd
	{  0, -1, -1, 0x18, 0x06200},	// bd
	{ -1, -1, -1, 0x38, 0x2e200},	// bdl
	{  1,  0, -1, 0x0c, 0x00300},	// rb
	{  0,  0, -1, 0x08, 0x00200},	// b
	{ -1,  0, -1, 0x28, 0x28200},	// bl
	{  1,  1, -1, 0x0e, 0x00338},	// urb
	{  0,  1, -1, 0x0a, 0x00238},	// ub
	{ -1,  1, -1, 0x2a, 0x28238},	// ubl
};






int DrawGLScene( GLvoid ) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();             
	
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(-2.0,0.0,-9.0);
	fps = frames * 1000.0 / tickslast;
	glPrint("fps %d %.2f", sleep, fps);
	glPopMatrix();
	glRotatef(cam.camr,1.0f,0.0f,0.0f);
	glRotatef(cam.camq,0.0f,1.0f,0.0f);
	glTranslatef(cam.camx, cam.camy, cam.camz);
	cam.inert();
	DrawCoords();
	DrawWalls();
	glTranslatef(0.0, 0.0, -4.0);
	
	DrawUgolok( 0.0, 0.0,  0.0, 0x3f, 0, 0.55);
	for(int i = 0; i < 26; i++)
		DrawUgolok( step * cubik[i][0], step * cubik[i][1], step * cubik[i][2], cubik[i][3], cubik[i][4], size);
	
	glTranslatef(0.0, 1.0, 0.0);
	
	return true;               
}

void onKeyDown(int key) {
	switch(key) {
	case VK_ESCAPE: PostQuitMessage(0); break;
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
	case 'C': cam.switchview(1); break;
	case 'V': cam.switchview(0); break;
	}
}




int WINAPI WinMain(  HINSTANCE  hInstance,
      HINSTANCE  hPrevInstance,
      LPSTR    lpCmdLine,
      int    nCmdShow ) {
	MSG  msg;            
	if( !CreateGLWindow( "OpenGL", 800, 600, 32, fullscreen ) )
		return 0;

	ticks = GetTickCount();
	while( true ) {
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
			if( msg.message == WM_QUIT ) {
				break;
			} else {        
				TranslateMessage( &msg );
				DispatchMessage( &msg ); 
			}
		} //else {            
			if( active ) {
					frames++;
					tickslast = GetTickCount() - ticks;
					if (tickslast > 10000) {
						frames = 0;
						ticks = GetTickCount();
						tickslast = 1;
					}
					DrawGLScene();
					SwapBuffers( hDC ); 
					if ((frames & 0x1ff) && fps > 35.0)
						switch(sleep) {
						case 1: sleep = 10; break;
						case 10: sleep = 15; break;
						case 15: sleep = 20; break;
						case 20: sleep = 35; break;
						}
					else if (fps < 24.0)
						switch(sleep) {
						case 10: sleep = 1; break;
						case 15: sleep = 10; break;
						case 20: sleep = 15; break;
						case 35: sleep = 20; break;
						}
			}
			
		//}
		Sleep(sleep);
	}
	KillGLWindow();
	return ( msg.wParam );
}
