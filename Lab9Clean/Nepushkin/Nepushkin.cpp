// NepushkinLib.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "Nepushkin.h"
#define PI 3.14159265358979323846

double bernulli[50];
int bernulliCount = 0;
void calcBernulli(int n)
{
	double res = 0;
	for (int i = 1; i <= n - 1; i++)
	{
		int pow = ((i - 1) % 2 == 1 ? -1 : 1);
		int numerator = 1;
		for (int j = 2 * n - 2 * i + 2; j <= 2 * n; j++)
		{
			numerator *= j;
		}
		int denominator = 1;
		for (int j = 1; j <= 2 * i; j++)
		{
			denominator *= j;
		}
		res += pow * bernulli[i] * numerator / denominator;
	}

	int pow = (n % 2 == 1 ? -1 : 1);
	bernulli[n] = pow * ((double)1 / (2 * n + 1) - (double)1 / 2 + res);
}

double Bernulli(int n)
{
	for (int i = bernulliCount; i <= n; i++)
	{
		calcBernulli(i);
	}
	return bernulli[n];
}

double nepushkin_func(double x, double epsilon)
{
	double result = 0;
	int pow = 4;
	int n = 1;
	double delta = 0;
	double multfact = x / 2;

	do
	{
		delta = abs(Bernulli(n)) * pow * (pow - 1) * multfact;
		result += delta;
		pow = pow << 2;
		n++;
		multfact *= x * x / (2 * n * (2 * n - 1));
	} while (abs(delta) >= epsilon);
	return result;
}

double myf_math(double x, double y)
{
	return tan(x);
}

double myf_90001(double x, double y, double epsilon)
{
	while (x > PI / 2) x -= PI;
	while (x < -PI / 2) x += PI;
	if (abs(x) > PI / 4)
	{
		return 1 / myf_90001(PI / 2 - x, y, epsilon);
	}
	if (abs(x) <= epsilon / 10) return x;
	if (x < 0) return -nepushkin_func(-x, epsilon);
	return nepushkin_func(x, epsilon);
}

char* FName()
{
	return (char*) "myf_90001";
}