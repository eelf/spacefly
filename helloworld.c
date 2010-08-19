#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "helloworld.h"
#include "defs.h"
//#include "piece.h"
//#include "side.h"
#include "camera.h"
#include "cube.h"

#include "data.c"
#include "gl_extend.h"


t_camera camera;
t_box rube;
t_box cubic[28];
t_color color[6];

char s[40];

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2, 0.4, 0.7, 1);
	glLoadIdentity();
	
	
//camera setup
	glRotatef(camera.q, 1.0, 0.0, 0.0);
	glRotatef(camera.r, 0.0, 1.0, 0.0);
	glTranslatef(camera.x, camera.y, camera.z);
	
	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(-camera.x + 1, -camera.y + 1, -camera.z + 1);
		glVertex3f(0.0, 0.0, 0.0);

		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(100.0, 0.0, 0.0);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 100.0, 0.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 100.0);
	glEnd();
	
//draw text
	sprintf(s, "%.2f %.2f %.2f", camera.x, camera.y, camera.z);
	glPushAttrib(GL_CURRENT_BIT);
		glColor3f(1.0, 1.0, 0.0); 
		glPushMatrix();
			renderBitmapCharacher(0, 1.8, 0, GLUT_BITMAP_8_BY_13, s);
		glPopMatrix();
	glPopAttrib();
	
/* rubic 3x3x3  (x.y.z)
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
 
 
 i  -  0 // right - left
 j  -  1 // top   - bottom
 k  -  2 // front - back
 
 */
	
//draw scene
	for (int i = 0; i<27; i++) {
		drawbox(&cubic[i]);
	}
	
	
	
	glutSwapBuffers();
	
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
// что это такое
//	gluLookAt(0.0,0.0,5.0, 
//		      0.0,0.0,-1.0,
//			  0.0f,1.0f,0.0f);


}

void keyPressed(unsigned char key, int x, int y) {
	if (key == 27) exit(0);
	if (key == 'w') camera_move(&camera,  1.0, 0.0, 0.0);
	if (key == 's') camera_move(&camera, -1.0, 0.0, 0.0);
	if (key == '1') camera_move(&camera,  0.0, 0.0, 1.0);
	if (key == '3') camera_move(&camera,  0.0, 0.0,-1.0);
	if (key == 'f') camera_move(&camera,  0.0, 1.0, 0.0);
	if (key == 'r') camera_move(&camera,  0.0,-1.0, 0.0);

	if (key == 'a') camera_rotate(&camera,  0.0,-4.0);
	if (key == 'd') camera_rotate(&camera,  0.0, 4.0);
	if (key == 'q') camera_rotate(&camera, -4.0, 0.0);
	if (key == 'z') camera_rotate(&camera,  4.0, 0.0);

//	if (key == 'u') rotate_pieces(0, (t_piece*)&p);
/*	if (key == 'i') rotate_pieces(2, (t_piece*)&p);
	if (key == 'o') rotate_pieces(4, (t_piece*)&p);
	if (key == 'j') rotate_pieces(1, (t_piece*)&p);
	if (key == 'k') rotate_pieces(3, (t_piece*)&p);
	if (key == 'l') rotate_pieces(5, (t_piece*)&p);
*/
  	sprintf(s, "%c", key);
	
}

t_coord *set_coord(float x, float y, float z) { //всё ли тут верно?
	float Temp[3];
	Temp[0] = (float)x;
	Temp[1] = (float)y;
	Temp[2] = (float)z;
	return Temp;
}

t_color *set_color(float x, float y, float z) {
	float Temp[3];
	Temp[0] = (float)x;
	Temp[1] = (float)y;
	Temp[2] = (float)z;
	return Temp;
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
	//rube = create_box(0.45, set_coord(0.0, 1.0, 1.0));
	color[F_Front][0] = 1.0; color[F_Front][1] = 0.0; color[F_Front][2] = 0.0; //красная
	color[F_Back][0] = 1.0; color[F_Back][1] = 1.0; color[F_Back][2] = 1.0; //белая
	color[F_Top][0] = 0.0; color[F_Top][1] = 1.0; color[F_Top][2] = 0.0; //зеленый
	color[F_Bottom][0] = 0.0; color[F_Bottom][1] = 0.0; color[F_Bottom][2] = 1.0; //синий
	color[F_Right][0] = 1.0; color[F_Right][1] = 0.6; color[F_Right][2] = 0.0; //оранжевый
	color[F_Left][0] = 1.0; color[F_Left][1] = 1.0; color[F_Left][2] = 0.0; //желтый
	int n = 0;
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++) {
			for (int k = 0; k<3; k++) {
				cubic[n] = create_box(0.45, set_coord(i-1, j-1, k-1), *color);
				n++;
			}
		}
	}

	
	glutMainLoop();
	// never happen lol
	return 0;
}


