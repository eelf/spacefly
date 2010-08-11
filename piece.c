#if defined(__APPLE__) || defined(MACOSX)
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/freeglut.h>
#endif

#include "piece.h"

void rotate_pieces(int gran, t_piece* p) {
	// 0 - front, 1 - back, 2 - up, 3 - down, 4 - right, 5 - left
	int oldx;
	for(int i = 0; i < 26; i++) {
		if (i == 10 || i == 15) continue;
		if (p[i].z == 1 && gran == 0) {
			oldx = p[i].x;
			p[i].x = p[i].y;
			p[i].y = oldx == 1 ? -1 : (oldx == -1 ? 1 : 0);
			p[i].rz -= 90.0;
			if (p[i].rz == -90.0) p[i].rz = 270.0;
		}
		if (p[i].z == -1 && gran == 1) {
			oldx = p[i].x;
			p[i].x = p[i].y;
			p[i].y = oldx == 1 ? -1 : (oldx == -1 ? 1 : 0);
			p[i].rz += 90.0;
			if (p[i].rz == 360.0) p[i].rz = 0.0;
		}
		if (p[i].y == 1 && gran == 2) {
			oldx = p[i].x;
			p[i].x = p[i].z;
			p[i].z = oldx == 1 ? -1 : (oldx == -1 ? 1 : 0);
			p[i].ry += 90.0;
			if (p[i].ry == 360.0) p[i].ry = 0.0;
		}
		if (p[i].y == -1 && gran == 3) {
			oldx = p[i].x;
			p[i].x = p[i].z;
			p[i].z = oldx == 1 ? -1 : (oldx == -1 ? 1 : 0);
			p[i].ry += 90.0;
			if (p[i].ry == 360.0) p[i].ry = 0.0;
		}
		if (p[i].x == 1 && gran == 4) {
			oldx = p[i].z;
			p[i].z = p[i].y;
			p[i].y = oldx == 1 ? -1 : (oldx == -1 ? 1 : 0);
			p[i].rx += 90.0;
			if (p[i].rx == 360.0) p[i].rx = 0.0;
		}
		if (p[i].x == -1 && gran == 5) {
			oldx = p[i].z;
			p[i].z = p[i].y;
			p[i].y = oldx == 1 ? -1 : (oldx == -1 ? 1 : 0);
			p[i].rx += 90.0;
			if (p[i].rx == 360.0) p[i].rx = 0.0;
		}
	}
}


void render_pieces(t_piece *p, float scale, float size) {
	for (int i = 0; i < 26; i++) {
/*		if (*/
/*		p[i].x==-1*/
/*		||*/
/*		p[i].y==-1*/
		
/*		i > 16*/
/*		&&*/
/*		i < 17*/
/*		)*/
		render_piece(p[i], scale, size);
	}
}

void render_piece(t_piece p, float scale, float size) {
	float dsize = size * 2;
	glPushMatrix();
	glScalef(scale, scale, scale);
	glTranslatef(p.x * dsize, p.y * dsize, p.z * dsize);
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


