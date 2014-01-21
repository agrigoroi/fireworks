#include <cstdio>
#include <ctime>
#include <cmath>
#include <list>
#include <vector>
#include <random>
#include <iostream>

using namespace std;

#ifdef MACOSX
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

class Triple {
public:
  float x, y, z;
};

class Sphere;

class Particle {
public:
  Triple previousLocation;
  Triple location, speed, acceleration;
  Triple color;
  int ttl;
  void move();
  Particle() {};
  Particle(Sphere *);
};

class Sphere {
public:
  Particle center;
  float radius;
  int number_of_particles;
  Sphere();
  void move();
  list<Particle *> explode();
};

//Utils
double myRandom();
void add(Triple*, Triple *);
void set(Triple*, float, float, float);

extern float SPHERES_PER_FRAME;
extern float GRAVITY_POWER;
extern int SPHERE_TTL;
extern int SPHERE_PARTICLES;
extern int PARTICLE_TTL;