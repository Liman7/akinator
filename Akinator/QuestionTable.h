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
	Queue positive;
	Queue negative;
	int personsNumber;
	int questionsNumber;
	//void addQuestion(int, int);
	//void addPerson(int, int);
public:
	QuestionTable();
	~QuestionTable();
	void setQuestionTable();
	int nextQuestionNumber();
	void guess();
private:
	void newTable();
	int newQuestionValue(int);
	void nextStep();
public:
	void addPerson();
	void addQuestion();
private:
	void addAnswers(int);
};