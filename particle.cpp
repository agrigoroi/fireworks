#include "ex1.h"

Particle::Particle(Sphere *s) {
  location.x = s->center.location.x + 2*(myRandom() - 0.5)*s->radius;
  location.y = s->center.location.y + 2*(myRandom() - 0.5)*s->radius;
  location.z = s->center.location.z + 2*(myRandom() - 0.5)*s->radius;
  speed.x = (myRandom() - 0.5)*5;
  speed.y = (myRandom() - 0.5)*5;
  speed.z = (myRandom() - 0.5)*5;
  set(&color, s->center.color.x, s->center.color.y, s->center.color.z);
  add(&speed, &(s->center.speed));
  set(&acceleration, 0, 0-GRAVITY_POWER, 0);
  add(&acceleration, &(s->center.acceleration));
  ttl = int((myRandom() + 0.5)*PARTICLE_TTL);
}

void Particle::move() {
  previousLocation = location;
  add(&speed, &acceleration);
  add(&location, &speed);
}

// Particle::Particle(Triple l, Triple s, Triple a, float r) {
//   location = l;
//   speed = s;
//   acceleration = a;
//   size = r;
// }

/*void Particle::print() {
  printf("Pointer \n");
  printf("Location: %f %f %f\n", location.x, location.y, location.z);
  printf("Speed: %f %f %f\n", speed.x, speed.y, speed.z);
  printf("Acceleration: %f %f %f\n\n", acceleration.x, acceleration.y, acceleration.z);
}*/