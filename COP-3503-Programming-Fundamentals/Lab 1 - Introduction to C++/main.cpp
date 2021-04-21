#include <iostream>

#include "Functions.h"

using namespace std;

int main()
{
	int input;

	cout << "1. Quadratic Root" << endl;
	cout << "2. Grade Calculator" << endl;
	cout << "3. Credit Card Validator" << endl;
	cout << "Enter a number: ";
	cin >> input;

	if (cin.fail())
	{
		cout << "Please select a valid input" << endl;
		system("pause");
		cin.clear();
		main();
	}


	switch (input) {
	case 1:
		quadraticRoot();
		break;
	case 2:
		gradeCalculator();
		break;
	case 3:
		cardValidator();
		break;
	default:
		cout << "Please select an option from 1-3";
		system("pause");
		main();
		break;
	}

	return 0;
}