#include "Food.h"

// Constructor
Food::Food(string foodType, string foodName, int foodExpiration, int foodPrice, int foodCalories)
{
	foodArr = new string[6];

	auto foodExpirationStr = to_string(foodExpiration);
	auto foodPriceStr = to_string(foodPrice);
	auto foodCaloriesStr = to_string(foodCalories);

	setFoodArr(i, foodExpirationStr);
	setFoodArr(++i, foodType);
	setFoodArr(++i, foodName);
	setFoodArr(++i, foodPriceStr);
	setFoodArr(++i, foodCaloriesStr);
}

// Copy Constructor
Food::Food(const Food& origFood)
{
	/*
	dataObj = new int; // Allocate sub-object
	*dataObj = *(origClass.dataObj);
	*/
	foodArr = new string[6];
	for (int i = 0; i < 6; i++)
	{
		foodArr[i] = origFood.foodArr[i];
	}
}

// Destructor
Food::~Food()
{
	/*
	delete dataObj;
	*/
	delete[] foodArr;
}

void Food::setFoodArr(int i, string str)
{
	foodArr[i] = str;
}

string Food::getFoodArr(int i)
{
	return foodArr[i];
}