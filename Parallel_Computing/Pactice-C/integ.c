// 0 2 16.667

#include<stdio.h>
#define A 1
#define B 4
#define C 3

double x1, x2;
double integSum = 0;
double step = 1.0e-6;
double func(double x);
double integral(double x1, double x2);

int main() {
	printf("\nВведите левую границу X1: ");
	scanf("%lf", &x1);
	printf("Введите правую границу X2: ");
	scanf("%lf", &x2);
	printf("Используется шаг: %lf\n", step);
	

	integSum = integral(x1,x2);
	printf("Интеграл равен: %lf\n\n", integSum);
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
