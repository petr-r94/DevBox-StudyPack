#include "service.h"
#include <time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

double* mas = NULL;
double RMAX;
int N;

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

void msort_mpi(double *arr, size_t size) {
  size_t a_size = size / 2;
  size_t b_size = size - a_size;
  if (size <= 1) return;
  msort_mpi(arr, a_size);
  msort_mpi(arr + a_size, b_size);
  merge(arr, size, a_size, b_size);
}

double run_mpi(int N){
  double t= MPI_Wtime();
  msort_mpi(mas, N);
  return MPI_Wtime() - t;
}


int main(int argc, char* argv[]){
	
  //Generating array
  if(validateArgs(argc, argv)) {
	mas = generate_mas(N, RMAX);
  }
  else {
	
	exit(0);	  
  }
  
  //printf("\n===SOURCE MASSIV===:\n");
  //print_mas(mas, N);
  double t;
  MPI_Init(&argc, &argv);
  t = run_mpi(N);
  MPI_Finalize();
  //printf("\n===SORT MASSIV===:\n");
  //print_mas(mas, N);
  
  printf("MPI_TIME:\t%f seconds\n\n", t);
  free(mas);
  return 0;
}



// ****************
//Service Functions
void swap(double *a, double *b)
{
  int t=*a;
  *a=*b; 
  *b=t;
}

double doubleRand(double max) {
	return ((double)rand())/((double)RAND_MAX / max);
}

double* generate_mas(int N, double RMAX) {
	srand((unsigned)time(NULL));
	double* data = (double*) malloc(sizeof(double)*N);
	int i;
	for(i=0; i<N; i++) {
		data[i] = doubleRand(RMAX);
	}
	
	return data;
}

void print_mas(double* a, int N) {
	int i;
	for(i=0; i<N; i++) {
	printf("%f, ",a[i]);
	}
	printf("\n");
}

void print_help() {
	printf("\n----------Справка по аргументам----------\nВведите параметры сортировки в следующем порядке:\n");
	printf("\t1) Количество чисел\n\t2) Верхняя граница случайного числа(Double) при генерации данных\n");
	printf("\nПример: ./sortMpi 100 99\n\n");
}

bool validateArgs(int argc, char** argv) {
	if(argc != 3){
		printf("\nОшибка! Неверное число аргументов\n");
		print_help();
		return false;
	}
	else{
		bool flag = true;
		
		//Loading Args
		N=atoi(argv[1]);
		RMAX=atof(argv[2]);
		
		//Validate Args
		if(N<=0) { printf("\n\tОшибка! Количество чисел должно быть > 0\n"); flag=false;}
		if(RMAX<=0) { printf("\n\tОшибка! Верхняя граница чисел должна быть > 0\n"); flag=false;}
		printf("\n");
		return flag;
	}
}
