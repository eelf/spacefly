#ifndef _SIDE_H_
#define _SIDE_H_

#include "base_types.h"


typedef enum {
	XA, XB, YA, YB, ZA, ZB
} e_direction;
typedef unsigned char t_direction;

typedef enum {
	RNONE, RX, RY, RZ
} e_rotation_direction;
typedef unsigned char t_rotation_direction;



typedef struct {
	float angle;
	t_rotation_direction rdir;
} t_rotation;

typedef struct {
	t_color color;
	t_rotation rot;
	t_direction dir;
	unsigned char row, col;
} t_plane;

typedef t_plane t_cube[9 * 6];

void copy_color(t_color *a, t_color *b);
void create_cube(t_cube *cube);

void rotate_sides(t_cube* cube, t_rotation_direction rdir, unsigned char row);
void render_cube(t_cube *cube);
void render_plane(t_plane *plane);

#endif

