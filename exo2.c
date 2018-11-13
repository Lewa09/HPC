#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#ifdef _OPENMP
#include <omp.h>
#endif // _OPENMP

#ifndef VAL_N
#define VAL_N 100000
#endif

#ifndef VAL_M
#define VAL_M 5
#endif


int main()
{

   // Problem variables

   int n = VAL_N , m = VAL_M , i , index[n];
   double x[m] ; double z[m];

   // Initializing x array as index array (defining "an indirect access" to x)
	
   for(i=0; i<m; i++)     x[i] = 1.;
   for(i=0; i<n; i++) index[i] = i%m;

   // Print Sequential or Parallel execution

   int nbThreads = 0;

   #ifdef _OPENMP
      nbThreads = omp_get_max_threads();
      printf("\n\033[1m Parallel execution with \033[1;31m%d\033[0m\033[1m thread(s) in the team\033[0m\n\n",nbThreads);
   #else
      printf("\n\033[1m Sequential execution\033[0m\n\n");
   #endif

   // OpenMP Parallel Region

   #pragma omp parallel  private(z)
   {
      for (int j=0;j<m;j++){
        z[j]=0.0;
      }
      #pragma omp for //
      for(i=0; i<n; i++)
      {
        z[ index[i] ] = z[ index[i] ] + 1.;
		// memcpy(z, x, sizeof(z));
      }
     #pragma omp critical
     {
       for(int j=0;j<m;j++){
         x[j]=x[j]+z[j];
       }
     }
   }

	// ordered fonctionne bien mais n'a aucun intérêt parce qu'on ne 		parallélise pas

   // Final Check

   for(i=0; i<m; i++) printf("x[%d] = %7.1e (expected value = %7.1e)\n",i,x[i],(double)(n/m));

   return EXIT_SUCCESS;

}
