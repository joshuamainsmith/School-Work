#include "Shelf.h"

Shelf::Shelf(string na, int size)
{
	j = 0;
	name = na;
	shelfArr = new string[(size + 1) * 5];
	setSize((size + 1) * 5);

}

Shelf::Shelf(const Shelf& origShelf)
{
	this->arrSize = origShelf.arrSize;
	j = origShelf.j;
	shelfArr = new string[arrSize];
	for (int i = 0; i < arrSize; i++)
	{
		shelfArr[i] = origShelf.shelfArr[i];
	}
}

Shelf::~Shelf()
{
	delete[] shelfArr;
}

void Shelf::AddFood(const Food *f)
{

	for (int i = 0; i < 5; i++)
	{
		setShelfArr(j, f->foodArr[i]);
		j++;
	}
}

void Shelf::setShelfArr(int i, string str)
{
	shelfArr[i] = str;
}

string Shelf::getShelfArr(int i)
{
	return shelfArr[i];
}

void Shelf::setSize(int size)
{
	arrSize = size;
}

int Shelf::getSize()
{
	return arrSize;
}