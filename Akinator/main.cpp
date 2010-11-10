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
	while (true)
	{
		int c = command();
		switch (c)
		{
			case 1:
				qt.guess();
				break;
			case 2:
				qt.addQuestion();
				break;
			case 0:
				return 0;
		}
		qt = QuestionTable();
	}
	return 0;
}