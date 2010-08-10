#ifdef macintosh
	#include <GLUT/glut.h>
	#include <GL/gl.h>
#elseif _WIN32 // _WIN32
	#include <GL/glut.h>
#endif
#include <math.h>

#define PI 3.1415926
#define DELIT 0.017453292
#define PI75 2.35619445
#define PI50 1.5707963
#define PI25 0.78539815

float angle=0.0;
float cosa, cosb, cosc, cosd;
float coss(float cosx, float scal) {
	return scal * cosx + scal;
}
void renderScene(void) {

	// notice that we're now clearing the depth buffer 
	// as well this is required, otherwise the depth buffer 
	// gets filled and nothing gets rendered. 
	// Try it out, remove the depth buffer part.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// save the previous settings, in this case save 
	// we're refering to the camera settings.
	glPushMatrix();
	
	// Perform a rotation around the y axis (0,1,0) 
	// by the amount of degrees defined in the variable angle
		cosa = cos(angle * DELIT);
		cosb = cos(angle * DELIT - PI25);
		cosc = cos(angle * DELIT - PI50);
		cosd = cos(angle * DELIT - PI75);
	glRotatef(45.0,1.0,1.0,0.0);
	glRotatef(cosa,0.5,1.0,0.0);
//		glColor3f(1.0,0.0,1.0*cosb);
//		glColor3f(0.0,1.0*cosa,1.0);
//		glColor3f(1.0*cosa,0.0,1.0);
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
	
	// discard the modelling transformations
	// after this the matrix will have only the camera settings.
	glPopMatrix();
	
	// swapping the buffers causes the rendering above to be 
	// shown
	glutSwapBuffers();
	
	// finally increase the angle for the next frame
	angle += 0.2;
	if (angle > 360.0) angle = 0.0;
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0, 
		      0.0,0.0,-1.0,
			  0.0f,1.0f,0.0f);


}

void main(int argc, char **argv) {
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
	
	// enable depth testing
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}




