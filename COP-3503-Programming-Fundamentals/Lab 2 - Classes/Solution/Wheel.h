#pragma once

#include <iostream>
#include <string>

using namespace std;

class Wheel
{
public:
	/*		Default Constructor		*/
	Wheel();
	
	Wheel(string condition);

	void overrideCondition(string x);

	/*		Mileage Left		*/
	void setMileageLeft(int x);
	
	int getMileageLeft();

	/*		Condition		*/
	void setCondition(string x);
	
	string getCondition();
	
private:
	int mileageLeft;
	string condition;
};