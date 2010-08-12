#include "defs.h"

#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include "piece.h"
#include "side.h"
#include "camera.h"
#include "helloworld.h"

#include "cube.h"

#define PDEB 10

t_camera camera;

t_box rube;
t_color color[]= {
	{ 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0 }
};


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
	glRasterPos3f(x, y, z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.7, 0.9, 1);
	glLoadIdentity();
	
	
//camera setup
	glTranslatef(camera.x, camera.y, camera.z);
	glRotatef(camera.q, 1.0, 0.0, 0.0);
	glRotatef(camera.r, 0.0, 1.0, 0.0);
	
//draw text
	//sprintf(s, "%d", v);
	glPushAttrib(GL_CURRENT_BIT);
		glColor3f(1.0, 1.0, 0.0); 
		glPushMatrix();
			renderBitmapCharacher(0,1.8,0,GLUT_BITMAP_8_BY_13, (const unsigned char *) s);
		glPopMatrix();
	glPopAttrib();
	
/* rubic 3x3  (x.y.z)
 1.1.1	1.2.1	1.3.1
 2.1.1	2.2.1	2.3.1
 3.1.1	3.2.1	3.3.1
 
 1.1.2	1.2.2	1.3.2
 2.1.2	2.2.2	2.3.2
 3.1.2	3.2.2	3.3.2
 
 1.1.3	1.2.3	1.3.3
 2.1.3	2.2.3	2.3.3
 3.1.3	3.2.3	3.3.3
 
 2.2.2 - empty
 */
	
//draw scene
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			for (int k=0; k<3; k++) {
				glPushMatrix();
				glTranslatef(i-1, j-1, k-1); // -1 что бы 2.2.2 был в центре
				if (i!=1 || j!=1 || k!=1) {//не рисуем 2.2.2
					glCallList(rube.ID); //рисуем грани кубиков
					if (k==2) {
						color[F_Front][0] = 1.0; color[F_Front][1] = 0.0; color[F_Front][2] = 0.0; //красная
						drawbox(&rube, color, F_Front);
					}
					if (k==0) {
						color[F_Back][0] = 1.0; color[F_Back][1] = 1.0; color[F_Back][2] = 1.0; //белая
						drawbox(&rube, color, F_Back);
					}
					if (j==2) {
						color[F_Top][0] = 0.0; color[F_Top][1] = 1.0; color[F_Top][2] = 0.0; //зеленый
						drawbox(&rube, color, F_Top);
					}
					if (j==0) {
						color[F_Bottom][0] = 0.0; color[F_Bottom][1] = 0.0; color[F_Bottom][2] = 1.0; //синий
						drawbox(&rube, color, F_Bottom);
					}	
					if (i==0) {
						color[F_Left][0] = 1.0; color[F_Left][1] = 1.0; color[F_Left][2] = 0.0; //желтый
						drawbox(&rube, color, F_Left);
					}	
					if (i==2) {
						color[F_Right][0] = 1.0; color[F_Right][1] = 0.6; color[F_Right][2] = 0.0; //оранжевый
						drawbox(&rube, color, F_Right);
					}	
				}
				glPopMatrix();
			}
		}
	}
	glPopMatrix();
	glPopAttrib();
 
	
//	render_pieces(p, 0.5, 0.45);
//	render_sides(p, 0.5, 0.45);

	glutSwapBuffers();
	
	angle += 0.2;
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
	
	//init other
	rube = create_box(0.4, 0.4, 0.4);
	
	glutMainLoop();
	return 0;
}




