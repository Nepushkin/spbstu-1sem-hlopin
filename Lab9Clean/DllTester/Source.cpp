#include<Windows.h>
#include<iostream>
#include<locale.h>
#include<exception>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	cin.exceptions(cin.failbit | cin.badbit);

	HINSTANCE dll_link = LoadLibrary("Nepushkin.dll");

	typedef char*(*FuncName)();
	FuncName name = (FuncName)GetProcAddress(dll_link, "FName");

	typedef double(*TrigFunction)(double d1, double d2, double epsilon);
	TrigFunction nepushkin_tg = (TrigFunction)GetProcAddress(dll_link, name());

	typedef double(*TrigMathFunction)(double d1, double d2);
	TrigMathFunction nepushkin_math_tg = (TrigMathFunction)GetProcAddress(dll_link, "myf_math");

	double xstart;
	double xend;
	double xstep;
	double xideal;
	double eps;

	try {
		cout << "¬ведите x_start = ";
		cin >> xstart;
		cout << "¬ведите x_end = ";
		cin >> xend;
		cout << "¬ведите x_step = ";
		cin >> xstep;
		cout << "¬ведите epsilon = ";
		cin >> eps;
	}
	catch (exception e)
	{
		cout << "ќшибка ввода данных";
		return 0;
	}

	printf("\n");
	printf("     x    |         myFunction(x)        |         Function(x)          |   delta \n");
	double x;
	for (x = xstart; x < xend - xstep / 10; x = x + xstep)
	{
		double func = nepushkin_math_tg(x, 0);
		double myfunc = nepushkin_tg(x, 0, eps);
		double delta = (func - myfunc)*(func + myfunc);
		if (delta < 0) delta *= -1;
		delta = sqrt(delta);
		printf("%9.2lf | %28.10lf | %28.10lf | %10.20lf\n", x, myfunc, func, delta);
	}
	double func = nepushkin_math_tg(xend, 0);
	double myfunc = nepushkin_tg(xend, 0, eps);
	double delta = (func - myfunc)*(func + myfunc);
	if (delta < 0) delta *= -1;
	delta = sqrt(delta);
	printf("%9.2lf | %28.10lf | %28.10lf | %10.20lf\n", xend, myfunc, func, delta);

	try {
		cout << "¬ведите x_ideal = ";
		cin >> xideal;
	}
	catch (exception e)
	{
		cout << "ќшибка ввода данных";
		return 0;
	}
	eps = 1;

	printf("\n");
	printf("  epsilon |         myFunction(x)        |         Function(x)          |   delta \n");
	for (int i = 0; i < 7; i++)
	{
		eps /= 10;
		double func = nepushkin_math_tg(xideal, 0);
		double myfunc = nepushkin_tg(xideal, 0, eps);
		double delta = (func - myfunc)*(func + myfunc);
		if (delta < 0) delta *= -1;
		delta = sqrt(delta);
		printf("%9.7lf | %28.10lf | %28.10lf | %10.20lf\n", eps, myfunc, func, delta);
	}

	return 0;
}