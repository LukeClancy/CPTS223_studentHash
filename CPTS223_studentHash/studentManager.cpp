#include "studentManager.h"
void studentManager::setUp()
{
	if (files->getSpotsFilled() != 0)//checks for existing data and deletes it. Program made for initial entry and
		//not designed for subsaquent entrys as vector data corresponds to and is reliant on how it was ordered in 
		//the function "processInfo()".
	{
		hashTable *temp = studentInfo;
		vector *temp2 = files;
		this->studentInfo = new hashTable();
		files = new vector();
		delete temp;
		delete[] temp2;
	}
	enterInfo();
	processInfo();
	return;
}
void studentManager::enterInfo()
{
	//preset option for easy entry. For manual input enter no. 
	string willContinue = "";
	string fileName = "";
	int a = 0;
	string presets = "";
	cout << "use presets?(y/n)  Presets used for easy entry of test case. To use diffrent files press n";
	cin >> presets;
	do
	{
		if (presets == "y")
		{
			willContinue = "y";
			switch (a)
			{
			case 0:fileName = "exams_1.csv";
				break;
			case 1:fileName = "exams_2.csv";
				break;
			case 2:fileName = "homework_1.csv";
				break;
			case 3: fileName = "homework_2.csv";
				break;
			case 4: fileName = "quizzes_1.csv";
				break;
			case 5: fileName = "quizzes_2.csv";
				willContinue = "im done";
				break;
			default:
				break;
			}
		}
		else
		{
			cout << "please enter file name (the preset files are - exams_1.csv - exams_2.csv - homework_1.csv - homework_2.csv - quizzes_1.csv and quizzes_2.csv)\n";
			cin >> fileName;
			cout << "add anouther file? (y/n)";
			cin >> willContinue;
		}
		a++;
		files->add(fileName);
	} while (willContinue == "y");
	return;
}
studentManager::studentManager()
{
	this->studentInfo = new hashTable();
	files = new vector();
}
void studentManager::processInfo()
{
	int a = 0;
	int b = 1;
	int c;
	while (a < files->getSpotsFilled())
	{
		if (files->get(a) != "")
		{
			addFileInfo(1,files->get(a));
			c = b;
			while (c < files->getSpotsFilled())
			{
				if (isCatagory(files->get(a), files->get(c)))
				{
					addFileInfo(0, files->get(c));
					files->set(c,""); //yes mutilates my vector, but im not using it again.EDIT used it again in printing to file, mutilation helpfull in removing duplicates
				}
				c++;
			}
		}
		b++;
		a++;
	}
	return;
}
int studentManager::isCatagory(string one, string two)
{
	int end=0;
	while (one[end] == two[end])
	{
		if (one[end] == '_')
		{
			return 1;
		}
		end++;
	}
	return 0;
}
void studentManager::addFileInfo(int countParameters, string fileName) //countParamaters determines wheather I should count non-student information (this would be turned off
//if i had just done, for example, HW1 and was now doing HW2
{
	ifstream myFile;
	string line;
	myFile.open(fileName);
	if (0==countParameters)
	{
		getline(myFile, line);
		getline(myFile, line);
	}
	while (getline(myFile, line))
	{
		addLine(line);
	}
	myFile.close();
	return;
}
void studentManager::addLine(string myString)
{
	int start = 0;
	int temp = 1;
	int end = myString.length();
	int skipComma = 1;
	int skipKey = 0;//skips key as key is auto added in hashtable if it is deemed missing.
	string key = "";
	if (myString[0] == ',')
	{
		key = "0"; //this is here to assign to the row that determines what points that the assignment is out of
		start = 1;
		temp = 1;
		skipKey = 1;
	}
	while (temp != end)
	{
		if (myString[temp] == '"')//skips commas in case of quotations
		{
			skipComma = skipComma*-1;
		}

		if (skipComma != -1)
		{
			if (myString[temp] == ','&&skipKey == 0)
			{
				key = myString.substr(start, temp - start);//assigns key
				skipKey = 1;
				start = temp + 1;
			}
			else if (myString[temp] == ',')
			{
				studentInfo->add(key, myString.substr(start, temp - start));//adds value to hashtable using the key
				start = temp + 1; 
			}
		}
		temp++;
	}
	studentInfo->add(key, myString.substr(start, temp));//adds last value that was skipped (due to there being no comma at end of string)
	return;
}
void studentManager::printList()
{
	int x;//ignore this jus a diagnostic thing
	int y;
	int count = 0;
	string key = "";
	vector temp;
	cout << endl << studentInfo->keyList->getSpotsFilled() << endl;
	for (x = 0; x < studentInfo->keyList->getSpotsFilled(); x++)
	{
		key = studentInfo->keyList->get(x);
		temp = studentInfo->get(key);
		for (y = 0; y < temp.getSpotsFilled(); y++)
		{
			cout << temp.get(y) + " - ";
		}
		cout << endl;
		count++;
	}
	cout << endl << count;
	return;
}
void studentManager::writeFileOne()
{
	ofstream myFile;
	myFile.open("details.csv");
	int x = 0; //iterators
	int y = 0;
	int z = 0;
	int dontCount[500] = { NULL };//limit - 500 files.
	int numDontCount = 0;
	int skip = 0;
	string key = studentInfo->keyList->get(x);
	vector *temp = &(studentInfo->get(key));
	for (y = 0; y < temp->getSpotsFilled(); y++)
	{
		if (temp->get(y) == "Total")//determines the indexes at which to skip
		{
			dontCount[numDontCount] = y;
			numDontCount++;
		}
	}
	for (x = 0; x < studentInfo->keyList->getSpotsFilled(); x++) //reads each vector using keyList
	{
		key = studentInfo->keyList->get(x);//gets key
		temp = &(studentInfo->get(key));//gets vec using key
		for (y = 0; y < temp->getSpotsFilled(); y++)//gos through temp vals
		{
			skip = 0;
			for (z = 0; z < numDontCount; z++)
			{
				if (y == dontCount[z])//checks for skip
				{
					skip = 1;
				}
			}
			if (skip == 0)
			{
				if (x != 1 || y != 0)
				{
					myFile << temp->get(y);//adds info
				}
				if (y != temp->getSpotsFilled() - 1)
				{
					myFile << ',';
				}
			}
		}
		myFile << endl;
	}
	myFile.close();
	return;
}
void studentManager::writeFileTwo()
{
	ofstream myFile;
	myFile.open("overall.csv");
	int x = 0;
	int y;
	string key;
	vector *base = &(studentInfo->get("#ID"));
	vector *current;
	int toAdd[500] = { -666 };
	int toAddFilled = 0;
	int absoluteTotal = 0;
	int topGrade = 0;
	int temp;
	

	myFile << "#ID,Name,Final Grade";
	for (x = 0; x < files->getSpotsFilled(); x++)
	{
		if (files->get(x) != "")
		{
			myFile << "," << getType(files->get(x));
		}

	}
	myFile << endl;
	for (x = 1; x < studentInfo->keyList->getSpotsFilled(); x++) // x = 1 as im skipping top row which is handled in the for previously
	{
		key = studentInfo->keyList->get(x); 
		current = &(studentInfo->get(key));
		if (x != 1)
		{
			myFile << current->get(0) << "," << current->get(1);
		}
		else
		{
			myFile <<  "," << current->get(1);
		}
		for (y = 2; y < current->getSpotsFilled(); y++) //y = 2 as im skipping name and ID
		{
			if(base->get(y) == "Total")
			{
				temp = atoi((current->get(y)).c_str());
				absoluteTotal += temp;
				toAdd[toAddFilled] = temp;
				toAddFilled++;
			}
		}
		if (x == 1)
		{
			topGrade = absoluteTotal;
		}
		myFile << "," << to_string((100* (double)absoluteTotal)/(double)topGrade).substr(0,5);
		for (y = 0; y < toAddFilled; y++)
		{
			myFile << "," << to_string(toAdd[y]);
		}
		myFile << endl;
		absoluteTotal = 0;
		toAddFilled = 0;
	}
	myFile.close();
	return;
}
string studentManager::getType(string type)
{
	int y = 0;
	while (y < type.length() && type[y] != '_')
	{
		y++;
	}
	type = type.substr(0, y);
	type.append(" Total");
	return type;
}
studentManager::~studentManager()
{
	delete this->studentInfo;
	delete this->files;
}