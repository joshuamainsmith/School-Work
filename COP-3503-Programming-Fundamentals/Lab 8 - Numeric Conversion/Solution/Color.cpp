#include "Color.h"
#include <bitset>


Color::Color()
{
	size = 0;
	capacity = 1;
	ptrColor = new string[capacity];
}

void Color::SetName(string name)
{
	if (size == capacity)
	{
		resize(capacity);
		ptrColor[size] = name;
	}
	else
	{
		ptrColor[size] = name;
	}

	size++;
}

void Color::SetValue(int value)
{
	bitset<32> r(value);
	bitset<32> b(value);
	bitset<32> g(value);

	// Red
	r = (r >>= 16) & (bitset <32>)255;
	int red = (int)r.to_ulong();

	// Green
	g = (g >>= 8) & (bitset <32>)255;
	int green = (int)g.to_ulong();

	// Blue
	b = (b >>= 0) & (bitset <32>)255;
	int blue = (int)b.to_ulong();

	SetName(to_string(red));
	SetName(to_string(green));
	SetName(to_string(blue));

}

string Color::GetName()
{
	return *ptrColor;
}

string Color::GetR()
{
	return ptrColor[1];
}

string Color::GetG()
{
	return ptrColor[2];
}

string Color::GetB()
{
	return ptrColor[3];
}

string Color::GetHexValue()
{
	return "true";
}

void Color::resize(unsigned int &capacity)
{
	string *tmp;
	tmp = new string[capacity];

	for (unsigned int i = 0; i < size; i++)
	{
		tmp[i] = ptrColor[i];
	}

	delete[] ptrColor;

	capacity *= 2;
	ptrColor = new string[capacity];

	for (unsigned int i = 0; i < size; i++)
	{
		ptrColor[i] = tmp[i];
	}

	delete[] tmp;
}

