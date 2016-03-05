#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "SPHSolver.h"

using namespace std;

SPHSolver *fluid;

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

  eye.x = 1.0; eye.y = 1.0; eye.z = 1.0;
  view.x = 1.0; view.y = 1.0; view.z = 0.0;
  up.x = 0.0; up.y = 1.0; up.z = 0.0;

  gluLookAt(eye.x,eye.y,eye.z,view.x,view.y,view.z,up.x,up.y,up.z);
}

void drawParticles() {
  // draw particles
  glPointSize(2.5f);
  glBegin(GL_POINTS);
  vector<SPHParticle>::iterator pi = fluid->particles.begin();
  while(pi != fluid->particles.end()) {
    vector3 color = pi->color;
    glColor3f(color.x, color.y, color.z);
    vector2 position = pi->position;
    glVertex3f(position.x, position.y, 0.0f);
    ++pi;
  }
  glEnd();
  glFlush();
}

void draw_stuff()
{
  struct point front[4] = {
      {0.0f,0.0f,0.0f}, {0.0f,2.0f,0.0f}, {2.0f,2.0f,0.0f}, {2.0f,0.0f,0.0f} };


  // call for wireframe
  glPolygonMode(GL_FRONT,GL_LINE);
  glPolygonMode(GL_BACK,GL_LINE);

  // fat yellow lines
  glColor3f(1.0,1.0,0.0);
  glLineWidth(2.0);

  glBegin(GL_QUADS);
  for(int i=0; i<4; i++) glVertex3f(front[i].x,front[i].y,front[i].z);
  glEnd();

  drawParticles();
}


void initParticleSim() {
  srand (static_cast <unsigned> (time(0)));

  fluid = new SPHSolver(100, 0.0f, 2.0f);
}

void callbackDisplay( void )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  draw_stuff();
  glutSwapBuffers();
}

// animate and display new result
void callbackIdle() {
  fluid->update(0.000075f, LEAP_FROG);
//  for (unsigned long i = 0; i < 100; ++i) {
//    cout << fluid->particles.at(i).position.x << "   " << fluid->particles.at(i).position.y << endl;
//  }
  glutPostRedisplay();
}


void callbackKeyboard( unsigned char key, int x, int y )
{
  float new_dampening;
  switch (key)
  {
    case ',' : case '<':
      new_dampening = fluid->dampening - 0.01f;
      fluid->dampening = new_dampening >= 0.0f ? new_dampening : 0.0f;
      cout << "Setting dampening. Bounce energy is " << fluid->dampening * 100 << "% of original energy" << endl;
      break;

    case '.': case '>':
      fluid->dampening += 0.01f;
      cout << "Setting dampening. Bounce energy is " << fluid->dampening * 100 << "% of original energy" << endl;
      break;

    case 'q':
    cout << "Exiting Program" << endl;
    exit(0);

    case 'p':
      fluid->party_mode = !fluid->party_mode;
    default:
    break;
  }
}


void PrintUsage()
{
  cout << "sph_fluid_simulator keyboard choices\n";
  cout << "./,      increase/decrease % of energy retained after bounce\n";
  cout << "p        turn on party mode. Randomizes particle color on collison\n";
  cout << "spacebar paused the simulation. pressing it again un-pauses the simulation\n";
  cout << "q        exits the program\n";
}


int main(int argc, char** argv)
{
  initParticleSim();
  glutInit(&argc,argv);

  glutInitDisplayMode(GLUT_RGBA|GLUT_MULTISAMPLE);
  glutInitWindowSize(512,512);
  glutInitWindowPosition(100,50);
  glutCreateWindow("2D SPH Particle Simulation");
  glClearColor(0.35,0.35,0.35,0.0);
  glEnable(GL_MULTISAMPLE_ARB);
  setup_the_viewvolume();
  glutDisplayFunc(callbackDisplay);
  glutKeyboardFunc(&callbackKeyboard);
  glutIdleFunc(&callbackIdle);
  glutMainLoop();
  return 0;
}