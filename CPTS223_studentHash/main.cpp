/*
Luke Clancy

This program is made to process excel documents from TAs and (given the right formating which you can see in 
the files given) auto generate the excel files "details.csv" and "overall.csv". The Educational purpose of this program is
to practice hashtables and vectors. As such given the student ID the students data could be

I made a hashTable of vectors. The hashtable keeps track of the students, while the vector
is used to keep track of student information. File format must follow the examples in 
resourse files otherwise entrys will not work.

*/

#include "studentManager.h"

void main()
{
	int x;
	studentManager *myClass = new studentManager();
	myClass->setUp();
	//myClass.printList(); my own function
	myClass->writeFileOne();//overwrites details.csv if none exists creates new
	myClass->writeFileTwo();//overwrites overall.csv if none exists creates new
	delete myClass;//deallocate data
	return;
}
