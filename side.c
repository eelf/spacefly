#include <stdio.h>
#include "defs.h"

#include "side.h"


t_color color_red = {1.0, 0.0, 0.0};
t_color color_blue = {0.0, 0.0, 1.0};
t_color color_green = {0.0, 1.0, 0.0};
t_color color_white = {1.0, 1.0, 1.0};
t_color color_yellow = {1.0, 1.0, 0.0};
t_color color_magenta = {1.0, 0.0, 1.0};

extern float angle;


void copy_color(t_color *a, t_color *b) {
	(*a)[0] = (*b)[0];
	(*a)[1] = (*b)[1];
	(*a)[2] = (*b)[2];
}


void cube_init(t_cube *cube) {

	int row = 0, col = 0, dir = 0;
	for(int i = 0; i < 6 * 9; i++) {
		(*cube)[i].rot.angle = 0.0;
		(*cube)[i].rot.rdir = RNONE;
		
		(*cube)[i].row = row;
		(*cube)[i].col = col;
		(*cube)[i].dir = dir;
		switch((t_direction) dir) {
		case XA: copy_color(&(*cube)[i].color, &color_green); break;
		case XB: copy_color(&(*cube)[i].color, &color_blue); break;
		case YA: copy_color(&(*cube)[i].color, &color_red); break;
		case YB: copy_color(&(*cube)[i].color, &color_magenta); break;
		case ZA: copy_color(&(*cube)[i].color, &color_yellow); break;
		case ZB: copy_color(&(*cube)[i].color, &color_white); break;


		}		
		
		col++;
		if (col > 2) {
			col = 0;
			row++;
		}
		if (row > 2) {
			row = 0;
			dir++;
		}
	}
	/*
	unsigned char *p = cube, *pp = cube;
	for(; p - pp < sizeof(t_cube); p++) {
		if ((p - pp) % sizeof(t_plane) == 0 ) printf("\n");
		printf("%.2x ", *p);
	}
	printf("\n");
	*/
}


void cube_rotate(t_cube* cube, t_rotation_direction rdir, unsigned char row) {
	
	for(int i = 0; i < 54; i++) {
	switch (rdir) {
	case RX:
		if ((*cube)[i].dir == YA && (*cube)[i].row == row) (*cube)[i].rot.rdir = RX;
		if ((*cube)[i].dir == YB && (*cube)[i].row == row) (*cube)[i].rot.rdir = RX;
		if ((*cube)[i].dir == ZA && (*cube)[i].col == row) (*cube)[i].rot.rdir = RX;
		if ((*cube)[i].dir == ZB && (*cube)[i].col == row) (*cube)[i].rot.rdir = RX;

		if (row == 0 && (*cube)[i].dir == XB) (*cube)[i].rot.rdir = RX;
		if (row == 2 && (*cube)[i].dir == XA) (*cube)[i].rot.rdir = RX;
	break;
	case RY:
		if ((*cube)[i].dir == XA && (*cube)[i].row == row) (*cube)[i].rot.rdir = RY;
		if ((*cube)[i].dir == XB && (*cube)[i].row == row) (*cube)[i].rot.rdir = RY;
		if ((*cube)[i].dir == ZA && (*cube)[i].row == row) (*cube)[i].rot.rdir = RY;
		if ((*cube)[i].dir == ZB && (*cube)[i].row == row) (*cube)[i].rot.rdir = RY;

		if (row == 0 && (*cube)[i].dir == YB) (*cube)[i].rot.rdir = RY;
		if (row == 2 && (*cube)[i].dir == YA) (*cube)[i].rot.rdir = RY;
	break;
	case RZ:
		if ((*cube)[i].dir == YA && (*cube)[i].col == row) (*cube)[i].rot.rdir = RZ;
		if ((*cube)[i].dir == YB && (*cube)[i].col == row) (*cube)[i].rot.rdir = RZ;
		if ((*cube)[i].dir == XA && (*cube)[i].col == row) (*cube)[i].rot.rdir = RZ;
		if ((*cube)[i].dir == XB && (*cube)[i].col == row) (*cube)[i].rot.rdir = RZ;

		if (row == 0 && (*cube)[i].dir == ZB) (*cube)[i].rot.rdir = RZ;
		if (row == 2 && (*cube)[i].dir == ZA) (*cube)[i].rot.rdir = RZ;
	break;
	}
		
	}
}


/*
00 01 02	02 12 22
10 11 12	01 11 21
20 21 22    00 10 20

00 - 20, 01 - 10, 02 - 00
10 - 21, 11 - 11, 12 - 01
20 - 22, 21 - 12, 22 - 02
*/
void cube_end_rotate(t_cube* cube) {
	int tmp;
	for(int i = 0; i < 54; i++) {
	
		switch((*cube)[i].rot.rdir) {
		case RX:
			if ((*cube)[i].dir == XA || (*cube)[i].dir == XB) {
			tmp = (*cube)[i].col;
			(*cube)[i].col = (*cube)[i].row;
			(*cube)[i].row = 2 - tmp;
			}
			if ((*cube)[i].dir == YA) {
				(*cube)[i].dir = ZA;
				tmp = (*cube)[i].col;
				(*cube)[i].col = (*cube)[i].row;
				(*cube)[i].row = tmp;
			} else if ((*cube)[i].dir == ZA) {
				(*cube)[i].dir = YB;
				tmp = (*cube)[i].row;
				(*cube)[i].row = (*cube)[i].col;
				(*cube)[i].col = tmp;
			} else if ((*cube)[i].dir == YB) {
				(*cube)[i].dir = ZB;
				tmp = (*cube)[i].col;
				(*cube)[i].col = (*cube)[i].row;
				(*cube)[i].row = tmp;
			} else if ((*cube)[i].dir == ZB) {
				(*cube)[i].dir = YA;
				tmp = (*cube)[i].row;
				(*cube)[i].row = (*cube)[i].col;
				(*cube)[i].col = tmp;
			}
		break;
		case RY:
			if ((*cube)[i].dir == YA || (*cube)[i].dir == YB) {
			tmp = (*cube)[i].row;
			(*cube)[i].row = (*cube)[i].col;
			(*cube)[i].col = 2 - tmp;
			}
			if ((*cube)[i].dir == XA) (*cube)[i].dir = ZB;
			else if ((*cube)[i].dir == ZA) (*cube)[i].dir = XA;
			else if ((*cube)[i].dir == XB) (*cube)[i].dir = ZA;
			else if ((*cube)[i].dir == ZB) (*cube)[i].dir = XB;
		break;
		case RZ:
			if ((*cube)[i].dir == ZA || (*cube)[i].dir == ZB) {
			tmp = (*cube)[i].row;
			(*cube)[i].row = (*cube)[i].col;
			(*cube)[i].col = 2 - tmp;
			}
			if ((*cube)[i].dir == YA) (*cube)[i].dir = XB;
			else if ((*cube)[i].dir == XA) (*cube)[i].dir = YA;
			else if ((*cube)[i].dir == YB) (*cube)[i].dir = XA;
			else if ((*cube)[i].dir == XB) (*cube)[i].dir = YB;
		break;
		}
		
		(*cube)[i].rot.rdir = RNONE;
	}	
}

void plane_render(t_plane *plane) {
	float s = 0.45;
	float t = 1.0;
	/*
	static float i = 1.0;
	static int d = 0;
	if (d) i -= 0.00001;
	else i += 0.00001;
	if (i <  0.4) d = 0;
	if (i >  1.0) d = 1;
	*/
	
	switch( (t_rotation_direction) (*plane).rot.rdir ) {
	case RX: glRotatef(angle, 1.0, 0.0, 0.0); break;
	case RY: glRotatef(angle, 0.0, 1.0, 0.0); break;
	case RZ: glRotatef(angle, 0.0, 0.0, 1.0); break;
	}
	
	glColor3f((*plane).color[0], (*plane).color[1], (*plane).color[2]);
	switch((t_direction)(*plane).dir) {
	case XA: 
		glTranslatef(  t, t * ((*plane).row - 1), t * ((*plane).col - 1));
		glBegin(GL_QUADS);
		glVertex3f(  s, -s, -s);
		glVertex3f(  s, -s,  s);
		glVertex3f(  s,  s,  s);
		glVertex3f(  s,  s, -s);
		glEnd();
	break;
	case XB: 
		glTranslatef( -t, t * ((*plane).row - 1), t * ((*plane).col - 1));
		glBegin(GL_QUADS);
		glVertex3f( -s, -s, -s);
		glVertex3f( -s, -s,  s);
		glVertex3f( -s,  s,  s);
		glVertex3f( -s,  s, -s);
		glEnd();
	break;
	case YA: 
		glTranslatef(  t * ((*plane).row - 1), t, t * ((*plane).col - 1));
		glBegin(GL_QUADS);
		glVertex3f( -s,  s, -s);
		glVertex3f( -s,  s,  s);
		glVertex3f(  s,  s,  s);
		glVertex3f(  s,  s, -s);
		glEnd();
	break;
	case YB: 
		glTranslatef( t * ((*plane).row - 1), -t, t * ((*plane).col - 1));
		glBegin(GL_QUADS);
		glVertex3f( -s, -s, -s);
		glVertex3f( -s, -s,  s);
		glVertex3f(  s, -s,  s);
		glVertex3f(  s, -s, -s);
		glEnd();
	break;
	case ZA: 
		glTranslatef(  t* ((*plane).col - 1), t * ((*plane).row - 1), t );
		glBegin(GL_QUADS);
		glVertex3f( -s, -s,  s);
		glVertex3f(  s, -s,  s);
		glVertex3f(  s,  s,  s);
		glVertex3f( -s,  s,  s);
		glEnd();
	break;
	case ZB: 
		glTranslatef(  t* ((*plane).col - 1), t * ((*plane).row - 1), -t);
		glBegin(GL_QUADS);
		glVertex3f( -s, -s, -s);
		glVertex3f(  s, -s, -s);
		glVertex3f(  s,  s, -s);
		glVertex3f( -s,  s, -s);
		glEnd();
	break;
	}
}



void cube_render(t_cube *cube) {
	for(int i = 0; i < 54; i++) {
		glPushMatrix();
		plane_render(&(*cube)[i]);
		glPopMatrix();
	}

}




