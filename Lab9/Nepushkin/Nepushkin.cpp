// NepushkinLib.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "Nepushkin.h"

double bernulli[30];
double bernulliCount = 0;
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
	double prev = -1;
	double next = 0;
	int pow = 1;
	int fact = 1;
	double mult = 1 / x;
	int n = 0;
	while (true)
	{
		next += abs(Bernulli(n)) * pow * (pow - 1) * mult / fact;
		mult *= x * x;
		pow = pow << 2; // pow = pow * 2^2;
		n++;
		fact *= 2 * n *(2 * n - 1);
		//n = 3 -> fact = 1 * 2 * 3 * 4 * 5 * 6
		//n = 4 -> fact = 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8
		//cout << next << " " << prev << endl;
		if (abs(prev - next) < epsilon) break; //0.0001 = epsilon
		prev = next;
	}
	return next;
}

double myf_math(double x, double y)
{
	return tan(x);
}

double myf_90001(double x, double y, double epsilon)
{
	return nepushkin_func(x, epsilon);
}

char* FName()
{
	return (char*) "myf_90001";
}