#include "Include.h"
void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
int returnNumber(int number, int lenght)
{
	int k = (number - lenght) / 2;
	return number - k;
}
int choice(string str[], int n, string s)
{
	int number = 0;
	while (true)
	{
		if (_kbhit() == 1)
		{
			int ch = _getch();
			if (ch == 224)
			{
				ch = _getch();
				if (ch == 72)
				{
					system("cls");
					if (number)
						number--;
					else
						number = n - 1;
					menu(str, n, number, s);
				}
				if (ch == 80)
				{
					system("cls");
					if (number < n - 1)
						number++;
					else
						number = 0;
					menu(str, n, number, s);
				}
			}
			else
				if (ch == 13)
				{
					system("cls");
					return number + 1;
				}
		}
	}
}
void menu(string str[], int kol, int index, string s)
{
	if (s != "")
	{
		SetColor(14, 0);
		cout << s << endl;
		SetColor(15, 0);
	}
	for (int i = 0; i < kol; i++)
	{
		if (i == index)
		{
			SetColor(2, 0);
			cout << str[i] << endl;
			SetColor(15, 0);
		}
		else
			cout << str[i] << endl;
	}
}