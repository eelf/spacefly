#ifndef _PIECE_H_
#define _PIECE_H_

typedef struct {
	// translate
	int x, y, z;
	// rotate
	float rx, ry, rz;
	// color vectors
	float cf[3], ct[3], cr[3];
	int sides;
} t_piece;

void rotate_pieces(int gran, t_piece* p);
void render_pieces(t_piece *p, float scale, float size);
void render_piece(t_piece p, float scale, float size);

#endif

