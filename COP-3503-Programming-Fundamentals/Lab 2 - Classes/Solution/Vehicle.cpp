#include "Vehicle.h"
#include "Chassis.h"
#include "Wheel.h"

/*		Default Constructor		*/
Vehicle::Vehicle(Chassis chassis)
{
	i = 0, j = 0, numWheels = 0;

	chasSize = chassis.getSize();
	chasCondition = chassis.getQuality();
	numberOfWheels = chassis.getNumWheels();

}

/*			Display				*/
void Vehicle::Display()
{
	price = setPrice(500);
	cout << fixed << showpoint;
	cout << setprecision(1);
	cout << "Vehicle:" << endl;
	cout << "\tPrice: " << price - 0.01 << endl;
	cout << "Chassis:" << endl;
	cout << "\tSize: " << chasSize << endl;
	cout << "\tQuality: " << chasCondition << endl;

	cout << "\tNumber of Wheels: " << numberOfWheels << endl;
	for (int j = 0; j < numberOfWheels; j++)
	{
		cout << "Wheel " << j + 1 << ":" << endl;
		cout << "\tMileage Left: " << tireMileage[j] << endl;
		cout << "\tCondition: " << tireCondition[j] << endl;
	}
	cout << "\n";
}

/*				Price					*/	
float Vehicle::setPrice(float price)
{
	if (chasCondition == "poor")
	{
		x = 5;
	}
	else if (chasCondition == "fair")
	{
		x = 8;
	}
	else
	{
		x = 12;
	}

	for (i = 0, y = 1; i < numberOfWheels; i++)
	{
		if (tireCondition[i] == "poor")
		{
			y *= 1.5;
		}
		else if (tireCondition[i] == "fair")
		{
			y *= 1.8;
		}
		else
		{
			y *= 2.2;
		}
	}

	return price = price * x * y;
}

/*			Adding Wheels					*/
void Vehicle::addWheel(Wheel wheel)
{
	tireCondition[i] = wheel.getCondition();
	tireMileage[i] = wheel.getMileageLeft();
	i++;
	numWheels++;
	if (numberOfWheels == numWheels)
	{

	}
}

/*				# Wheels ==  Chassis size?							*/
bool Vehicle::isBuilt()
{
	if (numWheels != numberOfWheels)
	{
		return false;
	}
	if ((numberOfWheels == 3) && (chasSize == "small"))
	{
		return true;
	}
	else if ((numberOfWheels == 4) && (chasSize == "medium"))
	{
		return true;
	}
	else if ((numberOfWheels == 6) && (chasSize == "large"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*				Drive						*/
/*		Tested - initial condition							*/
void Vehicle::Drive(int milesTested)
{
	float tmp;
	int tmp2 = 0;
	//cout << "Test Drive" << endl;
	for (i = 0; i < numberOfWheels; i++)
	{
		tmp = tireMileage[i];
		tireMileage[i] = tireMileage[i] - milesTested;
		if (tireMileage[i] < 0)
		{
			cout << "Broke down! ";
			cout << "You've traveled " << tmp << " miles!" << endl << endl;
			tireMileage[i] = 0;
			i++;
			for (; i < numberOfWheels; i++)
			{
				tireMileage[i] = tireMileage[i] - milesTested;

				if (tireMileage[i] < 0)
				{
					tireMileage[i] = 0;
				}

			}
			tmp2 = 1;
			break;
		}
		if (tireMileage[i] > 10000)
		{
			tireCondition[i] = "good";
		}
		else if (tireMileage[i] > 5000)
		{
			tireCondition[i] = "fair";
		}
		else
		{
			tireCondition[i] = "poor";
		}

	}
	if (tmp2 == 0)
	{
		cout << "You've traveled " << (float)milesTested << " miles!" << endl << endl;
	}

	setPrice(500);

}

/*				Return Chassis						*/
Chassis Vehicle::getChassis()
{
	return chasSize;
}