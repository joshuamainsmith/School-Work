#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <iomanip>
#include <set>
#include <algorithm>
#include "Color.h"

using namespace std;

void ReadFile(const char *filename, vector<Color> &outVector);
void SortColors(vector<Color> &colors);
void PrintColors(vector<Color> &colors);


int main()
{
	cout << "1-6: Load colors1/2/3/4/5/6.txt" << endl;
	cout << "7. Load all 6 files" << endl;
	int choice;
	cin >> choice;

	vector<Color> colors;
	// Load the selected files
	if (choice >= 1 && choice <= 6)
	{
		string file = "colors" + to_string(choice) + ".txt";
		ReadFile(file.c_str(), colors);

	}
	else if (choice == 7)
	{
		for (int i = 1; i <= 6; i++)
		{
			string file = "colors" + to_string(i) + ".txt";
			ReadFile(file.c_str(), colors);
		}
	}

	// Sort and print the loaded data
	SortColors(colors);
	PrintColors(colors);


	return 0;
}

void ReadFile(const char *filename, vector<Color> &outVector)
{
	// TODO: Load the file and store the resulting colors in outVector.
	fstream file(filename, ios_base::in);
	string line;
	int colorInt;
	int i = 0;
	while (getline(file, line))
	{
		Color c;
		string data = line.substr(0, line.find(' '));
		c.SetName(data);
		data = line.substr(line.find(' ') + 1, line.size());
		colorInt = stoi(data);
		c.SetValue(colorInt);
		outVector.push_back(c);
		i++;
	}
	file.close();
}

void SortColors(vector<Color> &colors)
{
	// TODO: Sort the colors in ascending order by name.

	string cmprColor1, cmprColor2;
	vector<Color> sorted;
	cmprColor1 = colors[0].GetName();
	cmprColor2 = colors[1].GetName();

	sorted.push_back(colors[0]);
	for (unsigned int i = 0; i < colors.size(); i++)
	{
		int index = i;
		cmprColor1 = sorted[sorted.size() - 1].GetName();
		if ((unsigned int)i + 1 != colors.size())
		{
			cmprColor2 = colors[i + 1].GetName();

		}
		else
		{
			index = -1;
		}

		while (index >= 0)
		{
			if (cmprColor1[0] == cmprColor2[0])	
			{
				int j = 1;
				int tmp = index;
				while (index >= 0)
				{
					if (cmprColor1[j] == cmprColor2[j])
					{
						j++;
					}
					else if (cmprColor1[j] < cmprColor2[j])
					{			
						sorted.resize(sorted.size());
						sorted.insert(sorted.begin() + index + 1, colors[i + 1]);
						index = -1;						
					}
					else
					{
						if (index != 0)
						{
							cmprColor1 = sorted[tmp - 1].GetName();
							tmp--;

							if (cmprColor1[0] == cmprColor2[0])
							{
								j = 0;
								index = tmp;
							}
							else
							{
								sorted.resize(sorted.size());
								sorted.insert(sorted.begin() + index, colors[i + 1]);
								index = -1;
							}
						}
						else
						{
							sorted.resize(sorted.size());
							sorted.insert(sorted.begin() + index, colors[i + 1]);
							index = -1;
						}
					}
				}
			}
			else if (cmprColor1[0] < cmprColor2[0])
			{
				sorted.resize(sorted.size());
				sorted.insert(sorted.begin() + index + 1, colors[i + 1]);
				index = -1;
			}
			else if (index == 0)
			{
				sorted.insert(sorted.begin(), colors[i + 1]);
				index--;
			}
			else
			{
				index--;
				cmprColor1 = sorted[index].GetName();

			}
		}		
	}	
		for (unsigned int i = 0; i < sorted.size(); i++)
		{
			colors[i] = sorted[i];
		}
}


void PrintColors(vector<Color> &colors)
{
	for (unsigned int i = 0; i < colors.size(); i++)
	{
		cout << colors[i].GetName();
		for (unsigned int j = 0; j < 3 - colors[i].GetName().size() / 8; j++)
			cout << '\t';
		//cout << fixed << setprecision(2) << hex << uppercase << "0x" << stoi(colors[i].GetR()) << stoi(colors[i].GetG()) << stoi(colors[i].GetB());
		printf("0x%.2X%.2X%.2X", stoi(colors[i].GetR()), stoi(colors[i].GetG()), stoi(colors[i].GetB()));
		cout << '\t';
		cout << colors[i].GetR() << "," << colors[i].GetG() << "," << colors[i].GetB() << endl;
	}
	cout << "Number of colors: " << colors.size() << endl;
}