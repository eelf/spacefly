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

#include "side.h"


void rotate_sides(int gran, t_side* p) {
}
void render_sides(t_side *p, float scale, float size) {
	glPushMatrix();
	glTranslatef(0,0,1);
	render_side(p[0], scale, size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	glRotatef(90,0,1,0);
	render_side(p[1], scale, size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	glRotatef(180,0,1,0);
	render_side(p[2], scale, size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	glRotatef(270,0,1,0);
	render_side(p[3], scale, size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	glRotatef(90,1,0,0);
	render_side(p[4], scale, size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	glRotatef(270,1,0,0);
	render_side(p[5], scale, size);
	glPopMatrix();
}
void render_side(t_side p, float scale, float size) {
	glBegin(GL_QUADS);
	for(int i = 0; i < 9; i++) {
		glColor3fv(p.color[i]);
		glVertex3f(-size, -size, size);
		glVertex3f( size, -size, size);
		glVertex3f( size,  size, size);
		glVertex3f(-size,  size, size);
	}
	glEnd();
}

