#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

struct point {
  float x, y, z;
};

void setup_the_viewvolume()
{
  struct point eye, view, up;

  // specify size and shape of view volume
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0,1.0,-1.0,1.0,0.0,20.0);

  // specify position for view volume
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  eye.x = 0; eye.y = 0; eye.z = 1.0;
  view.x = 0.0; view.y = 0.0; view.z = 0.0;
  up.x = 0.0; up.y = 1.0; up.z = 0.0;

  gluLookAt(eye.x,eye.y,eye.z,view.x,view.y,view.z,up.x,up.y,up.z);
}

void draw_stuff()
{
  int i;
  struct point front[4] = {
      {-1.0f,-1.0f,1.0}, {-1.0f,1.0,1.0}, {1.0,1.0,1.0}, {1.0,-1.0f,1.0} };

  // gray background
  glClearColor(0.35,0.35,0.35,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // call for wireframe
  glPolygonMode(GL_FRONT,GL_LINE);
  glPolygonMode(GL_BACK,GL_LINE);

  // fat yellow lines
  glColor3f(1.0,1.0,0.0);
  glLineWidth(2.0);

  // anti-aliasing
  glEnable(GL_MULTISAMPLE_ARB);

  glBegin(GL_QUADS);
  for(i=0;i<4;i++) glVertex3f(front[i].x,front[i].y,front[i].z);
  glEnd();
  glFlush();
}


int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_MULTISAMPLE);
  glutInitWindowSize(512,512);
  glutInitWindowPosition(100,50);
  glutCreateWindow("my_cool_cube");
  setup_the_viewvolume();
  glutDisplayFunc(draw_stuff);
  glutMainLoop();
  return 0;
}