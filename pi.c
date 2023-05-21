/* Exercise: Pi
 *
 * In this exercise you will determine the value
 * of PI using the integral  of
 *    4/(1+x*x) between 0 and 1.
 *
 * The integral is approximated by a sum of n intervals.
 *
 * The approximation to the integral in each interval is:
 *    (1/n)*4/(1+x*x).
 */
#include "mpi.h"
#include <stdio.h>
#include <time.h>

#define PI25DT 3.141592653589793238462643

#define INTERVALS 10, 000, 000, 000
#define MASTER 0

int main(int argc, char **argv)
{
  long int i, intervals = INTERVALS;
  double x, dx, f, globalSum, pi;
  double time2;
  time_t time1 = clock();
  int numtasks, taskid, numtaskperprocess;

  numtaskperprocess = 10;

  MPI_Init(&argc, &argc);
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

  printf("Number of intervals: %ld\n", intervals);

  float localSum = 0.0;

  dx = 1.0 / (double)numtasks;

  for (i = numtaskperprocess; i >= 1; i--)
  {
    x = dx * ((double)(i - 0.5));
    f = 4.0 / (1.0 + x * x);
    localSum = localSum + f;
  }

  MPI_Reduce(&localSum, &globalSum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

  pi = dx * globalSum;

  if (taskid == MASTER)
  {
    printf("SUM %d", sum);
  }

  MPI_Finalize();

  time2 = (clock() - time1) / (double)CLOCKS_PER_SEC;

  printf("Computed PI %.24f\n", pi);
  printf("The true PI %.24f\n", PI25DT);
  printf("Error       %.24f\n\n", PI25DT - pi);
  printf("Elapsed time (s) = %f\n", time2);

  return 0;
}