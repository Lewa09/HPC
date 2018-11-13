#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#ifdef _OPENMP
#include <omp.h>
#endif // _OPENMP

#ifndef VAL_N
#define VAL_N 20
#endif

int main()
{

   // Problem variables

   int n = VAL_N , i , k = 2 , me = 0;
   double a[n];

   // Initializing a array

   for(i=0; i<n; i++) a[i] = 1.;

   // Print Sequential or Parallel execution

   int nbThreads = 0;

   #ifdef _OPENMP
      nbThreads = omp_get_max_threads();
      printf("\n\033[1m Parallel execution with \033[1;31m%d\033[0m\033[1m thread(s) in the team\033[0m\n\n",nbThreads);
   #else
      printf("\n\033[1m Sequential execution\033[0m\n\n");
   #endif

   // OpenMP Parallel Region

   #pragma omp parallel
   {
      #pragma omp for schedule(dynamic,2) 
      for(i=0; i<n-k; i++)
      {
         a[i] = a[i+k] + 1.;
      }
   }

   // Final Check

   for(i=0; i<n; i++) printf("a[%3d] = %4.1f\n",i,a[i]);

   return EXIT_SUCCESS;

}
