#include "cube.h"

void draw(unsigned int ID) {
	glCallList(ID);
}

void drawbox(t_box *box) {
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glTranslatef(box->coord[0], box->coord[1], box->coord[2]);
	for (int i=0; i<6; i++) {
		glColor3fv(box->color[i]);
		glCallList(box->planes[i]);
	}
	glPopMatrix();
	glPopAttrib();
}

unsigned int create_plane(float width, float height) {
	t_plane p;
	
	p.width = width;
	p.height = height;
	p.ID = glGenLists(1);
	
	glNewList(p.ID, GL_COMPILE);
	
	glPolygonMode(GL_BACK, GL_LINE);
	//glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	
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

t_box create_box(float size, t_coord* coord, t_color_box* colors) {
	t_box b;
	
	b.width = size;
	b.height = size;
	b.depth = size;
	
	b.coord[0] = (*coord)[0];
	b.coord[1] = (*coord)[1];
	b.coord[2] = (*coord)[2];
	
	for (int i = 0; i<6; i++) { //ЧИНИТЬ НАДО
		b.draw_plane[i] = TRUE;
	}
	
	for (int i = 0; i<3; i++) {
		b.color[F_Front][i] = colors->front[i];
		b.color[F_Back][i] = colors->back[i];
		b.color[F_Top][i] = colors->top[i];
		b.color[F_Bottom][i] = colors->bottom[i];
		b.color[F_Right][i] = colors->right[i];
		b.color[F_Left][i] = colors->left[i];
	}
	
	glEnable(GL_BLEND);
	
// Front Plane
	b.planes[0] = glGenLists(1);
	glNewList(b.planes[0], GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f( b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f( b.width,  b.height,  b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f(-b.width,  b.height,  b.depth);
	glEnd();
	// Front Face Border
	glPushAttrib(GL_CURRENT_BIT);
	glPolygonMode(GL_FRONT, GL_LINE);
	glLineWidth(2);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f( b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f( b.width,  b.height,  b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f(-b.width,  b.height,  b.depth);
	glEnd();
	glPopAttrib();
	glEndList();
	
// Back Plane
	b.planes[1] = glGenLists(1);
	glNewList(b.planes[1], GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_QUADS);	
	// Back Face
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-b.width, -b.height, -b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f(-b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f( b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f( b.width, -b.height, -b.depth);
	glEnd();
	// Back Face Border
	glPushAttrib(GL_CURRENT_BIT);
	glPolygonMode(GL_FRONT, GL_LINE);
	glLineWidth(2);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-b.width, -b.height, -b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f(-b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f( b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f( b.width, -b.height, -b.depth);
	glEnd();
	glPopAttrib();
	glEndList();

// Back Plane
	b.planes[2] = glGenLists(1);
	glNewList(b.planes[2], GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_QUADS);
	// Top Face
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f(-b.width,  b.height,  b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f( b.width,  b.height,  b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f( b.width,  b.height, -b.depth);
	glEnd();
	// Top Face Border
	glPushAttrib(GL_CURRENT_BIT);
	glPolygonMode(GL_FRONT, GL_LINE);
	glLineWidth(2);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f(-b.width,  b.height,  b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f( b.width,  b.height,  b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f( b.width,  b.height, -b.depth);
	glEnd();
	glPopAttrib();
	glEndList();
	
// Bottom Plane
	b.planes[3] = glGenLists(1);
	glNewList(b.planes[3], GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_QUADS);
	// Bottom Face
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-b.width, -b.height, -b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f( b.width, -b.height, -b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f( b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f(-b.width, -b.height,  b.depth);
	glEnd();
	// Bottom Face Border
	glPushAttrib(GL_CURRENT_BIT);
	glPolygonMode(GL_FRONT, GL_LINE);
	glLineWidth(2);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-b.width, -b.height, -b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f( b.width, -b.height, -b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f( b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f(-b.width, -b.height,  b.depth);
	glEnd();
	glPopAttrib();
	glEndList();
	
// Right Plane
	b.planes[4] = glGenLists(1);
	glNewList(b.planes[4], GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_QUADS);
	// Right face
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f( b.width, -b.height, -b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f( b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f( b.width,  b.height,  b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f( b.width, -b.height,  b.depth);
	glEnd();
	// Right Face Border
	glPushAttrib(GL_CURRENT_BIT);
	glPolygonMode(GL_FRONT, GL_LINE);
	glLineWidth(2);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f( b.width, -b.height, -b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f( b.width,  b.height, -b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f( b.width,  b.height,  b.depth);
	glTexCoord2f(0.0, 0.0); glVertex3f( b.width, -b.height,  b.depth);
	glEnd();
	glPopAttrib();
	glEndList();
	
// Left Plane
	b.planes[5] = glGenLists(1);
	glNewList(b.planes[5], GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_QUADS);
	// Left Face
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-b.width, -b.height, -b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f(-b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f(-b.width,  b.height,  b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f(-b.width,  b.height, -b.depth);
	glEnd();
	// Left Face Border
	glPushAttrib(GL_CURRENT_BIT);
	glPolygonMode(GL_FRONT, GL_LINE);
	glLineWidth(2);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-b.width, -b.height, -b.depth);
	glTexCoord2f(1.0, 0.0); glVertex3f(-b.width, -b.height,  b.depth);
	glTexCoord2f(1.0, 1.0); glVertex3f(-b.width,  b.height,  b.depth);
	glTexCoord2f(0.0, 1.0); glVertex3f(-b.width,  b.height, -b.depth);
	glEnd();
	glPopAttrib();
	glEndList();
// end of planes
	
	glDisable(GL_BLEND);
	
	return b;
}

// translate in to C please
// N = precision
GLuint create_sphere(GLfloat radius, int n) {
	GLuint result;
	int i, j;
	GLfloat theta1, theta2, theta3;
	GLfloat x, y, z, px, py, pz;

	result = glGenLists(1);
	glNewList(result, GL_COMPILE);
	if (radius < 0) radius = -radius;
	if (n < 0) n = -n;
	if ((n < 4) || (radius <= 0)) {
		glBegin(GL_POINTS);
		glVertex3f(0.0, 0.0, 0.0);
		glEnd();
		return result;
	}

	for (j = 0; j < n / 2 - 1; j++) {
		theta1 = j * 2 * PI / n - PI / 2;
		theta2 = (j + 1) * 2 * PI / n - PI / 2;
		glBegin(GL_QUAD_STRIP);
		for (i = 0; i < n; i++) {
			theta3 = i * 2 * PI / n;
			x = cos(theta2) * cos(theta3);
			y = sin(theta2);
			z = cos(theta2) * sin(theta3);
			px = radius * x;
			py = radius * y;
			pz = radius * z;

			glNormal3f(x, y, z);
			glTexCoord2f(1 - i / n, 2 * (j + 1) / n);
			glVertex3f(px, py, pz);

			x = cos(theta1) * cos(theta3);
			y = sin(theta1);
			z = cos(theta1) * sin(theta3);
			px = radius * x;
			py = radius * y;
			pz = radius * z;

			glNormal3f(x, y, z);
			glTexCoord2f(1 - i / n, 2 * j / n);
			glVertex3f(px, py, pz);
		}
		glEnd();
	}
	glEndList();
	return result;
}

