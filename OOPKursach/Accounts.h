#pragma once
#include "Include.h"
void enterDate(int* day, int* month, int* year);

string encrypt(string str);
string decrypt(string str);
class Account
{
protected:
	string login, password, file;
public:
	Account()
	{
		login = password = "";
	}
	Account(string login, string password)
	{
		this->login = login;
		this->password = password;
	}
	~Account() {}
	string returnLogin() { return login; }
	string returnPassword() { return password; }
	void setData(string login, string password);
	int returnLenghtLogin(vector <Account> vector);
	int returnLenghtPassword(vector <Account> vector);
	friend istream& operator >>(istream& s, Account& e);
	friend ostream& operator <<(ostream& s, Account& e);
};

class User :public virtual Account
{
public:
	User() { file = "USERS.DAT"; };
	User(string login, string password);
	void SortByLogin(vector <User>* vector);
	int returnLenghtLogin(vector <User> vector);
	int returnLenghtPassword(vector <User> vector);
	void print(vector <User> vector);
};
class Admin : public virtual Account
{
public:
	Admin() { file = "ADMINS.DAT"; };
	Admin(string login, string password);
	void SortByLogin(vector <Admin>* vector);
	int returnLenghtLogin(vector <Admin> vector);
	int returnLenghtPassword(vector <Admin> vector);
	void print(vector <Admin> vector);
};
bool search_login(string login, vector <Admin> veca, vector <User> vecu);
template <class T>
void create_admin(vector <T>* vec, string login, string password);

int search_account(string login, string password, vector<Admin> veca, vector <User> vecu);

void create_new_user(vector <User>* vecu, vector <Admin>* veca, int n);

string enterLogin();
string sign_in_password();
int sign_in(vector<User> vecu, vector <Admin>veca);
template <class T>
void deleteAccount(vector <T>* vector_of_users, int n);
void editAccount(vector <User>* vector_of_users);



void editAccount(vector <Admin>* vector_of_users);

void menuEditAccount(vector <Admin>* veca, vector <User>* vecu);

void menuDeleteAccount(vector <Admin>* veca, vector<User>* vecu, int n);
template <class T>
void viewAccounts(vector <T> ob);
void viewAccounts(string str, vector <Admin> vector);

void viewAccounts(string str, vector <User> vector);

void searchAccountsByLogin(vector <Admin> veca, vector <User> vecu, string login);
void searchAccountByPassword(vector <Admin> veca, vector <User> vecu, string password);
void menuSearchAccount(vector <User> vecu, vector <Admin> veca);