#include "defs.h"

#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include "piece.h"
#include "side.h"
#include "camera.h"
#include "helloworld.h"
#define PDEB 10

t_camera camera;
int v = 0;


t_piece p[] = {
	{-1, -1, 1,   0.0,   0.0,180.0, {1.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 3},
	{ 0, -1, 1,   0.0,   0.0,180.0, {1.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 2},
	{ 1, -1, 1,   0.0,   0.0,270.0, {1.0, 1.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, 3},

	{-1,  0, 1,   0.0,   0.0, 90.0, {1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, 2},
	{ 0,  0, 1,   0.0,   0.0,  0.0, {1.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 1},
	{ 1,  0, 1,   0.0,   0.0,270.0, {1.0, 1.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, 2},

	{-1,  1, 1,   0.0,   0.0, 90.0, {1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, 3},
	{ 0,  1, 1,   0.0,   0.0,  0.0, {1.0, 1.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, 2},
	{ 1,  1, 1,   0.0,   0.0,  0.0, {1.0, 1.0, 1.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, 3},



	{-1, -1, 0,   0.0, 270.0,180.0, {0.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 2},
	{ 0, -1, 0,  90.0,   0.0,  0.0, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 1},
	{ 1, -1, 0,   0.0,  90.0,180.0, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, 2},

	{-1,  0, 0,   0.0, 270.0,  0.0, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, 1},
//	{ 0,  0, 0,   0.0,   0.0,  0.0, {1.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 1},
	{ 1,  0, 0,   0.0,  90.0,  0.0, {1.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, 1},

	{-1,  1, 0,   0.0, 270.0,  0.0, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, 2},
	{ 0,  1, 0, 270.0,   0.0,  0.0, {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, 1},
	{ 1,  1, 0,   0.0,  90.0,  0.0, {1.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, 2},


	{-1, -1,-1,   0.0, 180.0,270.0, {1.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, 3},
	{ 0, -1,-1,   0.0, 180.0,180.0, {1.0, 1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 2},
	{ 1, -1,-1,   0.0, 180.0,180.0, {1.0, 1.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, 3},

	{-1,  0,-1,   0.0, 180.0,270.0, {1.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, 2},
	{ 0,  0,-1,   0.0, 180.0,  0.0, {1.0, 1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 1},
	{ 1,  0,-1,   0.0, 180.0, 90.0, {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, 2},

	{-1,  1,-1,   0.0, 180.0,  0.0, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, 3},
	{ 0,  1,-1,   0.0, 180.0,  0.0, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, 2},
	{ 1,  1,-1,   0.0, 180.0, 90.0, {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, 3}

};

/*
t_side p[] = {
{0, {{0,1,0}, {0,1,0}, {0,1,0}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}}},
{1, {{1,1,1}, {1,1,1}, {1,1,1}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,1}}},
{2, {{0,0,1}, {0,0,1}, {0,0,1}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}}},
{3, {{1,0,0}, {1,0,0}, {1,0,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}}},
{4, {{1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}}},
{5, {{1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}}}
};
/*
t_side p[] = {
{0, {{1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}}},
{1, {{0,0,1}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,1}}},
{2, {{1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}}},
{3, {{0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}}},
{4, {{1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}}},
{5, {{1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}}}
};
*/
char s[40];

void renderBitmapCharacher(float x, float y, float z, void *font,char *string)
{
	
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glTranslatef(camera.x, camera.y, camera.z);
	glRotatef(camera.q, 1.0, 0.0, 0.0);
	glRotatef(camera.r, 0.0, 1.0, 0.0);

	glColor3f(1.0, 1.0, 0.0); 
  	glRasterPos3f(0.0,0.5,0.4);
  	sprintf(s, "%d", v);

	glPushMatrix();
		renderBitmapCharacher(0,1.8,0,GLUT_BITMAP_8_BY_13,(const unsigned char *)s);
	glPopMatrix();
	
	render_pieces(p, 0.5, 0.45);
//	render_sides(p, 0.5, 0.45);

	glutSwapBuffers();
	
	angle += 0.1;
	if (angle > 360.0) angle = 0.0;
//	camera.r = cos(angle * DELIT) * 5.0;
	camera_inert(&camera);
}


void changeSize(int w, int h) {
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	if (h == 0) h = 1;
	float ratio = 1.0* w / h;
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0.0,0.0,5.0, 
//		      0.0,0.0,-1.0,
//			  0.0f,1.0f,0.0f);


}

void keyPressed(unsigned char key, int x, int y) {
	if (key == 27) exit(0);
	if (key == 'w') camera_move(&camera,  1.0, 0.0, 0.0);
	if (key == 's') camera_move(&camera, -1.0, 0.0, 0.0);
	if (key == '1') camera_move(&camera,  0.0, 0.0,-1.0);
	if (key == '3') camera_move(&camera,  0.0, 0.0, 1.0);

	if (key == 'a') camera_rotate(&camera,  0.0,-4.0);
	if (key == 'd') camera_rotate(&camera,  0.0, 4.0);
	if (key == 'q') camera_rotate(&camera, -4.0, 0.0);
	if (key == 'z') camera_rotate(&camera,  4.0, 0.0);

	if (key == 'u') rotate_pieces(0, (t_piece*)&p);
	if (key == 'i') rotate_pieces(2, (t_piece*)&p);
	if (key == 'o') rotate_pieces(4, (t_piece*)&p);
	if (key == 'j') rotate_pieces(1, (t_piece*)&p);
	if (key == 'k') rotate_pieces(3, (t_piece*)&p);
	if (key == 'l') rotate_pieces(5, (t_piece*)&p);
/*
	if (key == 'v') {
		p[PDEB].rx += 90.0;
		if (p[PDEB].rx == 360.0) {
			p[PDEB].rx = 0.0;
			p[PDEB].ry += 90.0;
			if (p[PDEB].ry == 360.0) {
				p[PDEB].ry = 0.0;
				p[PDEB].rz += 90.0;
				if (p[PDEB].rz == 360.0) p[PDEB].rz = 0.0;
			}
		}
		v = (int)p[PDEB].rz / 0.9  + (int)p[PDEB].ry / 9 + (int)p[PDEB].rx / 90;
	}
*/
  	sprintf(s, "%c", key);
	
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	
	// This is where we say that we want a double buffer
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,400);
	glutCreateWindow("DanCake roulette");
	glutDisplayFunc(renderScene);
	
	// here is the setting of the idle function
	glutIdleFunc(renderScene);
	
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyPressed);
	
	// enable depth testing
	glEnable(GL_DEPTH_TEST);
  	sprintf(s, "%c", 65);
  	camera_init(&camera);
	glutMainLoop();
	// never happen lol, main() must return int
	return 0;
}




