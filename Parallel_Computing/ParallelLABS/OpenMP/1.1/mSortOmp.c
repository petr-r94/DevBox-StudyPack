#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "service.h"
int* mas_parallel= NULL;
int maxlvl;

//Merge two parts
void merge(int *arr, size_t size, size_t a_size, size_t b_size)
{
  int i, j, k;
  int *a = arr, *b = arr + a_size;
  int *c;

  if (a[a_size-1] <= b[0]) return;
//Buffering right piece
  c = (int *)malloc(b_size * sizeof(int));
  memcpy(c, b, b_size * sizeof(int));
//compare last elements of parts
  i = a_size - 1; j = b_size - 1; k = size - 1;
  while (i >= 0 && j >= 0)
  {
    if (a[i] > c[j])
      arr[k--] = a[i--];
    else 
      arr[k--] = c[j--];
  }
  while (j >= 0) arr[k--] = c[j--];
  free(c);
}

void msort_serial(int *arr, size_t size) {
  size_t a_size = size / 2;
  size_t b_size = size - a_size;
  if (size <= 1) return;
  msort_serial(arr, a_size);
  msort_serial(arr + a_size, b_size);
  merge(arr, size, a_size, b_size);
}

void msort_omp(int *arr, size_t size) {
  size_t a_size = size / 2;
  size_t b_size = size - a_size;
  //printf("SIZE== %d \n", size);
    if (size <= 1) return;
    if(omp_get_active_level() >= omp_get_max_active_levels()) {
	msort_omp(arr, a_size);
	msort_omp(arr + a_size, b_size);
    }
    else {
    #pragma omp parallel sections num_threads(2)
    {

      #pragma omp section
      {
	//printf("Thread %d %d\n",omp_get_thread_num(), a_size);
	msort_serial(arr, a_size);
      }

      #pragma omp section
      {
	//printf("Thread %d %d\n",omp_get_thread_num(), b_size);
	msort_serial(arr + a_size, b_size);
      }
    }
    }
  merge(arr, size, a_size, b_size);
}

double run_parallel(int N){
  omp_set_nested(1);
  omp_set_max_active_levels(maxlvl);
  double t=omp_get_wtime();
  msort_omp(mas_parallel, N);
  return omp_get_wtime() - t;
}


int main(int argc, char* argv[]){
 //Detect threads
  printf("Максимальное количество уровней рекурсии: ");
  scanf("%d", &maxlvl);
 //Generating array
  if(argc == 3) {
	N = atoi(argv[1]);
	RMAX = atoi(argv[2]);
  }
  else {
	N = N_DEF;
	RMAX = RMAX_DEF;	  
  }
  mas_parallel = generate_mas(N, RMAX);
  /*
  printf("\n===SOURCE MASSIV===:\n");
  print_mas(mas_parallel, N);
  printf("\n");
  */
  
  double t;
  t = run_parallel(N);
  
  /*
  printf("\n===SORT MASSIV===:\n");
  print_mas(mas_parallel, N);
  printf("\n");
  */
  
  printf("PARALLEL_TIME\t%f\n", t);
  free(mas_parallel);
  return 0;
}
