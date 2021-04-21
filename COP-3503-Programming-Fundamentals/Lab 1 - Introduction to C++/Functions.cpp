#include "Functions.h"
#include <vector>


int quadraticRoot()
{
	double a = 0, b = 0, c = 0, discrim = 0, r1 = 0, r2 = 0, r = 0;

	cout << "Enter a, b, c: ";
	cin >> a >> b >> c;

	discrim = b * b - 4 * a * c;

	if (discrim < 0)
	{
		cout << "The equation has no real roots.";
		system("pause");
	
	}

	else if (discrim > 0)
	{
		r1 = (-b + sqrt(discrim)) / (2 * a);

		r2 = (-b - sqrt(discrim)) / (2 * a);

		cout << "The equation has two roots: " << r1 << " and " << r2 << endl;
		system("pause");
		
	}

	else
	{
		r = -b / (2 * a);

		cout << "The equation has one root: " << r << endl;
		system("pause");
	}

	return 0;
}

int gradeCalculator()
{
	int best = -1, num = 0, i = 0;
	

	cout << "Enter the number of students: ";
	cin >> num;
	vector<int> scores(num);
	vector<char> grades(num);

	cout << "Enter " << num << " scores: ";

	for (i = 0; i < num; i++)
	{
		cin >> scores[i];
		if (best < scores[i])
		{
			best = scores[i];
		}
	}

	for (i = 0; i < num; i++)
	{
		if (scores[i] >= best - 10)
		{
			grades[i] = 'A';
		}
		else if (scores[i] >= best - 20)
		{
			grades[i] = 'B';
		}
		else if (scores[i] >= best - 30)
		{
			grades[i] = 'C';
		}
		else if (scores[i] >= best - 40)
		{
			grades[i] = 'D';
		}
		else
		{
			grades[i] = 'F';
		}

		cout << "Student " << i + 1 << " - Score: " << scores[i] << ", Letter: " << grades[i] << endl;
	}
	system("pause");
	return 0;
}

int cardValidator()
{
	long long number;

	cout << "Enter a credit card number: ";
	cin >> number;

	cout << number << " is ";

	if (isValid(number))
	{
		cout << "valid." << endl;
		system("pause");
	}

	else
	{
		cout << "invalid." << endl;
		system("pause");
	}

	return 0;
}

bool isValid(long long number)
{
	//string numSize = to_string(number);

	int numSize = getSize(number);

	if (numSize > 16 || numSize < 13)
	{
		return false;
	}

	int sum = sumOfDoubleEvenPlace(number) + sumOfOddPlace(number);

	if ((sum % 10) != 0)
	{
		return false;
	}

	if (prefixMatched(number, 4)) return true;
	if (prefixMatched(number, 5)) return true;
	if (prefixMatched(number, 37)) return true;
	if (prefixMatched(number, 6)) return true;

	return false;
}

int sumOfDoubleEvenPlace(long long number)
{
	int sum = 0;

	while (number > 0)
	{
		int digit = (int)((number % 100) / 10);
		number /= 100;

		sum += getDigit(2 * digit);
	}

	return sum;
}

int getDigit(int number)
{
	return (number / 10) + (number % 10);
}

int sumOfOddPlace(long long number)
{
	int sum = 0;

	while (number > 0)
	{
		int digit = (int)(number % 10);
		number /= 100;

		sum += getDigit(digit);
	}
	return sum;
}

bool prefixMatched(long long number, int digit)
{
	return getPrefix(number, getSize(digit)) == digit;
}

int getSize(long long number)
{
	int digitCount = 0;

	while (number > 0)
	{
		number /= 10;
		digitCount++;
	}

	return digitCount;
}

long long getPrefix(long long number, int numDigits)
{
	int numberSize = getSize(number);

	int decimalMovements = numberSize - numDigits;

	while (decimalMovements-- > 0)
	{
		number /= 10;
	}

	return number;
}