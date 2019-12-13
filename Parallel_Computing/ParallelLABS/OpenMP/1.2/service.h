#include <time.h>
#include <stddef.h>

int N;
double RMAX;
 
void swap(double *a, double *b)
{
  int t=*a;
  *a=*b; 
  *b=t;
}

double doubleRand(double max) {
	return ((double)rand())/((double)RAND_MAX / max);
}

double* generate_mas(int N, int RMAX) {
	srand((unsigned)time(NULL));
	double* data = malloc(sizeof(double)*N);
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
