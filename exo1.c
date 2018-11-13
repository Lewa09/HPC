#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#ifdef _OPENMP
#include <omp.h>
#endif // _OPENMP

#ifndef VAL_N
#define VAL_N 3000000
#endif

int main()
{

   // Problem variables

   int n = VAL_N , i , count = 0 , mycount = 0, me = 0;

   // Print Sequential or Parallel execution

   int nbThreads = 0;

   #ifdef _OPENMP
      nbThreads = omp_get_max_threads();
      printf("\n\033[1m Parallel execution with \033[1;31m%d\033[0m\033[1m thread(s) in the team\033[0m\n\n",nbThreads);
   #else
      printf("\n\033[1m Sequential execution\033[0m\n\n");
   #endif

   #ifdef _OPENMP
      int *loopThreads=NULL;
      loopThreads = (int*)malloc(nbThreads*sizeof(int));
   #endif

   // OpenMP Parallel Region

   #pragma omp parallel private(me) private(mycount) //
   {
      #ifdef _OPENMP
         me = omp_get_thread_num();
      #endif

      mycount = 0;

      #pragma omp for reduction(+:count)   //
      for(i=0; i<n; i++)
      {
           count += 1;
         mycount += 1;
      }

      #ifdef _OPENMP
         loopThreads[me] = mycount;
      #endif
   }

   // Final Check

   printf("counter = %d / n = %d\n",count,n);

   #ifdef _OPENMP
      printf("\nIndex per thread:\n");
      int sum = 0;
      for(i=0; i<nbThreads; i++) {
         printf("Thread %2d %8d\n",i,loopThreads[i]);
         sum += loopThreads[i];
      }
      printf("Sum       %8d\n",sum);
      free(loopThreads);
   #endif

   return EXIT_SUCCESS;

}
