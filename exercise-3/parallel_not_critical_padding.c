#include <stdlib.h>
#include <time.h> 
#include <stdio.h> 
#include <sys/time.h>
#include <omp.h>

#define N 1000000
#define REPS 10
#define MAX_THREADS 32

double mysecond();

typedef struct {
  double maxval;
  int maxloc;
  char pad[116];
} thread_vals;

int main() {

  int x[N];
  double t1, t2;
  double realmaxval = 0.0;
  int realmaxloc = 0;

  //init array and find the real maxval and maxloc
  srand(time(0)); // seed
  for(int i=0; i < N;i++){
    // Generate random number between 0 and 1
    x[i] = ((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*1000;
    if (x[i] > realmaxval) {
      realmaxval = x[i];
      realmaxloc = i;
    }
  }

  printf("Real maxval = %f\nReal maxloc = %d\n", realmaxval, realmaxloc);

  thread_vals vals[MAX_THREADS];
  
  t1 = mysecond();

  //Parallel section
  #pragma omp parallel
  { 
    int id = omp_get_thread_num();
    vals[id].maxval = -1.0e30;
    #pragma omp for
      for (int i=0; i < N; i++) { 
        if (x[i] > vals[id].maxval) {
          vals[id].maxval = x[i]; 
          vals[id].maxloc = i;
        } 
      }
    
  }

  int maxloc = vals[0].maxloc;
  double maxval = vals[0].maxval;
  for (int i = 0; i < MAX_THREADS; i++) {
    if (vals[i].maxval > maxval) {
      maxval = vals[i].maxval;
      maxloc = vals[i].maxloc;
    }
  }
  
  t2 = mysecond();
  printf("Time=%11.8f\nFound maxval=%f\nFound maxloc=%d\n", (t2 - t1), maxval, maxloc);
  printf("---------------------------------------\n");

  return 0;
}

// function with timer                                                             
double mysecond(){
  struct timeval tp;
  struct timezone tzp;
  int i;

  i = gettimeofday(&tp,&tzp);
  return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}