#include <time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

int N;
double RMAX;
int maxlvl= 1;
 
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

void print_help() {
	printf("\n----------Справка по аргументам----------\nВведите параметры сортировки в следующем порядке:\n");
	printf("\t1) Количество чисел\n\t2) Верхняя граница случайного числа(Double) при генерации данных\n\t3) Количество вложенных уровней параллелизма [только для OMP версии]\n");
	printf("\nПример: ./sortSerial 100 99\n\t./sortOmp 10000000 9999 2\n\n");
}

bool validateArgs(int argc, char** argv) {
	if((argc != 3)&&(argc!=4)) {
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
		if(argc == 4) {
			maxlvl=atoi(argv[3]);
			if(maxlvl<=0) { printf("\n\tОшибка! Количество вложенных уровней параллелизма должно быть > 0\n"); flag=false;}
		}
		printf("\n");
		return flag;
	}
}
