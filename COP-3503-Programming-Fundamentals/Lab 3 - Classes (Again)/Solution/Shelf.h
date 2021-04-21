#pragma once
#include <iostream>
#include <string>
#include "Food.h"

using namespace std;

class Shelf
{
	friend class Cabinet;
public:
	Shelf(string na, int size);

	Shelf(const Shelf& origShelf);

	~Shelf();

	void AddFood(const Food *f);

	void setShelfArr(int i, string str);

	string getShelfArr(int i);

	void setSize(int size);

	int getSize();
private:
	string *shelfArr;
	int arrSize;
	int j;
	string name;

};