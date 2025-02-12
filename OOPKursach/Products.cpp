#pragma once
#include "Products.h"

void Product::Product1(const Product& ob)
{
	price = ob.price;
	name = ob.name;
	manufacturer = ob.manufacturer;
	vendor_code = ob.vendor_code;
	amount = ob.amount;
	day = ob.day;
	month = ob.month;
	year = ob.year;
}
void Product::setDate()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	day = st.wDay;
	month = st.wMonth;
	year = st.wYear;
}
void Product:: setAmount()
{
	cout << "Введите количество: ";
	cin >> amount;
}
void Product::setPrice()
{
	cout << "Введите стоимость одного товара: ";
	cin >> price;
}
void Product::setKod()
{
	cout << "Введите артикул: ";
	cin >> vendor_code;
}
void Product::setName()
{
	while (true)
	{
		cin.clear();
		cout << "Введите название товара: ";
		getline(cin, name);
		if (name != "")
			break;
		SetColor(4, 0);
		cout << "Неправильный ввод данных!" << endl;
		SetColor(15, 0);
	}
}
void Product::setManufacturer()
{
	while (true)
	{
		cin.clear();
		cout << "Введите производителя: ";
		getline(cin, manufacturer);
		if (manufacturer != "")
			break;
		SetColor(4, 0);
		cout << "Неправильный ввод данных!" << endl;
		SetColor(15, 0);
	}
}
void Product::setData()
{
	setName();
	setManufacturer();
	setKod();
	setAmount();
	setPrice();
	cin.clear();
	setDate();
}
void Product::setAmount(int amount)
{
	this->amount = amount;
}
int Product::decreaseAmount(int number)
{
	if (number > amount)
	{
		cout << "Столько товара нет!" << endl;
		return -1;
	}
	amount -= number;
	return amount;
}
int Product::returnLengthNumber(vector <Product> vector)
{
	int buf = vector.size();
	return to_string(buf).length() + 2;
}
int Product::returnLengthName(vector <Product> vector)
{
	int buf = vector[0].name.length();
	for (size_t i = 1; i < vector.size(); i++)
	{
		if (int(vector[i].name.length()) > buf)
			buf = vector[i].name.length();
	}
	return buf < 12 ? 14 : buf + 2;
}
int Product::returnLengthManufacturer(vector <Product> vector)
{
	int buf = vector[0].manufacturer.length();
	for (size_t i = 1; i < vector.size(); i++)
	{
		if (int(vector[i].manufacturer.length()) > buf)
			buf = vector[i].manufacturer.length();
	}
	return buf < 13 ? 15 : buf + 2;
}
int Product::returnLengthPrice(vector <Product> vector)
{
	int buf = to_string(vector[0].price).length();
	for (size_t i = 1; i < vector.size(); i++)
	{
		if (int(to_string(vector[i].price).length()) > buf)
			buf = to_string(vector[i].price).length();
	}
	buf -= 7;
	return buf < 9 ? 11 : buf + 2;
}

int Product::returnLengthKod(vector <Product> vector)
{
	int buf = to_string(vector[0].vendor_code).length();
	for (size_t i = 1; i < vector.size(); i++)
	{
		if (int(to_string(vector[i].vendor_code).length()) > buf)
			buf = to_string(vector[i].vendor_code).length();
	}
	return buf < 7 ? 9 : buf + 2;
}
int Product::returnLengthAmount(vector <Product> vector)
{
	int buf = to_string(vector[0].amount).length();
	for (size_t i = 1; i < vector.size(); i++)
	{
		if (int(to_string(vector[i].amount).length()) > buf)
			buf = to_string(vector[i].amount).length();
	}
	return buf < 10 ? 12 : buf + 2;
}
int Product::returnWidthTable(vector <Product> vector)
{
	return returnLengthAmount(vector) + returnLengthKod(vector) + returnLengthManufacturer(vector) + returnLengthName(vector) + returnLengthNumber(vector) + returnLengthPrice(vector) + 24;
}
void Product::print(vector <Product> vector)
{
	string s1, s2, s3;
	stringstream str, str1, str2, str3, str4;
	cout.setf(ios::right);
	SetColor(14, 0);
	cout << setw(returnNumber(returnLengthName(vector), name.length())) << name;
	SetColor(15, 0);
	cout << setw(returnLengthName(vector) + 1 - returnNumber(returnLengthName(vector), name.length())) << "|";
	SetColor(14, 0);
	str << vendor_code;
	str >> s1;
	cout << setw(returnNumber(returnLengthKod(vector), s1.length())) << s1;
	SetColor(15, 0);
	cout << setw(returnLengthKod(vector) + 1 - returnNumber(returnLengthKod(vector), s1.length())) << "|";
	str1.clear();
	str1 << amount;
	str1 >> s1;
	SetColor(14, 0);
	cout << setw(returnNumber(returnLengthAmount(vector), s1.length())) << s1;
	SetColor(15, 0);
	cout << setw(returnLengthAmount(vector) + 1 - returnNumber(returnLengthAmount(vector), s1.length())) << "|";
	str.clear();
	str << price;
	str >> s1;
	SetColor(14, 0);
	cout << setw(returnNumber(returnLengthPrice(vector), s1.length())) << s1;
	SetColor(15, 0);
	cout << setw(returnLengthPrice(vector) + 1 - returnNumber(returnLengthPrice(vector), s1.length())) << "|";
	SetColor(14, 0);
	cout << setw(returnNumber(returnLengthManufacturer(vector), manufacturer.length())) << manufacturer;
	SetColor(15, 0);
	cout << setw(returnLengthManufacturer(vector) + 1 - returnNumber(returnLengthManufacturer(vector), manufacturer.length())) << "|";
	str1.clear();
	str1 << day;
	str1 >> s1;
	str2 << month;
	str2 >> s2;
	str3 << year;
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
	SetColor(14, 0);
	cout << setw(returnNumber(18, s.length())) << s << setw(19 - returnNumber(18, s.length()));
	SetColor(15, 0);
	cout << "|" << endl;
	for (int i = 0; i < returnWidthTable(vector) + 2; i++)
		cout << "-";
	cout << endl;
	cout.unsetf(ios::right);
}
void Product::print(ostream& ouf, vector <Product> vector)
{
	string s1, s2, s3;
	stringstream str, str1, str2, str3, str4;
	ouf.setf(ios::right);
	ouf << setw(returnNumber(returnLengthName(vector), name.length())) << name;
	ouf << setw(returnLengthName(vector) + 1 - returnNumber(returnLengthName(vector), name.length())) << "|";
	str << vendor_code;
	str >> s1;
	ouf << setw(returnNumber(returnLengthKod(vector), s1.length())) << s1;
	ouf << setw(returnLengthKod(vector) + 1 - returnNumber(returnLengthKod(vector), s1.length())) << "|";
	str1.clear();
	str1 << amount;
	str1 >> s1;
	ouf << setw(returnNumber(returnLengthAmount(vector), s1.length())) << s1;
	ouf << setw(returnLengthAmount(vector) + 1 - returnNumber(returnLengthAmount(vector), s1.length())) << "|";
	str.clear();
	str << price;
	str >> s1;
	ouf << setw(returnNumber(returnLengthPrice(vector), s1.length())) << s1;
	ouf << setw(returnLengthPrice(vector) + 1 - returnNumber(returnLengthPrice(vector), s1.length())) << "|";
	ouf << setw(returnNumber(returnLengthManufacturer(vector), manufacturer.length())) << manufacturer;
	ouf << setw(returnLengthManufacturer(vector) + 1 - returnNumber(returnLengthManufacturer(vector), manufacturer.length())) << "|";
	str1.clear();
	str1 << day;
	str1 >> s1;
	str2 << month;
	str2 >> s2;
	str3 << year;
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
	ouf << setw(returnNumber(19, s.length())) << s << setw(20 - returnNumber(19, s.length()));
	ouf << "|\n";
	for (int i = 0; i < returnWidthTable(vector) + 2; i++)
		ouf << "-";
	ouf << "\n";
	ouf.unsetf(ios::right);
}
void Product::SortByName(vector <Product>* vector)
{
	sort((*vector).begin(), (*vector).end(), [](const Product& a, const Product& b)
		{
			return a.name < b.name;
		}
	);
}
void Product::SortByDate(vector <Product>* vector)
{
	sort((*vector).begin(), (*vector).end(), [](const Product& a, const Product& b)
		{
			if (a.year == b.year)
			{
				if (a.month == b.month)
					return a.day > b.day;
				else
					return a.month < b.month;
			}
			else
				return a.year > b.year;
		}
	);
}
void Product::SortByAmount(vector <Product>* vector)
{
	sort((*vector).begin(), (*vector).end(), [](const Product& a, const Product& b)
		{
			return a.amount < b.amount;
		}
	);
}
void Product::SortByPrice(vector <Product>* vector)
{
	sort((*vector).begin(), (*vector).end(), [](const Product& a, const Product& b)
		{
			return a.price < b.price;
		}
	);
}

istream& operator >> (istream& s, Product& e)
{
	string buf;
	getline(s, buf, '|');
	if (buf == "")
		return s;
	e.name = buf;
	getline(s, buf, '|');
	e.vendor_code = stoi(buf);
	getline(s, buf, '|');
	e.amount = stoi(buf);
	getline(s, buf, '|');
	e.price = stod(buf);
	getline(s, e.manufacturer, '|');
	getline(s, buf, '|');
	e.day = stoi(buf);
	getline(s, buf, '|');
	e.month = stoi(buf);
	getline(s, buf);
	e.year = stoi(buf);
	return s;
}
ostream& operator << (ostream& s, Product& e)
{
	s << "|" << e.name << "|" << e.vendor_code << "|" << e.amount << "|" << e.price << "|" << e.manufacturer << "|" << e.day << "|" << e.month << "|" << e.year << '\n';
	return s;
}





void Section::addVector()
{
	Subsection subsection;
	subsection.setData();
	subsections.push_back(subsection);
}

int searchSection(vector <Section> vec, string name)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i].returnName() == name)
			return i;
	}
	return -1;
}
int searchSection(vector <Subsection> vec, string name)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i].returnName() == name)
			return i;
	}
	return -1;
}

istream& operator >> (istream& s, vector <Section>* e)
{
	string section, subsection, name;
	getline(s, section, '|');
	if (searchSection(*e, section) == -1)
	{
		(*e).push_back(Section(section));
	}
	getline(s, subsection, '|');
	if (searchSection((*e)[searchSection(*e, section)].subsections, subsection) == -1)
	{
		(*e)[searchSection(*e, section)].subsections.push_back(Subsection(subsection));
	}
	Product product;
	s >> product;
	(*(*e)[searchSection(*e, section)].subsections[searchSection((*e)[searchSection(*e, section)].subsections, subsection)].returnProduct()).push_back(product);
	return s;
}
ostream& operator << (ostream& s, Section& e)
{
	for (size_t i = 0; i < (*e.returnVectorSubsection()).size(); i++)
	{
		for (size_t j = 0; j < (*(*e.returnVectorSubsection())[i].returnProduct()).size(); j++)
		{
			s << e.returnName() << "|" << (*e.returnVectorSubsection())[i].returnName();
			s << (*(*e.returnVectorSubsection())[i].returnProduct())[j];
		}
	}
	return s;
}
void read(vector <Section>* s, string str)
{
	ifstream in;
	in.open(str, ios_base::in);
	while (true)
	{
		if (in.eof()) break;
		in >> s;
	}
	(*s).erase((*s).begin() + (*s).size() - 1);
	in.close();
}
void write(vector <Section> s)
{
	ofstream of;
	of.open("COURSE.DAT", ios_base::trunc | ios_base::binary);
	for (size_t i = 0; i < s.size(); i++)
	{
		of << s[i];
	}
	of.close();
}


void Subsection::setData()
{
	while (1)
	{
		cout << "Введите название подраздела: ";
		getline(cin, name);
		if (name != "")
			break;
		cout << "Неправильный ввод данных!" << endl;
	}
}
void Subsection::addVector()
{
	Product product;
	product.setData();
	products.push_back(product);
}
void Section::setData()
{
	while (1)
	{
		cout << "Введите название раздела: ";
		getline(cin, name);
		if (name != "")
			break;
		cout << "Неправильный ввод данных!" << endl;
	}
}