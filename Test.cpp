 #include "Test.h"


/*vector <unsigned> Test::get_up_limits()
{
	return up_limits;
}*/

Test::Test()
{
	readed = false;
}

unsigned Test::get_up_limits_size()
{
	return up_limits.size();
}

bool Test::get_readed()
{
	return readed;
}

/*vector <unsigned> Test::get_down_limits()
{	
	return down_limits;
}*/

unsigned Test::get_down_limits_size()
{	
	return down_limits.size();
}

unsigned Test::get_test_id()
{
	return test_id;
}

void Test::set_test_id(unsigned value)
{
	test_id = value;
}

void Test::set_weighting_factor(unsigned value)
{
	weighting_factor.insert(weighting_factor.end(), value);
}
unsigned Test::get_weighting_factor(unsigned pos)
{
	return weighting_factor[pos];
}
unsigned Test::get_up_limit(unsigned pos)
{
	return up_limits[pos];
}

unsigned Test::get_down_limit(unsigned pos)
{
	return down_limits[pos];
}

void Test::set_up_limit(unsigned value)
{
	up_limits.insert(up_limits.end(), value);
}

void Test::set_down_limit(unsigned value)
{
	down_limits.insert(down_limits.end(), value);
}

long int Test::array_ask(vector <Test>& s, unsigned start, unsigned end)
{
//	cout << "array ask!" << endl;
//	for (unsigned i = 0; i < s.size(); i++)
//		cout << s[i].test_id<< ' ';
//	cout << endl;
//	cout << test1id << endl;
	if (s.empty())
		return -1;
	long int pos = (start + end - 1) / 2;
//	cout << "================================"<< endl;
//	cout << '@' <<pos << endl;
//	cout << s[pos].test_id << endl;
//	cout << "================================"<< endl;
//	cout << end << endl;
//	cout << "(s[pos].test_id == test1id)" <<(s[pos].test_id == test1id) << endl;

	if (s[pos].test_id == test_id)
		return pos;
	else 
	{
//		cout << "(s[pos].test_id > test_id)" << (s[pos].test_id > test_id)  << endl;
		if (s[pos].test_id > test_id)
		{
			if (pos-1 > start)
				return this->array_ask(s, start, pos-1);
			else 
			{
				if (s[start].test_id == test_id)
					return start;
				else
					return -1;
			}
		} 
		else 
		{
//			cout << "((s[pos].test_id < test_id) && (pos+1 < end))" <<(s[pos].test_id < test_id) << (pos+1 < end) << endl;
			if((s[pos].test_id < test_id) && (pos+1 < end))
			{
				return this->array_ask(s, pos+1, end);
			}
			else
				return -1;
		}
	}
}

bool Test::compare_for_sort(Test test1,Test test2)
{
	if (test1.test_id <= test2.test_id)
		return true;
	else 
		return false;
}

void Test::add(vector <Test>& s)
{
	if (readed)
	{
//		cout << test_id << endl;
//		cout << up_limits.size() << endl;
//		cout << down_limits.size() << endl;
		s.insert(s.end(), *this);
		sort(s.begin(), s.begin()+s.size(), compare_for_sort);
	}
}

unsigned Test::load(char* test_filename, vector <Test>& tests)
{
	readed = true;

//	cout << "load" << endl;
//	Test ret;
	if (file_ask(test_filename))
		{
			up_limits.clear();
			down_limits.clear();
			weighting_factor.clear();
			string file_s;
			ifstream file(test_filename);
			while ((file_s != "<num>" + to_string(test_id)) && (!file.eof()))
			{
				getline(file, file_s);
			}
			if(file.eof())
			{
//				cout << "в файле " << test_filename << " теста № " << num << " не существует" << endl;
				readed = false;
				file.close();
				return 1; 
			}
			unsigned temp;
			getline(file, file_s);
			temp = abs(atol(file_s.c_str()));
//			cout << "temp " << temp << endl;
			unsigned t;
			for (unsigned i = 0;i < temp; i++)
			{
				getline(file, file_s);
//				cout << "1 " <<file_s<<endl;
				if (file.eof())
				{
//					cout << "1" <<endl;
					readed = false;
					return 3;
				}
				else
				{	
					t = abs(atol(file_s.c_str()));
					up_limits.insert(up_limits.end(), t);
				}
			}
			for (unsigned i = 0;i < temp; i++)
			{
				getline(file, file_s);
//				cout << "2 " << file_s<<endl;
				if (file.eof())
				{
//					cout << "2" <<endl;
					readed = false;
					return 3;
				}
				else
				{
					t = abs(atol(file_s.c_str()));
					down_limits.insert(down_limits.end(), t);
				}
			}
			for (unsigned i = 0;i < temp; i++)
			{
				getline(file, file_s);
//				cout << "3 " << file_s<<endl;
				if (file.eof())
				{
//					cout << "3" <<endl;
					readed = false;
					return 3;
				}
				else
				{
					t = abs(atol(file_s.c_str()));
					weighting_factor.insert(weighting_factor.end(), t);
				}
			}
			this->add(tests);
			file.close();
			return 0;
		}
	else 
		{
			readed = false;
//			cout << "файла" << test_filename <<"не существует" << endl; 
			return 2;
		}
}

bool Test::k_load(vector <Test>& tests, unsigned num, istream &s, bool key)
{
	readed = true;
	long int t;
	up_limits.clear();
	down_limits.clear();
	weighting_factor.clear();
	long int temp;
	test_id = num;
	if (key)
	{
		cout << "введите количество критериев теста №" << test_id << endl;
		cout << ">";
	}
	while (!(s >> temp, s.good()) || (temp < 0))
	{
		s.clear(ios_base::goodbit);
		s.ignore(100,'\n');
		cout << "значение некорректно" << endl;
		if(!key)
		{
			readed = false;
			return readed;
		}
		else
			cout << ">";
	}
	if(key)
	{
		cout << "введите ограничения сверху для теста №" << test_id << endl;
	}
	for (unsigned i = 0;i < temp; i++)
	{
		if(key)
			cout << ">";
		while (!(s >> t, s.good()) || (t < 0))
		{
			s.clear(ios_base::goodbit);
			s.ignore(100,'\n');
			cout << "значение некорректно" << endl;
			if(!key)
			{
				readed = false;
				return readed;
			}
			else
				cout << ">";
		}
		up_limits.push_back(t);
	}
	if(key)
	{
		cout << "введите ограничения снизу для теста №" << test_id << endl;
	}
	for (unsigned i = 0;i < temp; i++)
	{
		if (key)
			cout << ">";
		while (!(s >> t, s.good()) || (t < 0))
		{
			s.clear(ios_base::goodbit);
			s.ignore(100,'\n');
			cout << "значение некорректно" << endl;
			if(!key)
			{
				readed = false;
				return readed;
			}
			else
				cout << ">";
		}
		down_limits.push_back(t);
	}
	if(key)
		cout << "введите стандартные весовые коэффициенты для теста " << test_id << endl;
	for (unsigned i = 0;i < temp; i++)
	{
		if (key)
			cout << ">";
		while (!(s >> t, s.good()) || (t < 0))
		{
			s.clear(ios_base::goodbit);
			s.ignore(100,'\n');
			cout << "значение некорректно" << endl;
			if(!key)
			{
				readed = false;
				return readed;
			}
			else
				cout << ">";
		}
		weighting_factor.push_back(t);
	}
	this->add(tests);
	return true;
}

/*void Test::soft_write(char* test_filename)
{
//	cout << "write_test" << endl;
	vector<string> saved;
	if (file_ask(test_filename))
	{
//		cout << "code2" << endl;
		string file_s;
		ifstream file(test_filename);
		unsigned num = 0;
		bool searched1 = false;
		unsigned last_num = 0;
		while(!file.eof())
		{
			getline(file, file_s);
			
//			while(file_s == "\n")
//				getline(file, file_s);

			saved.insert(saved.end(),file_s);
			if (!searched1)
				num ++;
			if (file_s.substr(0,5) == "<num>")
			{
				file_s.erase(0,5);
//				cout << file_s << endl;
				last_num = abs(atol(file_s.c_str()));
				if(last_num == test_id)
				{
					searched1 = true;
				}
			}
		}
		file.close();
		// debug
//		cout << '@' << last_num << endl;
//		cout << searched1 << endl;
//		cout << '#' <<num << endl;
//		for (unsigned i = 0; i < saved.size(); i++)
//			cout << saved[i] << endl;
//		cout << "---------------------" <<endl;
		if(searched1)
		{
			num++;
			if (saved[num].substr(0,5) == "<num>")
			{
//				cout << "1st if out" << endl;
				saved.erase(saved.begin() + num - 1, saved.begin() + num);
				searched1 = false;
			}
			
			if(saved[num + 1].substr(0,5) == "<num>")
			{
//				cout << "2nd if out" << endl;
				saved.erase(saved.begin() + num - 1, saved.begin() + num + 1);
				searched1 = false;
			}
		}
		if (searched1)
		{
//			cout << up_limits.size() << '^' << endl;
//			cout << saved[num-1] << '@' << endl;
			if (saved[num - 1] != to_string(up_limits.size()))
				saved[num - 1] = to_string(up_limits.size());
			for(unsigned i = 0; i < up_limits.size(); i++)
			{
				if (num + i < saved.size())
					if (saved[num + i].substr(0,5) != "<num>")
						saved[num + i] = to_string(up_limits[i]);
					else 
						saved.insert(saved.begin() + num + i, to_string(up_limits[i]));
				else 
					saved.insert(saved.begin() + num + i, to_string(up_limits[i]));
			}
			num += up_limits.size();
			for(unsigned i = 0; i < up_limits.size(); i++)
			{
				if (num + i < saved.size())
					if (saved[num + i].substr(0,5) != "<num>")
						saved[num + i] = to_string(down_limits[i]);
					else 
						saved.insert(saved.begin() + num + i, to_string(down_limits[i]));
				else 
					saved.insert(saved.begin() + num + i, to_string(down_limits[i]));
			}
			num += up_limits.size();
			for(unsigned i = 0; i < up_limits.size(); i++)
			{
//				cout << '@' << i << '@' << weighting_factor[i] << endl;
				if (num + i < saved.size())
					if (saved[num + i].substr(0,5) != "<num>")
						saved[num + i] = to_string(weighting_factor[i]);
					else 				
						saved.insert(saved.begin() + num + i, to_string(weighting_factor[i]));
				else 
					saved.insert(saved.begin() + num + i, to_string(weighting_factor[i]));
			}
//			cout << "+++++++++++++++++++++++++++" << endl;
//			for (unsigned i = 0; i < saved.size(); i++)
//				cout << saved[i] << endl;
			num += up_limits.size();
			if (num < saved.size())
				if (saved[num].substr(0,5) != "<num>")
				{
//					cout << "enter" << endl;
					last_num = num;
//					cout << last_num << endl;
					while (saved[num].substr(0,5) != "<num>") 
						num++;
//					cout << last_num << endl;
//					cout << num << endl;
					saved.erase(saved.begin() + last_num, saved.begin() + num);
				}
		}
		if (!searched1)
	 	{
//			cout << "enter" << endl;
			saved.insert(saved.end(), "<num>" + to_string(test_id));
			saved.insert(saved.end(), to_string(up_limits.size()));
			for(unsigned i = 0; i < up_limits.size(); i++)
				saved.insert(saved.end(), to_string(up_limits[i]));
			for(unsigned i = 0; i < up_limits.size(); i++)
				saved.insert(saved.end(), to_string(down_limits[i]));
			for(unsigned i = 0; i < up_limits.size(); i++)
				saved.insert(saved.end(), to_string(weighting_factor[i]));
		}
	}
	else
	{
//		cout << "#####" << endl;
		saved.insert(saved.end(), "<num>" + to_string(test_id));
		saved.insert(saved.end(), to_string(up_limits.size()));
		for(unsigned i = 0; i < up_limits.size(); i++)
			saved.insert(saved.end(), to_string(up_limits[i]));
		for(unsigned i = 0; i < up_limits.size(); i++)
			saved.insert(saved.end(), to_string(down_limits[i]));
		for(unsigned i = 0; i < up_limits.size(); i++)
			saved.insert(saved.end(), to_string(weighting_factor[i]));
	}
	// debug
	for (unsigned i = 0; i < saved.size(); i++)
		cout << saved[i] << endl;

	ofstream file(test_filename);
	for (unsigned i = 0; i < saved.size(); i++)
	{
		if(saved[i].size() > 0)
			file << saved[i] << endl;
	}
	file.close();
}
*/
void Test::generate(vector<string>& saved)
{
	saved.insert(saved.end(), "<num>" + to_string(test_id));
	saved.insert(saved.end(), to_string(up_limits.size()));
	for(unsigned i = 0; i < up_limits.size(); i++)
		saved.insert(saved.end(), to_string(up_limits[i]));
	for(unsigned i = 0; i < up_limits.size(); i++)
		saved.insert(saved.end(), to_string(down_limits[i]));
	for(unsigned i = 0; i < up_limits.size(); i++)
		saved.insert(saved.end(), to_string(weighting_factor[i]));
}
//void Test::hard_write(char* test_filename)
//{
//	vector<string> saved;
//	generate(saved);
//	ofstream file(test_filename);
//	for (unsigned i = 0; i < saved.size(); i++)
//	{
//		if(saved[i].size() > 0)
//			file << saved[i] << endl;
//	}
//}