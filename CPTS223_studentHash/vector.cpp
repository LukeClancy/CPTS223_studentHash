#include "vector.h"

void vector::resize()
{//resizes when half full called in add
	size = size * 2;
	string *newValues = new string[size];
	string *temp;
	for (int x = 0; x < (size / 2); x++)
	{
		newValues[x] = values[x];
	}
	temp = values;
	values = newValues;
	delete[] temp;
	return;
}
int vector::needResize()
{//checks whether vector needs to be resized
	if (this->size <= 2*spotsFilled)
	{
		return 1;
	}
	return 0;
}
vector::vector()
{// allocates memory and initializes values
	this->size = 4;
	this->values = new string[4];
	this->spotsFilled = 0;
	return;
}
void vector::add(string value)
{//checks resize and then adds to next element
	if (needResize())
	{
		resize();
	}
	values[this->spotsFilled] = value;
	spotsFilled++;
	return;
}
string vector::get(int index)
{//checks invalid entry then adds
	if (index >= this->spotsFilled)
	{
		cout << "entered invalid index into vector::get() function, returning invalid";
		return "invalid";
	}
	return values[index];
}

void vector::set(int index, string myString)
{//adding to random indexes is not allowed in my vector. So the set function does not go over spots filled.
	if (index < spotsFilled)
	{
		values[index] = myString;
	}
	return;
}

int vector::getSpotsFilled()
{//returns private variable value
	return this->spotsFilled;
}

vector::~vector()
{
	delete[] values;
}
