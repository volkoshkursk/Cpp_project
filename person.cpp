#include "person.h"



string Person::get_name()
{
	return name;
}

void Person::clear()
{
	balls.clear();
	name = ' ';
	tests = NULL;
	test_number = 0;
	readed = false;
}

void Person::clear(Test_array * tests1)
{
	balls.clear();
	name = ' ';
	tests = tests1;
	test_number = 0;
	readed = false;
}

unsigned Person::set(string name_,unsigned test_id, vector <unsigned>& balls_)
{
	readed = false;
	name = name_;
	test_number = test_id;
	Test * new_test = new Test ();
	new_test->set_test_id(test_number);
//	cout << "####" << endl;
	long int pos = new_test->array_ask(*tests->get_pointer(), 0, tests->size());
//	cout << "!@#$" << endl;
	if(pos == -1)
		return 1;   //нет теста в массиве
	if ((tests->ind(pos)).get_down_limits_size() != balls_.size())
		return 2; // несоответствие количества оценок количеству оценок в данном тесте
	for(unsigned i = 0; i<balls_.size(); i++)
	{
		if((balls_[i] > (tests->ind(pos)).get_up_limit(i)) || (balls_[i] < (tests->ind(pos)).get_down_limit(i)))
		{
			break;
			return 3; // недопустимаяя оценка
		}
		balls.push_back(balls_[i]);
	}
	readed = true;
	return 0; //всё нормально
}
//unsigned Person::get_test_pos()
//{
//	return test_pos;
//}

void Person::make_out_array(vector<string> & saved, unsigned num)
{
//	cout<<"!!!"<<endl;
	saved.insert(saved.end(), "<num>" + to_string(num));
	saved.insert(saved.end(), name);
	saved.insert(saved.end(), to_string(test_number));
	for(unsigned i = 0; i < balls.size(); i++)
		saved.insert(saved.end(), to_string(balls[i]));
}

Person::Person(Test_array * tests1)
{
	readed = false;
	this->tests = tests1;
}

Person::Person()
{
	readed = false;
	this->tests = NULL;
}

void Person::initialize(Test_array * tests1)
{
	this->tests = tests1;
}

void Person::read(char* filename, char* test_filename, unsigned num) // Чтение из файла
{
	clear(tests);
	if (tests != NULL)
	{
		if (file_ask(filename))
		{
			readed = true;
			string file_s;
			ifstream file(filename);
			getline(file, file_s);
			while ((file_s != "<num>" + to_string(num)) && (!file.eof()))
			{
	//			cout << file_s<< endl;
				getline(file, file_s);
			}
			if (file.eof())
				readed = false;
			else
			{
				getline(file, name);
				getline(file, file_s);
				unsigned test_pos;
				test_number = abs(atol(file_s.c_str()));
				Test * new_test = new Test ();
				new_test->set_test_id(test_number);
				long int pos = new_test->array_ask(*tests->get_pointer(), 0, tests->size());
//				getline(file, file_s);
				if (pos == -1)
				{
					unsigned temp = new_test->load(test_filename,*tests->get_pointer());
//					cout << temp << endl;
					if (temp == 0)
					{
//						cout << "enter" << endl;
						unsigned t;
						test_pos = new_test->array_ask(*tests->get_pointer(), 0, tests->size());
//						cout << "@ "<<new_test->get_down_limits_size()<<endl;
//						cout << "enter " <<tests[test_pos].up_limits.size() << endl;
						for (unsigned i = 0;i < tests->ind(test_pos).get_up_limits_size(); i++)
						{
							getline(file, file_s);
							t = abs(atol(file_s.c_str()));
//							cout << 'b' << ' ' << t << endl;
							if ((t < tests->ind(test_pos).get_down_limit(i)) || (t > tests->ind(test_pos).get_up_limit(i)))
							{
								cout << "файл повреждён. Информация о баллах недопустима" << endl;
								readed = false;
								break;
							}
							balls.insert(balls.end(), t);
						}
						delete new_test;
					}
					else
					{
						switch(temp)
						{
							case 1:
								cout << "в файле " << test_filename << " теста № " << test_number << " не существует" << endl;
								readed = false;
								break;
							case 2:
								cout << "файла " << test_filename <<" не существует" << endl; 
								readed = false;
								break;
							case 3:
								cout << "файл " << test_filename <<" повреждён. Данные недоступны" << endl; 
								readed = false;
								break;
								
						}
					}
			}
		
				else
				{	
					unsigned t;
					test_pos = pos;
					for (unsigned i = 0;i < tests->ind(test_pos).get_up_limits_size(); i++)
					{	
						getline(file, file_s);
						t = abs(atol(file_s.c_str()));
//						cout << 'b' << ' ' << t << endl;
						if ((t < tests->ind(test_pos).get_down_limit(i)) || (t > tests->ind(test_pos).get_up_limit(i)))
						{
							cout << "файл повреждён. Информация о баллах недопустима" << endl;
							readed = false;
							break;
						}
						balls.insert(balls.end(), t);
					}
				} 
			}
			file.close();
		}
		else
			cout << "файла " << filename <<" не существует" << endl; 
	}
	else
		cout << "объект не инициализирован" << endl;
}	
	
void Person::read(char* filename, char* test_filename, string name_asked, unsigned * num)
{
	clear(tests);
	if (tests != NULL)
	{
		if (file_ask(filename))
		{
			readed = true;
			string file_s;
			ifstream file(filename);
			bool se = true;
			getline(file, file_s);
			while (se)
			{
				getline(file, file_s);
				if ((file_s == name_asked) || (file.eof()))
					if ((num == NULL) || (file.eof()))
						se = false;
					else
					{
						getline(file, file_s);
						if(abs(atol(file_s.c_str())) == *num)
							se = false;
					}
			}
			if (file.eof())
			{
				readed = false;
				cout << name_asked << " в файле "<< filename << " нет" <<endl;
			}
			else
			{
				name = name_asked;
				if (num == NULL)
					getline(file, file_s);
				unsigned test_pos;
				test_number = abs(atol(file_s.c_str()));
				Test * new_test = new Test ();
				new_test->set_test_id(test_number);
				long int pos = new_test->array_ask(*tests->get_pointer(), 0, tests->size());
	//			getline(file, file_s);
				if (pos == -1)
				{
						unsigned temp = new_test->load(test_filename,*tests->get_pointer());
						if (temp == 0)
						{
	//						cout << "enter" << endl;
							unsigned t;
							test_pos = new_test->array_ask(*tests->get_pointer(), 0, tests->size());
	//						cout << "@ "<<new_test->get_down_limits_size()<<endl;
						
	//						cout << "enter " <<tests[test_pos].up_limits.size() << endl;
							for (unsigned i = 0;i < tests->ind(test_pos).get_up_limits_size(); i++)
							{
								getline(file, file_s);
								t = abs(atol(file_s.c_str()));
	//							cout << 'b' << ' ' << t << endl;
								if ((t < tests->ind(test_pos).get_down_limit(i)) || (t > tests->ind(test_pos).get_up_limit(i)))
								{
									cout << "файл повреждён. Информация о баллах недопустима" << endl;
									readed = false;
									break;
								}
								balls.insert(balls.end(), t);
							}
							delete new_test;
						}
						else
							{
								switch(temp)
								{
									case 1:
										cout << "в файле " << test_filename << " теста № " << test_number << " не существует" << endl;
										readed = false;
										break;
									case 2:
										cout << "файла " << test_filename <<" не существует" << endl; 
										readed = false;
										break;
									case 3:
										cout << "файл " << test_filename <<" повреждён. Данные недоступны" << endl; 
										readed = false;
										break;
								}
							}
				}
			
				else
				{
					unsigned t;
					test_pos = pos;
					for (unsigned i = 0;i < tests->ind(test_pos).get_up_limits_size(); i++)
					{	
						getline(file, file_s);
						t = abs(atol(file_s.c_str()));
	//					cout << 'b' << ' ' << t << endl;
						if ((t < tests->ind(test_pos).get_down_limit(i)) || (t > tests->ind(test_pos).get_up_limit(i)))
						{
							cout << "файл повреждён. Информация о баллах недопустима" << endl;
							readed = false;
							break;
						}
						balls.insert(balls.end(), t);
					}
				} 
			}
			file.close();
		}
		else
			cout << "файла " << filename <<" не существует" << endl; 
	}
	else 
		cout << "объект не инициализирован" << endl;
}

void Person::read()
{
	if (tests != NULL)
	{
		readed = true;
		cout << "имя" << endl;
		cout << ">";
		cin >> name;
		cout << "№ теста" << endl;
		cout << ">";
		long int t;
		while (!(cin >> t, cin.good()) || (t < 0))
		{
			cin.clear(ios_base::goodbit);
			cin.ignore(100,'\n');
			cout << "номер не может быть отрицательным" << endl;
			cout << ">";
//			A.readed = false;
//			return s;
		}
		test_number = t;
	//	cout << "# " << endl;
		Test * new_test = new Test ();
		new_test->set_test_id(test_number);
	//	cout << '@' << endl;
		long int pos = new_test->array_ask(*(tests->get_pointer()), 0, tests->size());
	//	long int pos = -1;
		delete new_test;
		unsigned test_pos;
//		cout << pos << endl;
		if (pos == -1)
		{
			Test neww;
			if (neww.k_load(*(tests->get_pointer()), test_number, cin, 1))
			{
				cout << "введите критерии теста №" << test_number << " для " << name << endl;
				Test * new_test = new Test ();
				new_test->set_test_id(test_number);
				
	//			cout << new_test->array_ask(*(A.tests->get_pointer()), 0, A.tests->size()) << endl;
				for (unsigned i = 0;i < (tests->ind(new_test->array_ask(*(tests->get_pointer()), 0, tests->size()))).get_up_limits_size(); i++)
				{
					cout << ">";
					while (!(cin >> t, cin.good()) || (t < neww.get_down_limit(i)) || (t > neww.get_up_limit(i)))
					{
						cin.clear(ios_base::goodbit);
						cin.ignore(100,'\n');
						cout << "значение некорректно" << endl;
						cout << ">";
//						A.readed = false;
//						return s;
					}
					balls.insert(balls.end(), t);
				}
				delete new_test;
			}
		}
		else
		{
			test_pos = pos;
			cout << "введите критерии теста №" << test_number << " для " << name << endl;
			//s >> t;
			pos = tests->ind(test_pos).get_up_limits_size();
			for (unsigned i = 0;i < pos; i++)
			{
				cout << ">";
				while (!(cin >> t, cin.good()) || (t < tests->ind(test_pos).get_down_limit(i)) || (t > tests->ind(test_pos).get_up_limit(i)))
				{
		//				cout << "!(s >> t, s.good())" << !(s >> t, s.good()) << "(t < A.tests->ind(test_pos).get_down_limit(i))" << (t < A.tests->ind(test_pos).get_down_limit(i)) << "(t > A.tests->ind(test_pos).get_up_limit(i))" << (t > A.tests->ind(test_pos).get_up_limit(i)) <<endl;
		//				cout << "t" << t
					cin.clear(ios_base::goodbit);
					cin.ignore(100,'\n');
					cout << "значение некорректно" << endl;
					cout << ">";
//					A.readed = false;
//					return s;
				}
				balls.insert(balls.end(), t);
			}
		}
	}
	else
		cout << "объект не инициализирован" << endl;
}


/*void Person::soft_write(char* filename, char* test_filename, bool mode)  
{
//	cout << "write_person" << endl;
	if (readed)
	{
		vector<string> saved;
		if(file_ask(filename)) // если файл существует
		{
			string file_s;
			ifstream file(filename);
			unsigned num = 0;
			bool searched1 = false;
			unsigned last_num = 0;
			bool next_step = false;
			while(!file.eof())
			{
				getline(file, file_s);
				
//				while(file_s == "\n")
//					getline(file, file_s);
	
				saved.insert(saved.end(),file_s);
				if (next_step)
				{
					if (file_s == name)
						searched1 = true;
					next_step = false;
				}
				if (!searched1)
					num ++;
				if (file_s.substr(0,5) == "<num>")
				{
					next_step = true;
					file_s.erase(0,5);
//					cout << file_s << endl;
					last_num = abs(atol(file_s.c_str()));
				}
			}
			file.close();
			// debug
//			cout << last_num << endl;
//			cout << num << endl;
//			for (unsigned i = 0; i < saved.size(); i++)
//				cout << saved[i] << endl;
//			cout << "---------------------" <<endl;
			if (searched1)
			{
				num ++;
				bool searched = false;
//				cout << "after " << saved[num];
				saved[num] =  to_string(test_number);
//				cout << " before " << saved[num] << endl;
				num ++;
				unsigned i = num;
				for (unsigned j = i; j < (balls.size() + num); j++)
				{
//					cout << "counter" << endl;
					if((saved[j].substr(0,5) != "<num>") && (searched == false))
					{
//						cout << "1st if" << endl;
//						cout << "after " << saved[j];
						saved[j] = to_string(balls[j - num]);
//						cout << " before " << saved[j] << endl;
					}
					else
					{
						if (searched == false)
							searched = true;	
						if (searched)
						{
//							cout << "2nd if" << endl;
							saved.insert(saved.begin() + j, to_string(balls[j - num]));
//							cout << saved[j]<< endl;
						}
					}
					i = j;	
				}
				if ((!searched) || (saved[i+1].substr(0,5) != "<num>"))
				{
					num = i;
					while((saved[num].substr(0,5) != "<num>") && (saved.size() - 1 > num))
					{
						num ++;
//						cout << "@ "<<num << endl;
					}
//					cout << "+++++++++++++++" << i << ' ' << num << endl;
					saved.erase(saved.begin()+i+1, saved.begin()+num + 1);
				}
			}
			else
			{
//				saved.insert(saved.end(), "<num>" + to_string(last_num + 1));
//				saved.insert(saved.end(), name);
//				saved.insert(saved.end(), to_string(test_number));
//				for(unsigned i = 0; i < balls.size(); i++)
//					saved.insert(saved.end(), to_string(balls[i]));
				make_out_array(saved, last_num + 1);
			}
		}
		else 
		{
//			saved.insert(saved.end(), "<num>0");
//			saved.insert(saved.end(), name);
//			saved.insert(saved.end(), to_string(test_number));
//			for(unsigned i = 0; i < balls.size(); i++)
//				saved.insert(saved.end(), to_string(balls[i]));
//			cout << '@' <<endl;
			make_out_array(saved);
		}
//		for (unsigned i = 0; i < saved.size(); i++)
//		{
//			cout << saved[i] << endl;
//		}
		ofstream file(filename);
		for (unsigned i = 0; i < saved.size(); i++)
		{
//			cout<<i<<' ';
			if(saved[i].size() > 0)
				file << saved[i] << endl;
		}
		file.close();
		Test * new_test = new Test ();
		new_test->set_test_id(test_number);
		long int t = new_test->array_ask(*tests->get_pointer(), 0, tests->size());
//		cout << '@' << t << endl;
		if (t > -1)
		{
//			cout << tests->ind(t).get_test_id();
			if(mode)
				tests->ind(t).hard_write(test_filename);
			else
				tests->ind(t).soft_write(test_filename);
			delete new_test;
		}
		else
			cout << "ошибка записи теста в файл" << endl;
	}
	else 
		cout << "элемент не был корректно сохранён" << endl;
}
*/
//void Person::set_test_number(unsigned id)
//{
//	test_number = id;
//}
//
//void Person::set_name(string i_name)
//{
//	name = i_name;
//}
//void Person::set_ball(unsigned value)
//{
//	balls.insert(balls.end(), value);
//}
unsigned Person::get_test_number()
{
	return test_number;
}

bool Person::get_readed()
{
	return readed;
}
vector <unsigned> Person::get_balls()
{
	return balls;
}

short int Person::compare(Person B, bool type) // сделано
{
	if (readed && B.get_readed())
	{
		short int ret;
		if (type)
		{
			ret = name.compare(B.get_name());
		}
		else
		{
			unsigned temp = B.get_test_number();
			if(test_number > temp)
				ret = 1;
			else
				if (test_number == temp)
					ret = 0;
				else
					ret = -1;
		}
		return ret;
	}
	else 
		cout << "элемент не был корректно сохранён" << endl;
}

short int Person::compare(Person B)
{
	short int ret = this->compare(B, 1);
	if(ret == 0)
	{
		return this->compare(B, 0);
	}
	return ret;
}

bool Person::check(string name_i) 
{
	if (readed)
	{
		return name == name_i;
	}
	else 
		return 0;
}
bool Person::check(unsigned test_id_i)
{
	if (readed)
	{
		return test_number == test_id_i;
	}
	else 
		return 0;
}
bool Person::check(vector<unsigned>& balls_i_l, vector<unsigned>& balls_i_m, vector<unsigned>& numbers)
{
	if ((readed) && (balls_i_l.size() == balls_i_m.size()))
	{
		bool l = 1;
		for (unsigned i = 0; i < numbers.size(); i++)
		{
//			cout << '@'<< i << '@' << numbers[i] << '@' << balls[numbers[i]] << '@' << balls_i[i] << endl;
//			cout << (numbers[i] < balls.size()) << '@'  << endl;
			if((numbers[i] < balls.size()) && (i < balls_i_l.size()))
			{
//				cout << "enter" << ' ' << l << ' ' << (balls[numbers[i]] == balls_i[i])<< ' ';
				l = l && ((balls[numbers[i]] <= balls_i_m[i]) && (balls[numbers[i]] >= balls_i_l[i]));
//				cout << l << endl;
			}
			else
			{
//				cout << "out" << endl;
				return false;
			}
					
		}
		return l;
	}
	else
		return false;
}
bool Person::check(string name_i, unsigned test_id_i, vector<unsigned>& balls_i_l, vector<unsigned>& balls_i_m, vector<unsigned>& numbers, bool first, bool second, bool third)
{
	bool ret = true;
	if (first)
	{
		ret = this->check(name_i);
	}
	if(second)
	{
		ret = ret && this->check(test_id_i);
	}
	if(third)
	{
		ret = ret && this->check(balls_i_l, balls_i_m, numbers);
	}
	if (!first && !second && !third)
		ret = false;
	return ret;
}
unsigned Person::getProperty(vector<unsigned>& weight)
{
	if (readed)
	{
		if(weight.size() < balls.size())
		{
			Test * new_test = new Test ();
			new_test->set_test_id(test_number);
			long int t = new_test->array_ask(*tests->get_pointer(), 0, tests->size());
			unsigned ret = 0;
			if(t > -1)
			{
				if (tests->ind(t).get_readed() == true)
				{
					for (unsigned i = 0; i < tests->ind(t).get_up_limits_size(); i++)
					{
						ret += balls[i] * (tests->ind(t).get_weighting_factor(i));
					}
				}
			}
			return ret;
		}
		else 
		{
			unsigned ret = 0;
			for (unsigned i = 0; i < balls.size(); i++)
			{
				ret += balls[i] * weight[i];
			}
			return ret;
		}
	}
	else 
		cout << "элемент не был корректно сохранён" << endl;
}

Test Test_array::ind(unsigned pos)
{
	return tests[pos];
}
unsigned Test_array::size()
{
	return tests.size();
}
void Test_array::insert(vector<Test>::iterator position, Test value)
{
	tests.insert(position, value);
}
vector<Test>::iterator Test_array::begin()
{
	return tests.begin();
}
vector<Test>::iterator Test_array::end()
{
	return tests.end();
}

void Test_array::save(char* test_filename)
{
	vector<string> saved;
	for(unsigned i = 0; i<tests.size(); i++)
	{
		tests[i].generate(saved);
	}
	ofstream file(test_filename);
	for (unsigned i = 0; i < saved.size(); i++)
	{
		if(saved[i].size() > 0)
			file << saved[i] << endl;
	}
}

vector<Test> * Test_array::get_pointer()
{
	return &tests;
}
bool operator>= (Person A, Person B)
{
//	cout << endl;
//	cout << (A.compare(B)) << endl;
	if (A.compare(B) >= 0)
		return true;
	else 
		return false;
}

bool operator<= (Person A, Person B)
{
//	cout << endl;
//	cout << (B.compare(A) > 0) << endl;
	if (B.compare(A) >= 0)
		return true;
	else 
		return false;
}

istream& operator >> (istream &s, Person& A)
{
	A.readed = true;
	cout << "имя" << endl;
	s >> A.name;
	cout << "№ теста" << endl;
	long int t;
	if (!(s >> t, s.good()) || (t < 0))
	{
		s.clear(ios_base::goodbit);
		s.ignore(100,'\n');
		cout << "номер не может быть отрицательным" << endl;
		A.readed = false;
		return s;
	}
	A.test_number = t;
//	cout << "# " << endl;
	Test * new_test = new Test ();
	new_test->set_test_id(A.test_number);
//	cout << '@' << endl;
	long int pos = new_test->array_ask(*(A.tests->get_pointer()), 0, A.tests->size());
//	long int pos = -1;
	delete new_test;
	unsigned test_pos;
	cout << pos << endl;
	if (pos == -1)
	{
		Test neww;
		if(neww.k_load(*(A.tests->get_pointer()), A.test_number, s, 1))
		{
			cout << "введите критерии теста №" << A.test_number << " для " << A.name << endl;
			Test * new_test = new Test ();
			new_test->set_test_id(A.test_number);
//			cout << new_test->array_ask(*(A.tests->get_pointer()), 0, A.tests->size()) << endl;
			for (unsigned i = 0;i < (A.tests->ind(new_test->array_ask(*(A.tests->get_pointer()), 0, A.tests->size()))).get_up_limits_size(); i++)
			{
				if (!(s >> t, s.good()) || (t < neww.get_down_limit(i)) || (t > neww.get_up_limit(i)))
				{
					s.clear(ios_base::goodbit);
					s.ignore(100,'\n');
					cout << "значение некорректно" << endl;
					A.readed = false;
					return s;
				}
				A.balls.insert(A.balls.end(), t);
			}
			delete new_test;
		}
		else
		{
			A.readed = false;
			return s;
		}
	}
	else
	{
		test_pos = pos;
		cout << "введите критерии теста №" << A.test_number << " для " << A.name << endl;
		//s >> t;
		pos = A.tests->ind(test_pos).get_up_limits_size();
		for (unsigned i = 0;i < pos; i++)
		{
			if (!(s >> t, s.good()) || (t < A.tests->ind(test_pos).get_down_limit(i)) || (t > A.tests->ind(test_pos).get_up_limit(i)))
			{
//				cout << "!(s >> t, s.good())" << !(s >> t, s.good()) << "(t < A.tests->ind(test_pos).get_down_limit(i))" << (t < A.tests->ind(test_pos).get_down_limit(i)) << "(t > A.tests->ind(test_pos).get_up_limit(i))" << (t > A.tests->ind(test_pos).get_up_limit(i)) <<endl;
//				cout << "t" << t
				s.clear(ios_base::goodbit);
				s.ignore(100,'\n');
				cout << "значение некорректно" << endl;
				A.readed = false;
				return s;
			}
			A.balls.insert(A.balls.end(), t);
		}
	}
	return s;
}

ostream& operator << (ostream &s, Person& A)
{
//	s<<"code";
	if (A.get_readed())
	{
		vector<string> saved;
		A.make_out_array(saved);
		for (unsigned i = 1; i < saved.size(); i++)
			if(saved[i].size() > 0)
				s << saved[i] << endl;
	}
	else
		s << "элемент не был корректно сохранён" << endl;
	return s;
}
short int Person::compare_for_sort(Person A,Person B)
{
	return A.compare(B);
}

//void Person::hard_write(char* filename, char* test_filename/*, bool mode*/)
//{
//	if (readed)
//	{
//		vector<string> saved;
//		make_out_array(saved);
//		ofstream file(filename);
//		for (unsigned i = 0; i < saved.size(); i++)
//		{
////			cout<<i<<' ';
//			if(saved[i].size() > 0)
//				file << saved[i] << endl;
//		}
//		file.close();
//		Test * new_test = new Test ();
//		long int t = new_test->array_ask(*tests->get_pointer(), 0, tests->size());
//		delete new_test;
//		//		cout << '@' << t << endl;
//		if (t > -1)
//		{
////			cout << tests->ind(t).get_test_id();
////			if(mode)
//				tests->ind(t).hard_write(test_filename);
////			else
////				tests->ind(t).soft_write(test_filename);
//		}
//		else
//			cout << "ошибка записи теста в файл" << endl;
//	}
//	else 
//		cout << "элемент не был корректно сохранён" << endl;
//}