#include "Products.h"
#include "Accounts.h"
using namespace std;

string sign_in_password();
void menuSearchAccount(vector <User>, vector <Admin>);
void viewProducts(vector <Section>, int, int, string, string);
string enterLogin();
void menuWorkWithData(vector<Section>* vec);
void sell(vector <Section>* vec);
int CreateReport();
void CreatePriceList(vector<Section>);


template <class T>
void write(vector <T> staff, string file)
{
	int accNum = staff.size();
	ofstream ouf;
	ouf.open(file, ios_base::out | ios_base::binary);
	
	if (!ouf)
	{
		cout << "\nНевозможно открыть файл\n";
		return;
	}
	for (int i = 0; i < accNum; i++)
	{
		ouf << staff[i];
		if (!ouf)
		{
			cout << "\nЗапись в файл невозможна\n";
			return;
		}
	}
	ouf.close();
}
template <class T>
void read(vector <T>* vec, string file)
{
	ifstream inf;
	inf.open(file, ios::binary);
	T buf;
	if (!inf && file == "ADMINS.DAT")
	{
		throw 1;
	}
	int accNum = 0;
	while (true)
	{
		if (inf.eof()) break;
		if (!inf)
		{
			cout << "\nНевозможно чтение типа\n";
			break;
		}
		(*vec).push_back(T());
		inf >> (*vec)[(*vec).size() - 1];
		accNum++;
		inf.seekg(1, ios::cur);
	}
	inf.close();
	if ((*vec).size() > 0)
		(*vec).pop_back();
}


void menuAdmin(vector <User>* vecu, vector <Admin>* veca, int n, vector <Section>* vecs) 
{ 
	int userChoice, kod;
	string s2[4] = { "По алфавиту", "В обратном порядке", "Назад" };
	string s[4] = { "Работа с аккаунтами", "Работа с данными", "Выход из аккаунта" }, admin = "--------------------МЕНЮ АДМИНИСТРАТОРА--------------------";
	string s1[8] = { "Просмотр списка всех записей", "Создание новой записи", "Изменение записи","Удаление записи","Поиск записи", "Сортировка записей", "Назад"};
	while (1)
	{
		system("cls");
		menu(s, 3, 0, admin);
		userChoice = choice(s, 3, admin);
		switch (userChoice)
		{
		case 1:
			
			while (1)
			{
				system("cls");
				menu(s1, 7, 0, "");
				kod = choice(s1, 7, "");
				switch (kod)
				{
				case 1:
					viewAccounts("Аккаунты администраторов", *veca);
					viewAccounts(*veca);
					cout << endl << endl;
					viewAccounts("Аккаунты пользователей", *vecu);
					viewAccounts(*vecu);
					system("pause");
					break;
				case 2:
					create_new_user(vecu, veca, 0);
					break;
				case 3:
					menuEditAccount(veca, vecu);
					break;
				case 4:
					menuDeleteAccount(veca, vecu, n);
					break;
				case 5:
					menuSearchAccount(*vecu, *veca);
					break;
				case 6:
					menu(s2, 3, 0, "");
					kod = choice(s2, 3, "");
					switch (kod)
					{
					case 1:
						if ((*vecu).size() > 1)
							(*vecu)[0].SortByLogin(vecu);
						if ((*veca).size() > 1)
							(*veca)[0].SortByLogin(veca);
						break;
					case 2:
						if ((*vecu).size() > 1)
						{
							(*vecu)[0].SortByLogin(vecu);
							std::reverse((*vecu).begin(), (*vecu).end());
						}
						if ((*veca).size() > 1)
						{
							(*veca)[0].SortByLogin(veca);
							std::reverse((*veca).begin(), (*veca).end());
						}
						break;
					}
					viewAccounts("Аккаунты администраторов", *veca);
					viewAccounts(*veca);
					cout << endl << endl;
					viewAccounts("Аккаунты пользователей", *vecu);
					viewAccounts(*vecu);
					system("pause");
					break;
				default:
					break;
				}
				if (kod == 7)
					break;
			}
			break;
		case 2:
			menuWorkWithData(vecs);
			break;
		case 3:
			return;
		}
		if (userChoice == 3)
			break;
	}
}

void printSections(vector <Section> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		cout << vec[i].returnName() << endl;
	}
}
void printSections(vector <Subsection> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		cout << vec[i].returnName() << endl;
	}
}

void addProduct(vector<Section>* vec, int number2)
{
	int kod, number, number1;
	string s[5];
	if (number2)
	{

		s[0] = "Добавить раздел";
		s[1] = "Добавить подраздел";
		s[2] = "Добавить товар";
		s[3] = "Назад";
	}
	else
	{
		s[0] = "Добавить товар";
		s[1] = "Назад";
	}
	if (number2)
	{
		menu(s, 4, 0, "");
		kod = choice(s, 4, "");
	}
	else
	{
		menu(s, 2, 0, "");
		kod = choice(s, 2, "");
		kod += 2;
	}
	Section section;
	string buf;
	int size, i;
	string* s2, * s3, s1;
	switch (kod)
	{
	case 1:
		section.setData();
		(*vec).push_back(section);
		break;
	case 2:
		system("cls");
		size = (*vec).size() + 2;
		s2 = new string[size];
		for (i = 0; i < size - 2; i++)
		{
			s2[i] = (*vec)[i].returnName();
		}
		s2[i] = "Назад";
		s1 = "Выберите раздел";
		menu(s2, size - 1, 0, s1);
		number = choice(s2, size - 1, s1);
		if(s2[number - 1] != "Назад")
			(*vec)[number - 1].addVector();
		break;
	case 3:
		system("cls");
		size = (*vec).size() + 2;
		s2 = new string[size];
		for (i = 0; i < size - 2; i++)
		{
			s2[i] = (*vec)[i].returnName();
		}
		s2[i] = "Назад";
		s1 = "Выберите раздел";
		menu(s2, size - 1, 0, s1);
		number = choice(s2, size - 1, s1);
		if (s2[number - 1] == "Назад")
			break;
		size = (*(*vec)[number - 1].returnVectorSubsection()).size() + 2;
		s3 = new string[size];
		for (i = 0; i < size - 2; i++)
		{
			s3[i] = (*(*vec)[number - 1].returnVectorSubsection())[i].returnName();
		}
		s3[i] = "Назад";
		cout << "Выберите подраздел" << endl;
		menu(s3, size - 1, 0, "");
		number1 = choice(s3, size - 1, "");
		if (s3[number1 - 1] == "Назад")
			break;
		(*(*vec)[number - 1].returnVectorSubsection())[number1 - 1].addVector();
		break;
	case 4:
		break;
	}
}

void menuSort(vector <Product> * section)
{
	if ((*section).size() < 1)
	{
		cout << "Нет данных для сортировки!" << endl;
		system("pause");
		return;
	}
	int kod;
	string s[9] = { "По алфавиту", "Сначала новые", "Сначала старые", "По возрастанию количества товара", "По убыванию количества товара", "По возрастанию стоимости товара",
		"По убыванию стоимости товара", "Назад" };
	menu(s, 8, 0, "");
	kod = choice(s, 8, "");
	switch (kod)
	{
	case 1:
		(*section)[0].SortByName(section);
		break;
	case 2:
		(*section)[0].SortByDate(section);
		break;
	case 3:
		(*section)[0].SortByDate(section);
		std::reverse((*section).begin(), (*section).end());
		break;
	case 4:
		(*section)[0].SortByAmount(section);
		break;
	case 5:
		(*section)[0].SortByAmount(section);
		std::reverse((*section).begin(), (*section).end());
		break;
	case 6:
		(*section)[0].SortByPrice(section);
		break;
	case 7:
		(*section)[0].SortByPrice(section);
		std::reverse((*section).begin(), (*section).end());
		break;
	default:
		break;
	}
}

void menuSearchData(vector <Section> vec)
{
	int i, number, number1;
	string sec = "Выберите раздел", subsec = "Выберите подраздел";
	string* s2, * s3;
	int size;
	double left, right;
	while (1)
	{
		system("cls");
		size = vec.size() + 2;
		s2 = new string[size];
		for (i = 0; i < size - 2; i++)
		{
			s2[i] = vec[i].returnName();
		}
		s2[i] = "Назад";
		menu(s2, size - 1, 0, sec);
		number = choice(s2, size - 1, sec);
		if (s2[number - 1] == "Назад")
			break;
		while (1)
		{
			size = (*vec[number - 1].returnVectorSubsection()).size() + 2;
			s3 = new string[size];
			for (i = 0; i < size - 2; i++)
			{
				s3[i] = (*vec[number - 1].returnVectorSubsection())[i].returnName();
			}
			s3[i] = "Назад";
			menu(s3, size - 1, 0, subsec);
			number1 = choice(s3, size - 1, subsec);
			if (s3[number1 - 1] == "Назад")
				break;
			vector <Product> product = *((*vec[number - 1].returnVectorSubsection())[number1 - 1]).returnProduct();
			if (product.size() == 0)
			{
				SetColor(4, 0);
				cout << "Список товаров пуст!" << endl;
				SetColor(15, 0);
				Sleep(1000);
				return;
			}
			int kod;
			string name;
			string s[6] = { "По названию","По количеству","По стоимости","По производителю", "Назад" };
			menu(s, 5, 0, "");
			kod = choice(s, 5, "");
			switch (kod)
			{
			case 1:	
				while (true)
				{
					cout << "Введите название товара: ";
					getline(cin, name);
					if (name != "")
						break;
					cout << "Неправильный ввод данных!" << endl;
				}
				Product::SearchByName(product, name, s2[number - 1], s3[number1 - 1]);
				return;
			case 2:
				int amount;
				cout << "Введите количество товара: ";
				cin >> amount;
				Product::SearchByAmount(product, amount, s2[number - 1], s3[number1 - 1]);
				return;
			case 3:
				cout << "Введите минимальную стоимость: ";
				cin >> left;
				cout << "Введите максимальную стоимость: ";
				cin >> right;
				Product::SearchByPrice(product, s2[number - 1], s3[number1 - 1], left, right);
				return;
			case 4:
				while (true)
				{
					cout << "Введите производителя: ";
					getline(cin, name);
					if (name != "")
						break;
					cout << "Неправильный ввод данных!" << endl;
				}
				Product::SearchByMan(product, s2[number - 1], s3[number1 - 1], name);
				return;
			case 5:
				break;
			}
		}
	}
}

void editData(Product* product)
{
	int kod;
	string s1 = "Выберите, что изменить";
	string s[7] = { "Наименование", "Производителя", "Стоимость", "Артикул", "Количество", "Назад" };
	menu(s, 6, 0, s1);
	kod = choice(s, 6, s1);
	switch (kod)
	{
	case 1:
		(*product).setName();
		break;
	case 2:
		(*product).setManufacturer();
		break;
	case 3:
		(*product).setPrice();
		break;
	case 4:
		(*product).returnKod();
		break;
	case 5:
		(*product).setAmount();
		break;
	default:
		break;
	}
}

void menuWorkWithData(vector<Section>* vec)
{
	int kod, number, number1, numberEdit;
	while (1)
	{
		string s[10] = { "Просмотр списка товаров на складе", "Добавление товара на склад", "Редактирование", "Продажа товара", "Поиск/Фильтрация", "Сортировка", "Отчёт о проданных товарах за период", "Создание прайс-листа", "Назад" };
		string section, subsection;
		int size, i;
		string* s2;
		string* s3;
		string sec = "Выберите раздел", subsec = "Выберите подраздел";
		while (true)
		{
			system("cls");
			menu(s, 9, 0, "");
			kod = choice(s, 9, "");
			switch (kod)
			{
			case 1:
				system("cls");
				size = (*vec).size() + 2; // vector [3]= ["vector[0]", "Back"] .size = 1
				s2 = new string[size];
				for (i = 0; i < size - 2; i++)
				{
					s2[i] = (*vec)[i].returnName();
				}
				s2[i] = "Назад";
				menu(s2, size - 1, 0, sec);
				number = choice(s2, size - 1, sec);
				if (s2[number - 1] == "Назад")
					break;
				size = (*(*vec)[number - 1].returnVectorSubsection()).size() + 2;
				s3 = new string[size];
				for (i = 0; i < size - 2; i++)
				{
					s3[i] = (*(*vec)[number - 1].returnVectorSubsection())[i].returnName();
				}
				s3[i] = "Назад";
				menu(s3, size - 1, 0, subsec);
				number1 = choice(s3, size - 1, subsec);
				if (s3[number1 - 1] == "Назад")
					break;
				viewProducts(*vec, number - 1, number1 - 1, s2[number - 1], s3[number1 - 1]);
				break;
			case 2:
				addProduct(vec, 1);
				break;
			case 3:
				system("cls");
				size = (*vec).size() + 2; // vector [3]= ["vector[0]", "Back"] .size = 1
				s2 = new string[size];
				for (i = 0; i < size - 2; i++)
				{
					s2[i] = (*vec)[i].returnName();
				}
				s2[i] = "Назад";
				menu(s2, size - 1, 0, sec);
				number = choice(s2, size - 1, sec);
				if (s2[number - 1] == "Назад")
					break;
				size = (*(*vec)[number - 1].returnVectorSubsection()).size() + 2;
				s3 = new string[size];
				for (i = 0; i < size - 2; i++)
				{
					s3[i] = (*(*vec)[number - 1].returnVectorSubsection())[i].returnName();
				}
				s3[i] = "Назад";
				menu(s3, size - 1, 0, subsec);
				number1 = choice(s3, size - 1, subsec);
				if (s3[number1 - 1] == "Назад")
					break;
				viewProducts(*vec, number - 1, number1 - 1, s2[number - 1], s3[number1 - 1]);
				while (1)
				{
					cout << "Введите порядковый номер изменяемой записи: ";
					cin >> numberEdit;
					if (numberEdit > (*(*(*vec)[number - 1].returnVectorSubsection())[number1 - 1].returnProduct()).size() || numberEdit < 1)
					{
						cout << "Такого номера нет!" << endl;
					}
					else
						break;
				}
				system("cls");
				editData(&((*(*(*vec)[number - 1].returnVectorSubsection())[number1 - 1].returnProduct())[numberEdit - 1]));
				viewProducts(*vec, number - 1, number1 - 1, s2[number - 1], s3[number1 - 1]);
				break;
			case 4:
				sell(vec);
				break;
			case 5:
				menuSearchData(*vec);
				system("pause");
				break;
			case 6:
				system("cls");
				size = (*vec).size() + 2; // vector [3]= ["vector[0]", "Back"] .size = 1
				s2 = new string[size];
				for (i = 0; i < size - 2; i++)
				{
					s2[i] = (*vec)[i].returnName();
				}
				s2[i] = "Назад";
				menu(s2, size - 1, 0, sec);
				number = choice(s2, size - 1, sec);
				if (s2[number - 1] == "Назад")
					break;
				size = (*(*vec)[number - 1].returnVectorSubsection()).size() + 2;
				s3 = new string[size];
				for (i = 0; i < size - 2; i++)
				{
					s3[i] = (*(*vec)[number - 1].returnVectorSubsection())[i].returnName();
				}
				s3[i] = "Назад";
				menu(s3, size - 1, 0, subsec);
				number1 = choice(s3, size - 1, subsec);
				if (s3[number1 - 1] == "Назад")
					break;
				menuSort((*(*vec)[number - 1].returnVectorSubsection())[number1 - 1].returnProduct());
				viewProducts(*vec, number - 1, number1 - 1, s2[number - 1], s3[number1 - 1]);
				break;
			case 7:
				if (!CreateReport())
					CreateReport();
				break;
			case 8:
				CreatePriceList(*vec);
				break;
			}
			if (kod == 9)
				break;
		}
		if (kod == 9)
			break;
	}
}
void viewProducts(vector <Section> vec, int number, int number1, string section, string subsection)
{

	vector <Product> product = *((*vec[number].returnVectorSubsection())[number1]).returnProduct();
	if (product.size() == 0)
	{
		SetColor(4, 0);
		cout << "Список товаров пуст!" << endl;
		SetColor(15, 0);
		Sleep(1000);
		return;
	}
	string s1;
	stringstream str;
	int width, lengthNumber = product[0].returnLengthNumber(product);
	int lengthName = product[0].returnLengthName(product), lengthKod = product[0].returnLengthKod(product), lengthAmount = product[0].returnLengthAmount(product),
		lengthPrice = product[0].returnLengthPrice(product), lengthManuf = product[0].returnLengthManufacturer(product);
	while (true)
	{
		system("cls");
		if ( number1 != -1)
		{
			width = product[0].returnWidthTable(product);
			cout.setf(ios::right);
			for (int i = 0; i < width + 2; i++)
				cout << "-";
			cout << endl << "|";
			SetColor(6, 0);
			cout << setw(returnNumber(width, section.length())) << section << setw(width + 1 - returnNumber(width, section.length()));
			SetColor(15, 0);
			cout << "|" << endl;
			for (int i = 0; i < width + 2; i++)
				cout << "-";
			cout << endl << "|";
			SetColor(10, 0);
			cout << setw(returnNumber(width, subsection.length())) << subsection << setw(width + 1 - returnNumber(width, subsection.length()));
			SetColor(15, 0);
			cout << "|" << endl;
			for (int i = 0; i < width + 2; i++)
				cout << "-";
			cout << endl << "|";
			SetColor(11, 0);
			cout << setw(returnNumber(lengthNumber, 1)) << "№";
			SetColor(15, 0);
			cout << setw(lengthNumber + 1 - returnNumber(lengthNumber, 1)) << "|";
			SetColor(11, 0);
			cout << setw(returnNumber(lengthName, 12)) << "Наименование" << setw(lengthName + 1 - returnNumber(lengthName, 12));
			SetColor(15, 0);
			cout << "|" << setw(returnNumber(lengthKod, 7));
			SetColor(11, 0);
			cout << "Артикул" << setw(lengthKod + 1 - returnNumber(lengthKod, 7));
			SetColor(15, 0);
			cout << "|" << setw(returnNumber(lengthAmount, 10));
			SetColor(11, 0);
			cout << "Количество";
			SetColor(15, 0);
			cout << setw(lengthAmount + 1 - returnNumber(lengthAmount, 10)) << "|";
			SetColor(11, 0);
			cout << setw(returnNumber(lengthPrice, 9)) << "Стоимость";
			SetColor(15, 0);
			cout << setw(lengthPrice + 1 - returnNumber(lengthPrice, 9)) << "|";
			SetColor(11, 0);
			cout << setw(returnNumber(lengthManuf, 13)) << "Производитель";
			SetColor(15, 0);
			cout << setw(lengthManuf + 1 - returnNumber(lengthManuf, 13)) << "|";
			SetColor(11, 0);
			cout << setw(returnNumber(18, 16)) << "Дата поступления";
			SetColor(15, 0);
			cout << setw(19 - returnNumber(18, 16)) << "|" << endl;
			for (int i = 0; i < width + 2; i++)
				cout << "-";
			cout << endl;
			for (size_t i = 0; i < product.size(); i++)
			{
				str << i + 1;
				str >> s1;
				cout << "|" << setw(returnNumber(lengthNumber, s1.length()));
				SetColor(6, 0);
				cout << i + 1 << setw(lengthNumber + 1 - returnNumber(lengthNumber, s1.length()));
				SetColor(15, 0);
				cout << "|";
				product[i].print(product);
			}
			cout.unsetf(ios::right);
			break;
		}
	}
	system("pause");
}
void menuUser(vector <Section> * vec)
{
	int userChoice, size, i, number, number1;
	while (1)
	{
		string user = "----------МЕНЮ ПОЛЬЗОВАТЕЛЯ----------", * s2, * s3, sec = "Выберите раздел:", subsec = "Выберите подраздел:";
		string s[8] = { "Просмотр списка товаров на складе","Добавление товара на склад", "Продажа товара со склада", "Поиск/Фильтрация", "Сортировка", "Создание прайс-листа", "Выход из аккаунта" };
		system("cls");
		menu(s, 7, 0, user);
		userChoice = choice(s, 7, user);
		switch (userChoice)
		{
		case 1:
			system("cls");
			size = (*vec).size() + 2; // vector [3]= ["vector[0]", "Back"] .size = 1
			s2 = new string[size];
			for (i = 0; i < size - 2; i++)
			{
				s2[i] = (*vec)[i].returnName();
			}
			s2[i] = "Назад";
			menu(s2, size - 1, 0, sec);
			number = choice(s2, size - 1, sec);
			if (s2[number - 1] == "Назад")
				break;
			size = (*(*vec)[number - 1].returnVectorSubsection()).size() + 2;
			s3 = new string[size];
			for (i = 0; i < size - 2; i++)
			{
				s3[i] = (*(*vec)[number - 1].returnVectorSubsection())[i].returnName();
			}
			s3[i] = "Назад";
			menu(s3, size - 1, 0, subsec);
			number1 = choice(s3, size - 1, subsec);
			if (s3[number1 - 1] == "Назад")
				break;
			viewProducts(*vec, number - 1, number1 - 1, s2[number - 1], s3[number1 - 1]);
			break;
		case 2:
			addProduct(vec, 0);
			break;
		case 3:
			sell(vec);
			break;
		case 4:
			menuSearchData(*vec);
			system("pause");
			break;
		case 5:
			system("cls");
			size = (*vec).size() + 2; // vector [3]= ["vector[0]", "Back"] .size = 1
			s2 = new string[size];
			for (i = 0; i < size - 2; i++)
			{
				s2[i] = (*vec)[i].returnName();
			}
			s2[i] = "Назад";
			menu(s2, size - 1, 0, sec);
			number = choice(s2, size - 1, sec);
			if (s2[number - 1] == "Назад")
				break;
			size = (*(*vec)[number - 1].returnVectorSubsection()).size() + 2;
			s3 = new string[size];
			for (i = 0; i < size - 2; i++)
			{
				s3[i] = (*(*vec)[number - 1].returnVectorSubsection())[i].returnName();
			}
			s3[i] = "Назад";
			menu(s3, size - 1, 0, subsec);
			number1 = choice(s3, size - 1, subsec);
			if (s3[number1 - 1] == "Назад")
				break;
			menuSort((*(*vec)[number - 1].returnVectorSubsection())[number1 - 1].returnProduct());
			viewProducts(*vec, number - 1, number1 - 1, s2[number - 1], s3[number1 - 1]);
			break;
		case 6:
			CreatePriceList(*vec);
			break;
		case 7:
			break;
		}
		if (userChoice == 7)
			break;
	}
}



int CreateReport()
{
	try
	{
		int day1, month1, year1, day2, month2, year2;
		vector <Section> section;
		read(&section, "ITEMSOLT.DAT");
		cout << "Введите период, за какой требуется сформировать отчёт: " << endl;
		while (1)
		{
			cout << "c ";
			enterDate(&day1, &month1, &year1);
			cout << endl;
			if (month1 > 12 || month1 == 0 || day1 == 0 || to_string(year1).length() != 4)
			{
				SetColor(4, 0);
				cout << "Введена некорректная дата!" << endl;
				SetColor(15, 0);
				continue;
			}
			if (month1 == 2)
			{
				if (year1 % 4 == 0)
				{
					if (day1 > 29)
					{
						SetColor(4, 0);
						cout << "Введена некорректная дата!" << endl;
						SetColor(15, 0);
						continue;
					}
				}
				else
				{
					if (day1 > 28)
					{
						SetColor(4, 0);
						cout << "Введена некорректная дата!" << endl;
						SetColor(15, 0);
						continue;
					}
				}
			}
			if ((month1 == 1 || month1 == 3 || month1 == 5 || month1 == 7 || month1 == 8 || month1 == 10 || month1 == 12) && day1 > 31)
			{
				SetColor(4, 0);
				cout << "Введена некорректная дата!" << endl;
				SetColor(15, 0);
				continue;
			}
			if ((month1 == 2 || month1 == 4 || month1 == 6 || month1 == 9 || month1 == 11) && day1 > 30)
			{
				SetColor(4, 0);
				cout << "Введена некорректная дата!" << endl;
				SetColor(15, 0);
				continue;
			}
			break;
		}
		while (1)
		{
			cout << "по ";
			enterDate(&day2, &month2, &year2);
			cout << endl;
			if (month2 > 12 || month2 == 0 || day2 == 0 || to_string(year2).length() != 4)
			{
				SetColor(4, 0);
				cout << "Введена некорректная дата!" << endl;
				SetColor(15, 0);
				continue;
			}
			if (month2 == 2)
			{
				if (year2 % 4 == 0)
				{
					if (day2 > 29)
						continue;
				}
				else
				{
					if (day2 > 28)
						continue;
				}
			}
			if ((month2 == 1 || month2 == 3 || month2 == 5 || month2 == 7 || month2 == 8 || month2 == 10 || month2 == 12) && day2 > 31)
				continue;
			if ((month2 == 2 || month2 == 4 || month2 == 6 || month2 == 9 || month2 == 11) && day2 > 30)
				continue;
			break;
		}
		ofstream ouf("REPORT.TXT", ios_base::out);
		ouf << "ОТЧЁТ О ПРОДАННЫХ ТОВАРАХ ЗА ПЕРИОД С ";
		if (day1 < 10)
			ouf << "0" << day1 << ".";
		else
			ouf << day1 << ":";
		if (month1 < 10)
			ouf << "0" << month1 << ".";
		else
			ouf << month1 << ".";
		ouf << year1 << " ПО ";
		if (day2 < 10)
			ouf << "0" << day2 << ".";
		else
			ouf << day2 << ":";
		if (month2 < 10)
			ouf << "0" << month2 << ".";
		else
			ouf << month2 << ".";
		ouf << year2 << "\n";
		int number = 0;
		string s1;
		stringstream str;
		double sum = 0;
		int kol = 0, width = 1, width1;
		int lengthNumber = 1, lengthName = 1, lengthKod = 1, lengthAmount = 1, lengthPrice = 1, lengthManuf = 1;
		int lengthNumber1 = 1, lengthName1 = 1, lengthKod1 = 1, lengthAmount1 = 1, lengthPrice1 = 1, lengthManuf1 = 1;
		for (size_t i = 0; i < section.size(); i++)
		{
			for (size_t j = 0; j < (*section[i].returnVectorSubsection()).size(); j++)
			{
				vector<Product> product = (*(*section[i].returnVectorSubsection())[j].returnProduct());
				lengthNumber1 = product[0].returnLengthNumber(product);
				lengthName1 = product[0].returnLengthName(product);
				lengthKod1 = product[0].returnLengthKod(product);
				lengthAmount1 = product[0].returnLengthAmount(product);
				lengthPrice1 = product[0].returnLengthPrice(product);
				lengthManuf = product[0].returnLengthManufacturer(product);
				if (lengthAmount1 > lengthAmount)
					lengthAmount = lengthAmount1;
				if (lengthManuf1 > lengthManuf)
					lengthManuf = lengthManuf1;
				if (lengthPrice1 > lengthPrice)
					lengthPrice = lengthPrice1;
				if (lengthKod1 > lengthKod)
					lengthKod = lengthKod1;
				if (lengthName1 > lengthName)
					lengthName = lengthName1;
				if (lengthNumber1 > lengthNumber)
					lengthNumber = lengthNumber1;
			}
		}
		width = lengthNumber + lengthName + lengthKod + lengthPrice + lengthManuf + lengthAmount + 20;
		for (size_t i = 0; i < section.size(); i++)
		{
			for (size_t j = 0; j < (*section[i].returnVectorSubsection()).size(); j++)
			{
				vector<Product> product = (*(*section[i].returnVectorSubsection())[j].returnProduct());
				for(size_t k = 0; k < product.size(); k++)
				{
					if (product[k].returnYear() < year1 || product[k].returnYear() > year2)
					{
						break;
					}
					else
					{
						if (product[k].returnYear() == year1)
						{
							if (product[k].returnMonth() < month1)
								break;
							else
							{
								if (product[k].returnDay() < day1)
									break;
							}
						}
						else
						{
							if (product[k].returnYear() == year2)
							{
								if (product[k].returnMonth() > month1)
									break;
								else
								{
									if (product[k].returnDay() > day1)
										break;
								}
							}
						}
					}
					for (int p = 0; p < width + 2; p++)
						ouf << "-";
					ouf << "\n" << "|";
					SetColor(6, 0);
					ouf << setw(returnNumber(width, section[i].returnName().length())) << section[i].returnName() << setw(width + 1 - returnNumber(width, section[i].returnName().length()));
					ouf << "|" << endl;
					for (int p = 0; p < width + 2; p++)
						ouf << "-";
					ouf << "\n" << "|";
					ouf << setw(returnNumber(width, (*section[i].returnVectorSubsection())[j].returnName().length())) << (*section[i].returnVectorSubsection())[j].returnName() << setw(width + 1 - returnNumber(width, (*section[i].returnVectorSubsection())[j].returnName().length()));
					ouf << "|" << "\n";
					for (int p = 0; p < width + 2; p++)
						ouf << "-";
					ouf << "\n" << "|";
					ouf << setw(returnNumber(lengthNumber, 1)) << "№";
					ouf << setw(lengthNumber + 1 - returnNumber(lengthNumber, 1)) << "|";
					ouf << setw(returnNumber(lengthName, 12)) << "Наименование" << setw(lengthName + 1 - returnNumber(lengthName, 12));
					ouf << "|" << setw(returnNumber(lengthKod, 7));
					ouf << "Артикул" << setw(lengthKod + 1 - returnNumber(lengthKod, 7));
					ouf << "|" << setw(returnNumber(lengthAmount, 10));
					ouf << "Количество";
					ouf << setw(lengthAmount + 1 - returnNumber(lengthAmount, 10)) << "|";
					ouf << setw(returnNumber(lengthPrice, 9)) << "Стоимость";
					ouf << setw(lengthPrice + 1 - returnNumber(lengthPrice, 9)) << "|";
					ouf << setw(returnNumber(lengthManuf, 13)) << "Производитель";
					ouf << setw(lengthManuf + 1 - returnNumber(lengthManuf, 13)) << "|";
					ouf << setw(returnNumber(14, 12)) << "Дата продажи";
					ouf << setw(15 - returnNumber(14, 12)) << "|" << "\n";
					for (int p = 0; p < width + 2; p++)
						ouf << "-";
					ouf << "\n";
					for (size_t p = 0; p < product.size(); p++)
					{
						str << p + 1;
						str >> s1;
						ouf << "|" << setw(returnNumber(lengthNumber, s1.length()));
						ouf << p + 1 << setw(lengthNumber + 1 - returnNumber(lengthNumber, s1.length()));
						ouf << "|";
						string s1, s2, s3;
						stringstream str, str1, str2, str3, str4;
						ouf << setw(returnNumber(lengthName, product[p].returnName().length())) << product[p].returnName();
						ouf << setw(lengthName + 1 - returnNumber(lengthName, product[p].returnName().length())) << "|";
						str << product[p].returnKod();
						str >> s1;
						ouf << setw(returnNumber(lengthKod, s1.length())) << s1;
						ouf << setw(lengthKod + 1 - returnNumber(lengthKod, s1.length())) << "|";
						str1.clear();
						str1 << product[p].returnAmount();
						str1 >> s1;
						ouf << setw(returnNumber(lengthAmount, s1.length())) << s1;
						ouf << setw(lengthAmount + 1 - returnNumber(lengthAmount, s1.length())) << "|";
						str.clear();
						str << product[p].returnPrice();
						str >> s1;
						ouf << setw(returnNumber(lengthPrice, s1.length())) << s1;
						ouf << setw(lengthPrice + 1 - returnNumber(lengthPrice, s1.length())) << "|";
						ouf << setw(returnNumber(lengthManuf, product[p].returnManufacturer().length())) << product[p].returnManufacturer();
						ouf << setw(lengthManuf + 1 - returnNumber(lengthManuf, product[p].returnManufacturer().length())) << "|" << " ";
						str1.clear();
						str1 << product[p].returnDay();
						str1 >> s1;
						str2 << product[p].returnMonth();
						str2 >> s2;
						str3 << product[p].returnYear();
						str3 >> s3;
						string s;
						if (s1.length() == 2)
							s = s1 + ".";
						else
							s = "0" + s1 + ".";
						if (s2.length() == 2)
							s += s2 + ".";
						else
							s += "0" + s2 + ".";
						s += s3;
						ouf << setw(returnNumber(14, s.length())) << s << setw(15 - returnNumber(14, s.length()));
						ouf << "|\n";
						for (int i = 0; i < width + 2; i++)
							ouf << "-";
						ouf << "\n";
						kol += product[p].returnAmount();
						sum += product[p].returnPrice() * product[p].returnAmount();
					}
					ouf.unsetf(ios::right);
					break;
				}
			}
		}
		string buf = to_string(kol);
		ouf << setw(width - buf.length()) << "Количество проданного товара: " << kol << "\n" << setw(width - buf.length()) << "Сумма проданного товара: " << sum << "\n";
		ouf.close();
		SetColor(2, 0);
		cout << "Отчёт успешно сформирован" << endl;
		Sleep(2500);
		SetColor(15, 0);
		return 1;
	}
	catch (double)
	{
		SetColor(4, 0);
		cout << "Введена некорректная дата!" << endl;
		SetColor(15, 0);
		return 0;
	}

}

void CreatePriceList(vector<Section> vectorSection)
{
	ofstream ouf;
	ouf.setf(ios::right);
	ouf.open("Price.txt", ios_base::out);
	SYSTEMTIME st;
	GetLocalTime(&st);
	int day, month, year, hour, minute;
	day = st.wDay;
	month = st.wMonth;
	year = st.wYear;
	hour = st.wHour;
	minute = st.wMinute;
	int width, buf, name = 1, price = 1, vendor_code = 1, bufn, bufv, bufp, number = 0;
	for (size_t i = 0; i < vectorSection.size(); i++)
		for (size_t j = 0; j < (*vectorSection[i].returnVectorSubsection()).size(); j++)
		{
			vector<Product> product = (*(*vectorSection[i].returnVectorSubsection())[j].returnProduct());
			if (product.size() == 0)
				break;
			buf = product[0].returnWidthTable(product);
			bufp = product[0].returnLengthPrice(product);
			bufn = product[0].returnLengthName(product);
			bufv = product[0].returnLengthKod(product);
			if (bufn > name)
				name = bufn;
			if (bufp > price)
				price = bufp;
			if (bufv > vendor_code)
				vendor_code = bufv;
		}
	if (price < 17)
		price = 17;
	width = name + vendor_code + price + 7;
	ouf.setf(ios::left);
	ouf << setw(45) << "ПРАЙС-ЛИСТ КОМПАНИИ ОТ ";
	ouf.unsetf(ios::left);
	if (hour < 10)
		ouf << "0" << hour;
	else
		ouf << hour;
	if (minute < 10)
		ouf << ":0" << minute << " ";
	else
		ouf << ":" << minute << " ";
	if (day < 10)
		ouf << "0" << day << ".";
	else
		ouf << day << ":";
	if (month < 10)
		ouf << "0" << month << ".";
	else
		ouf << month << ".";
	ouf << year << "\n";
	for (int j = 0; j < width + 2; j++)
		ouf << "-";
	ouf << "\n";
	ouf << "|" << "  №  " << "|" << setw(returnNumber(name, 12)) << "Наименование" << setw(name + 1 - returnNumber(name, 12)) << "|";
	ouf << setw(returnNumber(vendor_code, 7)) << "Артикул" << setw(vendor_code + 1 - returnNumber(vendor_code, 7)) << "|";
	ouf << setw(returnNumber(price, 15)) << "Стоимость, руб." << setw(price + 1 - returnNumber(price, 15)) << "|\n";
	for (int j = 0; j < width + 2; j++)
		ouf << "-";
	ouf << "\n";
	for (size_t i = 0; i < vectorSection.size(); i++)
	{
		ouf << "| " << setw(returnNumber(width, vectorSection[i].returnName().length())) << vectorSection[i].returnName() << setw(width + 1 - returnNumber(width, vectorSection[i].returnName().length())) << "|\n";
		for (int j = 0; j < width + 2; j++)
			ouf << "-";
		ouf << "\n";
		for (size_t j = 0; j < (*vectorSection[i].returnVectorSubsection()).size(); j++)
		{
			ouf << "| " << setw(returnNumber(width, (*vectorSection[i].returnVectorSubsection())[j].returnName().length())) << (*vectorSection[i].returnVectorSubsection())[j].returnName() << setw(width + 1 - returnNumber(width, (*vectorSection[i].returnVectorSubsection())[j].returnName().length())) << "|\n";
			for (int k = 0; k < width + 2; k++)
				ouf << "-";
			ouf << "\n";
			vector<Product> product = (*(*vectorSection[i].returnVectorSubsection())[j].returnProduct());
			for (size_t k = 0; k < product.size(); k++)
			{
				number++;
				string s1;
				stringstream str;
				str << number;
				str >> s1;
				str.clear();
				ouf << "|" <<setw(returnNumber(5, s1.length())) << number << setw(6 - returnNumber(5, s1.length())) << "|" << setw(returnNumber(name, product[k].returnName().length())) << product[k].returnName() << setw(name + 1 - returnNumber(name, product[k].returnName().length())) << "|";
				str << product[k].returnKod();
				str >> s1;
				ouf << setw(returnNumber(vendor_code, s1.length())) << s1 << setw(vendor_code + 1 - returnNumber(vendor_code, s1.length())) << "|";
				str.clear();
				str << product[k].returnPrice();
				str >> s1;
				ouf << setw(returnNumber(price, s1.length())) << s1 << setw(price + 1 - returnNumber(price, s1.length())) << "|\n";
				for (int p = 0; p < width + 2; p++)
					ouf << "-";
				ouf << "\n";
			}
		}
	}
	SetColor(2, 0);
	cout << "Прайс-лист успешно сформирован" << endl;
	Sleep(2500);
	SetColor(15, 0);
	ouf.unsetf(ios::right);
	ouf.close();
}


int main()
{
	vector <Section> sections;
	vector <Account> accounts;
	vector <User> users;
	vector <Admin> admins;
	Account account;
	User user;
	int whatAcc;
	system("chcp 866");
	setlocale(LC_ALL, "ru");
	system("cls");
	int userChoice;
	read(&sections, "COURSE.DAT");
	read(&admins, "ADMINS.DAT");
	read(&users, "USERS.DAT");
	while (true)
	{
		system("cls");
		try
		{
			system("cls");
			string s[4] = { "Войти", "Создать аккаунт", "Выход" };
			menu(s, 3, 0, "");
			userChoice = choice(s, 3, "");
			switch (userChoice)
			{
			case 1:
				whatAcc = sign_in(users, admins);
				if (whatAcc == -2)
					menuUser(&sections);
				else
					menuAdmin(&users, &admins, whatAcc, &sections);
				break;
			case 2:
				create_new_user(&users, &admins, 1);
				break;
			case 3:
				write(admins, "ADMINS.DAT");
				write(users, "USERS.DAT");
				write(sections);
				return 1;
			}
		}
		catch (int)
		{
			cout << "\nФайл с аккаунтами пуст! Создаётся аккаунт...\n";
			Admin account;
			create_new_user(&users, &admins, 0);
			write(admins, "ADMINS.DAT");
		}
	}
	return 0;
}


void sell(vector <Section>* vec)
{
	int size, number1, number, i, number_to_sell, amount;
	string* s2, * s3, section = "Выберите раздел", subsection = "Выберите подраздел";
	while (true)
	{
		system("cls");
		size = (*vec).size() + 2;
		s2 = new string[size];
		for (i = 0; i < size - 2; i++)
		{
			s2[i] = (*vec)[i].returnName();
		}
		s2[i] = "Назад";
		menu(s2, size - 1, 0, section);
		number = choice(s2, size - 1, section);
		if (s2[number - 1] == "Назад")
			break;
		size = (*(*vec)[number - 1].returnVectorSubsection()).size() + 2;
		s3 = new string[size];
		for (i = 0; i < size - 2; i++)
		{
			s3[i] = (*(*vec)[number - 1].returnVectorSubsection())[i].returnName();
		}
		s3[i] = "Назад";
		menu(s3, size - 1, 0, subsection);
		number1 = choice(s3, size - 1, subsection);
		if (s3[number1 - 1] != "Назад")
		{
			viewProducts(*vec, number - 1, number1 - 1, s2[number - 1], s3[number1 - 1]);
			cout << "Введите порядковый номер товара, который хотите продать: ";
			cin >> number_to_sell;
			cout << "Введите количество товара, которое хотите продать: ";
			cin >> amount;
			int kol = (*(*(*vec)[number - 1].returnVectorSubsection())[number1 - 1].returnProduct())[number_to_sell - 1].decreaseAmount(amount);
			if (kol == -1)
				return;
			ofstream ouf;
			Product product, product1;
			product = (*(*(*vec)[number - 1].returnVectorSubsection())[number1 - 1].returnProduct())[number_to_sell - 1];
			product1 = Product(product);
			product1.setDate();
			product1.setAmount(amount);
			if (kol == 0)
			{
				(*(*(*vec)[number - 1].returnVectorSubsection())[number1 - 1].returnProduct()).erase((*(*(*vec)[number - 1].returnVectorSubsection())[number1 - 1].returnProduct()).begin() + number_to_sell - 1);
			}
			ouf.open("ITEMSOLT.DAT", ios_base::app | ios_base::binary);
			ouf << s2[number - 1] << "|" << s3[number1 - 1];
			ouf << product1;
			ouf.close();
			break;
		}
	}
}