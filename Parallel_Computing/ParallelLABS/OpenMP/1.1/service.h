#include <time.h>
#include <stddef.h>

int N;
int RMAX;
int N_DEF = 50000000;
int RMAX_DEF =99999;
 
void swap(int *a, int *b)
{
  int t=*a;
  *a=*b; 
  *b=t;
}

int* generate_mas(int N, int RMAX) {
	srand(time(NULL));
	int* data = malloc(sizeof(int)*N);
	int i;
	for(i=0; i<N; i++) {
	data[i] = rand() % RMAX + 1;
	}
	return data;
}

void print_mas(int* a, int N) {
	int i;
	for(i=0; i<N; i++) {
	printf("%d, ",a[i]);
	}
}
