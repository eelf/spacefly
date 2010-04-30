
float distraw(float x1, float y1, float z1, float x2, float y2, float z2) {
	float dx, dy, dz;
	dx = x2 - x1;
	dy = y2 - y1;
	dz = z2 - z1;
	return dx * dx + dy * dy + dz * dz;
}
float dist(float x1, float y1, float z1, float x2, float y2, float z2) {
	return sqrt(distraw(x1, y1, z1, x2, y2, z1));
}

class MassObject {
	public: float mass, x, y, z, q, r, vx, vy, vz, vq, vr, v;
	MassObject(float cmass, float cx, float cy, float cz) {
		mass = cmass;
		x = cx;
		y = cy;
		z = cz;
	}
	void draw() {
		x += vx;
		y += vy;
		z += vz;
		DrawPrism(x, y, z, q, r, 0.1, 0.1, 0.1);
	}
	void gravity(MassObject *o) {
		float dist = distraw(x, y, z, o->x, o->y, o->z);
		float a = o->mass / dist;
		v += a;
		//vx = (x - o->x) * v;
	}
	
};
