#include<Windows.h>
#include<iostream>
#include<locale.h>
#include<exception>

using namespace std;

void closeToZero(double& variable)
{
	if (variable >= -0.00000001 && variable <= 0.00000001)
	{
		variable = 0;
	}
}

double Delta(double& func, double& myfunc)
{
	double result = (func - myfunc)*(func + myfunc);
	if (result < 0) result *= -1;
	result = sqrt(result);
	closeToZero(func);
	closeToZero(myfunc);
	closeToZero(result);
	return result;
}

void printHead(const char* start, char* name)
{
	printf("%10.7s | MY %16s |    %16s |   delta \n", start, name, name);
}

void printValues(double x, double myfunc, double func, double delta)
{
	printf("%10.7lf |", x);
	if (_isnan(myfunc))
	{
		printf("     NOT  DEFINED    |");
	}
	else
	{
		printf("%20.7lf |", myfunc);
	}
	if (_isnan(func))
	{
		printf("     NOT  DEFINED    |");
	}
	else
	{
		printf("%20.7lf |", func);
	}
	if (_isnan(delta))
	{
		printf(" NOT  DEFINED\n");
	}
	else
	{
		printf(" %11.10lf\n", delta);
	}
}

void swap(double &a, double &b)
{
	double temp = a;
	a = b;
	b = temp;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cin.exceptions(cin.failbit | cin.badbit);

	HINSTANCE dll_link = LoadLibrary("Nepushkin.dll");
	//HINSTANCE dll_link = LoadLibrary("Dll1.dll");

	typedef char*(*FuncName)();
	FuncName name = (FuncName)GetProcAddress(dll_link, "FName");

	typedef double(*TrigFunction)(double a, double x, double epsilon);
	TrigFunction nepushkin_tg = (TrigFunction)GetProcAddress(dll_link, "myf_1b");

	typedef double(*TrigMathFunction)(double x, double a);
	TrigMathFunction nepushkin_math_tg = (TrigMathFunction)GetProcAddress(dll_link, "myf_math");

	double xstart;
	double xend;
	double xstep;
	double xideal;
	double eps;
	double A;
	try {
		cout << "Введите A > 0 (второй параметр, если требуется) = ";
		cin >> A;
		if (A <= 0) throw exception();
		cout << "Введите x_start = ";
		cin >> xstart;
		cout << "Введите x_end = ";
		cin >> xend;
		cout << "Введите x_step = ";
		cin >> xstep;
		if (xstep <= 0) throw exception();
		cout << "Введите epsilon = ";
		cin >> eps;
		if (eps <= 0) throw exception();
	}
	catch (exception e)
	{
		cout << "Ошибка ввода данных";
		return 0;
	}
	while (xend < xstart)
	{
		cout << "xstart оказался больше, чем xend, поменять их местами? Y/N" << endl;
		char choice;
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			swap(xend, xstart);
		}
		if (choice == 'n' || choice == 'N')
		{
			cout << "Тогда у нас с вами ничего не получится =(" << endl;
			break;
		}
	}

	if (xend >= xstart) {
		printHead(" x ", name());
		double x;
		for (x = xstart; x < xend - xstep / 10; x = x + xstep)
		{
			double func = nepushkin_math_tg(x, A);
			double myfunc = nepushkin_tg(A, x, eps);
			double delta = Delta(func, myfunc);
			printValues(x, myfunc, func, delta);
		}
		double func = nepushkin_math_tg(xend, A);
		double myfunc = nepushkin_tg(A, xend, eps);
		double delta = Delta(func, myfunc);
		printValues(xend, myfunc, func, delta);
	}

	try {
		cout << "Введите x_ideal = ";
		cin >> xideal;
	}
	catch (exception e)
	{
		cout << "Ошибка ввода данных";
		return 0;
	}
	eps = 1;

	printf("\n");
	printHead("eps", name());
	for (int i = 0; i < 7; i++)
	{
		eps /= 10;
		double func = nepushkin_math_tg(xideal, A);
		double myfunc = nepushkin_tg(A, xideal, eps);
		double delta = Delta(func, myfunc);
		printValues(eps, myfunc, func, delta);
	}
	return 0;
}