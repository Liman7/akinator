#include <iostream>
#include <stdexcept>
#include <string>
#include "userCommunication.h"
#include "Questiontable.h"
#include <fstream>
using namespace std;

int main()
{
	QuestionTable qt;
	qt = QuestionTable();
	qt.guess();
	int i;
	cin >> i;
	return 0;
}