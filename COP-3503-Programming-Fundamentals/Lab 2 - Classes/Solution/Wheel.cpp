#include "Wheel.h"
#include "Chassis.h"
#include "Vehicle.h"

/*		Default Constructors		*/
Wheel::Wheel()
{
	setCondition("fair");
}
Wheel::Wheel(string condition)
{
	setCondition(condition);
}

void Wheel::overrideCondition(string x)
{
	setCondition(x);
}

/*		Mileage Left		*/
void Wheel::setMileageLeft(int x)
{
	mileageLeft = x;
}
int Wheel::getMileageLeft()
{
	return mileageLeft;
}

/*		Condition		*/
void Wheel::setCondition(string x)
{
	condition = x;
	if (condition == "poor")
	{
		setMileageLeft(5000);
	}
	else if (condition == "fair")
	{
		setMileageLeft(10000);
	}
	else if (condition == "good")
	{
		setMileageLeft(20000);
	}
}
string Wheel::getCondition()
{
	return condition;
}