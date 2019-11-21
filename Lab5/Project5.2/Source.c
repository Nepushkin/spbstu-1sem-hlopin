#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <time.h>

HANDLE hStdout;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo; //переменная для считывания характеристик консоли

int random(int a, int b)
{
	return (rand() % (b - a + 1) + a);
}

int isDigit(char c)
{
	return ((c >= '0') && (c <= '9'));
}

int charToDigit(char c)
{
	if (isDigit(c))
	{
		return c - '0';
	}
	return -1;
}

//0 - Ошибка; 1 - Ввелось корректно
int inputInt(int *var)
{
	char c = 0;
	int value = -1;
	while ((c = getchar()) != '\n')
	{
		if (!isDigit(c))
		{
			return 0;
		}
		if (value == -1)
		{
			value = 0;
		}
		value = value * 10 + charToDigit(c);
	}
	if (value < 1)
	{
		return 0;
	}
	*var = value;
	return 1;
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	WORD bgcolor, color, srccolor;
	GetConsoleScreenBufferInfo(hStdout, &csbiInfo); //считываем характеристики консоли
	srccolor = csbiInfo.wAttributes; // выковыряли цвет
	bgcolor = (srccolor & 0xF0); // выковыряли цвет фона

	//csbiInfo.wAttributes  = 1011 0101
	//0xF0					= 1111 0000
	//						= 1011 0000
	//FOREGROUND_INTENSITY	= 0000 1000
	//FOREGROUND_RED		= 0000 0100
	//FOREGROUND_BLUE		= 0000 0001
	//                      = 1011 1101

	color = bgcolor | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;//добавляем к цвету фона наш цвет
	SetConsoleTextAttribute(hStdout, color); //устанавливаем наш цвет в консоль

	printf("Введите размерность матрицы : ");
	int n;
	if (!inputInt(&n))
	{
		printf("Некорректный ввод числа\n");
		return 0;
	}

	int* arr = (int*)calloc(n * n, sizeof(int));
	for (int i = 0; i < n * n; ++i)
	{
		arr[i] = rand() % 90 + 10;
	}

	for (int i = 0; i < n * n; ++i)
	{
		color = bgcolor | (rand() % 15 + 1);
		SetConsoleTextAttribute(hStdout, color);
		printf("%d ", arr[i]);
	}
	printf("\n\n");

	color = bgcolor | FOREGROUND_GREEN;
	SetConsoleTextAttribute(hStdout, color);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			printf("%d ", arr[j * n + i]);
		}
		printf("\n");
	}
	printf("\n");

	color = bgcolor | FOREGROUND_RED | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(hStdout, color);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i == j)
			{
				color = bgcolor | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
				SetConsoleTextAttribute(hStdout, color);
				printf("%d ", arr[j * n + i]);
			}
			else if (i < j)
			{
				color = bgcolor | FOREGROUND_RED | FOREGROUND_GREEN;
				SetConsoleTextAttribute(hStdout, color);
				printf("%d ", arr[j * n + i]);
			}
			else
			{
				printf("   ");
			}
		}
		printf("\n");
	}

	free(arr);
	SetConsoleTextAttribute(hStdout, srccolor);
	return 0;
}