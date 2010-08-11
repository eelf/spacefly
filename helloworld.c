#ifdef macintosh
	#include <GLUT/glut.h>
	#include <GL/gl.h>
#elseif _WIN32
	#include <GL/glut.h>
//	#include <windows.h>
#else
	#include <GL/gl.h>
	#include <GL/freeglut.h>
#endif

#include <math.h>
#include <stdio.h>
#include "piece.h"
#include "camera.h"
#include "helloworld.h"

t_camera camera;
t_piece p1 = {-1.0, -1.0, 1.0,   0.0,   0.0,180.0, {1.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 3};
t_piece p2 = { 0.0, -1.0, 1.0,   0.0,   0.0,180.0, {1.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 2};
t_piece p3 = { 1.0, -1.0, 1.0,   0.0,   0.0,270.0, {1.0, 1.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, 3};
char s[40];

float coss(float cosx, float scal) {
	return scal * cosx + scal;
}
void renderScene(void) {
	// notice that we're now clearing the depth buffer 
	// as well this is required, otherwise the depth buffer 
	// gets filled and nothing gets rendered. 
	// Try it out, remove the depth buffer part.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// save the previous settings, in this case save 
	// we're refering to the camera settings.
//	glPushMatrix();
	
	// Perform a rotation around the y axis (0,1,0) 
	// by the amount of degrees defined in the variable angle
		cosa = cos(angle * DELIT);
		cosb = cos(angle * DELIT - PI25);
		cosc = cos(angle * DELIT - PI50);
		cosd = cos(angle * DELIT - PI75);
		
		
	
	glRotatef(camera.q, 1.0, 0.0, 0.0);
	glRotatef(camera.r, 0.0, 1.0, 0.0);
	glTranslatef(camera.x, camera.y, camera.z);
//	glRotatef(cosa,0.5,1.0,0.0);

	glColor3f(0.7+0.3*cosa, 1.0, 0.0); 
  	glRasterPos3f(0.0,0.5,0.4);
  	sprintf(s, "%.2f %.2f", camera.z, camera.vz);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char *)s);
//		glColor3f(1.0,0.0,1.0*cosb);
//		glColor3f(0.0,1.0*cosa,1.0);
//		glColor3f(1.0*cosa,0.0,1.0);

	render_piece(p1, 0.3, 0.45);
	render_piece(p2, 0.3, 0.45);
	render_piece(p3, 0.3, 0.45);

	glPushMatrix();
	glTranslatef(2.0,-1.0,-1.0);
	glBegin(GL_QUAD_STRIP);

		glColor3f(0.0,0.0,1.0);
		glVertex3f(0.0,0.0,0.05*cosa);
		
		glColor3f(0.0,0.0,1.0);
		glVertex3f(0.0,1.0,0.05*cosa);
		
		glColor3f(0.0,0.0,0.9+0.1*cosb);
		glVertex3f(1.0,0.0,0.1*cosb);

		glColor3f(0.0,0.0,0.9+0.1*cosb);
		glVertex3f(1.0,1.0,0.1*cosb);

		glColor3f(0.0,0.0,0.85+0.15*cosc);
		glVertex3f(2.0,0.0,0.15*cosc);
		
		glColor3f(0.0,0.0,0.85+0.15*cosc);
		glVertex3f(2.0,1.0,0.15*cosc);

		glColor3f(0.0,0.0,0.8+0.2*cosd);
		glVertex3f(3.0,0.0,0.2*cosd);

		glColor3f(0.0,0.0,0.8+0.2*cosd);
		glVertex3f(3.0,1.0,0.2*cosd);
	glEnd();
	glPopMatrix();
	

	glutSwapBuffers();
	
	// finally increase the angle for the next frame
	angle += 0.2;
	if (angle > 360.0) angle = 0.0;
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
	if (key == 'a') camera_rotate(&camera,  0.0,-1.0);
	if (key == 'd') camera_rotate(&camera,  0.0, 1.0);
	if (key == 'q') camera_rotate(&camera, -1.0, 0.0);
	if (key == 'z') camera_rotate(&camera,  1.0, 0.0);
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




