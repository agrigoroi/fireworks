
////////////////////////////////////////////////////////////////
// School of Computer Science
// The University of Manchester
//
// This code is licensed under the terms of the Creative Commons 
// Attribution 2.0 Generic (CC BY 3.0) License.
//
// Skeleton code for COMP37111 coursework, 2012-13
//
// Authors: Arturs Bekasovs and Toby Howard
//
/////////////////////////////////////////////////////////////////

#include "ex1.h"
#define RENDERING_TRAIL 1

list<Particle *> particles;
int frames;
//smaller than one?
list<Sphere *> spheres;
float SPHERES_PER_FRAME;
float GRAVITY_POWER;
int SPHERE_TTL;
int SPHERE_PARTICLES;
int PARTICLE_TTL;
int renderingType = 0;
///////////////////////////////////////////////

void initData(void) {
  frames = 0;
  SPHERES_PER_FRAME = 0.03;
  GRAVITY_POWER = 0.05;
  SPHERE_TTL = 150;
  SPHERE_PARTICLES = 150;
  PARTICLE_TTL = 100;
  // for(int i=0;i<20;i++)
}

///////////////////////////////////////////////

void animate(void)
{
  frames++;
  if(SPHERES_PER_FRAME > myRandom())
    spheres.push_back(new Sphere());
  auto spheres_iterator = spheres.begin();
  while(spheres_iterator != spheres.end()) {
    ((*spheres_iterator)->center).ttl--;
    if(((*spheres_iterator)->center).ttl <= 0) {
      particles.splice(particles.end(), (*spheres_iterator)->explode());
      delete *spheres_iterator;
      spheres_iterator = spheres.erase(spheres_iterator); 
    } else {
      (*spheres_iterator)->move();
      spheres_iterator++;
    }
  }
  auto particles_iterator = particles.begin();
  while(particles_iterator != particles.end()) {
    (*particles_iterator)->ttl--;
    if((*particles_iterator)->ttl <= 0) {
      delete *particles_iterator;
      particles_iterator = particles.erase(particles_iterator);
    } else {
      (*particles_iterator)->move();
      particles_iterator++;
    }
  }
  glutPostRedisplay();
}


void display()
{
  glLoadIdentity();
  gluLookAt(0.0, 100.0, 1000.0,
            0.0, 500.0, 0.0,
            0.0, 1.0, 0.0);
  // Clear the screen
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(1.0f);
  glLineWidth(1.0f);
  // glColor3f(0.0f, 0.0f, 1.0f);
  //   glBegin(GL_QUADS);
  //   //bl
  //   glVertex3f(-4000.0,-100,10000.0);
  //   //br
  //   glVertex3f(4000.0,-100,10000.0);
  //   //tr
  //   glVertex3f(4000.0,80,-10000.0);
  //   //tl
  //   glVertex3f(-4000.0,80,-10000.0);
  // glEnd();
  // glColor3f(1.0f, 1.0f, 1.0f);
  for(auto it = spheres.begin(); it != spheres.end(); it++) {
    glPushMatrix();
    glTranslatef(((*it)->center).location.x, ((*it)->center).location.y, ((*it)->center).location.z);
    glColor3f(((*it)->center).color.x, ((*it)->center).color.y, ((*it)->center).color.z);
    glutSolidSphere((*it)->radius, 8, 8);
    glPopMatrix();
  }
  switch(renderingType){
  case RENDERING_TRAIL:
    glBegin(GL_LINES);
      for(auto it = particles.begin(); it != particles.end(); it++) {
        glColor3f((*it)->color.x, (*it)->color.y, (*it)->color.z);
        glVertex3f((*it)->location.x, (*it)->location.y, (*it)->location.z);
        glVertex3f((*it)->previousLocation.x, (*it)->previousLocation.y, (*it)->previousLocation.z);
      }
    glEnd();
    break;
  default:
    glBegin(GL_POINTS);
      for(auto it = particles.begin(); it != particles.end(); it++) {
        glColor3f((*it)->color.x, (*it)->color.y, (*it)->color.z);
        glVertex3f((*it)->location.x, (*it)->location.y, (*it)->location.z);
      }
    glEnd();
  }
  glutSwapBuffers();
}

///////////////////////////////////////////////

void keyboard(unsigned char key, int x, int y)
{
  if(key == 27) exit(0);
  // If space restart program??
  if(key == 32) 
    exit(0);
  glutPostRedisplay();
}

///////////////////////////////////////////////

void reshape(int width, int height)
{
  glClearColor(0.9, 0.9, 0.9, 1.0);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 10000.0);
  glMatrixMode(GL_MODELVIEW);
}

void change_sphere_rate(int value) {
  SPHERES_PER_FRAME = value/100.0;
}

void change_gravity(int value) {
  GRAVITY_POWER = value*0.025;
}

void change_sphere_ttl(int value) {
  SPHERE_TTL = value;
}

void change_sphere_particles(int value) {
  SPHERE_PARTICLES = value;
}

void change_particle_ttl(int value) {
  PARTICLE_TTL = value;
}

void change_rendering_type(int value) {
  renderingType = value;
}

///////////////////////////////////////////////
void initGraphics(int argc, char *argv[])
{
  initData();
  glutInit(&argc, argv);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutCreateWindow("COMP37111 Particles");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutIdleFunc(animate);
  auto sphere_rate_submenu = glutCreateMenu(change_sphere_rate);
    glutAddMenuEntry("Very few", 1);
    glutAddMenuEntry("Few", 2);
    glutAddMenuEntry("Normal", 3);
    glutAddMenuEntry("Many", 4);
    glutAddMenuEntry("A lot ", 5);
  auto gravity_power_submenu = glutCreateMenu(change_gravity);
    glutAddMenuEntry("No Gravity", 0);
    glutAddMenuEntry("Low", 1);
    glutAddMenuEntry("Medium", 2);
    glutAddMenuEntry("High", 3);
    glutAddMenuEntry("Very Hight", 4);
  auto sphere_ttl_submenu = glutCreateMenu(change_sphere_ttl);
    glutAddMenuEntry("Very Short", 50);
    glutAddMenuEntry("Short", 100);
    glutAddMenuEntry("Normal", 150);
    glutAddMenuEntry("Long", 200);
    glutAddMenuEntry("Very Long", 250);
  auto sphere_particles_submenu = glutCreateMenu(change_sphere_particles);
    glutAddMenuEntry("Very few", 50);
    glutAddMenuEntry("Few", 100);
    glutAddMenuEntry("Normal", 150);
    glutAddMenuEntry("Many", 200);
    glutAddMenuEntry("A lot", 250);
  auto particle_ttl_submenu = glutCreateMenu(change_particle_ttl);
    glutAddMenuEntry("Very Short", 50);
    glutAddMenuEntry("Short", 100);
    glutAddMenuEntry("Normal", 150);
    glutAddMenuEntry("Long", 200);
    glutAddMenuEntry("Very Long", 250);
  auto rendering_type_submenu = glutCreateMenu(change_rendering_type);
    glutAddMenuEntry("Points", 0);
    glutAddMenuEntry("Trails", 1);
  auto main_menu = glutCreateMenu(NULL);
    glutAddSubMenu("Number of Spheres", sphere_rate_submenu);
    glutAddSubMenu("Gravity", gravity_power_submenu);
    glutAddSubMenu("Lifetime of Spheres", sphere_ttl_submenu);
    glutAddSubMenu("Number of Particles", sphere_particles_submenu);
    glutAddSubMenu("Lifetime of Particles", particle_ttl_submenu);
    glutAddSubMenu("Rendering Type", rendering_type_submenu);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  // double f;
  srand(time(NULL));
  initGraphics(argc, argv);
  glEnable(GL_POINT_SMOOTH);
  glutMainLoop();
  return 0;
}