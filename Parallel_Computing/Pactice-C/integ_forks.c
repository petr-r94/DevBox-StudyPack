#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<semaphore.h>

#define A 1
#define B 4
#define C 3

double integral(double x1, double x2);
double mx1, mx2;
double step = 1.0e-6;
double func(double x);
double* integSum;
double insum = 0.0;
int num_forks;
sem_t locker;

int main() {
	printf("\nВведите левую границу X1: ");
	scanf("%lf", &mx1);
	printf("Введите правую границу X2: ");
	scanf("%lf", &mx2);
	printf("Используется шаг: %lf\n", step);
	printf("\nВведите количество процессов: ");
	scanf("%d", &num_forks);

	srand(time(NULL));
	//Разделяемая память
	int shmid, mem_status;
	key_t key;
	key = ftok("integ_forks.c", (rand() % 100) + (rand() % 100));

	//Выделение разделяемого сегмента памяти под интегральную сумму
	shmid = shmget(key, sizeof(double), 0666 | IPC_CREAT);
	if (shmid < 0) {
		perror("Failed to Create Shared Memory\n");
		exit(1);
	}

	//Присоединение частичной суммы к сегменту разделяемой памяти
	integSum = (double*) shmat(shmid, NULL, 0);
	if (integSum < 0) {
		perror("Attach Error\n");
	}
	//Инициализация межпроцессорного семафора c начальным значением 1
	int semIni = sem_init(&locker, 1, 1);
	if(semIni < 0) {
		perror("Sem_Init Error\n");
	}

	double OnPerThread = ((mx2-mx1) ) / num_forks;
	//printf("На каждый поток приходится отрезок длины: %lf\n", OnPerThread);
	int idFork;
	pid_t pid;

	//Создаем потоки и передаем каждому структуры на аргументы
	for(idFork=0; idFork < num_forks; idFork++) {
		//Распределяем нагрузку
		pid = fork();
		if (pid == -1) {
			printf("Ошибка создания дочернего процесса");
			exit(1);
		}
		
		if (pid == 0) {
			//int pnum = getpid() - getppid();
			//printf("\nСоздался %d Дочерний процесс: ID = %d  parent ID: %d\n", idFork+1, getpid(), getppid());
			mx1 += (idFork * OnPerThread); 
			mx2 = mx1 + OnPerThread;
			insum = integral(mx1, mx2);
			//printf("\n[Процесс %d] Частичная сумма на подотрезке [%lf, %lf] равна: %lf\n", idFork+1, mx1, mx2, insum);

			//Обрабатываем критическую область
			sem_wait(&locker); // уменьшаем счетчик
			*(integSum) += insum;
			sem_post(&locker); // увеличиваем счетчик
			exit(0);
		}
}

	//Ждем завершения всех процессов
	int n;
	for(n=0; n < num_forks; n++) {
	waitpid(-1, NULL, 0);
}
	//Выводим результат
	printf("Интеграл равен: %lf\n\n", *(integSum));
	
	//Отсоединение интегральной суммы от сегмента
	if (shmdt(integSum) == -1) {
		perror("Detach Error");
		exit(1);
	}

	//Очистка разделяемой памяти
	mem_status = shmctl(shmid, IPC_RMID, NULL);
	if (mem_status < 0) {
		perror("Deletion of Shared Memory was unsucessful\n");
	}
	//Очищаем семафор
	sem_destroy(&locker);
	return 0;

}

double func(double x) {
	double result = A * (x * x) + (B * x ) + C;
	return result;

}

double integral(double x1, double x2) {
	long pointsNum = (x2 - x1) / step;
	double a = x1;
	double b = x1 + step;
	double integ = 0;
	int i;
	for (i = 0; i < pointsNum; i++) {
		// Более точно - средних прямоугольников integ += func((a + b) / 2) * (b - a);
		//Метод левых прямоугольников
		integ += func(a) * (b - a);
		a += step;
		b += step;
	}
	return integ;
}
