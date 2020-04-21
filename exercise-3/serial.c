#include <stdlib.h>
#include <time.h> 
#include <stdio.h> 
#include <sys/time.h>

#define N 1000000
#define REPS 10

double mysecond();

int main() {

  int x[N];
  double t1, t2;
  double maxval;
  int maxloc;

  srand(time(0)); // seed
  for(int i=0; i < N;i++){
    // Generate random number between 0 and 1
    x[i] = ((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*1000;
  }

  for (int j=0; j < REPS; j++) {
    maxval = 0.0; 
    maxloc = 0;
  
    t1 = mysecond();
    for (int i=0; i < N; i++){
        if (x[i] > maxval) {
              maxval = x[i]; 
              maxloc = i;
        }
    }
    t2 = mysecond();
    printf("%11.8f\n", (t2 - t1));
  }
  
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