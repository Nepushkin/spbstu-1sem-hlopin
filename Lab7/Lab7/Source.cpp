#include<iostream>
#include<fstream>
#include<clocale>
#include<string>
using namespace std;

struct Text {
	char** text;
	int** sortedIndexes;
	int capacity;
	int lines;
	int linelength;

	void init(string filename)
	{
		linelength = 2000;
		lines = 0;
		capacity = 10;
		text = new char*[capacity];

		ifstream ifs(filename);
		while (!ifs.eof())
		{
			if (lines == capacity)
			{
				expand();
			}
			text[lines] = new char[linelength];
			ifs.getline(text[lines], linelength);
			lines++;
		}
		ifs.close();

		sortedIndexes = new int*[lines];
		for (int i = 0; i < lines; i++)
		{
			sortedIndexes[i] = new int[linelength];
			for (int j = 0; j < linelength; j++)
			{
				sortedIndexes[i][j] = j;
			}
		}
		sort();
	}

	void expand()
	{
		int newlines = capacity * 2;
		char** newtext = new char*[newlines];
		for (int i = 0; i < capacity; i++)
		{
			newtext[i] = text[i];
		}
		delete[] text;
		text = newtext;
		capacity = newlines;
	}

	void print()
	{
		for (int i = 0; i < lines; i++)
		{
			cout << text[i] << endl;
		}
	}

	void printSorted()
	{
		for (int i = 0; i < lines; i++)
		{
			cout << "\"";
			for (int j = 0; text[i][j] != '\0'; j++)
			{
				cout << text[i][sortedIndexes[i][j]];
			}
			cout << "\"" << endl;
		}
	}

	void endWork()
	{
		for (int i = 0; i < lines; i++)
		{
			delete[] text[i];
			delete[] sortedIndexes[i];
		}
		delete[] text;
		delete[] sortedIndexes;
	}

	void swap(int &a, int &b)
	{
		int c = a;
		a = b;
		b = c;
	}

	void sort()
	{
		for (int k = 0; k < lines; k++)
		{
			for (int i = 0; text[k][sortedIndexes[k][i]] != '\0'; i++)
			{
				for (int j = 0; text[k][sortedIndexes[k][j]] != '\0'; j++)
				{
					if (text[k][sortedIndexes[k][i]] < text[k][sortedIndexes[k][j]])
					{
						swap(sortedIndexes[k][i], sortedIndexes[k][j]);
					}
				}
			}
		}
	}
};

pair<int, int> countCharsLinear(Text text, char chr)
{
	int result = 0;
	int comp = 0;
	for (int i = 0; i < text.lines; i++)
	{
		int linecount = 0;
		for (int j = 0; text.text[i][j] != '\0'; j++)
		{
			if (text.text[i][j] == chr)
			{
				linecount++;
				result++;
			}
			comp++;
		}
		//cout << "\t" << linecount << endl;
	}
	return pair<int, int>(result, comp);
}

pair<int, int> countCharsBinary(Text text, char chr)
{
	int result = 0;
	int comp = 0;

	for (int i = 0; i < text.lines; i++)
	{
		char* line = text.text[i];
		int* ind = text.sortedIndexes[i];
		int len = strlen(line);

		int m1 = 0;
		int m2 = 0;
		
		int s = 0;
		int e = len - 1;
		while (s < e)
		{
			m1 = (s + e) / 2;
			if (line[ind[m1]] < chr)
				s = m1 + 1;
			else
				e = m1;
			comp++;
		}
		if (line[ind[s]] != chr) continue;
		m1 = s;

		s = 0;
		e = len - 1;
		while (s < e)
		{
			m2 = (s + e + 1) / 2;
			if (line[ind[m2]] <= chr)
				s = m2;
			else
				e = m2 - 1;
			comp++;
		}
		m2 = s;

		result += m2 - m1 + 1;
	}

	return pair<int, int>(result, comp);
}

void printSymbolCount(Text text, char symbol)
{
	cout << "\"" << symbol << "\":";
	pair<int, int> res;
	res = countCharsLinear(text, symbol);
	cout << "\tlinear : " << res.first << " " << res.second << endl;
	res = countCharsBinary(text, symbol);
	cout << "\tbinary : " << res.first << " " << res.second << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Text text;
	text.init("in.txt");
	text.print();
	cout << endl;
	text.printSorted();

	string symbols = "МОвгде!ктулху! .;";
	for (int i = 0; i < symbols.length(); i++)
	{
		printSymbolCount(text, symbols[i]);
	}

	cout << "Найти количество букв, равных предпоследней букве текста" << endl;
	char* str = text.text[text.lines - 1];
	if (strlen(str) > 1)
	{
		char chr = str[strlen(str) - 2];
		printSymbolCount(text, chr);
	}

	text.endWork();
	return 0;
}