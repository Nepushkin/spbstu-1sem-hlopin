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

WORD randomColor(WORD srccolor)
{
	WORD bgcolor = srccolor & 0xF0;			//		wxyz abcd & 1111 0000	-> wxyz 0000
	WORD excludeColor = srccolor >> 4;		//		wxyz abcd >> 4			-> 0000 wxyz
	WORD res = rand() % 15 + 1;				//		0000 efgh
	res ^= excludeColor;					//		0000 efgh ^ 0000 wxyz
	return bgcolor | res;
}

WORD inverseColor(WORD srccolor)
{
	WORD bgcolor = srccolor & 0xF0;
	WORD res = ((~bgcolor & 0xFF) >> 4); //добавляем к цвету фона инвертированный цвет фона
	return bgcolor | res;
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

	WORD bgcolor, color, srccolor, textcolor, bgintentity;
	GetConsoleScreenBufferInfo(hStdout, &csbiInfo); //считываем характеристики консоли
	srccolor = csbiInfo.wAttributes; // выковыряли цвет
	//bgcolor = (srccolor & 0xF0); // выковыряли цвет фона
	//textcolor = (srccolor & 0x0F); //выковыряли цвет текста
	//bgintentity = (srccolor & 0x80); //интенсивность фона

	//csbiInfo.wAttributes  = 1011 0101
	//0xF0					= 1111 0000
	//						= 1011 0000
	//FOREGROUND_INTENSITY	= 0000 1000
	//FOREGROUND_RED		= 0000 0100
	//FOREGROUND_BLUE		= 0000 0001
	//                      = 1011 1101
	//a						= wxyz abcd
	//a >> 1				= 0wxy zabc
	//a >> 2				= 00wx yzab
	//a >> 3				= 000w xyza
	//a >> 4				= 0000 wxyz

	color = inverseColor(srccolor);
	SetConsoleTextAttribute(hStdout, color); //устанавливаем наш цвет в консоль

	printf("Введите размерность матрицы : ");
	int n;
	if (!inputInt(&n))
	{
		printf("Некорректный ввод числа\n");
		SetConsoleTextAttribute(hStdout, srccolor);
		return 0;
	}

	int* arr = (int*)calloc(n * n, sizeof(int));
	for (int i = 0; i < n * n; ++i)
	{
		arr[i] = rand() % 90 + 10;
	}

	for (int i = 0; i < n * n; ++i)
	{
		color = randomColor(srccolor);
		SetConsoleTextAttribute(hStdout, color);
		printf("%d ", arr[i]);
	}
	printf("\n\n");

	color = randomColor(srccolor);
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

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i == j)
			{
				color = inverseColor(srccolor) | 0x08;
				SetConsoleTextAttribute(hStdout, color);
				printf("%d ", arr[j * n + i]);
			}
			else if (i < j)
			{
				color = inverseColor(srccolor) & 0xF7;
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