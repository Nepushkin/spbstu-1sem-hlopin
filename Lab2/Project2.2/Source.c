#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

int isDigit(char c)
{
	return ((c - '0' <= 9 && c - '0' >= 0) ? 1 : 0);
}

int isDash(char c)
{
	return (c == '-' ? 1 : 0);
}

int toDigit(char c)
{
	return (c - '0');
}

int isLeapYear(int year)
{
	if (year < 0)
	{
		year = (year + 1) * (-1);
	}
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 1 : 0;
}

int inputYear(int* year)
{
	int result = 0;
	int sign = 1;
	char c;
	int index;
	int digit; // текущая цифра
	for (index = 0, c = getchar(); c != '\n'; index++, c = getchar())
	{
		if (!isDigit(c))
		{
			if (index != 0)
			{
				return 0;
			}
			if (!isDash(c))
			{
				return 0;
			}
		}
		if (isDash(c))
		{
			sign = -1;
			continue;
		}
		digit = toDigit(c);
		if (digit == 0 && index == 0)
		{
			return 0;
		}
		if (digit == 0 && index == 1 && sign == -1)
		{
			return 0;
		}
		result = result * 10 + digit;
	}
	if (result == 0)
	{
		return 0;
	}
	*year = sign * result;
	return 1;
}

int inputMonth(int* month)
{
	int result = 0;
	char c;
	int index;
	int digit = 0;
	for (index = 0, c = getchar(); c != '\n'; index++, c = getchar())
	{
		if (!isDigit(c))
		{
			return 0;
		}
		if (index == 2)
		{
			return 0;
		}
		digit = toDigit(c);
		if (digit == 0 && index == 0)
		{
			return 0;
		}
		result = result * 10 + digit;
	}
	if (result <= 0 || result >= 13)
	{
		return 0;
	}
	*month = result;
	return 1;
}

int inputDay(int* day, int month, int year)
{
	int result = 0;
	char c;
	int index;
	int digit = 0;
	for (index = 0, c = getchar(); c != '\n'; index++, c = getchar())
	{
		if (!isDigit(c))
		{
			return 0;
		}
		if (index == 2)
		{
			return 0;
		}
		digit = toDigit(c);
		if (digit == 0 && index == 0)
		{
			return 0;
		}
		result = result * 10 + digit;
	}
	if (result == 0) {
		return 0;
	}
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (result > 31)
		{
			return 0;
		}
		break;
	case 4: case 6: case 9: case 11:
		if (result > 30)
		{
			return 0;
		}
		break;
	case 2:
		if (isLeapYear(year) && result > 29) {
			return 0;
		}
		if (!isLeapYear(year) && result > 28) {
			return 0;
		}
	}
	*day = result;
	return 1;
}

int countDays(int day, int month, int year)
{
	int result = 0;
	if (year > 0)
	{
		result = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
	}
	if (year < 0)
	{
		result = 365 * year + (year - 3) / 4 - (year + 1) / 100 + (year + 1) / 400;
	}
	switch (month) {
	case 12: result += 30;
	case 11: result += 31;
	case 10: result += 30;
	case 9: result += 31;
	case 8: result += 31;
	case 7: result += 30;
	case 6: result += 31;
	case 5: result += 30;
	case 4: result += 31;
	case 3: result += 28; if (isLeapYear(year)) { result++; }
	case 2: result += 31;
	}
	result += day;
	return result;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int A, B, C, D, G, M, N, K, W, m;
	printf("Введите первую дату: \n");
	printf("\t год : ");
	if (!inputYear(&A))
	{
		printf("Неверный формат ввода, запустите программу заново.\n");
		return 0;
	}
	printf("\t месяц: ");
	if (!inputMonth(&B))
	{
		printf("Неверный формат ввода, запустите программу заново.\n");
		return 0;
	}
	printf("\t день: ");
	if (!inputDay(&C, B, A))
	{
		printf("Неверный формат ввода, запустите программу заново.\n");
		return 0;
	}
	D = countDays(C, B, A);
	
	printf("Введите вторую дату: \n");
	printf("\t год : ");
	if (!inputYear(&A))
	{
		printf("Неверный формат ввода, запустите программу заново.\n");
		return 0;
	}
	printf("\t месяц: ");
	if (!inputMonth(&B))
	{
		printf("Неверный формат ввода, запустите программу заново.\n");
		return 0;
	}
	printf("\t день: ");
	if (!inputDay(&C, B, A))
	{
		printf("Неверный формат ввода, запустите программу заново.\n");
		return 0;
	}
	G = countDays(C, B, A);

	M = abs(G - D);
	printf("Между датами %d суток.\n", M);
	return 0;
}