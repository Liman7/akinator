#include <iostream>
#include <string>
#include <stdexcept>
#include "userCommunication.h"
using namespace std;

int userAnswer(string q)
{
	cout << q;
	string s;
	cin >> s;
	if ((s[0] == 'y') || (s[0] == 'Y'))
		return 1;
	if ((s[0] == 'n') || (s[0] == 'N'))
		return -1;
	return 0;
}

void write(int a)
{
	cout << a;
}

void write(string s)
{
	cout << s;
}

string characterName(string s)
{
	std::cout << s;
	string str, str1;
	std::cin >> str;
	std::cin >> str1;
	str += " ";
	str += str1;
	return str;
}

string newQuestion()
{
	std::cout << "Please, write here your question" << "\n";
	string s, str;
	do
	{
		std :: cin >> s;
		str += s;
		str += " ";
	}
	while (s[s.size() - 1] != '?');
	return str;
}

int command()
{
	string s;
	while (true)
	{
		std::cin >> s;
		switch (s[0])
		{
			case 'g':
				return 1;
			case 'a':
				return 2;
			case 'e':
				return 0;
			default:
			std::cout << "To play the game please write 'guess'\n";
			std::cout << "To add a question please write 'add'\n";
			std::cout << "To exit please write 'exit'\n";
		}
	}
}

