#include <iostream>
#include <fstream>
#include <string>
#include "Menu.h"
#include "MyCrt.h"
#include "Table.h"

#pragma warning (disable : 4996)

using namespace std;
Menu T;

struct words
{
	string word;
	int n;
};
//обьявление структуры слова, состоит из слова и частоты использования

void myFunction() {
	ifstream input("..\\input.txt"); // читаем файл 

	if (!input) //проверка на успешное откртие файла 
	{
		cout << "can not open file" << endl;
		while (1);
	}

	words* mas = new words[1]; // создаем новый массив из структурами вордс
	int n = 1;
	string a = "1";
	while (input)
	{
		bool flag = true;
		for (int i = 0; i < n; i++)
		{
			if (a == mas[i].word)
			{
				mas[i].n++;
				flag = false;
				break;
			}
		}
		if (flag)
		{
			mas[n - 1].word = a;
			mas[n - 1].n = 1;
			words* copy = new words[n];
			for (int i = 0; i < n; i++)
			{
				copy[i] = mas[i];
			}
			delete[] mas;
			mas = new words[n + 1];
			for (int i = 0; i < n; i++)
			{
				mas[i] = copy[i];
			}
			delete[] copy;
			n++;
		}
		input >> a;
		if (a.at(a.length() - 1) < 65 || (a.at(a.length() - 1) > 90 && a.at(a.length() - 1) < 97) || a.at(a.length() - 1) > 123)
		{
			a.erase(a.length() - 1);
		}
	}

	n--;
	for (int i = 1; i < n; i++)
	{
		cout << mas[i].word << " - " << mas[i].n << endl;
	}

	delete[] mas;
}



void InitMyMenu() {
	static char MenuParts[3][50] = {
	   "file",
	   "results",
	   "thierd",
	};
	InitMenu(T, 0, 0, 0, true, 10, 240, 3, 50, (char*)MenuParts);
}

int CommandChoise()
{
	int Command = -1;
	Show_Menu(T);
	do
	{
		if (ItemChoice(T))
			switch (T.Item)
			{
			case 0:
				Command = 0;
				break;
			case 1:
				Command = 1;
				break;
			case 2:
				Command = 2;
				break;
			default:
				cout << "Do u want to exit ?";
				break;
			}
	} while (Command == -1);
	return Command;
}


int main()
{
	setlocale(0, "1251");
	InitMyMenu();
	int com;
	do
	{
		com = CommandChoise();
		switch (com)
		{
		case 0: cout << "0"; break;
		case 1: cout << "1"; break;
		case 2: cout << "2"; break;
		case 4: com = 0; break;
		}
	} while (com != 4);
	return 0;
	//SetConsoleCP(1251);
	//setlocale(0, "1251");
	//SetConsoleCP(866);
}
