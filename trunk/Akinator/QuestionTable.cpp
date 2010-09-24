#include <iostream>
#include <stdexcept>
#include <string>
#include "QuestionTable.h"
#include <vector>
#include <fstream>
using namespace std;

const int MAX_ANS = 1000;
const int MAX_WRONG_ANS = 5;

QuestionTable::QuestionTable()
{
	questions = Table(MAX_ANS);
	ifstream input("questions.txt");
	int n;
	input >> n;
	int p;
	for (int i = 0; i < n; ++i)
	{
		input >> p;
		questions.addToTable(p, i);
	}
	ifstream input2("persons.txt");
	input2 >> n;
	persons = Table(MAX_WRONG_ANS);
	for(int i = 0; i < n; ++i)
	{
		persons.addToTable(0, i);
	}
}

QuestionTable::~QuestionTable()
{

}

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

string fileName(int q, bool isPerson)
{
	string s = "persons";
	if (isPerson)
		s = "persons/";
	else
		s = "questions/";
	if (q == 0)
		s += (char)('0');
	else
	{
		vector<int> vec;
		vec.resize(0);
		int q1 = q;
		int i = 0;
		while (q1 > 0)
		{
			vec.push_back(q1 % 10);
			q1 /= 10;
		}
		for (int j = 0; j <= i; ++j)
		{
			s += (char)('0' + vec[i]);
		}
	}	
	s += ".txt";
	return s;
}

int QuestionTable::newQuestionValue(int q)
{
	string s = fileName(q, false);
	ifstream input(s.c_str());
	int m, n;
	input >> m >> n;
	float p1 = 0;
	for (int i = 0; i < m; ++i)
	{
		int k;
		input >> k;
		p1 += persons.currency(k);
	}
	persons.setCurrentToHead();
	float p2 = 0;
	for (int i = 0; i < n; ++i)
	{
		int k;
		input >> k;
		p2 += persons.currency(k);
	}
	input.close();
	persons.setCurrentToHead();
	int t1 = (int)p1;
	int t2 = (int)p2;
	return min(t1, t2);
}

void QuestionTable::guess()
{
	int i = 0;
	for (int j = 0; j < 3; ++j)
	{
		
		while ((!questions.isEmpty()) && (!questions.isClear()) && (i < 20))
		{
			++i;
			write(i);
			write(".");
			nextStep();
		}
		++i;
		persons.setN0(0);
		string s = fileName(persons.minValue() -> a, true);
		ifstream input(s.c_str());
		getline(input, s);
		write(i);
		write(".Is ");
		write(s);
		int ans = userAnswer(" your character?");
		while (ans == 0)
		{
			ans = userAnswer("Please, answer yes or no");
		}
		if (ans == 1)
		{
			write("=)");
			break;
		}
		if ((i >= 20) || (j >= 2))
		{
			write("You win");
			break;
		}
	}
}

void QuestionTable::nextStep()
{
	Node * q = questions.headValue();
	while(true)
	{
		int i = newQuestionValue(q -> a);
		int j = questions.getN0();
		if (i == j)
			break;
		questions.addToTable(q, i);
		q = questions.headValue();
	}
	string s = fileName(q -> a, false);
	ifstream input(s.c_str());
	vector<int> pos;
	vector<int> neg;
	int m;
	int n;
	input >> m >> n;
	pos.resize(m);
	neg.resize(n);
	for (int i = 0; i < m; ++i)
	{
		input >> pos[i];
	}
	for (int i = 0; i < n; ++i)
	{
		input >> neg[i];
	}
	string str;
	getline(input, str);
	getline(input, str);
	input.close();
	int ans = userAnswer(str);
	Table* t = new Table(MAX_WRONG_ANS);
	if (ans == 1)
	{
		for (int i = 0; i < n; ++i)
		{
			int j = persons.search(neg[i]);
			if (j != -1)
			{
				Node* tmp = persons.current(j);
				if (j + 1 < MAX_WRONG_ANS)
				{
					t->addToTable(tmp, j + 1);
				}
				else
				{
					delete tmp;
				}
			}
		}
	}
	else if (ans == -1)
	{
		for (int i = 0; i < m; ++i)
		{
			int j = persons.search(pos[i]);
			if (j != -1)
			{
				Node* tmp = persons.current(j);
				if (j + 1 < MAX_WRONG_ANS)
				{
					t->addToTable(tmp, j + 1);
				}
				else
				{
					delete tmp;
				}
			}
		}
	}
	persons.addTable(t);
	delete t;	
	persons.setCurrentToHead();
}
