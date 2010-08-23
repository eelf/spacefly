#include "cube.h"

t_stack create_stack() {

}

void stack_add(t_stack *stack, t_box *box, int face) {
	/*int *a, n, i;
	 scanf("%d", &n);
	 a = malloc(n*sizeof(int));
	 // далее работаем как с массивом, например:
	 for (i=0; i <n; i++) {
     a[i]=0;
	 } // for
	 .............................................
	 free(a); // когда станет не нужно
	 */
	stack->n++;
	//stack->planes = malloc(stack->n * sizeof(int));
	stack->planes[stack->n-1] = box->planes[face];
	stack->color[stack->n-1][0] = box->color[face][0];
	stack->color[stack->n-1][1] = box->color[face][1];
	stack->color[stack->n-1][2] = box->color[face][2];
	stack->coord[stack->n-1][0] = box->coord[0];
	stack->coord[stack->n-1][1] = box->coord[1];
	stack->coord[stack->n-1][2] = box->coord[2];
}

unsigned int* stack_get(t_stack *stack) {
	return stack->planes;
	free(stack->planes);
}

unsigned int stack_get_n(t_stack *stack) {
	return stack->n;
}

void draw(unsigned int ID) {
	glCallList(ID);
}

void drawbox(t_box *box) {
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glTranslatef(box->coord[0], box->coord[1], box->coord[2]);
	for (int i=0; i<6; i++) {
		glColor3fv(box->color[i]);
		if (box->draw_plane[i]==TRUE) //статическое рисование
			glCallList(box->planes[i]);
		else { //рисование поворота
			
		}

	}
	glPopMatrix();
	glPopAttrib();
}

void draw_stack(t_stack *stack, float angle) {
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glRotatef(angle, 1, 0, 0);
	for (int i=0; i<stack->n; i++) {
		glPushMatrix();
		glTranslatef(stack->coord[i][0], stack->coord[i][1], stack->coord[i][2]);
		glColor3fv(stack->color[i]);
		//if (box->draw_plane[i]==TRUE)
		glCallList(stack->planes[i]);
		glPopMatrix();
	}
	glPopMatrix();
	glPopAttrib();
}

void draw_plane_off(t_box *box, t_stack *stack, int face) {
	if (box->draw_plane[face] != FALSE) {
		box->draw_plane[face] = FALSE;
		stack_add(stack, box, face);
	}
}

t_box create_box(float size, t_coord* coord, t_color_box* colors) {
	t_box b;
	
	b.width = size;
	b.height = size;
	b.depth = size;
	
	b.coord[0] = (*coord)[0]; // x
	b.coord[1] = (*coord)[1]; // y
	b.coord[2] = (*coord)[2]; // z
	
	for (int i = 0; i<6; i++)
		b.draw_plane[i] = FALSE;
	
	if (b.coord[2]==1)
		b.draw_plane[F_Front] = TRUE;
	if (b.coord[2]==-1)
		b.draw_plane[F_Back] = TRUE;
	if (b.coord[1]==1)
		b.draw_plane[F_Top] = TRUE;
	if (b.coord[1]==-1)
		b.draw_plane[F_Bottom] = TRUE;
	if (b.coord[0]==1)
		b.draw_plane[F_Right] = TRUE;
	if (b.coord[0]==-1)
		b.draw_plane[F_Left] = TRUE;
	
	// через жопу сделано, надо избавиться от t_color_box как от типа, при передаче цвета
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

