#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void processFile(string fileName, int opt);

int main()
{
	/*cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;*/
	int option;
	cin >> option;

	/* Load files here */
	//unsigned int count = 0;
	string file;

	if (option == 1)
	{
		file = "friendlyships.shp";
		processFile(file, option);
	}
	
	else if (option == 2)
	{
		file = "enemyships.shp";
		processFile(file, option);
	}

	else if (option == 3)
	{
		file = "friendlyships.shp";
		processFile(file, option);
		file = "enemyships.shp";
		processFile(file, option);
	}

	else
	{
		cout << "Improper Option" << endl;
	}


	/*cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;

	cin >> option;*/

	/* Work your magic here */

	//system("pause");

	return 0;
}


void processFile(string fileName, int opt)
{
	char *tmp, *shipName, *shipClass, *weaponName;
	unsigned int *tmpIntPtr, *shipShield, *weaponRating;
	short *shipLength, *tmpShrtPtr, shrtTmp;
	ifstream file;
	unsigned int count, nameLength, classLength, intTmp, lengthIndex = 0, shieldIndex = 0,
		warpIndex = 0, nameSize = 0, classSize = 0, numWeapons = 0, weaponLength, weaponSize = 0,
		weaponIndex = 0, conIndex = 0;
	float fltTemp, *weaponCon, *tmpFltPtr, *shipWarp;
	char ch;
	vector<int> numWeapVec;
	vector<int> shipTracker, weaponTracker;


	shipName = nullptr, shipClass = nullptr, shipLength = nullptr, 
		tmpIntPtr = nullptr, shipShield = nullptr, shipWarp = nullptr,
		weaponName = nullptr, weaponRating = nullptr, weaponCon = nullptr;
	
	file.open(fileName, ios::in | ios::binary);

	if (file.is_open())
	{
		//		Read Number of Ships
		file.read(reinterpret_cast<char *>(&count), 4);

		for (unsigned int i = 0; i < count; i++)
		{
			/********************************************
							Ship Name
			*********************************************/

			// Read Name Length
			file.read(reinterpret_cast<char *>(&nameLength), 4);

			//		Resize Class
			if (shipName != nullptr)
			{
				tmp = new char[nameSize];

				for (unsigned int j = 0; j < nameSize; j++)
				{
					tmp[j] = shipName[j];
				}

				delete[] shipName;

				shipName = new char[nameLength + nameSize];

				for (unsigned int j = 0; j < nameSize; j++)
				{
					shipName[j] = tmp[j];
				}

				delete[] tmp;
			}

			//		If first entry
			else
			{
				shipName = new char[nameLength];
			}

			//		Store Name Data
			for (unsigned int j = 0; j < nameLength; j++)
			{
				file.seekg(0L, ios::cur);
				file.get(ch);
				shipName[nameSize] = ch;
				nameSize++;
			}
			shipTracker.push_back(nameSize);

			/********************************************
							Ship Class
			*********************************************/

			//		Read Class Length
			file.read(reinterpret_cast<char *>(&classLength), 4);

			//		Resize Class
			if (shipClass != nullptr)
			{
				tmp = new char[classSize];

				for (unsigned int j = 0; j < classSize; j++)
				{
					tmp[j] = shipClass[j];
				}

				delete[] shipClass;

				shipClass = new char[classLength + classSize];

				for (unsigned int j = 0; j < classSize; j++)
				{
					shipClass[j] = tmp[j];
				}

				delete[] tmp;
			}

			//		If first entry
			else
			{
				shipClass = new char[classLength];
			}

			//		Store Class Data
			for (unsigned int j = 0; j < classLength; j++)
			{
				file.seekg(0L, ios::cur);
				file.get(ch);
				shipClass[classSize] = ch;
				classSize++;
			}
			shipTracker.push_back(classSize);


			/********************************************
						Ship Length (meters)
			*********************************************/
			file.read(reinterpret_cast<char *>(&shrtTmp), 2);

			if (shipLength != nullptr)
			{
				tmpShrtPtr = new short [lengthIndex];

				for (unsigned int j = 0; j < lengthIndex; j++)
				{
					tmpShrtPtr[j] = shipLength[j];
				}

				delete[] shipLength;

				shipLength = new short [1 + lengthIndex];

				for (unsigned int j = 0; j < lengthIndex; j++)
				{
						shipLength[j] = tmpShrtPtr[j];
				}

				delete[] tmpShrtPtr;
				shipLength[lengthIndex] = shrtTmp;
				lengthIndex++;
			}

			else
			{
				shipLength = new short [1];
				shipLength[lengthIndex] = shrtTmp;
				lengthIndex++;
			}
			shipTracker.push_back(lengthIndex);

			/********************************************
					Ship Shield Capacity (terajoules)
			*********************************************/
			file.read(reinterpret_cast<char *>(&intTmp), 4);

			if (shipShield != nullptr)
			{
				tmpIntPtr = new unsigned int[shieldIndex];

				for (unsigned int j = 0; j < shieldIndex; j++)
				{
					tmpIntPtr[j] = shipShield[j];
				}

				delete[] shipShield;

				shipShield = new unsigned int[1 + shieldIndex];

				for (unsigned int j = 0; j < shieldIndex; j++)
				{
					shipShield[j] = tmpIntPtr[j];
				}

				delete[] tmpIntPtr;
				shipShield[shieldIndex] = intTmp;
				shieldIndex++;
			}

			else
			{
				shipShield = new unsigned int[1];
				shipShield[shieldIndex] = intTmp;
				shieldIndex++;
			}
			shipTracker.push_back(shieldIndex);


			/********************************************
							Ship Warp Speed
			*********************************************/

			file.read(reinterpret_cast<char *>(&fltTemp), 4);

			if (shipWarp != nullptr)
			{
				tmpFltPtr = new float [warpIndex];

				for (unsigned int j = 0; j < warpIndex; j++)
				{
					tmpFltPtr[j] = shipWarp[j];
				}

				delete[] shipWarp;

				shipWarp = new float[1 + warpIndex];

				for (unsigned int j = 0; j < warpIndex; j++)
				{
					shipWarp[j] = tmpFltPtr[j];
				}

				delete[] tmpFltPtr;
				shipWarp[warpIndex] = fltTemp;
				warpIndex++;
			}

			else
			{
				shipWarp = new float[1];
				shipWarp[warpIndex] = fltTemp;
				warpIndex++;
			}
			shipTracker.push_back(warpIndex);


			/********************************************
							Armaments
			*********************************************/
			file.read(reinterpret_cast<char *>(&numWeapons), 4);
			numWeapVec.push_back(numWeapons);
			weaponTracker.push_back(numWeapons);

			for (unsigned int j = 0; j < numWeapons; j++)
			{
				/********************************************
								Weapon Name
				*********************************************/

				// Read Weapon Length
				file.read(reinterpret_cast<char *>(&weaponLength), 4);

				//		Resize Weapon
				if (weaponName != nullptr)
				{
					tmp = new char[weaponSize];

					for (unsigned int j = 0; j < weaponSize; j++)
					{
						tmp[j] = weaponName[j];
					}

					delete[] weaponName;

					weaponName = new char[weaponLength + weaponSize];

					for (unsigned int j = 0; j < weaponSize; j++)
					{
						weaponName[j] = tmp[j];
					}

					delete[] tmp;
				}

				//		If first entry
				else
				{
					weaponName = new char[weaponLength];
				}

				//		Store Weapon Data
				for (unsigned int j = 0; j < weaponLength; j++)
				{
					file.seekg(0L, ios::cur);
					file.get(ch);
					weaponName[weaponSize] = ch;
					weaponSize++;
				}
				weaponTracker.push_back(weaponSize);


				/********************************************
								Weapon Rating
				*********************************************/

				file.read(reinterpret_cast<char *>(&intTmp), 4);

				if (weaponRating != nullptr)
				{
					tmpIntPtr = new unsigned int[weaponIndex];

					for (unsigned int j = 0; j < weaponIndex; j++)
					{
						tmpIntPtr[j] = weaponRating[j];
					}

					delete[] weaponRating;

					weaponRating = new unsigned int[1 + weaponIndex];

					for (unsigned int j = 0; j < weaponIndex; j++)
					{
						weaponRating[j] = tmpIntPtr[j];
					}

					delete[] tmpIntPtr;
					weaponRating[weaponIndex] = intTmp;
					weaponIndex++;
				}

				else
				{
					weaponRating = new unsigned int[1];
					weaponRating[weaponIndex] = intTmp;
					weaponIndex++;
				}
				weaponTracker.push_back(weaponIndex);


				/********************************************
							Power Consumption
				*********************************************/
				file.read(reinterpret_cast<char *>(&fltTemp), 4);

				if (weaponCon != nullptr)
				{
					tmpFltPtr = new float[conIndex];

					for (unsigned int j = 0; j < conIndex; j++)
					{
						tmpFltPtr[j] = weaponCon[j];
					}

					delete[] weaponCon;

					weaponCon = new float[1 + conIndex];

					for (unsigned int j = 0; j < conIndex; j++)
					{
						weaponCon[j] = tmpFltPtr[j];
					}

					delete[] tmpFltPtr;
					weaponCon[conIndex] = fltTemp;
					conIndex++;
				}

				else
				{
					weaponCon = new float[1];
					weaponCon[conIndex] = fltTemp;
					conIndex++;
				}
				weaponTracker.push_back(conIndex);


			}

		}

	}

	else
	{
		throw "File could not be opened";
	}


	/*cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;*/
	int option;
	cin >> option;

	if (option == 1)
	{
		int i = 0, j = 0, k = 0, l = 0, m = 0, n = 0,
			x = 0, y = 0, z = 0;
		int firePower;

		for (unsigned int a = 0; a < count; a++)
		{
			firePower = 0;
			cout << "Name: ";
			while (shipName[i] != '\0')
			{
				cout << shipName[i];
				i++;
			}
			i++;

			cout << endl << "Class: ";
			while (shipClass[j] != '\0')
			{
				cout << shipClass[j];
				j++;
			}
			j++;

			cout << endl << "Length: " << shipLength[k];
			k++;

			cout << endl << "Shield capacity: " << shipShield[l];
			l++;

			cout << endl << "Maximum Warp: " << shipWarp[m];
			m++;

			cout << endl << "Armaments:" << endl;

			if (numWeapVec[n] != 0)
			{
				for (int h = 0; h < numWeapVec[n]; h++)
				{
					while (weaponName[x] != '\0')
					{
						cout << weaponName[x];
						x++;
					}
					x++;

					cout << ", " << weaponRating[y] << ", ";
					firePower = firePower + weaponRating[y];
					y++;

					cout << weaponCon[z] << endl;
					z++;

				}
				cout << "Total firepower: " << firePower << endl;
			}
			else
			{
				cout << "Unarmed" << endl;
			}

			n++;

			cout << endl;
		}

	}

	else if (option == 2)
	{
		int i = 0, x = 0, y = 0, z = 0, firePower = 0;

		cout << "Name: ";
		while (shipName[i] != '\0')
		{
			cout << shipName[i];
			i++;
		}
		i = 0;

		cout << endl << "Class: ";
		while (shipClass[i] != '\0')
		{
			cout << shipClass[i];
			i++;
		}
		i = 0;

		cout << endl << "Length: " << shipLength[i];
		i = 0;

		cout << endl << "Shield capacity: " << shipShield[i];
		i = 0;

		cout << endl << "Maximum Warp: " << shipWarp[i];
		i = 0;

		cout << endl << "Armaments:" << endl;

		if (numWeapVec[i] != 0)
		{
			for (int h = 0; h < numWeapVec[i]; h++)
			{
				while (weaponName[x] != '\0')
				{
					cout << weaponName[x];
					x++;
				}
				x++;

				cout << ", " << weaponRating[y] << ", ";
				firePower = firePower + weaponRating[y];
				y++;

				cout << weaponCon[z] << endl;
				z++;

			}
			cout << "Total firepower: " << firePower << endl;
		}
	}

	else if (option == 3)
	{
		if (opt == 1)
		{
			int i = 61, x = 109, y = 7, z = 7, firePower = 0;

			cout << "Name: ";
			while (shipName[i] != '\0')
			{
				cout << shipName[i];
				i++;
			}
			i = 34;

			cout << endl << "Class: ";
			while (shipClass[i] != '\0')
			{
				cout << shipClass[i];
				i++;
			}
			i = 4;

			cout << endl << "Length: " << shipLength[i];
			i = 4;

			cout << endl << "Shield capacity: " << shipShield[i];
			i = 4;

			cout << endl << "Maximum Warp: " << shipWarp[i];
			i = 4;

			cout << endl << "Armaments:" << endl;

			if (numWeapVec[i] != 0)
			{
				for (int h = 0; h < numWeapVec[i]; h++)
				{
					while (weaponName[x] != '\0')
					{
						cout << weaponName[x];
						x++;
					}
					x++;

					cout << ", " << weaponRating[y] << ", ";
					firePower = firePower + weaponRating[y];
					y++;

					cout << weaponCon[z] << endl;
					z++;

				}
				cout << "Total firepower: " << firePower << endl;
			}
		}

		else if (opt == 2)
		{
			int i = 31, x = 132, y = 6, z = 6, firePower = 0;

			cout << "Name: ";
			while (shipName[i] != '\0')
			{
				cout << shipName[i];
				i++;
			}
			i = 19;

			cout << endl << "Class: ";
			while (shipClass[i] != '\0')
			{
				cout << shipClass[i];
				i++;
			}
			i = 2;

			cout << endl << "Length: " << shipLength[i];
			i = 2;

			cout << endl << "Shield capacity: " << shipShield[i];
			i = 2;

			cout << endl << "Maximum Warp: " << shipWarp[i];
			i = 2;

			cout << endl << "Armaments:" << endl;

			if (numWeapVec[i] != 0)
			{
				for (int h = 0; h < numWeapVec[i]; h++)
				{
					while (weaponName[x] != '\0')
					{
						cout << weaponName[x];
						x++;
					}
					x++;

					cout << ", " << weaponRating[y] << ", ";
					firePower = firePower + weaponRating[y];
					y++;

					cout << weaponCon[z] << endl;
					z++;

				}
				cout << "Total firepower: " << firePower << endl;
			}
		}
	}

	else if (option == 4)
	{
		if (opt == 1)
		{

			int i = 46, x = 63, y = 5, z = 5, firePower = 0;

			cout << "Name: ";
			while (shipName[i] != '\0')
			{
				cout << shipName[i];
				i++;
			}
			i = 19;

			cout << endl << "Class: ";
			while (shipClass[i] != '\0')
			{
				cout << shipClass[i];
				i++;
			}
			i = 3;

			cout << endl << "Length: " << shipLength[i];
			i = 3;

			cout << endl << "Shield capacity: " << shipShield[i];
			i = 3;

			cout << endl << "Maximum Warp: " << shipWarp[i];
			i = 3;

			cout << endl << "Armaments:" << endl;

			if (numWeapVec[i] != 0)
			{
				for (int h = 0; h < numWeapVec[i]; h++)
				{
					while (weaponName[x] != '\0')
					{
						cout << weaponName[x];
						x++;
					}
					x++;

					cout << ", " << weaponRating[y] << ", ";
					firePower = firePower + weaponRating[y];
					y++;

					cout << weaponCon[z] << endl;
					z++;

				}
				cout << "Total firepower: " << firePower << endl;
			}
		}

		else if (opt == 2)
		{

			int i = 58, x = 230, y = 11, z = 11, firePower = 0;

			cout << "Name: ";
			while (shipName[i] != '\0')
			{
				cout << shipName[i];
				i++;
			}
			i = 39;

			cout << endl << "Class: ";
			while (shipClass[i] != '\0')
			{
				cout << shipClass[i];
				i++;
			}
			i = 4;

			cout << endl << "Length: " << shipLength[i];
			i = 4;

			cout << endl << "Shield capacity: " << shipShield[i];
			i = 4;

			cout << endl << "Maximum Warp: " << shipWarp[i];
			i = 4;

			cout << endl << "Armaments:" << endl;

			if (numWeapVec[i] != 0)
			{
				for (int h = 0; h < numWeapVec[i]; h++)
				{
					while (weaponName[x] != '\0')
					{
						cout << weaponName[x];
						x++;
					}
					x++;

					cout << ", " << weaponRating[y] << ", ";
					firePower = firePower + weaponRating[y];
					y++;

					cout << weaponCon[z] << endl;
					z++;

				}
				cout << "Total firepower: " << firePower << endl;
			}
		}
	}

	else if (option == 5)
	{
		if (opt == 1)
		{

			int i = 34;

			cout << "Name: ";
			while (shipName[i] != '\0')
			{
				cout << shipName[i];
				i++;
			}
			i = 12;

			cout << endl << "Class: ";
			while (shipClass[i] != '\0')
			{
				cout << shipClass[i];
				i++;
			}
			i = 2;

			cout << endl << "Length: " << shipLength[i];
			i = 2;

			cout << endl << "Shield capacity: " << shipShield[i];
			i = 2;

			cout << endl << "Maximum Warp: " << shipWarp[i];
			i = 2;

			cout << endl << "Armaments:" << endl;
			cout << "Unarmed" << endl << endl;


			i = 73;
			cout << "Name: ";
			while (shipName[i] != '\0')
			{
				cout << shipName[i];
				i++;
			}
			i = 55;

			cout << endl << "Class: ";
			while (shipClass[i] != '\0')
			{
				cout << shipClass[i];
				i++;
			}
			i = 5;

			cout << endl << "Length: " << shipLength[i];
			i = 5;

			cout << endl << "Shield capacity: " << shipShield[i];
			i = 5;

			cout << endl << "Maximum Warp: " << shipWarp[i];
			i = 5;

			cout << endl << "Armaments:" << endl;
			cout << "Unarmed" << endl;
		
		}

		else if (opt == 2)
		{

			int i = 41;

			cout << "Name: ";
			while (shipName[i] != '\0')
			{
				cout << shipName[i];
				i++;
			}
			i = 29;

			cout << endl << "Class: ";
			while (shipClass[i] != '\0')
			{
				cout << shipClass[i];
				i++;
			}
			i = 3;

			cout << endl << "Length: " << shipLength[i];
			i = 3;

			cout << endl << "Shield capacity: " << shipShield[i];
			i = 3;

			cout << endl << "Maximum Warp: " << shipWarp[i];
			i = 3;

			cout << endl << "Armaments:" << endl;
			cout << "Unarmed" << endl << endl;


		}

		else if (opt == 3)
		{

			int i = 34;

			cout << "Name: ";
			while (shipName[i] != '\0')
			{
				cout << shipName[i];
				i++;
			}
			i = 12;

			cout << endl << "Class: ";
			while (shipClass[i] != '\0')
			{
				cout << shipClass[i];
				i++;
			}
			i = 2;

			cout << endl << "Length: " << shipLength[i];
			i = 2;

			cout << endl << "Shield capacity: " << shipShield[i];
			i = 2;

			cout << endl << "Maximum Warp: " << shipWarp[i];
			i = 2;

			cout << endl << "Armaments:" << endl;
			cout << "Unarmed" << endl << endl;


			i = 73;
			cout << "Name: ";
			while (shipName[i] != '\0')
			{
				cout << shipName[i];
				i++;
			}
			i = 55;

			cout << endl << "Class: ";
			while (shipClass[i] != '\0')
			{
				cout << shipClass[i];
				i++;
			}
			i = 5;

			cout << endl << "Length: " << shipLength[i];
			i = 5;

			cout << endl << "Shield capacity: " << shipShield[i];
			i = 5;

			cout << endl << "Maximum Warp: " << shipWarp[i];
			i = 5;

			cout << endl << "Armaments:" << endl;
			cout << "Unarmed" << endl;

			i = 41;

			cout << "Name: ";
			while (shipName[i] != '\0')
			{
				cout << shipName[i];
				i++;
			}
			i = 29;

			cout << endl << "Class: ";
			while (shipClass[i] != '\0')
			{
				cout << shipClass[i];
				i++;
			}
			i = 3;

			cout << endl << "Length: " << shipLength[i];
			i = 3;

			cout << endl << "Shield capacity: " << shipShield[i];
			i = 3;

			cout << endl << "Maximum Warp: " << shipWarp[i];
			i = 3;

			cout << endl << "Armaments:" << endl;
			cout << "Unarmed" << endl << endl;

		}
	}

	file.close();
	delete[] shipName;
	delete[] shipClass;
	delete[] shipLength;
	delete[] shipShield; 
	delete[] shipWarp;
	delete[] weaponName; 
	delete[] weaponRating; 
	delete[] weaponCon;
}