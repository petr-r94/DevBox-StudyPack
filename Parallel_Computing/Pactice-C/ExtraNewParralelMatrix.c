#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int a_rows, a_columns, b_rows, b_columns, num_proc;

int main() {

	printf("===Параллельное Умножение матриц:=== \n\n");
	//Ввод исходных данных
	printf("Введите количество строк матрицы А: ");
	scanf("%d", &a_rows);
	printf("Введите количество столбцов матрицы А: ");
	scanf("%d", &a_columns);
	printf("Введите количество столбцов матрицы В: ");
	scanf("%d", &b_columns);
	b_rows = a_columns;
	printf("Введите количество процессов: ");
	scanf("%d", &num_proc);

	int matrixA[a_rows][a_columns];
	int matrixB[b_rows][b_columns];
	int* share_mul;
	/*
	 void multi(int first[a_rows][a_columns], int second[b_rows][b_columns], int res[a_rows][b_columns], int f_rows, int f_col, int s_col) {
	 int s_row = f_col;
	 for (int i=0; i < f_rows; i++){
	 for (int j=0; j < s_col; j++){ 
	 for (int k=0; k < f_col; k++){
	 res[i][j] += first[i][k] * second[k][j];
	 //*(res + i * s_col + j) = *(res + i * s_col + j) + ((int)(*(first + i * f_col + k)) * (int)(*(second + k * s_col + j)));
	 }
	 }
	 }
	 return;
	 }
	 */

	// Генерация статичных матриц
	srand (time(NULL));for
(	int i = 0; i < a_rows; i++) {
		for (int j = 0; j < a_columns; j++) {
			matrixA[i][j] = rand() % 10;
		}
	}

	for (int i = 0; i < b_rows; i++) {
		for (int j = 0; j < b_columns; j++) {
			matrixB[i][j] = rand() % 10;
		}
	}

	/*//Вывод сгенерированных матриц
	printf("\nМатрица A: \n");
	for (int i = 0; i < a_rows; i++) {
		for (int j = 0; j < a_columns; j++) {
			//printf("%d ", matrixA[i][j]);
			if (j >= a_columns - 1) {
				printf("\n");
			};
		}
	}

	printf("\nМатрица B: \n");
	for (int i = 0; i < b_rows; i++) {
		for (int j = 0; j < b_columns; j++) {
			//printf("%d ", matrixB[i][j]);
			if (j >= b_columns - 1) {
				printf("\n");
			};
		}
	}
*/
	//Разделяемая память
	int shmid, mem_status;
	key_t key;
	key = ftok("ParralelMatrix.c", (rand() % 100) + (rand() % 100));

	//Выделение разделяемого сегмента памяти под результат произведения
	size_t share_size = (sizeof(int) * (a_rows * b_columns));
	shmid = shmget(key, share_size, 0666 | IPC_CREAT);
	if (shmid < 0) {
		perror("Failed to Create Shared Memory\n");
		exit(1);
	}

	//Присоединение массива результата к сегменту разделяемой памяти
	share_mul = (int*) shmat(shmid, NULL, 0);
	if (share_mul < 0) {
		perror("Attach Error\n");
	}

	//Зануление результата
	for (int i = 0; i < a_rows; i++) {
		for (int j = 0; j < b_columns; j++) {
			//share_mul[i][j] = 0;
			*(share_mul + i * b_columns + j) = 0;
		}
	}
	//Создаем дочерние процессы
	pid_t pid;
	int leftBound = 0;
	int rightBound = (a_rows * b_columns) / num_proc;

	for (int n = 1; n <= num_proc; n++) {
		pid = fork();
		if (pid == -1) {
			printf("Ошибка создания дочернего процесса");
			exit(1);
		}

		if (pid == 0) {
			printf("\nСоздался %d Дочерний процесс: ID = %d  parent ID: %d\n",
					getpid() - getppid(), getpid(), getppid());
			int pnum = getpid() - getppid();
			if(n == num_proc) {
				rightBound = a_rows * b_columns;
			}
			//Умножаем матрицы
			for (int i = leftBound; i < rightBound; i++) {

				int row = i / b_columns;
				int col = i % b_columns;
/*
				printf("LeftBound %d \n", leftBound);
				printf("RightBound %d \n", rightBound);
				printf("I =  %d \n", i);
				printf("A_COLUMNS =  %d \n", a_columns);
				printf("A_ROWS =  %d \n", a_rows);

				printf("row =  %d \n", row);
				printf("col =  %d \n", col);
*/
				for (int k = 0; k < a_columns; k++) {
					//printf("MatrixA[row][k] %d	", matrixA[row][k]);
					//printf("MatrixB[k][col]] %d\n", matrixB[k][col]);
					//printf("MUL_EL: %3d\n", matrixA[row][k] * matrixB[k][col]);
					*(share_mul + row * b_columns + col) += matrixA[row][k]
							* matrixB[k][col];
					//printf("K =  %d \n", k);    
				}
			}

			exit(0);
		}
		leftBound += (a_rows * b_columns) / num_proc;
		rightBound += (a_rows * b_columns) / num_proc;

		

		

	}
	
	for (int n = 1; n <= num_proc; n++) {
	//printf("\nГлавный процесс: ID = %d\n", getpid());
			//printf("Ждем завершения всех процессов...\n");
			waitpid(-1, NULL, 0);
			//multi(matrixA, matrixB, share_mul, a_rows, a_columns, b_columns);
	}	
/*	
	//Вывод сгенерированных матриц
		printf("\nМатрица A: \n");
		for (int i = 0; i < a_rows; i++) {
			for (int j = 0; j < a_columns; j++) {
				printf("%d ", matrixA[i][j]);
				if (j >= a_columns - 1) {
					printf("\n");
				};
			}
		}

		printf("\nМатрица B: \n");
		for (int i = 0; i < b_rows; i++) {
			for (int j = 0; j < b_columns; j++) {
				printf("%d ", matrixB[i][j]);
				if (j >= b_columns - 1) {
					printf("\n");
				};
			}
		}
	
	//Выводим содержимое разделяемого сегмента памяти
			printf("\nПроизведение матрицы равно: \n");
			for (int i = 0; i < a_rows; i++) {
				for (int j = 0; j < b_columns; j++) {
					printf("%3d ", *(share_mul + i * b_columns + j));
					//printf("%3d", share_mul[i][j]);
					if (j >= b_columns - 1) {
						printf("\n");
					};
				}
			}
	*/
	//Отсоединение массива от сегмента
	if (shmdt(share_mul) == -1) {
		perror("Detach Error");
		exit(1);
	}

	//Очистка разделяемой памяти
	mem_status = shmctl(shmid, IPC_RMID, NULL);
	if (mem_status < 0) {
		perror("Deletion of Shared Memory was unsucessful\n");
	}

	return 0;
}
