#pragma once
#include "Include.h"

class Section;
class Subsection;
class Product;

class Section;

int searchSection(vector <Subsection> vec, string name);
int searchSection(vector <Section> vec, string name);

class Product
{
protected:
	string name, manufacturer;
	double price;
	int vendor_code, amount, day, month, year;
public:
	Product() 
	{
		name = "";
		manufacturer = "";
		price = 0;
		vendor_code = 0;
		amount = 0;
		day = 0;
		month = 0;
		year = 0;
	}
	int returnDay() { return day; }
	int returnMonth() { return month; }
	int returnYear() { return year; }
	double returnPrice() { return price; }
	string returnName() { return name; }
	int returnKod() { return vendor_code; }
	string returnManufacturer() { return manufacturer; }
	void Product1(const Product&);
	void setDate();
	void setAmount();
	void setPrice();
	void setKod();
	void setName();
	void setManufacturer();
	void setData();
	void setAmount(int);
	int returnAmount() { return amount; }
	int decreaseAmount(int number);
	int returnLengthNumber(vector <Product> vector);
	int returnLengthName(vector <Product> vector);
	int returnLengthManufacturer(vector <Product> vector);
	int returnLengthPrice(vector <Product> vector);
	int returnLengthKod(vector <Product> vector);
	int returnLengthAmount(vector <Product> vector);
	int returnWidthTable(vector <Product> vector);
	void print(vector <Product>);
	void print(ostream&, vector <Product>);
	friend istream& operator >>(istream& s, Product& e);
	friend ostream& operator << (ostream& s, Product& e);
	void SortByName(vector <Product>*);
	void SortByDate(vector <Product>*);
	void SortByAmount(vector <Product>*);
	void SortByPrice(vector <Product>*);
	static void headTable(vector <Product> product, string section, string subsection)
	{
		if (product.size() == 0)
			return;
		Product buf = product[0];
		int lengthName = buf.returnLengthName(product), lengthAmount = buf.returnLengthAmount(product), lengthNumber = buf.returnLengthNumber(product),
			lengthKod = buf.returnLengthKod(product), lengthPrice = buf.returnLengthPrice(product), lengthManuf = buf.returnLengthManufacturer(product);
		int width = product[0].returnWidthTable(product);
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
	}
	static void SearchByName(vector <Product> vector, string name, string section, string subsection)
	{
		for (size_t i = 0; i < vector.size(); i++)
		{
			if (vector[i].returnName() == name)
			{
				headTable(vector, section, subsection);
				cout << "| 1 |";
				vector[i].print(vector);
				return;
			}
		}
		SetColor(4, 0);
		cout << "Такого товара в этом разделе нет!" << endl;
		SetColor(15, 0);
	}
	static void SearchByAmount(vector <Product> vector, int amount, string section, string subsection)
	{
		int k = 0;
		for (size_t i = 0; i < vector.size(); i++)
		{
			if (vector[i].returnAmount() >= amount)
			{
				k++;
				if (k == 1)
					headTable(vector, section, subsection);
				string buf;
				stringstream s;
				s << i + 1;
				s >> buf;
				cout << "|" << setw(returnNumber(3, buf.length())) << buf << setw(4 - returnNumber(3, buf.length())) << "|";
				vector[i].print(vector);
			}
		}
		if (k == 0)
		{
			SetColor(4, 0);
			cout << "Такого товара в этом разделе нет!" << endl;
			SetColor(15, 0);
		}
	}
	static void SearchByPrice(vector <Product> vector, string section, string subsection, double priceL, double priceR)
	{
		int k = 0;
		for (size_t i = 0; i < vector.size(); i++)
		{
			if (vector[i].returnPrice() >= priceL && vector[i].returnPrice() <= priceR)
			{
				k++;
				if (k == 1)
					headTable(vector, section, subsection);
				string buf;
				stringstream s;
				s << i + 1;
				s >> buf;
				cout << "|" << setw(returnNumber(3, buf.length())) << buf << setw(4 - returnNumber(3, buf.length())) << "|";
				vector[i].print(vector);
			}
		}
		if (k == 0)
		{
			SetColor(4, 0);
			cout << "Такого товара в этом разделе нет!" << endl;
			SetColor(15, 0);
		}
	}
	static void SearchByMan(vector <Product> vector, string section, string subsection, string man)
	{
		int k = 0;
		for (size_t i = 0; i < vector.size(); i++)
		{
			if (vector[i].returnManufacturer() == man)
			{
				k++;
				if (k == 1)
					headTable(vector, section, subsection);
				string buf;
				stringstream s;
				s << i + 1;
				s >> buf;
				cout << "|" << setw(returnNumber(3, buf.length())) << buf << setw(4 - returnNumber(3, buf.length())) << "|";
				vector[i].print(vector);
			}
		}
		if (k == 0)
		{
			SetColor(4, 0);
			cout << "Такого товара в этом разделе нет!" << endl;
			SetColor(15, 0);
		}
	}
};


class Section
{
protected:
	string name;
	vector<Subsection> subsections;
public:
	Section()
	{
		name = "";
	}
	void Section1(const Section& ob)
	{
		name = ob.name;
	}
	Section(string name)
	{
		this->name = name;
	}
	void setData();
	void addVector();
	string returnName() { return name; }
	vector <Subsection>* returnVectorSubsection() { 
		return &subsections; }
	
	friend istream& operator >> (istream& s, vector <Section>* e);
	friend ostream& operator << (istream& s, Section& e);
};

class Subsection : public Section
{
protected:
	string name;
	vector <Product> products;
public:
	Subsection() {};
	Subsection(string name)
	{
		this->name = name;
	}
	void Subsection1(const Subsection& ob)
	{
		name = ob.name;
	}
	void setData();
	void addVector();
	string returnName() { return name; }
	vector <Product>* returnProduct() { return &products; }
	int returnSizeProduct() { return products.size(); }
};
int searchSection(vector <Section> vec, string name);
int searchSection(vector <Subsection> vec, string name);
istream& operator >> (istream& s, vector <Section>* e);
ostream& operator << (ostream& s, Section& e);
void read(vector <Section>* s, string str);
void write(vector <Section> s);
