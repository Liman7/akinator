#include <iostream>
#include <stdexcept>
#include <string>
#include "QuestionTable.h"
#include <vector>
#include <fstream>
using namespace std;

const int MAX_ANS = 1000;
const int MAX_WRONG_ANS = 5;

void QuestionTable::newTable()
{
	questions = Table(MAX_ANS);
	ifstream input("questions.txt");
	int n;
	input >> n;
	questionsNumber = n;
	int p;
	for (int i = 0; i < n; ++i)
	{
		input >> p;
		questions.addToTable(p, i);
	}
	ifstream input2("persons.txt");
	input2 >> n;
	personsNumber = n;
	persons = Table(MAX_WRONG_ANS);
	for(int i = 0; i < n; ++i)
	{
		persons.addToTable(0, i);
	}
}

QuestionTable::QuestionTable()
{
	newTable();
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
		int i = -1;
		while (q1 > 0)
		{
			vec.push_back(q1 % 10);
			q1 /= 10;
			++i;
		}
		for (int j = i; j >= 0; --j)
		{
			s += (char)('0' + vec[j]);
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
		while ((!questions.isEmpty()) && (questions.getN0() != 0) && (!persons.isClear()) && (i < 20))
		{
			++i;
			write(i);
			write(".");
			nextStep();
		}
		++i;
		persons.setN0(0);
		Node* minVal = persons.minValue();
		string s;
		if (minVal != NULL)
			s = fileName(minVal -> a, true);
		else
		{
			addPerson();
			break;
		}
		persons.setCurrentToHead();
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
			addAnswers(minVal -> a);
			break;
		}
		delete minVal;
		if ((i >= 20) || (j >= 2))
		{
			addPerson();
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
		positive.addToQueue(q -> a);
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
		negative.addToQueue(q -> a);
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

void addAnswer(int k, int l, bool ans)
{
	string s = fileName(k, false);
	ifstream input(s.c_str());
	int n, m;
	input >> n >> m;
	vector<int> pos;
	pos.resize(n);
	for (int i = 0; i < n; ++i)
	{
		input >> pos[i];
		if (pos[i] == l)
			return;
	}
	vector<int> neg;
	neg.resize(m);
	for (int i = 0; i < m; ++i)
	{	
		input >> neg[i];
		if (neg[i] == l)
			return;
	}
	string question;	
	getline(input, question);
	getline(input, question);
	input.close();
	if (ans)
	{
		++n;
		pos.push_back(l);
		int i = n - 1;
		while ((i > 0) && (pos[i - 1] > pos[i]))
		{
			int c = pos[i];
			pos[i] = pos[i - 1];
			pos[i - 1] = c;
		}
	}
	else
	{
		++m;
		neg.push_back(l);
		int i = m - 1;
		while ((i > 0) && (neg[i - 1] > neg[i]))
		{
			int c = neg[i];
			neg[i] = neg[i - 1];
			neg[i - 1] = c;
		}
	}
	ofstream output(s.c_str());
	output << n << " " << m << "\n";
	for (int i = 0; i < n; ++i)
		output << pos[i] << " ";
	output << "\n";
	for (int i = 0; i < m; ++i)
		output << neg[i] << " ";
	output << "\n";
	output << question;
}

int currency(int i)
{
	string s = fileName(i, false);
	ifstream input(s.c_str());
	int n, m;
	input >> n >> m;
	return min(m, n);
}

void QuestionTable::addPerson()
{
	int n;
	ifstream input("persons.txt");
	input >> n;
	++n;
	input.close();
	ofstream output1("persons.txt");
	output1 << n;
	output1.close();
	string s = fileName(n - 1, true);
	ofstream output(s.c_str());
	string name = characterName("What is your character's name?");
	output << name;
	output.close();
	addAnswers(n - 1);
}

void QuestionTable::addQuestion()
{
	string question = newQuestion();
	write("Please, answer this question for a few characters\n");
	int m = 0;
	int n = 0;
	Queue pos, neg;
	int i = 0;
	while (i < personsNumber)
	{
		string s = fileName(i, true);
		ifstream input(s.c_str());
		getline(input, s);
		input.close();
		int ans = userAnswer(s + ": ");
		if (ans == 1)
		{
			++m;
			pos.addToQueue(i);
		}
		else if (ans == -1)
		{
			++n;
			neg.addToQueue(i);
		}
		if ((i % 5 == 0) && (i > 0) && (userAnswer("Continue?") != 1))
		{
				break;
		}
		++i;
	}
	ifstream input("questions.txt");
	int k;
	input >> k;
	int * a = new int [k];
	for (int i = 0; i < k; ++i)
	{
		input >> a[i];
	}
	input.close();
	string s = fileName(k, false);
	ofstream output(s.c_str());
	output << m << " " << n << "\n";
	while (!pos.isEmpty())
		output << pos.headValue()->a << " ";
	output << "\n";
	while (!neg.isEmpty())
		output << neg.headValue()->a << " ";
	output << "\n";
	output << question;
	output.close();
	ofstream output2("questions.txt");
	output2 << (k + 1) << "\n";
	for (int i = 0; i < k; ++i)
		output2 << a[i] << " ";
	output2 << (min(m, n));
}

void QuestionTable::addAnswers(int l)
{
	while (!(positive.isEmpty()))
		addAnswer(positive.headValue()->a, l, true);
	while (!(negative.isEmpty()))
		addAnswer(negative.headValue()->a, l, false);
	newTable();
	int num;
	ifstream input("questions.txt");
	input >> num;
	ofstream output("questions.txt");
	output << num << "\n";
	for (int i = 0; i < num; ++i)
	{
		output << currency(i) << " ";
	}	
}