#ifndef _CUBE_H_
#define _CUBE_H_

#include <math.h>
#include "defs.h"
#include "base_types.h"

#define F_Front 0
#define F_Back 1
#define F_Top 2
#define F_Bottom 3
#define F_Right 4
#define F_Left 5

typedef struct {
	unsigned int ID;
	float width, height, depth;
	t_color color;
} t_plane;

typedef struct {
	float width, height, depth;
	t_coord coord;
	int planes[6];
	unsigned int draw_plane[6];
	t_color color[6];
} t_box;

typedef struct {
	
} t_rube;

void draw(unsigned int ID);
void drawbox(t_box *box);
unsigned int create_plane(float width, float height);
t_box create_box(float size, t_coord *coord, float color[6][3]);

GLuint create_sphere(GLfloat radius, int n);

#endif


