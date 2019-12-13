#include <time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "service.h"


double RMAX;
int N;

// Sorting functions
void merge(double *arr, int size, int a_size, int b_size)
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

void msort_mpi(double *arr, int size) {
  unsigned int a_size = size / 2;
  unsigned int b_size = size - a_size;
  if (size <= 1) return;
  msort_mpi(arr, a_size);
  msort_mpi(arr + a_size, b_size);
  merge(arr, size, a_size, b_size);
}


int main(int argc, char* argv[]){
  double* mas = NULL;
	//Generating array
	if(validateArgs(argc, argv)) {
	  mas = generate_mas(N, RMAX);
	  //printf("\n===SOURCE MASSIV===:\n");
	  //print_mas(mas, N);
	}
	else {
	  
	  exit(0);	  
    }
    
  //Initialize
  double t1, t2;
  int w_rank, w_size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &w_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &w_size);
  
  //Sorting
  //Делим на равные порции
  int chunk_size = N/w_size;
  double *sub_mas = malloc(chunk_size * sizeof(double));
  if(w_rank ==0){
    printf("\nScattering by chunk size: %i\n", chunk_size);
    t1= MPI_Wtime();
  }
  MPI_Scatter(mas, chunk_size, MPI_DOUBLE, sub_mas, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  
  //Сортируем на каждом потоке
  msort_mpi(sub_mas, chunk_size);
  //printf("\nrank: %d\n", w_rank);
  //print_mas(sub_mas, chunk_size);
  
  //Собираем отсортированные части
  double *sort_mas = NULL;
  if(w_rank == 0) {
	sort_mas = malloc(N * sizeof(double));
	printf("\nGathering...\n");
  }
  
  MPI_Gather(sub_mas, chunk_size, MPI_DOUBLE, sort_mas, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  
  if(w_rank == 0) {
    //printf("\nGathered Data: \n");
    //print_mas(sort_mas, N);
    printf("\nFinal Sorting...\n");
	msort_mpi(sort_mas, N);
	//printf("\n===SORT MASSIV===:\n");
    //print_mas(sort_mas, N);
    free(sort_mas);
  }	
  free(sub_mas);
  free(mas);
  if(w_rank == 0){
	t2= MPI_Wtime() -t1;
	printf("\nMPI_TIME:\t%f seconds\n\n", t2);
  }
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  return 0;
}


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
	printf("\n\n");
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
		return 0;
	}
	else{
		int flag = true;
		
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
