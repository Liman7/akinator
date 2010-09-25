#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Table.h"
#include "userCommunication.h"
using namespace std;

class QuestionTable
{
private:
	Table persons; 
	Table questions;
	//void addQuestion(int, int);
	//void addPerson(int, int);
public:
	QuestionTable();
	~QuestionTable();
	void setQuestionTable();
	int nextQuestionNumber();
	void guess();
private:
	int newQuestionValue(int);
	void nextStep();
};