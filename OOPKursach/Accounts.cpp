#include "Accounts.h"

void enterDate(int* day, int* month, int* year)
{
	string buf;
	int ch;
	int k = 0, n = 1;
	while (true)
	{
		while ((ch = _getch()) != '\r')
		{
			if (k == 2)
				n = 3;
			if (int(buf.length()) > n && ch != 8)
				continue;
			if (ch < 48 || ch > 57)
			{
				if (ch == 8)
				{
					if (buf.length() != 0)
					{
						cout << (char)8 << " " << (char)8;
						if (!buf.empty())
							buf.erase(buf.length() - 1);
					}
					continue;
				}
				ch = _getch();
				if (ch > 57 || ch < 48)
					continue;
				buf.push_back(ch);
				_putch(ch);
			}
			else
			{
				buf.push_back(ch);
				_putch(ch);
			}
		}
		if (ch == '\r' && buf.length() == 0)
			continue;
		k++;
		if (k == 1)
			*day = stoi(buf);
		else
		{
			if (k == 2)
				*month = stoi(buf);
			else
			{
				*year = stoi(buf);
				break;
			}
		}
		buf.clear();
		cout << ".";
	}

}
void Account::setData(string login, string password)
{
	this->login = login;
	this->password = password;
}
int Account::returnLenghtLogin(vector <Account> vector)
{
	int buf = vector[0].login.length();
	for (size_t i = 1; i < vector.size(); i++)
	{
		if (int(vector[i].login.length()) > buf)
			buf = vector[i].login.length();
	}
	return buf + 6;
}
int Account::returnLenghtPassword(vector <Account> vector)
{
	int buf = vector[0].password.length();
	for (size_t i = 1; i < vector.size(); i++)
	{
		if (int(vector[i].password.length()) > buf)
			buf = vector[i].password.length();
	}
	return buf + 6;
}
string encrypt(string str)
{
	for (int i = 0; i < int(str.length()); i++)
		str[i] += i + 1;
	return str;
}
string decrypt(string str)
{
	for (int i = 0; i < int(str.length()); i++)
		str[i] -= i + 1;
	return str;
}
istream& operator >>(istream& s, Account& e)
{
	s >> e.login >> e.password;
	e.password = decrypt(e.password);
	e.login = decrypt(e.login);
	return s;
}
ostream& operator <<(ostream& s, Account& e)
{
	e.password = encrypt(e.password);
	e.login = encrypt(e.login);
	s << e.login << " " << e.password << "\n";
	return s;
}

User::User(string login, string password)
{
	this->login = login;
	this->password = password;
}
void User::SortByLogin(vector <User>* vector)
{
	sort((*vector).begin(), (*vector).end(), [](const User& a, const User& b)
		{
			return a.login > b.login;
		}
	);
}
int User::returnLenghtLogin(vector <User> vector)
{
	int buf = vector[0].login.length();
	for (size_t i = 1; i < vector.size(); i++)
	{
		if (int(vector[i].login.length()) > buf)
			buf = vector[i].login.length();
	}
	return buf + 6;
}
int User::returnLenghtPassword(vector <User> vector)
{
	int buf = vector[0].password.length();
	for (size_t i = 1; i < vector.size(); i++)
	{
		if (int(vector[i].password.length()) > buf)
			buf = vector[i].password.length();
	}
	return buf + 6;
}
void User::print(vector <User> vector)
{
	string str = "";
	cout.setf(ios::right);
	SetColor(14, 0);
	cout << setw(returnNumber(returnLenghtLogin(vector), login.length())) << login;
	SetColor(15, 0);
	cout << setw(returnLenghtLogin(vector) + 1 - returnNumber(returnLenghtLogin(vector), login.length())) << "|"
		<< setw(returnNumber(returnLenghtPassword(vector), password.length()));
	SetColor(14, 0);
	for (size_t i = 0; i < password.length(); i++)
		str += "*";
	cout << str << setw(returnLenghtPassword(vector) + 1 - returnNumber(returnLenghtPassword(vector), password.length()));
	SetColor(15, 0);
	cout << "|" << endl;
	for (int i = 0; i < returnLenghtPassword(vector) + returnLenghtLogin(vector) + 9; i++)
		cout << "-";
	cout << endl;
	cout.unsetf(ios::right);
}

Admin::Admin(string login, string password)
{
	this->login = login;
	this->password = password;
}
void Admin::SortByLogin(vector <Admin>* vector)
{
	sort((*vector).begin(), (*vector).end(), [](const Admin& a, const Admin& b)
		{
			return a.login > b.login;
		}
	);
}
int Admin::returnLenghtLogin(vector <Admin> vector)
{
	int buf = vector[0].login.length();
	for (size_t i = 1; i < vector.size(); i++)
	{
		if (int(vector[i].login.length()) > buf)
			buf = vector[i].login.length();
	}
	return buf + 6;
}
int Admin::returnLenghtPassword(vector <Admin> vector)
{
	size_t buf = vector[0].password.length();
	for (size_t i = 1; i < vector.size(); i++)
	{
		if (vector[i].password.length() > buf)
			buf = vector[i].password.length();
	}
	return buf + 6;
}
void Admin::print(vector <Admin> vector)
{
	string str = "";
	cout.setf(ios::right);
	SetColor(14, 0);
	cout << setw(returnNumber(returnLenghtLogin(vector), login.length())) << login;
	SetColor(15, 0);
	cout << setw(returnLenghtLogin(vector) + 1 - returnNumber(returnLenghtLogin(vector), login.length())) << "|"
		<< setw(returnNumber(returnLenghtPassword(vector), password.length()));
	SetColor(14, 0);
	for (size_t i = 0; i < password.length(); i++)
		str += "*";
	cout << str << setw(returnLenghtPassword(vector) + 1 - returnNumber(returnLenghtPassword(vector), password.length()));
	SetColor(15, 0);
	cout << "|" << endl;
	for (int i = 0; i < returnLenghtPassword(vector) + returnLenghtLogin(vector) + 9; i++)
		cout << "-";
	cout << endl;
	cout.unsetf(ios::right);
}


bool search_login(string login, vector <Admin> veca, vector <User> vecu)
{
	for (size_t i = 0; i < veca.size(); i++)
		if (veca[i].returnLogin() == login)
			return true;
	for (size_t i = 0; i < vecu.size(); i++)
		if (vecu[i].returnLogin() == login)
			return true;
	return false;
}
template <class T>
void create_admin(vector <T>* vec, string login, string password)
{
	T admin = T(login, password);
	(*vec).push_back(admin);
}

int search_account(string login, string password, vector<Admin> veca, vector <User> vecu)
{
	Account user = Account(" ", " ");
	for (size_t i = 0; i < veca.size(); i++)
		if (veca[i].returnLogin() == login && veca[i].returnPassword() == password)
		{
			return i;
		}
	for (size_t i = 0; i < vecu.size(); i++)
		if (vecu[i].returnLogin() == login && vecu[i].returnPassword() == password)
		{
			return -2;
		}
	return -1;
}

void create_new_user(vector <User>* vecu, vector <Admin>* veca, int n)
{
	string login, password, password1, s1[4] = { "Создать администратора", "Создать пользователя", "Назад" };
	int userChoice = 2;

	if (n == 0)
	{
		system("cls");
		menu(s1, 3, 0, "");
		userChoice = choice(s1, 3, "");
		if (userChoice == 3)
			return;
	}
	else
	{
		cout << "Вы можете создать только пользователя" << endl;
	}

	while (true)
	{
		bool k = true;
		login = enterLogin();
		if (login.length() < 6 || login.length() > 32)
		{
			SetColor(4, 0);
			cout << "Логин должен состоять из не менее 6 символов и не более 32" << endl;
			SetColor(15, 0);
		}
		else
		{
			if (search_login(login, *veca, *vecu))
			{
				system("cls");
				SetColor(4, 0);
				cout << "Аккаунт с таким логином уже существует" << endl;
				SetColor(15, 0);
			}
			else
				break;
		}
	}
	while (true)
	{
		cout << "Для создания аккаунта требуется ввести два раза пароль, который должен совпасть" << endl;
		password = sign_in_password();
		cout << endl;
		if (password.length() < 6 || password.length() > 32)
		{
			SetColor(4, 0);
			cout << "Пароль должен состоять из не менее 6 символов и не более 32!\n";
			SetColor(15, 0);
		}
		else
		{
			password1 = sign_in_password();
			if (!password.compare(password1))
			{
				break;
			}
			else
			{
				SetColor(4, 0);
				cout << "\nПароли не совпадают! Попробуйте снова" << endl;
				SetColor(15, 0);
			}
		}
	}
	if (userChoice == 1)
	{
		create_admin(veca, login, password);

	}
	else
	{
		User user = User(login, password);
		(*vecu).push_back(user);
	}
	SetColor(2, 0);
	cout << "\nАккаунт успешно создан!" << endl;
	Sleep(1000);
	SetColor(15, 0);
}


string enterLogin()
{
	string login;
	int ch;
	while (true)
	{
		cout << "Введите логин: ";
		while ((ch = _getch()) != '\r')
		{
			if (ch == 0)
			{
				ch = _getch();
				if ((ch > 58 && ch < 69) || ch > 79 && ch < 84 || ch > 70 && ch < 74 || ch == 75 || ch == 77 || ch == 79)
					continue;
				login.push_back(ch);
				_putch(ch);
			}
			else
			{
				if (ch == 8)
				{
					if (login.length() != 0)
					{
						cout << (char)8 << " " << (char)8;
						if (!login.empty())
							login.erase(login.length() - 1);
					}
					continue;
				}
				if (ch == 27 || ch == 9 || ch == 96 || ch == 32)
					continue;
				if (ch == 224)
				{
					ch = _getch();
					if (ch == 134 || ch > 78 && ch < 84 || ch > 70 && ch < 74 || ch == 75 || ch == 77)
						continue;
				}
				login.push_back(ch);
				_putch(ch);
			}
		}
		if (login.length())
		{
			cout << endl;
			return login;
		}
		else
			cout << "\nЛогин пуст!" << endl;
	}
}
string sign_in_password()
{
	while (true)
	{
		string password;
		int ch;
		cout << "Введите пароль: ";
		while ((ch = _getch()) != '\r')
		{
			if (ch == 0)
			{
				ch = _getch();
				if ((ch > 58 && ch < 69) || ch > 79 && ch < 84 || ch > 70 && ch < 74 || ch == 75 || ch == 77 || ch == 79)
					continue;
				password.push_back(ch);
				_putch('*');
			}
			else
			{
				if (ch == 8)
				{
					if (password.length() != 0)
					{
						cout << (char)8 << " " << (char)8;
						if (!password.empty())
							password.erase(password.length() - 1);
					}
					continue;
				}
				if (ch == 27 || ch == 9 || ch == 96 || ch == 32)
					continue;
				if (ch == 224)
				{
					ch = _getch();
					if (ch == 134 || ch > 78 && ch < 84 || ch > 70 && ch < 74 || ch == 75 || ch == 77)
						continue;
				}
				password.push_back(ch);
				_putch('*');
			}
		}
		if (password.length())
			return password;
		else
			cout << "\nПароль пуст!" << endl;
	}
}
int sign_in(vector<User> vecu, vector <Admin>veca)
{
	Account account;
	int t = 0, isAcc;
	string password, login;
	do
	{
		if (t)
		{
			SetColor(4, 0);
			cout << "Вы ввели неверный логин или пароль. Попробуйте ещё раз" << endl;
			SetColor(15, 0);
		}
		login = enterLogin();
		password = sign_in_password();
		isAcc = search_account(login, password, veca, vecu);
		if (t == 2)
		{
			SetColor(4, 0);
			cout << "\nПопробуйте ещё раз через ";
			cout << "30";
			cout << " секунд(-ы)";
			cout << (char)8 << (char)8 << (char)8 << (char)8 << (char)8 << (char)8 << (char)8 << (char)8 << (char)8 << (char)8 << (char)8;
			for (int i = 30; i > 0; i--)
			{
				if (i > 8)
				{
					cout << (char)8 << " " << (char)8;
					if (i == 9)
						cout << (char)8 << "  ";
				}
				cout << (char)8 << " " << (char)8;
				cout << i;
				Sleep(1000);
			}
			t = -1;
		}
		t++;
		Sleep(900);
		system("cls");
		SetColor(15, 0);
	} while (isAcc == -1);
	return isAcc;
}

template <class T>
void deleteAccount(vector <T>* vector_of_users, int n)
{
	size_t number;
	cout << "Введите порядковый номер удаляемой записи: ";
	cin >> number;
	if (number < 0 || number >(*vector_of_users).size())
	{
		SetColor(4, 0);
		cout << "Номер введён неверно!" << endl;
		SetColor(15, 0);
		Sleep(2000);
		return;;
	}
	else
	{
		if (vector_of_users->size() == 1 && n == -1)
		{
			cout << "Вы не можете удалить единственный аккаунт администратора!" << endl;
			Sleep(3000);
			return;
		}
		(*vector_of_users).erase((*vector_of_users).begin() + number - 1);
	}
}
void editAccount(vector <User>* vector_of_users)
{
	bool k;
	int number, kod;
	string login, password, s, s1[4] = { "Логин", "Пароль", "Назад" };
	cout << "Введите порядковый номер: ";
	cin >> number;
	while (!cin || number < 0)
	{
		cout << "Введите корректный номер!!!" << endl;
		cout << "Номер: ";
		cin.clear();
		cin.ignore();
		cin >> number;
	}
	system("cls");
	s = "Что Вы хотите изменить?";
	menu(s1, 3, 0, s);
	kod = choice(s1, 3, s);
	switch (kod)
	{
	case 1:
		getline(cin, login);
		do
		{
			k = false;
			login = enterLogin();
			for (size_t i = 0; i < (*vector_of_users).size(); i++)
				if ((*vector_of_users)[i].returnLogin() == login && login != (*vector_of_users)[number - 1].returnLogin())
				{
					system("cls");
					SetColor(4, 0);
					cout << "Этот логин уже используется" << endl;
					SetColor(15, 0);
					k = true;
				}
		} while (k);
		(*vector_of_users)[number - 1].setData(login, (*vector_of_users)[number - 1].returnPassword());
		break;
	case 2:
		getline(cin, password);
		password = sign_in_password();
		(*vector_of_users)[number - 1].setData((*vector_of_users)[number - 1].returnLogin(), password);
		break;
		break;
	default:
		break;
	}
	SetColor(2, 0);
	cout << "\nАккаунт успешно изменён" << endl;
	SetColor(15, 0);
	Sleep(2000);
}



void editAccount(vector <Admin>* vector_of_users)
{
	bool k;
	int number, kod;
	string login, password, s, s1[4] = { "Логин", "Пароль", "Назад" };
	cout << "Введите порядковый номер: ";
	cin >> number;
	while (!cin || number < 0)
	{
		cout << "Введите корректный номер!!!" << endl;
		cout << "Номер: ";
		cin.clear();
		cin.ignore();
		cin >> number;
	}
	system("cls");
	s = "Что Вы хотите изменить?";
	menu(s1, 3, 0, s);
	kod = choice(s1, 3, s);
	switch (kod)
	{
	case 1:
		getline(cin, login);
		do
		{
			k = false;
			login = enterLogin();
			for (size_t i = 0; i < (*vector_of_users).size(); i++)
				if ((*vector_of_users)[i].returnLogin() == login && login != (*vector_of_users)[number - 1].returnLogin())
				{
					system("cls");
					SetColor(43, 0);
					cout << "Этот логин уже используется" << endl;
					SetColor(15, 0);
					k = true;
				}
		} while (k);
		(*vector_of_users)[number - 1].setData(login, (*vector_of_users)[number - 1].returnPassword());
		break;
	case 2:
		getline(cin, password);
		password = sign_in_password();
		(*vector_of_users)[number - 1].setData((*vector_of_users)[number - 1].returnLogin(), password);
		break;
		break;
	default:
		break;
	}
	SetColor(2, 0);
	cout << "Аккаунт успешно изменён" << endl;
	SetColor(15, 0);
	Sleep(2000);
}

void menuEditAccount(vector <Admin>* veca, vector <User>* vecu)
{
	int userChoice;
	string s[4] = { "Изменить данные администратора", "Изменить данные пользователя", "Назад" };
	while (true)
	{
		menu(s, 3, 0, "");
		userChoice = choice(s, 3, "");
		switch (userChoice)
		{
		case 1:
			viewAccounts("Аккаунты администраторов", *veca);
			viewAccounts(*veca);
			editAccount(veca);
			system("cls");
			cout << "После редактирования: " << endl;
			viewAccounts("Аккаунты администраторов", *veca);
			viewAccounts(*veca);
			system("pause");
			return;
		case 2:
			viewAccounts("Аккаунты пользователей", *vecu);
			viewAccounts(*vecu);
			editAccount(vecu);
			system("cls");
			cout << "После редактирования: " << endl;
			viewAccounts("Аккаунты пользователей", *vecu);
			viewAccounts(*vecu);
			system("pause");
			return;
		case 3:
			return;
		default:
			cout << "Введено некорректное значение" << endl;
			break;
		}
	}
}

void menuDeleteAccount(vector <Admin>* veca, vector<User>* vecu, int n)
{
	int userChoice;
	string s1[4] = { "Удалить аккаунт администратора", "Удалить аккаунт пользователя", "Назад" };
	system("cls");
	menu(s1, 3, 0, "");
	userChoice = choice(s1, 3, "");
	switch (userChoice)
	{
	case 1:
		viewAccounts("Аккаунты администраторов", *veca);
		viewAccounts(*veca);
		deleteAccount(veca, -1);
		break;
	case 2:
		viewAccounts("Аккаунты пользователей", *vecu);
		viewAccounts(*vecu);
		deleteAccount(vecu, n);
		break;
	default:
		break;
	}
}
template <class T>
void viewAccounts(vector <T> ob)
{
	cout.setf(ios::right);
	for (size_t i = 0; i < ob.size(); i++)
	{
		cout << "|" << setw(3);
		SetColor(6, 0);
		cout << i + 1 << setw(3);
		SetColor(15, 0);
		cout << "|";
		ob[i].print(ob);
	}
	cout.unsetf(ios::right);
}
void viewAccounts(string str, vector <Admin> vector)
{
	if (vector.size() == 0)
		return;
	cout.setf(ios::right);
	for (int i = 0; i < vector[0].returnLenghtPassword(vector) + vector[0].returnLenghtLogin(vector) + 9; i++)
		cout << "-";
	cout << endl;
	cout << "|" << setw(returnNumber(vector[0].returnLenghtPassword(vector) + vector[0].returnLenghtLogin(vector) + 7, str.length()));
	SetColor(7, 0);
	cout << str << setw(vector[0].returnLenghtPassword(vector) + vector[0].returnLenghtLogin(vector) + 8 - returnNumber(vector[0].returnLenghtPassword(vector) + vector[0].returnLenghtLogin(vector) + 7, str.length()));
	SetColor(15, 0);
	cout << "|" << endl;
	for (int i = 0; i < vector[0].returnLenghtPassword(vector) + vector[0].returnLenghtLogin(vector) + 9; i++)
		cout << "-";
	cout << endl << "|";
	SetColor(11, 0);
	cout << setw(returnNumber(5, 1)) << "№" << setw(6 - returnNumber(5, 1));
	SetColor(15, 0);
	int lengthLogin = vector[0].returnLenghtLogin(vector), lengthPassword = vector[0].returnLenghtPassword(vector);
	cout << "|" << setw(returnNumber(lengthLogin, 5));
	SetColor(11, 0);
	cout << "Логин" << setw(lengthLogin + 1 - returnNumber(lengthLogin, 5));
	SetColor(15, 0);
	cout << "|";
	SetColor(11, 0);
	cout << setw(returnNumber(lengthPassword, 6)) << "Пароль" << setw(lengthPassword + 1 - returnNumber(lengthPassword, 6));
	SetColor(15, 0);
	cout << "|" << endl;
	for (int i = 0; i < vector[0].returnLenghtPassword(vector) + vector[0].returnLenghtLogin(vector) + 9; i++)
		cout << "-";
	cout << endl;
	cout.unsetf(ios::right);
}

void viewAccounts(string str, vector <User> vector)
{
	if (vector.size() == 0)
		return;
	cout.setf(ios::right);
	for (int i = 0; i < vector[0].returnLenghtPassword(vector) + vector[0].returnLenghtLogin(vector) + 9; i++)
		cout << "-";
	cout << endl;
	cout << "|" << setw(returnNumber(vector[0].returnLenghtPassword(vector) + vector[0].returnLenghtLogin(vector) + 7, str.length()));
	SetColor(7, 0);
	cout << str << setw(vector[0].returnLenghtPassword(vector) + vector[0].returnLenghtLogin(vector) + 8 - returnNumber(vector[0].returnLenghtPassword(vector) + vector[0].returnLenghtLogin(vector) + 7, str.length()));
	SetColor(15, 0);
	cout << "|" << endl;
	for (int i = 0; i < vector[0].returnLenghtPassword(vector) + vector[0].returnLenghtLogin(vector) + 9; i++)
		cout << "-";
	cout << endl << "|";
	SetColor(11, 0);
	cout << setw(returnNumber(5, 1)) << "№" << setw(6 - returnNumber(5, 1));
	SetColor(15, 0);
	int lengthLogin = vector[0].returnLenghtLogin(vector), lengthPassword = vector[0].returnLenghtPassword(vector);
	cout << "|" << setw(returnNumber(lengthLogin, 5));
	SetColor(11, 0);
	cout << "Логин" << setw(lengthLogin + 1 - returnNumber(lengthLogin, 5));
	SetColor(15, 0);
	cout << "|";
	SetColor(11, 0);
	cout << setw(returnNumber(lengthPassword, 6)) << "Пароль" << setw(lengthPassword + 1 - returnNumber(lengthPassword, 6));
	SetColor(15, 0);
	cout << "|" << endl;
	for (int i = 0; i < vector[0].returnLenghtPassword(vector) + vector[0].returnLenghtLogin(vector) + 9; i++)
		cout << "-";
	cout << endl;
	cout.unsetf(ios::right);
}

void searchAccountsByLogin(vector <Admin> veca, vector <User> vecu, string login)
{
	cout.setf(ios::right);
	for (size_t i = 0; i < veca.size(); i++)
	{
		if (veca[i].returnLogin() == login)
		{
			viewAccounts("Аккаунт администратора", veca);
			cout << "|" << setw(3) << i + 1 << setw(3) << "|";
			veca[i].print(veca);
			cout.unsetf(ios::right);
			system("pause");
			return;
		}
	}
	for (size_t i = 0; i < vecu.size(); i++)
	{
		if (vecu[i].returnLogin() == login)
		{
			viewAccounts("Аккаунт пользователя", vecu);
			cout << "|" << setw(3) << i + 1 << setw(3) << "|";
			vecu[i].print(vecu);
			cout.unsetf(ios::right);
			system("pause");
			return;
		}
	}
	SetColor(4, 0);
	cout << "Аккаунта с таким логином не найдено" << endl;
	SetColor(15, 0);
	Sleep(1000);
}
void searchAccountByPassword(vector <Admin> veca, vector <User> vecu, string password)
{
	cout.setf(ios::right);
	int k = 0, b = 0;
	for (size_t i = 0; i < veca.size(); i++)
	{
		if (veca[i].returnPassword() == password)
		{
			if (k == 0)
			{
				viewAccounts("Аккаунт администратора", veca);
				k++;
			}
			cout << "|" << setw(3) << i + 1 << setw(3) << "|";
			veca[i].print(veca);
		}
	}
	for (size_t i = 0; i < vecu.size(); i++)
	{
		if (vecu[i].returnPassword() == password)
		{
			if (b == 0)
			{
				viewAccounts("Аккаунт пользователя", vecu);
				b++;
			}
			cout << "|" << setw(3) << i + 1 << setw(3) << "|";
			vecu[i].print(vecu);
		}
	}
	if (k == 0 && b == 0)
	{
		SetColor(4, 0);
		cout << "Аккаунтов с таким паролем нет" << endl;
		SetColor(15, 0);
	}
	cout.unsetf(ios::right);
	system("pause");
}
void menuSearchAccount(vector <User> vecu, vector <Admin> veca)
{
	int userChoice;
	string buf;
	string s1[4] = { "Найти по логину", "Найти по паролю", "Назад" };
	menu(s1, 3, 0, "");
	userChoice = choice(s1, 3, "");
	switch (userChoice)
	{
	case 1:
		cout << "Введите логин: ";
		cin >> buf;
		searchAccountsByLogin(veca, vecu, buf);
		break;
	case 2:
		cout << "Введите пароль: ";
		cin >> buf;
		searchAccountByPassword(veca, vecu, buf);
		break;
	default:
		break;
	}
}