#include "Chassis.h"
#include "Vehicle.h"
#include "Wheel.h"

/*		Default Constructors		*/
Chassis::Chassis()
{
	setSize("medium");
}
Chassis::Chassis(string size)
{
	setSize(size);
}
Chassis::Chassis(string size, string quality)
{
	setSize(size);
	setQuality(quality);
}

void Chassis::overrideSize(string x)
{
	setSize(x);
}

void Chassis::overrideSizeAndQuality(string x, string y)
{
	setSize(x);
	setQuality(y);
}

/*		Size		*/
void Chassis::setSize(string x)
{
	size = x;
	if (size == "small")
	{
		setNumWheels(3);
	}
	else if (size == "medium")
	{
		setNumWheels(4);
	}
	else if (size == "large")
	{
		setNumWheels(6);
	}
}
string Chassis::getSize()
{
	return size;
}

/*		Quality		*/
void Chassis::setQuality(string y)
{
	quality = y;
}
string Chassis::getQuality()
{
	return quality;
}


/*		Number of Wheels		*/
void Chassis::setNumWheels(int x)
{
	numWheels = x;
}
int Chassis::getNumWheels()
{
	return numWheels;
}