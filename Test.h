#pragma once
#include "global_func.h"

class Test
{
	bool readed;
	vector <unsigned> up_limits;
	vector <unsigned> down_limits;
	unsigned test_id;
	vector <unsigned> weighting_factor;
	static bool compare_for_sort(Test test1,Test test2);
public:
//	vector <unsigned> get_up_limits();
	Test();
//	Test(void * tests1);
	bool get_readed();
	unsigned get_up_limit(unsigned pos);
	vector<unsigned> get_up_limits(){return up_limits;}
	unsigned get_down_limit(unsigned pos);
	unsigned get_up_limits_size();
//	vector <unsigned> get_down_limits();
	unsigned get_down_limits_size();
	unsigned get_test_id();
	unsigned get_weighting_factor(unsigned pos);
	void set_test_id(unsigned value);
	void set_up_limit(unsigned value);
	void set_down_limit(unsigned value);
	void set_weighting_factor(unsigned value);
//	void soft_write(char* test_filename);
//	void hard_write(char* test_filename);
	long int array_ask(vector <Test>& s, unsigned start, unsigned end); // возвращает -1 если элемента нет и номер элемента, если он есть
	void add(vector <Test>& s);
	unsigned load(char* test_filename, vector <Test>& tests);
	bool k_load(vector <Test>& tests, unsigned num, istream &s, bool key); // stream load (key == 1 - cin)
	void generate(vector<string>& saved); // new
};
