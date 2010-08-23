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
	t_color front;
	t_color back;
	t_color top;
	t_color bottom;
	t_color right;
	t_color left;
} t_color_box;

typedef struct {
	unsigned int n; //count
	int planes[512];
	t_color color[512];
	t_coord coord[512];
} t_stack;

typedef struct {
	float width, height, depth;
	t_coord coord;
	int planes[6];
	unsigned int draw_plane[6];
	t_color_box colors;
	t_color color[6];
} t_box;

t_stack create_stack();
void stack_add(t_stack *stack, t_box *box, int face);
unsigned int* stack_get(t_stack *stack);
unsigned int stack_get_n(t_stack *stack);
void draw_stack(t_stack *stack);

void draw(unsigned int ID);
void drawbox(t_box *box);
void draw_plane_off(t_box *box, t_stack *stack, int face);
t_box create_box(float size, t_coord *coord, t_color_box* colors);

GLuint create_sphere(GLfloat radius, int n);

#endif


