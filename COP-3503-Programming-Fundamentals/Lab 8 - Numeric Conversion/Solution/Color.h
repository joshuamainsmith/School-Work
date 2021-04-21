#pragma once
#include <iostream>
#include <string>

using namespace std;

class Color
{

	string *ptrColor;
	unsigned int size;
	unsigned int capacity;

public:
	Color();
	void SetName(string name);
	void SetValue(int value);
	void resize(unsigned int &cap);
	string GetName();
	string GetR();
	string GetG();
	string GetB();
	string GetHexValue();
};

