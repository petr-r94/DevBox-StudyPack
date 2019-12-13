#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "service.h"
int* mas_serial = NULL;

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

double run_serial(int N){
  double t=omp_get_wtime();
  //printf("\n===SERIAL===:\n");
  msort_serial(mas_serial, N);
  return omp_get_wtime() - t;
}


int main(int argc, char* argv[]){
  //Generating array
  if(argc == 3) {
	N = atoi(argv[1]);
	RMAX = atoi(argv[2]);
  }
  else {
	N = N_DEF;
	RMAX = RMAX_DEF;	  
  }
  mas_serial = generate_mas(N, RMAX);
  /*
  printf("\n===SOURCE MASSIV===:\n");
  print_mas(mas_serial, N);
  printf("\n");
  */
  double t;
  t = run_serial(N);
  /*
  printf("\n===SORT MASSIV===:\n");
  print_mas(mas_serial, N);
  printf("\n");
  */
  printf("SERIAL_TIME\t%f\n", t);
  free(mas_serial);
  return 0;
}
