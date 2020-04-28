#include "stdio.h" // printf
#include "stdlib.h" // malloc and rand for instance. Rand not thread safe!
#include "time.h"   // time(0) to get random seed
#include "math.h"  // sine and cosine
#include "omp.h"   // openmp library like timing

#define DIM 2
#define MAX_PARTICLES 500
#define G 6.67408e-11
#define CYCLES 100
#define DELTA_T 0.05

typedef double vect_t[DIM];

void computeForces(vect_t* pos, double* masses, vect_t* forces);
void initParticles(vect_t* pos, vect_t* old_pos, vect_t* vel, double* masses);

int main(void) {

  vect_t* pos = (vect_t*) malloc (MAX_PARTICLES*sizeof(vect_t));
  vect_t* old_pos = (vect_t*) malloc (MAX_PARTICLES*sizeof(vect_t));
  vect_t* vel = (vect_t*) malloc (MAX_PARTICLES*sizeof(vect_t));
  vect_t* forces = (vect_t*) malloc (MAX_PARTICLES*sizeof(vect_t));
  double* masses = (double*) malloc (MAX_PARTICLES*sizeof(double));

  initParticles(pos, old_pos, vel, masses);
  computeForces(pos, masses, forces);

  for(int step = 0; step <= CYCLES/DELTA_T ; step++) {
    printf("%d \n", step);
  }
}

void computeForces(vect_t* pos, double* masses, vect_t* forces) {
  for(int q = 0; q < MAX_PARTICLES; q++) {
    for(int k = 0; k < MAX_PARTICLES; k++) {
      if(k == q) {
        continue;
      }
      double x_diff = pos[q][0] - pos[k][0];
      double y_diff = pos[q][1] - pos[k][1];

      double dist = sqrt(x_diff*x_diff + y_diff*y_diff);
      double dist_cubed = dist*dist*dist;

      forces[q][0] -= G*masses[q]*masses[k]/dist_cubed * x_diff;
      forces[q][1] -= G*masses[q]*masses[k]/dist_cubed * y_diff;
    }
  }
}
  
void initParticles(vect_t* pos,vect_t* old_pos, vect_t* vel, double* masses) {
  for(int q = 0; q < MAX_PARTICLES; q++) {
    pos[q][0] = (rand() / (double)(RAND_MAX)) * 2 - 1;
		pos[q][1] = (rand() / (double)(RAND_MAX)) * 2 - 1;

		old_pos[q][0] = -1;
		old_pos[q][1] = -1;

		vel[q][0] = (rand() / (double)(RAND_MAX)) * 2 - 1;
		vel[q][1] = (rand() / (double)(RAND_MAX)) * 2 - 1;
		
		masses[q] = fabs((rand() / (double)(RAND_MAX)) * 2 - 1);
  }
}




