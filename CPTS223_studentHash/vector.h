
#ifndef VECTOR
#define VECTOR

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class vector 
{
protected:
	string *values;//list of strings. spaces allocated in size. Number filled in spotsFilled.
	int size;
	int spotsFilled;
	//starts at size four, doubles once half full.
	void resize();
	int needResize();

public:
	vector();
	void add(string value);
	string get(int index);
	void set(int index, string myString);
	int getSpotsFilled();
	~vector();
};


#endif "VECTOR"