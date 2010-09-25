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

