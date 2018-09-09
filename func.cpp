#include "func.h"

void help()
{
	cout << "- help - вывести на экран список команд" << endl; //
	cout << "- clear - очистить список" << endl; //
	cout << "- load <filename> - добавить список из файла" << endl; //
//	cout << "- load <filename, name1, name2, ... , № теста для name1, № теста для name1, ...> - добавить список из файла (№ тестов опционально)" << endl;
	cout << "- save <filename> - сохранить список в файле" << endl; // 
	cout << "- add (переходит в режим ввода, начинающийся с "<<'"' << '>'<< '"' << ") - добавить элемент" << endl; //
	cout << "- sort - отсортировать " << endl;  //
	cout << "- print - вывести на экран весь список " << endl; //
	cout << "- find - вывести на экран элементы, удовлетворяющие условиям" << endl; //
	cout << "- delete - удалить элементы, удовлетворяющие условиям " << endl; //
	cout << "- exit - завершить работу и выйти" << endl; 
	cout << "- testno x - вывод всех, прошедших тест с номером х" << endl;
	cout << "во всех коммандах нумерация с нуля" << endl;
}

void sort(List<Person>& L)
{
	if(L.get_num() != 0)
		L.sort();
	else 
		cout << "список пуст" << endl;
}

void clear(List<Person>& L)
{
	L.~List();
}

void find(List<Person>& L, vector<unsigned>& s_balls_u, vector<unsigned>& s_balls_l, vector<unsigned>& s_nums, string s_name, unsigned *s_test)
{
//	cout << "----------------" << endl;
//	cout << s_name << endl;
//	cout << s_test << endl;
//	for (unsigned i = 0; i < s_nums.size(); i++)
//		cout << s_nums[i] << endl;
//	cout << "@" << endl;
//	for (unsigned i = 0; i < s_balls_l.size(); i++)
//		cout << s_balls_l[i] << endl;
//	cout << "@" << endl;
//	for (unsigned i = 0; i < s_balls_u.size(); i++)
//		cout << s_balls_u[i] << endl;
//	cout << "@" << endl;
//	cout << "----------------" << endl;
	Node<Person> * t = L.search(s_balls_u, s_balls_l, s_nums, L.get_first(), L.get_last(), s_name, s_test);
	if(t != NULL)
	{
		Person o = t->get_value();
		cout << o << endl;
		t = t->get_next();
		while (L.search(s_balls_u, s_balls_l, s_nums, t, L.get_last(), s_name, s_test) != NULL) 
		{
//			cout << "!!!" << endl;
			t = L.search(s_balls_u, s_balls_l, s_nums, t, L.get_last(), s_name, s_test);
			o = t->get_value();
			cout << o << endl;
			t = t->get_next();
		}
	}
	else
		cout << "ничего не найдено" << endl;
}
void del(List<Person>& L, vector<unsigned>& s_balls_u, vector<unsigned>& s_balls_l, vector<unsigned>& s_nums, string s_name, unsigned *s_test)
{
	Node<Person> * t = L.search(s_balls_u, s_balls_l, s_nums, L.get_first(), L.get_last(), s_name, s_test);
//	Person y = t->get_value();
//	cout << y << endl;
	if(t != NULL)
	{
		if (t != L.get_first())
		{
			t = t -> get_previous();
			L.pop(t -> get_next());
			Person y;
			while (L.search(s_balls_u, s_balls_l, s_nums, t, L.get_last(), s_name, s_test) != NULL) 
			{
//				y.clear(y.get_tests());
//				y = t->get_value();
//				cout << y << endl;
//				cout << "!!!" << endl;
				t = L.search(s_balls_u, s_balls_l, s_nums, t, L.get_last(), s_name, s_test);
				t = t -> get_previous();
				L.pop(t -> get_next());
			}
		}
		else
			if (t->get_next() != NULL)
			{
				t = t->get_next();
				L.pop(L.get_first());
				while (L.search(s_balls_u, s_balls_l, s_nums, t, L.get_last(), s_name, s_test) != NULL) 
				{
					t = L.search(s_balls_u, s_balls_l, s_nums, t, L.get_last(), s_name, s_test);
					if (t->get_next() != NULL)
					{
						t = t->get_next();
						L.pop(t->get_previous());
					}
					else
					{
						L.pop(t);
						break;
					}
				}
			}
	}
	else
		cout << "ничего не найдено" << endl;
	
}
void load(List<Person>& L, string filenames)
{
	if (filenames.size() != 0)
		if ((filenames.find(",") != string::npos) && ((filenames.find(",") + 1) != filenames.size()) && (filenames.find(",") != 0))
		{
			char* t;
			char* tt;
			t = new char[filenames.find(",")];
	
			tt = new char[filenames.size() - filenames.find(",")];
		
			memcpy(t, filenames.substr(0, filenames.find(",")).c_str(), filenames.find(",") + 1);
			memcpy(tt, filenames.substr(filenames.find(",")+1, filenames.size()).c_str(), filenames.size() - filenames.find(","));
//			cout << t << endl;
//			cout << tt << endl;
			clear(L);
			L.load(t, tt);
		}
		else
		{
			cout << "неправильные значения" << endl;
			cout << "вводите в формате load<person_file,test_file>" << endl;
		
		}
	else
	{
		cout << "неправильные значения" << endl;
	}
}
bool save(List<Person>& L, string filenames)
{
	if (filenames.size() != 0)
		if ((filenames.find(",") != string::npos) && ((filenames.find(",") + 1) != filenames.size()) && (filenames.find(",") != 0))
		{
			char* t;
			char* tt;
			t = new char[filenames.find(",")];
	
			tt = new char[filenames.size() - filenames.find(",")];
			memcpy(t, filenames.substr(0, filenames.find(",")).c_str(), filenames.find(",") + 1);
			memcpy(tt, filenames.substr(filenames.find(",")+1, filenames.size()).c_str(), filenames.size() - filenames.find(","));
			L.save(t,tt);
			return true;
		}
		else
		{
			cout << "неправильные значения" << endl;
			cout << "вводите в формате person_file,test_file" << endl;
			return false;
		}
	else
	{
		cout << "неправильные значения" << endl;
		return false;
	}
}
void add(List<Person>& L, vector<unsigned>& s_balls_u, vector<unsigned>& s_balls_l, vector<unsigned>& s_nums, string s_name, unsigned *s_test)
{
	Person A(L.get_tests());
	if(s_balls_u.size() == 0 && s_balls_l.size() == 0 && s_nums.size() == 0 && s_name == " " && s_test == NULL)
	{
		A.read();
		L.add(NULL, A);
	}
	else
	{
		A.read();
		L.add(L.search(s_balls_u, s_balls_l, s_nums, L.get_first(), L.get_last(), s_name, s_test), A);
	}
}

void read(List<Person>& L, string f_name, void f(List<Person>& L, vector<unsigned>& s_balls_u, vector<unsigned>& s_balls_l, vector<unsigned>& s_nums, string s_name, unsigned *s_test))
{
	cout << f_name << endl;
	string cmd;
	string name = " ";
	unsigned* test_id = NULL;
	vector<unsigned> balls_u;
	vector<unsigned> balls_l;
	vector<unsigned> nums;
	bool tn;
	cout << "поиск по имени? [y/n]" << endl;
	cout << ">";
	cin >> cmd;
	if ((cmd == "y") || (cmd == "Y"))
	{
		cout << "введите имя" << endl;
		cout << ">";
		cin >> name;
	}
	cout << "Поиск по номеру теста? [y/n]" << endl;
	cout << ">";
	cin >> cmd;
	if ((cmd == "y") || (cmd == "Y"))
	{
		cout << "введите номер" << endl;
		cout << ">";
//		test_id = new unsigned;
		unsigned j;
		while(!(cin >> j, cin.good())) 
		{
			cin.clear(ios_base::goodbit);
			cin.ignore(100,'\n');
			cout << "значение некорректно" << endl;
			cout << ">";
		}
		test_id = &j;
	}
		
	cout << "Поиск по баллам в тесте? [y/n]" << endl;
	cout << ">";
	cin >> cmd;
	if ((cmd == "y") || (cmd == "Y"))
	{
		unsigned t;
		unsigned tt;
		cout << "введите количество баллов" << endl;
		cout << ">";
		while(!(cin >> t, cin.good())) 
		{
			cin.clear(ios_base::goodbit);
			cin.ignore(100,'\n');
			cout << "значение некорректно" << endl;
			cout << ">";
		}
		cout << "введите количество баллы: сначала ограничение номер, затем сверху, затем снизу (в разных строках)" << endl;
		for (unsigned i = 0; i < 3*t; i++)
		{
			cout << ">";
			if(i%3 == 0)
			{
				while(!(cin >> tt, cin.good())) 
				{
					cin.clear(ios_base::goodbit);
					cin.ignore(100,'\n');
					cout << "значение некорректно" << endl;
					cout << ">";
				}
				nums.push_back(tt);
			}
			else
				if (i%3 == 1)
				{
					while(!(cin >> tt, cin.good())) 
					{
						cin.clear(ios_base::goodbit);
						cin.ignore(100,'\n');
						cout << "значение некорректно" << endl;
						cout << ">";
					}
					balls_u.push_back(tt);
				}
				else
					if (i%3 == 2)
					{
						while(!(cin >> tt, cin.good())) 
						{
							cin.clear(ios_base::goodbit);
							cin.ignore(100,'\n');
							cout << "значение некорректно" << endl;
							cout << ">";
						}
						balls_l.push_back(tt);
					}
				 
		}
		if(!((nums.size() == balls_l.size()) && (balls_l.size() == balls_u.size())))
		{
			cout << "значение некорректно" << endl;
			nums.clear();
			balls_u.clear();
			balls_l.clear();
		}
	}
	f(L, balls_u, balls_l, nums, name, test_id);
}

void print(List<Person>& L, unsigned n)
{
	L.print(cout, n);
}
// по номеру теста вывести всех, кто прошёл этот тест