#pragma once
#include "person.h"

template <class T>
class Node
{
protected:
	Node* Previous;
	Node* Next;
	T value;
//	unsigned num;
public:
	Node(T value);
	void set_previous(Node * Pre);
	void set_next(Node * Ne);
	void set_value(T value);
	Node* get_previous();
	Node* get_next();
//	unsigned get_num();
	T get_value();
//	void set_num(unsigned n)
//	{
//		num = n;
//	}
};

template <class T>
class List
{
protected:
	Test_array* tests;
	Node<T>* first;
	Node<T>* middle;
	Node<T>* last;
	unsigned num;
	bool middle_correct;
	bool sorted;
// --------------------------
	void refind_mid();
	void frontBackSplit( Node<T>* theHead , Node<T>* &frontRef , Node<T>* &backRef );
	void mergeSort(Node<T>* &theHead);
//	Node<T>* q_search(string s_name, unsigned *s_test, vector<unsigned>& s_balls_u, vector<unsigned>& s_balls_l, vector<unsigned>& s_nums, bool a, bool b, bool c, unsigned n, Node<T>* s_first, Node<T>* s_end, T& obj);
public:
	unsigned get_num();
	Node<T>* get_first()
	{
		return first;
	}
	Node<T>* get_middle();
	Node<T>* get_last()
	{
		return last;
	}
	Test_array* get_tests();
	void kill_sorted(){sorted = false;}
	List(Test_array* tests1);
	List(unsigned n, Test_array* tests1);
	~List();
	List(List& old);
	void add(Node<T>* after, T value);
	void pop(Node<T>* obj);
	void print(ostream& s, unsigned test_num);
	bool get_middle_correct()
	{
		return middle_correct;
	}
	bool get_sorted()
	{
		return sorted;
	}
//	void generate_part(Node<T>* start, Node<T>* end, unsigned num);
	void sort();
	void load(char* filename, char* test_filename);
	void save(char* filename, char* test_filename);
	void read();
	Node<T>* search(vector<unsigned>& s_balls_u, vector<unsigned>& s_balls_l, vector<unsigned>& s_nums, Node<T> * head, Node<T> * end, string s_name = " ", unsigned *s_test = NULL);
};

template <class T>
Node<T>::Node(T value)
{
	Previous = NULL;
	Next = NULL;
//	num = n;
	this->value = value;
}

template <class T>
void Node<T>::set_value(T value)
{
	this->value = value;
}

template <class T>
void Node<T>::set_previous(Node * Pre)
{
	Previous = Pre;
}

template <class T>
void Node<T>::set_next(Node * Ne)
{
	Next = Ne;
}

template <class T>
Node<T>* Node<T>::get_previous()
{
	return Previous;
}

template <class T>
Node<T>* Node<T>::get_next()
{
	return Next;
}

//template <class T>
//unsigned Node<T>::get_num()
//{
//	return num;
//}

template <class T>
T Node<T>::get_value()
{
	return value;
}
template <class T>
List<T>::List(Test_array* tests1)
{
	first = NULL;
	middle = NULL;
	last = NULL;
	T* p;
	if ((strcmp("Person", typeid(*p).name())!=0) && (tests1 == NULL))
		tests = new Test_array;
	else
		tests = tests1;
	num = 0;
	middle_correct = true;
	sorted = false;
}

template <class T>
Node<T>* List<T>::get_middle()
{
	if (!middle_correct)
		refind_mid();
	return middle;
}

template <class T>
List<T>::~List()
{
//	cout << '@' << endl;
	if (first != NULL)
	{
		Node<T>* now = first;
		if (first->get_next() != NULL)
		{
//			cout << '@' << endl;
			Node<T>* forw = first->get_next();
			while (now->get_next() != NULL) 
			{
				delete now;
				now = forw;
				if (now != NULL)
					forw = now->get_next(); 
			}
			delete now;
		}
		else
			delete first;
	}
	else if (middle != NULL) 
	{
		Node<T>* now = middle;
		if (middle->get_previous() != NULL)
		{
			Node<T>* forw = now->get_previous();
			while (now->get_previous() != NULL) 
			{
				delete now;
				now = forw;
				forw = now->get_previous(); 
			}
			delete now;
		}
		else
			delete now;
		now = middle;
		if (middle->get_next() != NULL)
		{
//			cout << '@' << endl;
			Node<T>* forw = now->get_next();
			while (now->get_next() != NULL) 
			{
				delete now;
				now = forw;
				if (now != NULL)
					forw = now->get_next(); 
			}
			delete now;
		}
		else
			delete first;
	}
	else if (last != NULL) 
	{
		Node<T>* now = last;
		if (last->get_previous() != NULL)
		{
			Node<T>* forw = now->get_previous();
			while (now->get_previous() != NULL) 
			{
				delete now;
				now = forw;
				forw = now->get_previous(); 
			}
			delete now;
		}
		else
			delete now;
	}
	first = NULL;
	middle = NULL;
	last = NULL;
	num = 0;
	middle_correct = false;
	sorted = false;
}

template <class T>
Test_array* List<T>::get_tests()
{
	return tests;
}


template <class T>
List<T>::List(unsigned n, Test_array* tests1)
{
	T ini;
	middle_correct = true;
	sorted = false;
	tests = tests1;
	if (strcmp("Person", typeid(ini).name())!=0)
	{
		if (tests1 == NULL)
			tests = new Test_array;
		ini.initialize(tests);
	}
	num = n;
//	n--;
	first = new Node<T>(ini);
	Node<T>* t = first;
	Node<T>* tt;
//	cout << '%' << endl;
	for(unsigned i = 1; i < num;i++)
	{
		tt = new Node<T>(ini);
//		cout << i << endl;
		t->set_next(tt);
		tt->set_previous(t);
		if (i == (num / 2))
		{
			middle = tt;
//			cout << i << " middle "<< (num/2) << endl;
		}
		t = t->get_next();
	}
	last = tt;
}

template <class T>
unsigned List<T>::get_num()
{
	return num;
}

template <class T>
List<T>::List(List& old)
{
//	cout << typeid(*this).name() << ' ' << typeid(old).name() << endl;
	if (typeid(*this).name() == typeid(old).name())
	{
//		cout << "!2" << endl;
		num = old.get_num();
		unsigned n = num;
//		T = typeid(old);
		tests = old.get_tests();
		first = new Node<T>(old.get_first()->get_value());
		Node<T>* t = first;
		Node<T>* tt;
		Node<T>* o = old.get_first();
		o = o->get_next();
		while(o->get_next() != NULL)
		{
			tt = new Node<T>(o->get_value());
			t->set_next(tt);
			tt->set_previous(t);
			if (n == (num / 2))
				middle = tt;
			if (n==0)
				last = tt;
			t = tt;
//			tt = tt->get_next();
			o = o -> get_next();
			n--;
		}
		tt = new Node<T>(o->get_value());
		t->set_next(tt);
		tt->set_previous(t);
		if (n == ((num / 2)+1))
			middle = tt;
		if (n==0)
			last = tt;
		middle_correct = old.get_middle_correct();
		sorted = old.get_sorted();
//		tt = tt->get_next();
	}
	else
		cout << "при копировании возникли ошибки" << endl;
}

template <class T>
ostream& operator << (ostream &s, List<T>& A)
{
	T o = A.get_first()->get_value();
	Node<T>* t = A.get_first();
	for (unsigned i = 0; i < A.get_num()-1; i++)
	{
		s << o << endl;
		t = t->get_next();
		o = t->get_value();
	}
	s << o << endl;
	return s;
}


template <class T>
istream& operator >> (istream &s, List<T>& A)
{
	T o;
	if (strcmp("Person", typeid(o).name())!=0)
		o.initialize(A.get_tests());
	Node<T>* t = A.get_first();
	A.kill_sorted();
//	cout << '^' <<A.get_num() << endl;
	for (unsigned i = 0; i< A.get_num(); i++)
	{
//		cout << "@" << i << endl;
		s >> o;
		t->set_value(o);
		t = t->get_next();
		o.clear();
		if (strcmp("Person", typeid(o).name())!=0)
			o.initialize(A.get_tests());
	}
	return s;
}
template <class T>
void List<T>::add(Node<T>* after, T value)
{
	num++;
	middle_correct = false;
	sorted = false;
	if (after != NULL)
	{
		Node<T>* tt = new Node<T>(value);
		tt->set_next(after->get_next());
		after->set_next(tt);
		tt->set_previous(after);
		if (after == last)
			last = tt;
	}
	else
	{
//		cout << '@' << endl;
		Node<T>* tt = new Node<T>(value);
		tt->set_next(first);
		first = tt;
		if(last == NULL)
		{
			last = tt;
		}
//		middle = middle->get_previous();
	}
}

template <class T>
void List<T>::refind_mid()
{
	
	middle_correct = true;
	T o = middle->get_value();
//	cout << "!!!!" << endl;
//	cout << o << endl;
	Node<T>* t = first;
	for(unsigned i = 0; i < (num / 2); i++)
	{
		t = t->get_next();
	}
	middle = t;
	o = middle->get_value();
	cout << o << endl;
}

template <class T>
void List<T>::pop(Node<T>* obj)
{
	num --;
//	cout << '@' << num << endl;
	middle_correct = false;
	Node<T>* t = obj->get_next();
//	cout << '@' << t << endl;
	Node<T>* tt = obj->get_previous();
//	cout << '@' << tt << endl;
	if(t != NULL)
		if (tt != NULL)
			t->set_previous(tt);
		else 
			t->set_previous(NULL);
	else 
		last = tt;
	if (tt != NULL)
		if (t != NULL)
			tt->set_next(t);
		else 
			tt->set_next(NULL);
	else 
		first = t;
	
	delete obj;
	
}

template <class T>
void List<T>::print(ostream& s, unsigned test_num)
{
	T o;
	if (strcmp("Person", typeid(o).name())!=0)
	{
		vector<unsigned> a;
		Node<T>* t = first;
		for (unsigned i = 0; i < num; i ++)
		{
			o = t->get_value();
			if(o.check("", test_num, a, a, a, 0, 1, 0))
				s << o << endl;
			t = t->get_next();
		}
	}
	else 
		s << "type error" << endl;
}

template <class T>
Node<T>* List<T>::search(vector<unsigned>& s_balls_u, vector<unsigned>& s_balls_l, vector<unsigned>& s_nums, Node<T> * head, Node<T> * end, string s_name, unsigned *s_test)
{
	T o;
	if (strcmp("Person", typeid(o).name())!=0)
	{
		if ((head == NULL) || (end == NULL))
			return NULL;
		o.initialize(tests);
		bool a;
		bool b;
		bool c;
		a = (s_name == " ");
		b = (s_test == NULL);
		c = (s_balls_u.size() == 0) && (s_balls_l.size() == 0);
		if ((a && b && c) || (num == 0))
			return NULL;
//		if(!(a) && sorted && !(b))
//		{
//			unsigned q;
//			q = *s_test;
//			vector<unsigned> y = (tests->ind(0)).get_up_limits();
////			cout << y.size() << endl;
////			for(unsigned i = 0; i < y.size(); i++)
////				cout << y[i] << endl;
//			o.set(s_name, q, y);
//			return q_search(s_name, &q, s_balls_u, s_balls_l, s_nums, !(a), !(b), !(c), number, head, end, o);
//		}
//		else 
//		{
		Node<T> * t = head;
		unsigned q;
		if (!b)
			q = *s_test;
		else 
			q = (tests->ind(0)).get_test_id();
		o = head->get_value();
		if (o.check(s_name, q, s_balls_l, s_balls_u, s_nums, !(a), !(b), !(c)))
			return head;
		if (head == end)
			return NULL;
//		cout << "@ " << << endl;
		o.clear();
		t = head->get_next();
		while(t != end)
		{
			o = t->get_value();
//			cout << "t " << t << endl;
//			cout << o.check(s_name, q, s_balls_l, s_balls_u, s_nums, !(a), !(b), !(c)) << endl;
			if (o.check(s_name, q, s_balls_l, s_balls_u, s_nums, !(a), !(b), !(c)))
			{
				o.clear();
				return t;
			}
//			cout << "§" << endl;
			
//			if(t->get_next() != )
			
//			cout << t->get_next() <<endl;
			t = t->get_next();
		}
		if (end != NULL)
		{
			o = t->get_value();
			if (o.check(s_name, q, s_balls_l, s_balls_u, s_nums, !(a), !(b), !(c)))
				return t;
		}
		return NULL;
//		}
	}
	else 
		return NULL;
		
}

template <class T>
void List<T>::load(char* filename, char* test_filename)
{
	T A;
	if (strcmp("Person", typeid(A).name())!=0)
	{
		if (file_ask(filename))
		{
			ifstream file(filename);
			string file_s;
			vector<unsigned> nums;
			while (getline(file, file_s), !file.eof()) 
			{
//				cout << file_s << endl;
//				cout << file_s.substr(0,4) << endl;
				if(file_s.substr(0,5) == "<num>")
				{
					file_s = file_s.substr(5,file_s.size()-5);
//					cout << "@"<< file_s << endl;
					nums.push_back(abs(atol(file_s.c_str())));
				}
			}
//			unsigned e;      // эта переменная
//			vector<unsigned> p;// и эта
			for (unsigned i = 0; i < nums.size(); i++)
			{
				A.initialize(tests);
				A.read(filename, test_filename, nums[i]);
				
//				cout << A << endl;

				if (A.get_readed())
				{
//					e = A.get_test_number();
//				 	if (q_search(A.get_name(), &e , p, p, p, 1, 1, 0, num, first, last, A) == NULL) // и условие здесь нужно, если пара имя-номер теста должна быть уникальна
						add(last, A);
				}
			}
		}
		else
			cout << "файла " << filename <<" не существует" << endl; 
	}
	else 
		cout << "type error" << endl;
}
	
template <class T>
void List<T>::save(char* filename, char* test_filename)
{
	T o;
	if (strcmp("Person", typeid(o).name())!=0)
	{
		vector<string> saved;
		Node<Person>* t = first;
		for (unsigned i = 0; i < num; i++)
		{
			o = t -> get_value();
			o.make_out_array(saved, i);
			t = t -> get_next();
		}
		ofstream file(filename);
		for (unsigned i = 0; i < saved.size(); i++)
		{
			if(saved[i].size() > 0)
				file << saved[i] << endl;
		}
		file.close();
		tests->save(test_filename);
//		for(unsigned t = 0; t < tests->size(); t++)
			//tests->ind(t).hard_write(test_filename);
	}
	else 
		cout << "type error" << endl;

}
//template <class T>
//Node<T>* List<T>::q_search(string s_name,unsigned *s_test, vector<unsigned>& s_balls_u, vector<unsigned>& s_balls_l, vector<unsigned>& s_nums, bool a, bool b, bool c, unsigned n, Node<T>* s_first, Node<T>* s_end, T& obj)
//{
//	Node<T> * mid = s_first;
//	for (unsigned i = 0;i < n /2 ;i++)
//	{
//		mid = mid -> get_next();
//	}
//	if ((mid->get_value()).check(s_name, *s_test, s_balls_l, s_balls_u, s_nums, a, b, c))
//	{
//		return mid;
//	}
//	if (s_first == s_end)
//		return NULL;
//	else
//	{
//		
//		if (mid->get_value() <= obj)
//		{
////			cout << '#' << endl;
//			if (mid->get_next() == NULL)
//				return NULL;
//			if ((mid->get_next()->get_value()) >= obj)
//				return NULL;
//			return q_search(s_name, s_test, s_balls_u, s_balls_l, s_nums, a, b, c, n/2, mid->get_next(), s_end, obj);
//		}
//		else
//		{
////			cout << '@' << endl;
////			cout << (mid->get_previous() == NULL) << endl;
////			cout << ((mid->get_previous()->get_value()) < obj) << endl;
//			if (mid->get_previous() == NULL)
//				return NULL;
//			if ((mid->get_previous()->get_value()) <= obj)
//				return NULL;
//			return q_search(s_name, s_test, s_balls_u, s_balls_l, s_nums, a, b, c, n/2, s_first, mid->get_previous(), obj);
//		}
//	}
//}

//--------------------------------------------------------------
template <class T>
void List<T>::sort()
{
	sorted = true;
	mergeSort( first );
	while (last->get_next() != NULL) 
	{
		last = last -> get_next();
	}
}


template <class T>
void List<T>::mergeSort(Node<T>* &theHead)
{
	Node<T>* a = nullptr;
	Node<T>* b = nullptr;

	// Base case
	if( theHead == NULL || theHead->get_next() == NULL )
	{
		return;
	}

	// Split the list in half
	// For odd number of nodes, the extra node will be in the first half.
	frontBackSplit( theHead , a , b );

	// Recursively break the list down until the sublist contains 1 element (Sorted)
	mergeSort( a );
	mergeSort( b );

	// Merge the two sorted lists
	theHead = sortedMerge( a , b );
}

template <class T>
void List<T>::frontBackSplit( Node<T>* theHead , Node<T>* &frontRef , Node<T>* &backRef )
{
	Node<T>* fast;
	Node<T>* slow;

	// If the list is empty, both front and back points to null
	// If there is only one element, front points to it and back points
	//  to null.
	if( theHead == nullptr || theHead->get_next() == nullptr ) 
	{
		frontRef = theHead;
		backRef = nullptr;
	}
	else 
	{
		slow = theHead;
		fast = theHead->get_next();

		// Fast advances 2 nodes while slow advances 1 node
		while( fast != nullptr ) 
		{
			fast = fast->get_next();

			if( fast != nullptr ) 
			{
				slow = slow->get_next();
				fast = fast->get_next();
			}
		}

		// slow should be pointing right before midpoint. Split at this point
		frontRef = theHead;
		backRef = slow->get_next();

		// Update the prev and next pointers
		backRef->set_previous(NULL);
		slow->set_next(NULL);
	}
}

template <class T>
Node<T>* sortedMerge( Node<T>* a , Node<T>* b )
{
	Node<T>* headOfMerged;
	// If one of the node is nullptr, return the other node
	// No merging occurs this this case
	if( a == NULL ) 
	{
		return b;
	}
	else if( b == NULL ) 
	{
		return a;
	}

	// First element in list, a, is less than the first element in b
	if( a->get_value() <= b->get_value() ) 
	{
		headOfMerged = a;

		while( b != nullptr ) 
		{
			if( a->get_value() <= b->get_value() ) 
			{
				if( a->get_next() == nullptr ) 
				{
					a->set_next(b);
					b->set_previous(a);
					break;
				}
				a = a->get_next();
			}
			else
			{
				Node<T>* toAdd = b;
				b = b->get_next();
				toAdd->set_previous(a->get_previous());
				a->get_previous()->set_next(toAdd);
				toAdd->set_next(a);
				a->set_previous(toAdd);
			}
		}
	}
	// First element in list, b, is less than the first element in a
	else 
	{
		headOfMerged = b;

		while( a != nullptr )
		{
			if( b->get_value() <= a->get_value() ) 
			{
				if( b->get_next() == nullptr ) 
				{
					b->set_next(a);
					a->set_previous(b);
					break;
				}
				b = b->get_next();
			}
			else 
			{
				Node<T>* toAdd = a;
				a = a->get_next();
				toAdd->set_previous(b->get_previous());
				b->get_previous()->set_next(toAdd);
				toAdd->set_next(b);
				b->set_previous(toAdd);
			}
		}
	}

	return headOfMerged;
}
