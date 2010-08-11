#ifndef _PIECE_H_
#define _PIECE_H_

typedef struct {
	// translate
	float x, y, z;
	// rotate
	float rx, ry, rz;
	// color vectors
	float cf[3], ct[3], cr[3];
	int sides;
} t_piece;

void render_piece(t_piece p, float scale, float size);

#endif

