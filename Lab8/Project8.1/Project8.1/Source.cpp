#include<iostream>
#include<fstream>
#include<string>
#include<list>
using namespace std;
struct Text {
	list<pair<int, string>>words;
	//const int p = 137; // если и большие и маленькие
	//const int p = 31; если только маленькие 
	Text(string filename)
	{
		ifstream ifs(filename);
		while (!ifs.eof()) // ifs-input file stream
		{
			string str;
			ifs >> str; // только 1 слово
			// getline(ifs,str); всю строку
			words.push_back(pair<int, string>(hash(str), str));
		}
		ifs.close();
	}

	void print()
	{
		for (list<pair<int, string>>::iterator it = words.begin(); it != words.end(); it++)
		{
			cout << "\"(" << (*it).first << ")" << (*it).second << "\"" << endl;
			//cout << (*it).second << " " << endl;
		}
	}

	int compareStrings(string s1, string s2)
	{
		int result = 0;
		for (int i = 0; i < s1.length() && i < s2.length(); i++)
		{
			result += s1[i] - s2[i];
			if (result != 0)
			{
				break;
			}
		}
		return result;
	}

	int hash(string str)
	{
		int result = 0;
		//int base = 1;
		for (int i = 0; i < str.length(); i++)
		{
			result += str[i];
			//base *= p;
		}
		return result;
	}
	//моя исходная функция
	/*void findWord(string word)
	{
		int h = hash(word);
		int count = 0;
		int i = 0;
		for (list<pair<int, string>>::iterator it = words.begin(); it != words.end(); it++, i++)
		{
			if (((*it).first == h) && (compareStrings((*it).second, word) == 0))
			{
				cout << i + 1 << " ";
				count++;
			}
		}
		cout << endl << "found " << count << " words" << endl;
	}*/
	//моя доработанная функция
	void findWord(string word)
	{
		int h = hash(word);
		int count1 = 0;
		int count2 = 0;
		int i = 0;
		for (list<pair<int, string>>::iterator it = words.begin(); it != words.end(); it++, i++)
		{
			if ((*it).first == h)
			{
				count1++;
				if (compareStrings((*it).second, word) == 0)
				{
					count2++;
				}
			}
		}
		cout << endl << "using only hash we found " << count1 << " words" << endl;
		cout << "using also check hash we found " << count2 << " words" << endl;
	}
};

int main()
{
	Text text("in.txt");
	text.print();
	cout << "input word to find" << endl;
	string str;
	cin >> str;
	text.findWord(str);
	return 0;
}