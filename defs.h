#if defined(__APPLE__) || defined(MACOSX)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h> //!!! Not FreeGlut!! необходимо, что бы функционал везде совпдал
#endif

#ifndef PI
#define PI 3.1415926
#endif

