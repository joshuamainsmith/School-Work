#pragma once

#include<iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "Wheel.h"
#include "Chassis.h"

using namespace std;

class Vehicle
{
public:
	/*		Default Constructor		*/
	Vehicle(Chassis chassis);

	Chassis getChassis();

	/*		Price		*/

	float setPrice(float price);

	void Display();

	void addWheel(Wheel wheel);

	bool isBuilt();

	void Drive(int milesTested);

private:
	float price, y, x;
	//bool drivable;
	int i, j, numWheels, numberOfWheels;
	string chasSize;
	string chasCondition;
	string tireCondition[50];
	double tireMileage[50];
	
};

