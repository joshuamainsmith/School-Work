#pragma once
#include <iostream>
#include <string>

using namespace std;

class Chassis
{
public:
	/*		Default Constructor		*/
	Chassis();
	
	Chassis(string size);
	
	Chassis(string size, string quality);
	

	void overrideSize(string x);
	

	void overrideSizeAndQuality(string x, string y);
	

	/*		Size		*/
	void setSize(string x);
	
	string getSize();
	

	/*		Quality		*/
	void setQuality(string y);
	
	string getQuality();
	


	/*		Number of Wheels		*/
	void setNumWheels(int x);
	
	int getNumWheels();
	
private:
	string size = "medium";
	string quality = "fair";
	int numWheels;
};

