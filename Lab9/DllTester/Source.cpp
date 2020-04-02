#include<Windows.h>
#include<iostream>

using namespace std;

int main()
{
	HINSTANCE dll_link = LoadLibrary("Nepushkin.dll");

	typedef char*(*FuncName)();
	FuncName name = (FuncName)GetProcAddress(dll_link, "FName");

	typedef double(*TrigFunction)(double d1, double d2, double epsilon);
	TrigFunction nepushkin_tg = (TrigFunction)GetProcAddress(dll_link, name());

	typedef double(*TrigMathFunction)(double d1, double d2);
	TrigMathFunction nepushkin_math_tg = (TrigMathFunction)GetProcAddress(dll_link, "myf_math");

	double x;
	cin >> x;
	cout << name() << endl;
	cout << nepushkin_tg(x, 0, 0.001) << endl;
	cout << nepushkin_math_tg(x, 0) << endl;
	return 0;
}