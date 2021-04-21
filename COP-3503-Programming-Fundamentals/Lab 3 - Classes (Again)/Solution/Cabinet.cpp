#include "Cabinet.h"

Cabinet::Cabinet(string na, int shelfLimit)
{
	name = na;
	k = 0;
	index = 0;
	cabinetArr = new string[(shelfLimit + 1) * 50 * 5];
	shelfName = new string[(shelfLimit + 1) * 50 * 5];
	setCabSize((shelfLimit + 1) * 5);
}

Cabinet::Cabinet(const Cabinet& origCabinet)
{
	cabSize = origCabinet.cabSize;
	cabinetArr = new string[cabSize];
	for (int i = 0; i < cabSize; i++)
	{
		cabinetArr[i] = origCabinet.cabinetArr[i];
	}
}

Cabinet::~Cabinet()
{
	delete[] cabinetArr;
	delete[] shelfName;
}

void Cabinet::setCabSize(int s)
{
	cabSize = s;
}

int Cabinet::getCabSize()
{
	return cabSize;
}

void Cabinet::AddShelf(Shelf *s)
{
	shelfName[index] = s->name;
	index++;
	for (int i = 0; i < s->j; i++)
	{
		cabinetArr[k] = s->getShelfArr(i);
		k++;
	}
}

void Cabinet::ShowInventory()
{
	cout << "Inventory of " << name << endl;
	for (int i = 0; i < k; i++)
	{
		if ((i == 0) || (i == 15))
		{
			if (i == 0)
			{
				cout << "Food in " << shelfName[index/index - 1] << endl;
			}
			else
			{
				cout << "Food in " << shelfName[index/index] << endl;
			}
		}

		if ((i + 2) % 5 == 0)
		{
			cout << "$";
		}
		cout << cabinetArr[i] << " ";

		if ((i + 1) % 5 == 0)
		{
			cout << " cal";
		}

		if (((i + 5) % 5 == 0) || ((i + 3) % 5 == 0) || ((i + 2) % 5 == 0))
		{
			cout << "\t";
		}

		if (((i + 1) % 5 == 0) && (i != 0))
		{
			cout << endl;
		}
	}
	double price = GetAveragePrice();
	cout << "\nAverage price of food: $" << fixed << setprecision(2) << price << endl;
}

double Cabinet::GetAveragePrice()
{
	for (int i = 3; i < k; i += 5)
	{
		price += stod(cabinetArr[i]);
	}
	price = (price / ((double)k / (double)5));

	return price;
}