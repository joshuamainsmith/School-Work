#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Food
{
	friend class Shelf;
public:
	// Constructor
	Food(string foodType, string foodName, int foodExpiration, int foodPrice, int foodCalories);

	// Copy Constructor
	Food(const Food& origFood);

	// Destructor
	~Food();

	void setFoodArr(int i, string str);

	string getFoodArr(int i);

private:

	string *foodArr;
	int i = 0;
};