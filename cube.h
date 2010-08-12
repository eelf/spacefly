#ifndef _CUBE_H_
#define _CUBE_H_

#include "defs.h"
#include "base_types.h"

typedef struct {
	unsigned int ID;
	float width, height;
	t_color color;
} t_plane;

typedef struct {
	unsigned int ID;
	float width, height, depth;
} t_box;

typedef struct {
	
} t_rube;

void draw(unsigned int ID);
unsigned int create_plane(float width, float height);
unsigned int create_box(float width, float height, float depth);

#endif

/* translate in to C please
function CreateSphere(Radius : glFloat; N : Integer) : glUint;  // N = precision
var I, J : Integer;
theta1,theta2,theta3 : glFloat;
X, Y, Z, px, py, pz : glFloat;
begin
result :=glGenLists(1);
glNewList(result, GL_COMPILE);
if Radius < 0 then Radius :=-Radius;
if n < 0 then n := -n;
if (n < 4) OR (Radius <= 0) then
begin
glBegin(GL_POINTS);
glVertex3f(0.0, 0.0, 0.0);
glEnd();
exit;
end;

for J :=0 to N DIV 2 -1 do
begin
theta1 := J*2*PI/N - PI/2;
theta2 := (J+1)*2*PI/n - PI/2;
glBegin(GL_QUAD_STRIP);
For I :=0 to N do
begin
theta3 := i*2*PI/N;
x := cos(theta2) * cos(theta3);
y := sin(theta2);
z := cos(theta2) * sin(theta3);
px := Radius*x;
py := Radius*y;
pz := Radius*z;

glNormal3f(X, Y, Z);
glTexCoord2f(1-I/n, 2*(J+1)/n);
glVertex3f(px,py,pz);

X := cos(theta1) * cos(theta3);
Y := sin(theta1);
Z := cos(theta1) * sin(theta3);
px := Radius*X;
py := Radius*Y;
pz := Radius*Z;

glNormal3f(X, Y, Z);
glTexCoord2f(1-i/n, 2*j/n);
glVertex3f(px,py,pz);
end;
glEnd();
end;
glEndList();
end;
*/