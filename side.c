#include "defs.h"

#include "side.h"

void copy_color(t_color *a, t_color *b) {
	(*a)[0] = (*b)[0];
	(*a)[1] = (*b)[1];
	(*a)[2] = (*b)[2];
}

void copy_side(t_side *a, t_side *b) {
	for(int i = 0; i < 9; i++)
		copy_color(&(*a).color[i], &(*b).color[i]);
}

/*
typedef struct {
	int gran;
	int idxs[3];
} t_row;

typedef struct {
	t_row row[4];
} t_chain;

const t_row r00 = {4, {6, 7, 8}};
const t_row r01 = {1, {0, 3, 6}};
const t_row r02 = {5, {0, 1, 2}};
const t_row r03 = {3, {2, 5, 8}};

const t_chain chain1 = {r00, r01, r02, r03};

t_chains[] = {chain1};


t_chain chains[] = {
	{// vrasheniye grani 0
	{4, {6, 7, 8}}, {1, {0, 3, 6}}, {5, {0, 1, 2}}, {3, {2, 5, 8}}
	},
	
	{// vrasheniye grani 1
	{4, {8, 5, 2}}, {2, {0, 3, 6}}, {5, {2, 5, 8}}, {0, {8, 5, 2}}
	},

	{// vrasheniye grani 2*
	{4, {6, 7, 8}}, {1, {0, 3, 6}}, {5, {0, 1, 2}}, {3, {2, 5, 8}}
	},

	{// vrasheniye grani 3*
	{4, {6, 7, 8}}, {1, {0, 3, 6}}, {5, {0, 1, 2}}, {3, {2, 5, 8}}
	},

	{// vrasheniye grani 4*
	{4, {6, 7, 8}}, {1, {0, 3, 6}}, {5, {0, 1, 2}}, {3, {2, 5, 8}}
	},

	{// vrasheniye grani 5*
	{4, {6, 7, 8}}, {1, {0, 3, 6}}, {5, {0, 1, 2}}, {3, {2, 5, 8}}
	}
};
*/

int line[6][12] = {
{46, 47, 48, 10, 13, 16, 50, 51, 52, 32, 35, 38},
{48, 45, 42, 20, 23, 26, 52, 55, 58, 8, 5, 2},

{48, 45, 42, 20, 23, 26, 52, 55, 58, 8, 5, 2},
{48, 45, 42, 20, 23, 26, 52, 55, 58, 8, 5, 2},
{48, 45, 42, 20, 23, 26, 52, 55, 58, 8, 5, 2},
{48, 45, 42, 20, 23, 26, 52, 55, 58, 8, 5, 2}
};

void rotate_sides(int gran, t_side* p) {
	t_side tmp;
	copy_side(&tmp, &p[gran]);
	copy_color(&p[gran].color[0], &tmp.color[6]);
	copy_color(&p[gran].color[1], &tmp.color[3]);
	copy_color(&p[gran].color[2], &tmp.color[0]);
	copy_color(&p[gran].color[3], &tmp.color[7]);
	// 4 central
	copy_color(&p[gran].color[5], &tmp.color[1]);
	copy_color(&p[gran].color[6], &tmp.color[8]);
	copy_color(&p[gran].color[7], &tmp.color[5]);
	copy_color(&p[gran].color[8], &tmp.color[2]);
	
	t_color tmpcolor;
	copy_color(&tmpcolor, &p[line[gran][0] / 10].color[line[gran][0] % 10]);
	for(int i = 1; i < 12; i++) {
		copy_color(&p[line[gran][i - 1] / 10].color[line[gran][i - 1] % 10],
			 	   &p[line[gran][i] / 10].color[line[gran][i] % 10]);
	}
	copy_color(&p[line[gran][11] / 10].color[line[gran][11] % 10],
		 	   &tmpcolor);
	/*
	t_chain *chain = chains[gran];
	t_side *lastside;
	lastside = &p[chain[0].gran];
	for(int i = 0; i < 3; i++) {
		copy_side(&tmp, &p[chain[i + 1].gran]);
		for(int j = 0; j < 3; j++)
			p[chain[i].gran].color[chain[i].idxs[j]] = p[chain[i + 1].gran].color[chain[i + 1].idxs[j]];
	}
	for(int j = 0; j < 3; j++)
		p[3].color[chain[3].idxs[j]] = tmp.color[chain[i].idxs[j]];
	*/
/*
	  4
	3 0 1 2
      5
0 1 2
3 4 5
6 7 8
      
*/
	
}
void render_sides(t_side *p, float scale, float size) {
	glPushMatrix();
	glTranslatef(0,0,1);
	render_side(p[0], scale, size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	glRotatef(90,0,1,0);
	render_side(p[1], scale, size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	glRotatef(180,0,1,0);
	render_side(p[2], scale, size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	glRotatef(270,0,1,0);
	render_side(p[3], scale, size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	glRotatef(90,1,0,0);
	render_side(p[4], scale, size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	glRotatef(270,1,0,0);
	render_side(p[5], scale, size);
	glPopMatrix();
}
void render_side(t_side p, float scale, float size) {
	glBegin(GL_QUADS);
	float dsize = size * 2;
	glScalef(scale, scale, scale);
	for(int i = -1; i < 2; i++) {
		glPushMatrix();
		glTranslatef(0,i * dsize,0);
	for(int j = -1; j < 2; j++) {
		glPushMatrix();
		glTranslatef(j * dsize,0,0);
		glColor3fv(p.color[i*3 + j]);
		glVertex3f(-size, -size, size);
		glVertex3f( size, -size, size);
		glVertex3f( size,  size, size);
		glVertex3f(-size,  size, size);
		glPopMatrix();
	}
	glPopMatrix();
	}
	glEnd();
}

