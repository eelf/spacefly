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

void cube_init(t_cube *cube);
void cube_rotate(t_cube* cube, t_rotation_direction rdir, unsigned char row);
void cube_end_rotate(t_cube* cube);
void cube_render(t_cube *cube);

#endif

