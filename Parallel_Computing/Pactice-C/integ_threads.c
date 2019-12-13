#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#define A 1
#define B 4
#define C 3

double mx1, mx2;
double integSum = 0;
double step = 1.0e-6;
double func(double x);
int num_threads;
pthread_mutex_t locker = PTHREAD_MUTEX_INITIALIZER;

//Параметры для функции потоков
struct ArgsThreadFunc
{
    double x1, x2;
    double step;
    int tid;
};

static void *integral(void *_args) {
	struct ArgsThreadFunc *args = (struct ArgsThreadFunc*)_args;
	long pointsNum = ((args->x2) - (args->x1)) / (args->step);
	//Локальные левые и правые границы частичных отрезков
	double a = args->x1;
	double b = (args->x1) + (args->step);
	double integ = 0;
	int i;
	for (i = 0; i < pointsNum; i++) {
		// Более точно - средних прямоугольников integ += func((a + b) / 2) * (b - a);
		//Метод левых прямоугольников
		integ += func(a) * (b - a);
		a += step;
		b += step;
	}
	//Обрабатываем критическую область
	pthread_mutex_lock(&locker);
	//printf("[Поток %d] Частичная сумма равна: %lf\n", args->tid ,integSum);
	integSum += integ;
	pthread_mutex_unlock(&locker);
	return NULL;  
}

int main() {
	printf("\nВведите левую границу X1: ");
	scanf("%lf", &mx1);
	printf("Введите правую границу X2: ");
	scanf("%lf", &mx2);
	printf("Используется шаг: %lf\n", step);
	printf("\nВведите количество потоков: ");
	scanf("%d", &num_threads);

	pthread_t threads[num_threads];
	struct ArgsThreadFunc threads_args[num_threads];
	double OnPerThread = ((mx2-mx1) ) / num_threads;
	//printf("На каждый поток приходится отрезок длины: %lf\n", OnPerThread);
	int idThr;	

	//Создаем потоки и передаем каждому структуры на аргументы
	for(idThr=0; idThr<num_threads; idThr++) {
		//Распределяем нагрузку
		threads_args[idThr].x1 = mx1;
		threads_args[idThr].x2 = mx1 + OnPerThread;
		threads_args[idThr].step = step;
		threads_args[idThr].tid = idThr;
		if (pthread_create(&threads[idThr], NULL, integral, &threads_args[idThr]) < 0)
			{
			exit(-1);
		 }
		mx1+= OnPerThread;
}

	//Ждем завершения всех нитей
	for (idThr=0; idThr<num_threads; idThr++) {
		if (pthread_join(threads[idThr], NULL) != 0)
		{
		exit(-1);
		}
}
	pthread_mutex_destroy(&locker);
	//Выводим результат
	printf("Интеграл равен: %lf\n\n", integSum);
	return 0;

}

double func(double x) {
	double result = A * (x * x) + (B * x ) + C;
	return result;

}
