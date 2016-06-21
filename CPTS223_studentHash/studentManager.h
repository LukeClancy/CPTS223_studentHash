#ifndef STUMANAGER
#define STUMANAGER
#include <fstream>
#include "hashTable.h"

class studentManager
{
private:
	hashTable *studentInfo;
	vector *files;
	
	void processInfo();//calls add file info in the correct order to avoid any conflicts.
	void addFileInfo(int countParameters, string fileName);//reads files. Determines wether to read top 2 lines. calls addLine on each file line
	void addLine(string myString);//decodes string into subsequent parts and then adds them individually using Hashtables method add(key,value)
	int isCatagory(string one, string two);//used to figure out if anouther type of same file.
	void enterInfo();//gets user input
	string getType(string type);//used in writeFileTwo

public:
	studentManager();//initiates files & student info
	void setUp();//calls enter info and then process info
	void printList(); //my diagnostic method
	void writeFileOne();//writes to details.csv
	void writeFileTwo();//writes to overall.csv
	~studentManager();
};

#endif "STUMANAGER""