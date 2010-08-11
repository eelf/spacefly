#ifdef macintosh
	#include <GLUT/glut.h>
	#include <GL/gl.h>
#elseif _WIN32
	#include <GL/glut.h>
//	#include <windows.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif

#include "piece.h"


void render_piece(t_piece p, float scale, float size) {
	glPushMatrix();
	glScalef(scale, scale, scale);
	glTranslatef(p.x, p.y, p.z);
	glRotatef(p.rx, 1.0, 0.0, 0.0);
	glRotatef(p.ry, 0.0, 1.0, 0.0);
	glRotatef(p.rz, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glColor3fv(p.cf);
		glVertex3f(-size, -size, size);
		glVertex3f( size, -size, size);
		glVertex3f( size,  size, size);
		glVertex3f(-size,  size, size);
		if (p.sides >= 2) {
		glColor3fv(p.ct);
		glVertex3f(-size,  size, size);
		glVertex3f( size,  size, size);
		glVertex3f( size,  size,-size);
		glVertex3f(-size,  size,-size);
		}
		if (p.sides == 3) {
		glColor3fv(p.cr);
		glVertex3f( size, -size, size);
		glVertex3f( size, -size,-size);
		glVertex3f( size,  size,-size);
		glVertex3f( size,  size, size);
		}
	glEnd();
	glPopMatrix();
}


