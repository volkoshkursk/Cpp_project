#pragma once
#include "List.h"

void help(); // помощь
void sort(List<Person>& L);
void clear(List<Person>& L);
void find(List<Person>& L, vector<unsigned>& s_balls_u, vector<unsigned>& s_balls_l, vector<unsigned>& s_nums, string s_name = " ", unsigned *s_test = NULL);
void del(List<Person>& L, vector<unsigned>& s_balls_u, vector<unsigned>& s_balls_l, vector<unsigned>& s_nums, string s_name = " ", unsigned *s_test = NULL);
void load(List<Person>& L, string filenames);
bool save(List<Person>& L, string filenames);
void add(List<Person>& L, vector<unsigned>& s_balls_u, vector<unsigned>& s_balls_l, vector<unsigned>& s_nums, string s_name = " ", unsigned *s_test = NULL);
void read(List<Person>& L, string name, void f(List<Person>& L, vector<unsigned>& s_balls_u, vector<unsigned>& s_balls_l, vector<unsigned>& s_nums, string s_name, unsigned *s_test));
void print(List<Person>& L, unsigned n);