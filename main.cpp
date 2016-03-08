#include <GL/gl.h>
#include <GL/glut.h>
#include <OpenImageIO/imageio.h>
#include <time.h>

#include "SPHSolver.h"

OIIO_NAMESPACE_USING

#define MAX_TIME_STEP 0.04166667f // cap the maximum time step to 24 frames per second

struct point {
  float x, y, z;
};

SPHSolver *fluid;
unsigned int iwidth = 512;
unsigned int iheight = 512;
unsigned int frame_count = 0;
struct timespec start_time;
char *output_path;


void handleError(const char* error_message, int kill)
{
  fprintf(stderr, "Error: %s\n\n", error_message);

  if (kill == 1)
    exit(-1);
}


void writeImage() {
  char buffer[256];
  if (sprintf(buffer, "%s/fluid_simulator_%04d.jpg", output_path, frame_count++) < 0) {
    handleError((const char *) "creating filename in writeImage() failed", 0);
    return;
  }
  const char *filename = buffer;
  const unsigned int channels = 3; // RGB
  float *write_pixels = new float[iwidth * iheight * channels];
  float *window_pixels = new float[iwidth * iheight * channels];
  ImageOutput *out = ImageOutput::create(filename);
  if (!out) {
    handleError((const char *) "creating output file in writeImage() failed", 0);
    return;
  }

  glReadPixels(0, 0, iwidth, iheight, GL_RGB, GL_FLOAT, window_pixels);
  long index = 0;
  for (unsigned int j = 0; j < iheight; j++) {
    for (unsigned int i = 0; i < iwidth; i++) {
      for (unsigned int c = 0; c < channels; c++) {
        write_pixels[(i + iwidth * (iheight - j - 1)) * channels + c] = window_pixels[index++]; //color[index++];
      }
    }
  }

  ImageSpec spec (iwidth, iheight, channels, TypeDesc::FLOAT);
  out->open (filename, spec);
  out->write_image (TypeDesc::FLOAT, write_pixels);
  out->close ();
  delete out;
  delete write_pixels;
  delete window_pixels;
}


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
  std::vector<SPHParticle>::iterator pi = fluid->particles.begin();
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
  // adding dynamic timestep based off of speed of the computer
  timespec end_time;
  clock_gettime(CLOCK_REALTIME, &end_time);
  float delta_time = ((float)(end_time.tv_nsec - start_time.tv_nsec))*0.000000001f;
  start_time = end_time;

  // cap delta_time wiht min and max values
  if (delta_time < 0.0f) { delta_time = 0.0f; }
  else if (delta_time > MAX_TIME_STEP) {delta_time = MAX_TIME_STEP; }

  fluid->update(delta_time, LEAP_FROG);
  if (output_path != NULL) { writeImage(); }
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
      std::cout << "Setting dampening. Bounce energy is " << fluid->dampening * 100 << "% of original energy" << std::endl;
      break;

    case '.': case '>':
      fluid->dampening += 0.01f;
    std::cout << "Setting dampening. Bounce energy is " << fluid->dampening * 100 << "% of original energy" << std::endl;
      break;

    case 'q':
    std::cout << "Exiting Program" << std::endl;
    exit(0);

    case 'w':
      fluid->force.gravity = {0.0f, 9.8f};
      break;

    case 'a':
      fluid->force.gravity = {-9.8f, 0.0f};
      break;

    case 's':
      fluid->force.gravity = {0.0f, -9.0f};
      break;

    case 'd':
      fluid->force.gravity = {9.8f, 0.0f};
      break;

    case 'p':
      fluid->party_mode = !fluid->party_mode;
      break;
    default:
    break;
  }
}


void PrintUsage()
{
  std::cout << "sph_fluid_simulator keyboard choices\n";
  std::cout << "./,      increase/decrease % of energy retained after bounce\n";
  std::cout << "p        turn on party mode. Randomizes particle color on collison\n";
  std::cout << "w/a/s/d  switches gravity to point up/left/down/right\n";
  std::cout << "spacebar paused the simulation. pressing it again un-pauses the simulation\n";
  std::cout << "q        exits the program\n";
  std::cout << std::endl;
}


int main(int argc, char** argv) {
  output_path = new char[1024];
  if (argc==2) { output_path = argv[1]; } else { output_path = NULL; }
  clock_gettime(CLOCK_REALTIME, &start_time);

  PrintUsage();
  initParticleSim();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_MULTISAMPLE);
  glutInitWindowSize(iwidth, iheight);
  glutInitWindowPosition(100, 50);
  glutCreateWindow("2D SPH Particle Simulation");
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_MULTISAMPLE_ARB);
  setup_the_viewvolume();
  glutDisplayFunc(callbackDisplay);
  glutKeyboardFunc(&callbackKeyboard);
  glutIdleFunc(&callbackIdle);
  glutMainLoop();
  return 0;
}