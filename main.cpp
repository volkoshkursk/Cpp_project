#include "func.h"
//#include <cstdlib> // генератор случайных чисел 
//#include <ctime>
//#include <cstring>

int main()
{
	
	Test_array tests;
	List<Person> L(&tests);
//	Person A(&tests);
//	A.read("person.txt", "test.txt", 0);
////	cout << A << endl;
//	A.read("person.txt", "test.txt", 1);
////	cout << A << endl;
//	A.read("person.txt", "test.txt", 2);
////	cout << A << endl;
//	List<Person> L(4,&tests);
//	ifstream file("per.txt");
//	file >> L;
//	cout << L << endl;
//	L.sort();
//	cout << L << endl;
	bool work = true;
	string command;
	char* cmd_to_func;
	
	load(L, "person1.txt,test1.txt");
	List<Person> T= L;
	while (work)
	{
//		cout << "--------------------" << endl;
//		cout << L.get_first() << endl;
////		cout << L.get_middle() << endl;
//		cout << L.get_last() << endl;
//		cout << L.get_num() << endl;
//		Node<Person>* t = L.get_first();
//		for(unsigned i = 0; i < L.get_num(); i++)
//		{
//			cout << i <<endl;
////			cout << t->get_value().get_readed() << endl;
//			cout << "now"<<t << endl;
//			cout << "pre" << t->get_previous() <<endl;
//			cout << "next" << t ->get_next() << endl;
//			t = t->get_next();
//		}
//		cout << "--------------------" << endl;
		cin >> command;
		if (command.substr(0,4) == "help")
			help();
		else 
			if (command.substr(0,4) == "sort")
				sort(L);
			else
				if (command.substr(0,5) == "clear") 
					clear(L);
				else 
					if (command.substr(0,4) == "load") 
					{
						if (command.size() > 6)
						{
							command = command.substr(5,command.size()-6);
							load(L, command);
						}
						else
							cout << "неправильные значения" << endl;
					}
					else 
						if (command.substr(0,4) == "save") 
						{
							if (command.size() > 6)
							{
								command = command.substr(5,command.size()-6);
								save(L, command);
							}
							else
								cout << "неправильные значения" << endl;
						}
						else
							if(command.substr(0,4) == "exit") 
							{
								cout << "сохранить? [y/n]"<< endl;
								cin >> command;
								if (command == "y")
								{
									bool exited = false;
									while(!exited)
									{
										cout << "введите адрес" << endl;
										cin >> command;
										exited = save(L,command);
									}
								}
								work = false;
							}
							else
								if (command.substr(0,5) == "print")
									if(L.get_num() > 0)
										cout << L << endl;
									else
										cout << "список пустой"<< endl;
								else
									if (command.substr(0,4) == "find")
										read(L, "введите условия поиска", find);
									else 
										if (command.substr(0,3) == "add")
											read(L, "введите условия поиска", add);
										else
											if (command.substr(0,6) == "delete")
												read(L, "введите условия поиска", del);
											else
												if (command.substr(0,6) == "testno")
												{
													cin >> command;
													print(L, abs(atol(command.c_str())));
												}
													else
														cout << "комманды " << command << " не существует" << endl;
				
		}

	
	return 0;
}