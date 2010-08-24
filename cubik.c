#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "defs.h"
#include "side.h"
#include "camera.h"

#include "gl_extend.h"


t_camera camera;
t_cube cube;
char s[40];
float angle;
char rotation;

void timer(int value) {
	if (rotation && angle < 90.0) {
		angle += 0.5;
		glutTimerFunc(50, timer, 0); // Setup next timer
	} else {
		rotation = 0;
		// rotation done, swap planes, reset plane rotation state
		angle = 0.0;
	}
}


void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2, 0.4, 0.7, 1);
	glLoadIdentity();
	
	
//camera setup
	glRotatef(camera.q, 1.0, 0.0, 0.0);
	glRotatef(camera.r, 0.0, 1.0, 0.0);
	glTranslatef(camera.x, camera.y, camera.z);
	
	glBegin(GL_LINES);
		/*glColor3f(1.0, 1.0, 0.0);
		glVertex3f(-camera.x + 1, -camera.y + 1, -camera.z + 1);
		glVertex3f(0.0, 0.0, 0.0);*/

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
/*
	sprintf(s, "%.2f %.2f %.2f", camera.x, camera.y, camera.z);
	glPushAttrib(GL_CURRENT_BIT);
		glColor3f(1.0, 1.0, 0.0); 
		glPushMatrix();
			renderBitmapCharacher(0, 3, 0, GLUT_BITMAP_8_BY_13, s);
		glPopMatrix();
	glPopAttrib();
	*/

	
//draw scene
	render_cube(&cube);
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

	if (key == 'u') {
		rotation = 1;
		rotate_sides(&cube, RX, 0);
		glutTimerFunc(50, timer, 0);
	}
	if (key == 'i') {
		rotation = 1;
		rotate_sides(&cube, RX, 1);
		glutTimerFunc(50, timer, 0);
	}
	if (key == 'o') {
		rotation = 1;
		rotate_sides(&cube, RX, 2);
		glutTimerFunc(50, timer, 0);
	}
	
}


int main(int argc, char **argv) {
//	printf("%d %d %d %d %d %d \n", sizeof(t_cube), sizeof(t_plane), sizeof(t_color), sizeof(t_direction), sizeof(t_rotation), sizeof(t_rotation_direction));
	
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
  	rotation = 0;
  	camera_init(&camera);
	
	//init other
	create_cube(&cube);

	glutMainLoop();
	// never happen lol
	return 0;
}

