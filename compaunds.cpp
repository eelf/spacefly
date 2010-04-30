/*
	sides Bitmap code for 6 sides: front up right back down left
*/
void DrawUgolok(float x, float y, float z, int sides, int colors, float size) {
	/*	
		zyxz yxzy xzyx
		0010 0001 0011	front  z0
		1011 0000 0001  top	   y0
		1101 0000 0010  right  x0
		1011 0011 0111  back   z1
		1111 1001 0011  bottom y1
		1111 0100 1011  left   x1
	*/
	int grani[6] = {0x213, 0xb01, 0xd02, 0xb37, 0xf93, 0xf4b};
	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);
	for(int i = 0; i < 6; i++) {
		if ((sides & 1 << i) == 0) continue;
		glColor3f(colors & 1 << (i * 3 + 2) ? 1.0 : 0.0,
			colors & 1 << (i * 3 + 1) ? 1.0 : 0.0,
			colors & 1 << (i * 3    ) ? 1.0 : 0.0);
		for(int j = 0; j < 12; j+=3)
			glVertex3f(grani[i] & 1 << j ? -size : size,
				grani[i] & 2 << j ? -size : size,
				grani[i] & 4 << j ? -size : size);
	}
	glEnd();
	glPopMatrix();
		
}
void DrawNet(GLfloat size, GLint LinesX, GLint LinesZ) {
	glBegin(GL_LINES);
	for (int xc = 0; xc < LinesX; xc++) {
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
					0.0,
					size / 2.0);
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
					0.0,
					size / -2.0);
	}
	for (int zc = 0; zc < LinesX; zc++) {
		glVertex3f(	size / 2.0,
					0.0,
					-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
		glVertex3f(	size / -2.0,
					0.0,
					-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
	}
	glEnd();
}

void DrawPrism(float x, float y, float z, float yrot, float zrot, float width, float height, float depth) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glRotatef(zrot, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glColor3f(0.5, 0.5, 0.5);
		glVertex3f(-width, -height, -depth); // нижн€€
		glVertex3f( width, -height, -depth);
		glVertex3f( width, -height,  depth);
		glVertex3f(-width, -height,  depth);

		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(-width, -height, -depth); // лева€
		glVertex3f(-width,  height, -depth);
		glVertex3f(-width,  height,  depth);
		glVertex3f(-width, -height,  depth);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f( width, -height, -depth); // права€
		glVertex3f( width,  height, -depth);
		glVertex3f( width,  height,  depth);
		glVertex3f( width, -height,  depth);

		glColor3f(9.0, 9.0, 0.9);
		glVertex3f(-width,  height, -depth); // верхн€€
		glVertex3f( width,  height, -depth);
		glVertex3f( width,  height,  depth);
		glVertex3f(-width,  height,  depth);

	glEnd();
	glPopMatrix();

}
void DrawCoords() {
	glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
	glEnd();
}
void DrawWalls() {
	glColor3f(0.1,0.1,0.1);      // ”становим синий цвет только один раз
	glPushMatrix();
	glTranslatef(0.0f,-2.0f,0.0f);          // —двиг вправо на 1.5
	DrawNet(20.0f, 30, 30);
	glPopMatrix();

	glColor3f(0.0,0.0,1.0);      // ”становим синий цвет только один раз
	glPushMatrix();
	glTranslatef(10.1,8.0,0.0);          // —двиг вправо на 1.5
	glRotatef(90.0,0.0,0.0,1.0);
	DrawNet(20.0f, 30, 30);
	glPopMatrix();

	glColor3f(1.0,1.0,0.0);      // ”становим синий цвет только один раз
	glPushMatrix();
	glTranslatef(0.0,8.0,-10.1);          // —двиг вправо на 1.5
	glRotatef(90.0,1.0,0.0,0.0);
	DrawNet(20.0f, 30, 30);
	glPopMatrix();
}
