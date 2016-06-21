#include "hashTable.h"

int hashTable::needResize()
{
	if (this->spotsFilled * 2 > this->size) // resizes if half list full. Directly after resize list will be 1/4 full.
	{
		return 1;
	}
	return 0;
}

hashTable::hashTable()
{
	list = new vector*[10]; //creates a vector list of 10
	for (int x = 0; x < 10; x++)
	{
		list[x] = nullptr;
	}
	this->size = 10;
	this->spotsFilled = 0;
	this->keyList = new vector();
}
void hashTable::resize()
{
	size = size * 2;//this function copys data to a new list that is double the size, and deallocates the old list.
	int x;
	vector **newList = new vector*[size];
	vector **toDelete;
	for (x = 0; x < (size / 2); x++)
	{
		newList[x] = list[x];
	}
	for (x = (size / 2); x < size; x++)
	{
		newList[x] = nullptr;
	}
	toDelete = list;
	list = newList;
	delete toDelete;
	return;
}
void hashTable::add(string key, string value)
{	
	if (needResize())
	{
		resize();
	}
	int index = find(key);
	if (list[index] == nullptr)//student has not been registered yet
	{
		list[index] = new vector();
		list[index]->add(key);//on first creation of vector adds key for identification.
		list[index]->add(value);
		this->keyList->add(key);//stores key in seperate vector to find data in future.
		this->spotsFilled++; //increments number of students in list
	}
	else
	{
		if (value != list[index]->get(1))//checks value is not the name (name is in many of the files and is allways 2nd in, thus will correspond
		{//to second spot in the vector of get(1). This is to stop subsequent name entry)
			list[index]->add(value); //adds value
		}
	}
	return;
}
int hashTable::hash(string key, int modBy)
{
	int hashNum = 0;
	for (int x = 0; x < key.length(); x++)
	{
		hashNum = (key[x] - '0') + hashNum * 13;
	}
	if (hashNum < 0)
	{
		hashNum = hashNum * -1;
	}
	if (modBy > 10)
	{
		hashNum = (hashNum % (modBy / 2)) + (modBy / 2);
		return hashNum;
	}
	//above if statement and containments makes the hashtable more evenly distributed
	//by targeting areas that have recently been freed. This helps decrease the average number of traversals until free spot found.

	return hashNum % modBy;
	//keep this here to utilize 0-5. 0 stores OVERALL and is accessed directly when writing to file.
}
int hashTable::hash(string key)
{
	return hash(key, size);
}
int hashTable::find(string key)
{
	int found = 0;
	int modBy = size;
	int index = 0;
	while (found == 0)
	{
		index = hash(key, modBy);
		while (list[index] != nullptr && (*list[index]).get(0) != key)
		{
			index++;
			if (index >= size)
			{
				index = 0;
			}
		}
		if(list[index] == nullptr)
		{
			modBy = modBy / 2;// im doing this so I can check everywhere it could of been put in previous sizes.
		}
		else
		{
			return index; // found it, it is allready there at this index
		}
		if (modBy <= 5)
		{
			found = -1; //its not there, create a new spot // -----
		}//                                                         \  
	}//                                                             /
	if (found == -1) //okay time to create a new spot        <-----
	{
		index = hash(key, size);
		while (list[index] != nullptr)//looking for an empty space
		{
			index++;
			if (index >= size)
			{
				index = 0;
			}
		}
		return index; //found an empty spot
	}
	return -666; // it didnt return by the end of function? Obviously cursed.
}
vector& hashTable::get(string key)
{
	int index = find(key);
	if (list[index] == nullptr)
	{
		cout << "get function did not find vector corresponding to the key" + key;
	}
	return *list[index];
}
string hashTable::get(string key, int index)
{
	return get(key).get(index); // the second get refers to the vectors definition.
}
hashTable::~hashTable()
{
	
	for (int x = 0; x < this->spotsFilled; x++)
	{
		delete list[x];//delete list's vectors.
	}
	delete list;//delete list
	delete keyList;
}