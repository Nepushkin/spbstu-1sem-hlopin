#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <time.h>
using namespace std;

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

void initMatrix(int** &matrix, int rows, int cols)
{
	matrix = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[cols];
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = rand() % 100;
		}
	}
}

int** copyMatrix(int** matrix, int rows, int cols)
{
	int** res = nullptr;
	initMatrix(res, rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			res[i][j] = matrix[i][j];
		}
	}
	return res;
}

void deleteMatrix(int** &matrix, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete matrix;
}

void printMatrix(int** &matrix, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%2d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void swap(int &a, int &b)
{
	int c = a;
	a = b;
	b = c;
}

void mixMatrix(int** matrix, int rows, int cols)
{
	for (int j = 0; j < cols; j++)
	{
		for (int i = 0; i < rows; i++)
		{
			swap(matrix[i][j], matrix[rand() % rows][j]);
		}
	}
}

pair<int, int> bubbleColsSort(int** inmatrix, int rows, int cols)
{
	int** matrix = copyMatrix(inmatrix, rows, cols);
	int per = 0;
	int srav = 0;

	for (int k = 0, shift = 1; k < cols; k++)
	{
		for (int i = 0; (i < rows) && (shift > 0); i++)
		{
			shift = 0;
			for (int j = 0; j < rows - i - 1; j++)
			{
				if (matrix[j][k] < matrix[j + 1][k])
				{
					swap(matrix[j][k], matrix[j + 1][k]);
					per++;
					shift++;
				}
				srav++;
			}
		}
		shift = 1;
	}

	printf("Перестановки: %d \t Сравнения: %d \n", per, srav);
	printMatrix(matrix, rows, cols);
	deleteMatrix(matrix, rows, cols);

	return pair<int, int>(per, srav);
}

pair<int, int> selectionColsSort(int** inmatrix, int rows, int cols)
{
	int** matrix = copyMatrix(inmatrix, rows, cols);
	int per = 0;
	int srav = 0;

	for (int k = 0; k < cols; k++)
	{
		for (int i = 0; i < rows; i++)
		{
			int index = 0;
			for (int j = 0; j < rows - i; j++)
			{
				if (matrix[j][k] < matrix[index][k])
				{
					index = j;
				}
				srav++;
			}
			if (index != rows - i - 1)
			{
				swap(matrix[index][k], matrix[rows - i - 1][k]);
				per++;
			}
		}
	}

	printf("Перестановки: %d \t Сравнения: %d \n", per, srav);
	printMatrix(matrix, rows, cols);
	deleteMatrix(matrix, rows, cols);
	return pair<int, int>(per, srav);
}

pair<int, int> insertColsSort(int** inmatrix, int rows, int cols)
{
	int** matrix = copyMatrix(inmatrix, rows, cols);
	int per = 0;
	int srav = 0;

	for (int k = 0; k < cols; k++)
	{
		for (int i = 1; i < rows; i++)
		{
			int temp = matrix[i][k];
			int j = 0;
			for (j = i; j > 0 && temp > matrix[j - 1][k]; j--)
			{
				matrix[j][k] = matrix[j - 1][k];
				per++;
				srav++;
			}
			matrix[j][k] = temp;
		}
	}

	printf("Перестановки: %d \t Сравнения: %d \n", per, srav);
	printMatrix(matrix, rows, cols);
	deleteMatrix(matrix, rows, cols);
	return pair<int, int>(per, srav);
}

pair<int, int> shellColsSort(int** inmatrix, int rows, int cols)
{
	int** matrix = copyMatrix(inmatrix, rows, cols);
	int per = 0;
	int srav = 0;

	for (int k = 0; k < cols; k++)
	{
		for (int diff = rows / 2; diff > 0; diff /= 2)
		{
			for (int i = diff; i < rows; i++)
			{
				int temp = matrix[i][k];
				int j = 0;
				for (j = i; j >= diff && temp > matrix[j - diff][k]; j -= diff)
				{
					matrix[j][k] = matrix[j - diff][k];
					srav++;
					per++;
				}
				matrix[j][k] = temp;
			}
		}
	}

	printf("Перестановки: %d \t Сравнения: %d \n", per, srav);
	printMatrix(matrix, rows, cols);
	deleteMatrix(matrix, rows, cols);
	return pair<int, int>(per, srav);
}

pair<int, pair<int, int>> partition(int** inmatrix, int low, int high, int col)
{
	int per = 0;
	int srav = 0;
	int pivot = inmatrix[high][col];
	int i = low;
	for (int j = low; j <= high - 1; j++)
	{
		if (inmatrix[j][col] > pivot)
		{
			swap(inmatrix[i][col], inmatrix[j][col]);
			i++;
			per++;
		}
		srav++;
	}
	swap(inmatrix[i][col], inmatrix[high][col]);
	per++;
	return pair<int, pair<int, int>>(i, pair<int, int>(per, srav));
}

pair<int, int> quickSort(int** inmatrix, int low, int high, int col)
{
	pair<int, int> res(0, 0);
	if (low < high)
	{
		pair<int, pair<int, int>> pi = partition(inmatrix, low, high, col);
		res.first += pi.second.first;
		res.second += pi.second.second;
		quickSort(inmatrix, low, pi.first - 1, col);
		quickSort(inmatrix, pi.first + 1, high, col);
	}
	return res;
}

pair<int, int> quickColsSort(int** inmatrix, int rows, int cols)
{
	int** matrix = copyMatrix(inmatrix, rows, cols);
	int per = 0;
	int srav = 0;

	for (int k = 0; k < cols; k++)
	{
		pair<int, int> temp = quickSort(matrix, 0, rows - 1, k);
		per += temp.first;
		srav += temp.second;
	}

	printf("Перестановки: %d \t Сравнения: %d \n", per, srav);
	printMatrix(matrix, rows, cols);
	deleteMatrix(matrix, rows, cols);
	return pair<int, int>(per, srav);
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");

	printf("Введите количество строк матрицы : ");
	int n = 0;
	if (!inputInt(&n))
	{
		printf("Некорректный ввод числа\n");
		return 0;
	}

	printf("Введите количество столбцов матрицы : ");
	int m = 0;
	if (!inputInt(&m))
	{
		printf("Некорректный ввод числа\n");
		return 0;
	}

	int** matrix = nullptr;
	initMatrix(matrix, n, m);
	printMatrix(matrix, n, m);
	pair<int, int> res[5];

	printf("\n\nСортировка пузырьком:\n");
	res[0] = bubbleColsSort(matrix, n, m);

	printf("\n\nСортировка отбором:\n");
	res[1] = selectionColsSort(matrix, n, m);

	printf("\n\nСортировка вставками:\n");
	res[2] = insertColsSort(matrix, n, m);

	printf("\n\nСортировка Шелла:\n");
	res[3] = shellColsSort(matrix, n, m);

	printf("\n\nБыстрая сортировка:\n\n");
	res[4] = quickColsSort(matrix, n, m);

	deleteMatrix(matrix, n, m);

	printf("_____________________________________________________________________________________________________________________\n");
	printf("____________|Сортировка пузырьком| Сортировка отбором |Сортировка вставками|  Сортировка Шелла  | Быстрая сортировка |\n");

	/*for (int i = 0; i < 5; i++)
	{
		printf("%7d\t%7d\n", res[i].first, res[i].second);
	}*/
	printf("Сравнения   |");
	for (int i = 0; i < 5; i++)
	{
		printf("%20d|", res[i].first);
	}
	printf("\nПерестановки|");
	for (int i = 0; i < 5; i++)
	{
		printf("%20d|", res[i].second);
	}
	printf("\n____________|____________________|____________________|____________________|____________________|____________________|\n");
	return 0;
}