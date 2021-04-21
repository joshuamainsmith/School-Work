#include "Food.h"
#include "Cabinet.h"
#include "Shelf.h"
#include <iostream>
#include <limits>
#include <memory>
#include <iomanip>
#include <string.h>

using namespace std;

void TestOne(Food *v);
void TestTwo(Food *v);

int main()
{

	// Initialize some data. It's hard-coded here, but this data could come from a file, database, etc
	Food foods[] =
	{
		Food("Vegetable", "Avocado", 2019, 15, 5),
		Food("Cheese", "Moldy Cheddar", 1999, 7, 400),
		Food("Breakfast", "Pop-Tart", 2025, 5, 754),
		Food("Cereal", "Lucky Charms", 2001, 4, 600),
		Food("Frozen", "Cheese Pizza", 2021, 10, 1001),
		Food("Very-Processed", "Ramen", 3005, 1, 9999),
		Food("Expensive", "Caviar", 2017, 180, 150),
	};
		
	int testNum;
	cin >> testNum;

	if (testNum == 1)
		TestOne(foods);
	else if (testNum == 2)
		TestTwo(foods);
		
	system("pause");
	return 0;
}

void TestOne(Food *foods)
{
	// Shelfs to store the foods
	Shelf shelf("\"Healthy-Food Shelf\"", 3); //calls the constructor with parameters
	shelf.AddFood(&foods[0]);
	shelf.AddFood(&foods[1]);
	shelf.AddFood(&foods[2]);

	Shelf secondary("\"Treat Your Shelf\"", 4);
	secondary.AddFood(&foods[3]);
	secondary.AddFood(&foods[4]);
	secondary.AddFood(&foods[5]);
	secondary.AddFood(&foods[6]);

	// A "parent" object to store the Shelfs
	Cabinet cabinet("COP3503 Dormroom Cabinet", 2);
	cabinet.AddShelf(&shelf); //adding show rooms is the issue
	cabinet.AddShelf(&secondary);

	cabinet.ShowInventory();
}

void TestTwo(Food *foods)
{
	// Shelfs to store the foods
	Shelf shelf("\"Healthy-Food Shelf\"", 3);
	shelf.AddFood(&foods[0]);
	shelf.AddFood(&foods[1]);

	Shelf secondary("\"Treat Your Shelf\"", 4);

	secondary.AddFood(&foods[4]);
	secondary.AddFood(&foods[5]);

	Shelf third("\"Treat Your Shelf\"", 4);
	third.AddFood(&foods[3]);
	// A "parent" object to store the Shelfs
	Cabinet cabinet("COP3503 Dormroom Cabinet", 3);
	cabinet.AddShelf(&shelf);
	cabinet.AddShelf(&secondary);
	cabinet.AddShelf(&third);

	cout << "Using just the GetAveragePrice() function\n\n";

	cout << "Average price of the food in the cabinet: $" << std::fixed << std::setprecision(2);
	cout << cabinet.GetAveragePrice();
}

