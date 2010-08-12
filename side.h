#ifndef _SIDE_H_
#define _SIDE_H_

#include "base_types.h"

typedef struct {
	int side;
	t_color color[9];
} t_side;

void rotate_sides(int gran, t_side* p);
void render_sides(t_side *p, float scale, float size);
void render_side(t_side p, float scale, float size);

#endif

