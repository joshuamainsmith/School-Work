#include "Vehicle.h"
#include "Wheel.h"
#include <iostream>


int main()
{
	Wheel plainWheel;

	Chassis plainChassis("medium");
	Vehicle firstCar(plainChassis);

	for (int i = 0; i < firstCar.getChassis().getNumWheels(); i++) {
		firstCar.addWheel(plainWheel);
	}

	//since all plainWheels have been added, it should be built
	if (firstCar.isBuilt()) {
		std::cout << "Built!\n" << std::endl;
		firstCar.Display();
	}


	Chassis superChassis("large", "good");
	Vehicle superCar(superChassis);

	if (!superCar.isBuilt()) {
		std::cout << "Where are the wheels!\n" << std::endl;
	}

	Wheel superWheel("good");

	superCar.addWheel(superWheel);
	superCar.addWheel(superWheel);
	superCar.addWheel(superWheel);
	superCar.addWheel(superWheel);

	superCar.addWheel(plainWheel);
	superCar.addWheel(plainWheel);

	superCar.Display();
	superCar.Drive(8000);
	superCar.Display();

	Wheel badWheel("poor");
	Chassis reallyBadChassis("small", "poor");
	Vehicle badCar(reallyBadChassis);

	for (int i = 0; i < badCar.getChassis().getNumWheels(); i++) {
		badCar.addWheel(badWheel);
	}

	badCar.Display();
	badCar.Drive(6000);
	badCar.Display();

	system("pause");

	return 0;
}