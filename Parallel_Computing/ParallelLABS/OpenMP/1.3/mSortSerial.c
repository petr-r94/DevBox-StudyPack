#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "service.h"
double* mas_serial = NULL;

//Merge two parts
void merge(double *arr, size_t size, size_t a_size, size_t b_size)
{
  int i, j, k;
  double *a = arr, *b = arr + a_size;
  double *c;

  if (a[a_size-1] <= b[0]) return;
//Buffering right piece
  c = (double *)malloc(b_size * sizeof(double));
  memcpy(c, b, b_size * sizeof(double));
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

void msort_serial(double *arr, size_t size) {
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
  if(validateArgs(argc, argv)) {
	mas_serial = generate_mas(N, RMAX);
  }
  else {
	
	exit(0);	  
  }
  
  //printf("\n===SOURCE MASSIV===:\n");
  //print_mas(mas_serial, N);
  
  double t;
  t = run_serial(N);
  
  //printf("\n===SORT MASSIV===:\n");
  //print_mas(mas_serial, N);
  
  printf("SERIAL_TIME\t%f\n\n", t);
  free(mas_serial);
  return 0;
}
