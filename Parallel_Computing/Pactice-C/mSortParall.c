#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#define N 10000000
#define RMAX 29998
int mas_serial[N];
int mas_parallel[N];
//int cthr;
int maxlvl;

void swap(int *a, int *b)
{
  int t=*a;
  *a=*b; 
  *b=t;
}

/*
void quicksort_serial(int* mas, int start, int end){
    if (end > start + 1) {
    int piv = mas[start];
    int left = start + 1;
    int right = end;
    while (left < right) {
      if (mas[left] <= piv) {
        left++;
      }
      else {
        swap(&mas[left], &mas[--right]);
      }
    }
    swap(&mas[--left], &mas[start]);
    quicksort_serial(mas, start, left);
    quicksort_serial(mas, right, end);
    
  }
}
*/
void put_parall(int from[], int to[]) {
	int i;
	for(i=0; i<N; i++) {
	to[i] = from[i];
	}
}

void generate_mas(int* mas) {
	int i;
	for(i=0; i<N; i++) {
	mas[i] = rand() % RMAX + 1;
	}
}

void print_mas(int* a) {
	int i;
	for(i=0; i<N; i++) {
	printf("%d, ",a[i]);
	}
}

//Connect buf to a
void merge(int *arr, size_t size, size_t a_size, size_t b_size)
{
  int i, j, k;
  int *a = arr, *b = arr + a_size;
  int *c;

  if (a[a_size-1] <= b[0]) return;

  c = (int *)malloc(b_size * sizeof(int));
  memcpy(c, b, b_size * sizeof(int));

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

double run_serial(){
  double t=omp_get_wtime();
  //printf("\n===SERIAL===:\n");
  msort_serial(mas_serial, N);
  //print_mas(mas_serial);
  //printf("\n");
  return omp_get_wtime() - t;
}

double run_parallel(){
  omp_set_nested(1);
  omp_set_max_active_levels(maxlvl);
  double t=omp_get_wtime();
  //printf("\n===PARALLEL===:\n");
  msort_omp(mas_parallel, N);
  //print_mas(mas_parallel);
  //printf("\n");
  return omp_get_wtime() - t;
}


int main(void){
  //printf("Количество потоков: ");
  //scanf("%d", &cthr);
  printf("Максимальное количество уровней рекурсии: ");
  scanf("%d", &maxlvl);
  srand(time(NULL));
  generate_mas(mas_serial);
  //Копируем исходный массив отдельно для параллельного алгоритма
  put_parall(mas_serial, mas_parallel);
  //printf("\n===SOURCE MASSIV===:\n");
  //print_mas(mas_serial);
  printf("\n");
  double t1, t2;
  t1 = run_serial();
  t2 = run_parallel();
  printf("\n");
  printf("SERIAL_TIME\tPARALLEL_TIME\tt1/t2\n");
  printf("%lf\t%lf\t%lf\n", t1, t2, t1/t2);
  return 0;
}
