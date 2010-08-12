#include "cube.h"

void draw(unsigned int ID) {
	glCallList(ID);
}

unsigned int create_plane(float width, float height) {
	t_plane p;
	
	p.width = width;
	p.height = height;
	p.ID = glGenLists(1);
	
	glNewList(p.ID, GL_COMPILE);
	
	glPolygonMode(GL_BACK, GL_LINE);
	//glFrontFace(GL_CCW);
	//glEnable(GL_CULL_FACE);
	
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.5f, 0.5f);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0,1); glVertex2f(-p.width/2, -p.height/2);
	glTexCoord2f(1,1); glVertex2f( p.width/2, -p.height/2);
	glTexCoord2f(1,0); glVertex2f( p.width/2,  p.height/2);
	glTexCoord2f(0,0); glVertex2f(-p.width/2,  p.height/2);
	glEnd();
	glEndList();
	
	return p.ID;
}

unsigned int create_box(float width, float height, float depth) {
	t_box b;
	
	b.width = width;
	b.height = height;
	b.depth = depth;
	b.ID = glGenLists(1);
	
	glEnable(GL_BLEND);
	glNewList(b.ID, GL_COMPILE);
	
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_LINE);
	glColor3f(0, 0, 0);
	
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f( b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f( b.width,  b.height,  b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f(-b.width,  b.height,  b.depth);
	// Back Face
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-b.width, -b.height, -b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f(-b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f( b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f( b.width, -b.height, -b.depth);
	// Top Face
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f(-b.width,  b.height,  b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f( b.width,  b.height,  b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f( b.width,  b.height, -b.depth);
	// Bottom Face
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-b.width, -b.height, -b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f( b.width, -b.height, -b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f( b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f(-b.width, -b.height,  b.depth);
	// Right face
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f( b.width, -b.height, -b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f( b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f( b.width,  b.height,  b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f( b.width, -b.height,  b.depth);
	// Left Face
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-b.width, -b.height, -b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f(-b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f(-b.width,  b.height,  b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f(-b.width,  b.height, -b.depth);
	glEnd();
	
	glPolygonMode(GL_FRONT, GL_FILL);
	glColor4f(1, 0, 1, 0.5);
	
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f( b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f( b.width,  b.height,  b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f(-b.width,  b.height,  b.depth);
	// Back Face
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-b.width, -b.height, -b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f(-b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f( b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f( b.width, -b.height, -b.depth);
	// Top Face
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f(-b.width,  b.height,  b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f( b.width,  b.height,  b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f( b.width,  b.height, -b.depth);
	// Bottom Face
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-b.width, -b.height, -b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f( b.width, -b.height, -b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f( b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f(-b.width, -b.height,  b.depth);
	// Right face
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f( b.width, -b.height, -b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f( b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f( b.width,  b.height,  b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f( b.width, -b.height,  b.depth);
	// Left Face
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-b.width, -b.height, -b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f(-b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f(-b.width,  b.height,  b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f(-b.width,  b.height, -b.depth);
	glEnd();
	
	
	glEndList();
	glDisable(GL_BLEND);
	
	return b.ID;
}