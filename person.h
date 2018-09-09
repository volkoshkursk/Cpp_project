#pragma once
#include "Test.h"

class Test_array
{
	vector<Test> tests;
public:
	Test ind(unsigned pos);  // индексация
	unsigned size();
	void insert(vector<Test>::iterator position, Test value);
	vector<Test>::iterator begin();
	vector<Test>::iterator end();
	vector<Test> * get_pointer();
	void save(char* test_filename);
};

class Person
{
	vector <unsigned> balls;
//	unsigned test_pos;
	string name; // Имя
	Test_array * tests;
	unsigned test_number;
	bool readed;
//  -------------------------------------------------------------------------------------------
	short int compare(Person B, bool type); // сравнение, 2-й параметр: 0 - имя, 1 - номер теста
	bool check(unsigned test_id_i);
	bool check(vector<unsigned>& balls_i_l, vector<unsigned>& balls_i_m , vector<unsigned>& numbers);
	bool check(string name_i); 
	static short int compare_for_sort(Person A, Person B);
	long int  name_ask(vector <Person>& s, unsigned start, unsigned end, string name, unsigned * test_num = NULL);
	long int  num_ask(vector <Person>& s, unsigned start, unsigned end, unsigned * test_num);
public:
//	void set_name(string i_name);
	Person(Test_array * tests1);
	Person();
	void initialize(Test_array * tests1);
//	Person(string name, unsigned test_number, vector <unsigned>& balls);
	bool get_readed();
	string get_name();
	Test_array * get_tests(){return tests;}
	void clear();
	void clear(Test_array * tests1);
//	unsigned get_test_pos();
	vector <unsigned> get_balls();
//	void set_test_number(unsigned id);
//	void set_ball(unsigned value);
	unsigned get_test_number();
	void read(char* filename, char* test_filename, unsigned num = 0); // Чтение из файла по коду в файле
	void read(char* filename, char* test_filename, string name_asked, unsigned * num = NULL); // Чтение из файла по имени
	unsigned set(string name_, unsigned test_id, vector <unsigned>& balls_);
	void read(); // Чтение
//	void soft_write(char* filename, char* test_filename, bool mode); //запись в файл с сохранением имеющейся в нём информации;mode = 1 - hard write для теста
																		// 0 - soft write для теста
	short int compare(Person B);
	bool check(string name_i, unsigned test_id_i, vector<unsigned>& balls_i_l, vector<unsigned>& balls_i_m, vector<unsigned>& numbers, bool first, bool second, bool third);
	unsigned getProperty(vector<unsigned>& weight);
	void make_out_array(vector<string> & saved, unsigned num = 0);
//	void hard_write(char* filename, char* test_filename/*, bool mode*/); //запись в файл с перезаписью;mode = 1 - hard write для теста
	//																	 0 - soft write для теста
	friend istream& operator >> (istream &s, Person& A);
	friend ostream& operator << (ostream &s, Person& A);
};
bool operator>=(Person A, Person B);
bool operator<=(Person A, Person B);
// (check диапозон), list с возможностями (добавления), поиска и (удаления); (чтения/запись в поток (для листа)), (конструкторы (и копирования) и деструктор), 
// (сортировка) для данного теста, (вывести на экран список наборов баллов по всем прошедшим этот тест)
