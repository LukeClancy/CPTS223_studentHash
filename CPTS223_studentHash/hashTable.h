#ifndef HASHTABLE
#define HASHTABLE
#include "vector.h"

class hashTable //hashtable of vectors. Each vector corresponds to a student.
{
private:
	int size;//keeps track of spaces in list
	int spotsFilled;//keeps track of amount of variables in list
	vector **list;//list of pointers
	//starts at ten, doubles once half full

	int needResize();
	void resize();
	int hash(string key, int modBy);//returns hash number when given a key and specific modValues
	int hash(string key);//returns hash number when given a key. Uses size as modvalue
	int find(string key);//finds index given a key

public:
	vector *keyList; //keeps track of students. 
	void add(string key, string Value);//adds value to vector. if Vector not made, makes a new one, adds both key and value, and then adds key to keyList.
	vector& get(string key);//returns vector that corresponds to key
	string get(string key, int index);//returns key's vector's string at index
	hashTable();//makes hashtable
	~hashTable();

};


#endif "HASHTABLE"