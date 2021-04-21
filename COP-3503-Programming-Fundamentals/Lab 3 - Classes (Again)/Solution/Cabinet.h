#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "Shelf.h"

using namespace std;

class Cabinet
{

public:
	Cabinet(string na, int shelfLimit);

	Cabinet(const Cabinet& origCabinet);

	~Cabinet();

	void setCabSize(int s);

	int getCabSize();

	void AddShelf(Shelf *s);

	void ShowInventory();

	double GetAveragePrice();

private:
	string *cabinetArr;
	string name;
	string *shelfName;
	int cabSize;
	int k;
	double price;
	int index;
};