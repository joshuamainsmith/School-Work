#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

// Classes
template <typename T>
class LegoSets
{
private:
	unsigned int capacity;
	unsigned int size;
	unsigned int tmpItr;

	int piece;
	int stoiPiece;
	
	T *data;
	T *tmp;

	double price;
	double stodPrice;
public:
	LegoSets()
	{
		capacity = 1;
		size = 0;
		data = new T[capacity];

		price = 0;
	}

	LegoSets(int capacity)
	{
		this->capacity = capacity;
		size = 0;
		data = new T[capacity];
	}

	~LegoSets()
	{
		delete[] data;
	}

	void setData(T data, int itr)
	{
		this->data[itr] = data;
	}

	void push(T d)
	{
		if (capacity == size)
		{
			// double capacity
			increaseCap(capacity);
		}

		this->data[size] = d;

		size++;
	}

	T peek()
	{
		if (size == 0)
		{
			throw - 1;
		}

		return data[size - 1];
	}

	void increaseCap(int capacity)
	{
		tmp = new T[size];

		// Temporarily store content from data into tmp
		for (unsigned int i = 0; i < size; i++)
		{
			tmp[i] = data[i];
		}

		delete[] data;

		// Resize capacity
		this->capacity = capacity * 2;
		data = new T[this->capacity];

		for (unsigned int i = 0; i < size; i++)
		{
			data[i] = tmp[i];
		}

		delete[] tmp;
	}

	T pop()
	{
		if (size == 0)
		{
			throw - 1;
		}

		size--;
		T tmpPop = data[size];


		if (((double)capacity / (double)size) > 2)
		{
			// shrink capacity to half size
			decreaseCap(capacity);
		}

		return tmpPop;
	}

	void decreaseCap(int capacity)
	{
		tmp = new T[size];

		// Temporarily store content from data into tmp
		for (unsigned int i = 0; i < size; i++)
		{
			tmp[i] = data[i];
		}

		delete[] data;

		// Resize capacity
		this->capacity = capacity / 2;
		data = new T[this->capacity];

		for (unsigned int i = 0; i < size; i++)
		{
			data[i] = tmp[i];
		}

		delete[] tmp;
	}

	void mostExpensive()
	{
		int j = 0;
		for (unsigned int i = 11; i < size; i += 6)
		{
			stodPrice = stod(data[i]);

			if (stodPrice > price)
			{
				price = stodPrice;
				tmpItr = i - 5;
			}

			j++;
		}

		cout << "Total number of sets: " << j << endl << endl;

		cout << "The most expensive set is:" << endl;
		tmpItr += 2;
		cout <<  "Name: " << data[tmpItr] << endl;
		tmpItr -= 2;
		cout << "Number: " << data[tmpItr] << endl;
		tmpItr++;
		cout << "Theme: " << data[tmpItr] << endl;
		tmpItr += 4;
		cout << "Price: $" << fixed << setprecision(2) << stod(data[tmpItr]) << endl;
		tmpItr -= 2;
		cout << "Minifigures: " << data[tmpItr] << endl;
		tmpItr++;
		cout << "Piece count: " << data[tmpItr] << endl;
	}

	void largestPiece()
	{
		int j = 0;
		for (unsigned int i = 10; i < size; i += 6)
		{
			stoiPiece = stoi(data[i]);

			if (stoiPiece > piece)
			{
				piece = stoiPiece;
				tmpItr = i - 4;
			}
			j++;
		}

		cout << "Total number of sets: " << j << endl << endl;

		cout << "The set with the highest parts count:" << endl;
		tmpItr += 2;
		cout << "Name: " << data[tmpItr] << endl;
		tmpItr -= 2;
		cout << "Number: " << data[tmpItr] << endl;
		tmpItr++;
		cout << "Theme: " << data[tmpItr] << endl;
		tmpItr += 4;
		cout << "Price: $" << fixed << setprecision(2) << stod(data[tmpItr]) << endl;
		tmpItr -= 2;
		cout << "Minifigures: " << data[tmpItr] << endl;
		tmpItr++;
		cout << "Piece count: " << data[tmpItr] << endl;
	}

	void searchSet(string set)
	{
		int tmpArr[200];

		size_t temp;
		int z = 0, numSets=0;
		for (unsigned int i = 8; i < size; i += 6)
		{
			temp = data[i].find(set);
			if (temp < 100)
			{
				tmpItr = i - 2;
				tmpArr[z] = tmpItr;
				z++;
			}

			numSets++;
		}
		cout << "Total number of sets: " << numSets << endl << endl;

		if (z > 0)
		{
			cout << "Sets matching \"" << set << "\":" << endl;

			for (int i = 0; i < z; i++)
			{
				tmpItr = tmpArr[i];

				cout << data[tmpItr] << " ";
				tmpItr += 2;
				cout << data[tmpItr] << " $";
				tmpItr += 3;
				cout << fixed << setprecision(2) << stod(data[tmpItr]) << endl;
			}			
		}

		else
		{
			cout << "No sets found matching that search term" << endl;
		}
	}


	void searchTheme(string set)
	{
		int tmpArr[500];

		size_t temp;
		int z = 0, numSets = 0;
		for (unsigned int i = 7; i < size; i += 6)
		{
			temp = data[i].find(set);
			if (temp < 100)
			{
				tmpItr = i - 1;
				tmpArr[z] = tmpItr;
				z++;

			}	
			numSets++;
		}

		cout << "Total number of sets: " << numSets << endl << endl;

		if (z > 0)
		{
			cout << "Sets matching \"" << set << "\":" << endl;

			for (int i = 0; i < z; i++)
			{
				tmpItr = tmpArr[i];

				cout << data[tmpItr] << " ";
				tmpItr += 2;
				cout << data[tmpItr] << " $";
				tmpItr += 3;
				cout << fixed << setprecision(2) << stod(data[tmpItr]) << endl;
			}
		}

		else
		{
			cout << "No sets found matching that search term" << endl;
		}
	}

	void pieceInfo()
	{
		int j = 0;
		piece = 0;
		for (unsigned int i = 10; i < size; i += 6)
		{
			stoiPiece = stoi(data[i]);
			piece = piece + stoiPiece;
			j++;
		}

		cout << "Total number of sets: " << j << endl << endl;

		cout << "Average part count for " << j << " sets: " << piece / j << endl;
	}

	void priceInfo()
	{
		int tmpItr2 = 0, j = 0;
		double maxPrice = 0, minPrice = 100, totPrice = 0;
		for (unsigned int i = 11; i < size; i += 6)
		{
			stodPrice = stod(data[i]);

			if (stodPrice > maxPrice)
			{
				maxPrice = stodPrice;
				tmpItr = i - 5;
			}

			if (stodPrice < minPrice)
			{
				minPrice = stodPrice;
				tmpItr2 = i - 5;
			}

			totPrice = stodPrice + totPrice;
			j++;
		}

		cout << "Total number of sets: " << j << endl << endl;

		cout << "Average price for " << j << " sets: $" << totPrice / j << endl << endl;

		cout << "Least expensive set:" << endl;
		tmpItr2 += 2;
		cout << "Name: " << data[tmpItr2] << endl;
		tmpItr2 -= 2;
		cout << "Number: " << data[tmpItr2] << endl;
		tmpItr2++;
		cout << "Theme: " << data[tmpItr2] << endl;
		tmpItr2 += 4;
		cout << "Price: $" << fixed << setprecision(2) << stod(data[tmpItr2]) << endl;
		tmpItr2 -= 2;
		cout << "Minifigures: " << data[tmpItr2] << endl;
		tmpItr2++;
		cout << "Piece count: " << data[tmpItr2] << endl << endl;


		cout << "Most expensive set:" << endl;
		tmpItr += 2;
		cout << "Name: " << data[tmpItr] << endl;
		tmpItr -= 2;
		cout << "Number: " << data[tmpItr] << endl;
		tmpItr++;
		cout << "Theme: " << data[tmpItr] << endl;
		tmpItr += 4;
		cout << "Price: $" << fixed << setprecision(2) << stod(data[tmpItr]) << endl;
		tmpItr -= 2;
		cout << "Minifigures: " << data[tmpItr] << endl;
		tmpItr++;
		cout << "Piece count: " << data[tmpItr] << endl;
	}

	void miniInfo()
	{
		int minifig = 0, maxMini = 0, j = 0;
		int tmpMini = 0;

		for (unsigned int i = 9; i < size; i += 6)
		{
			tmpMini = stoi(data[i]);
			if (tmpMini > maxMini)
			{
				maxMini = tmpMini;
				tmpItr = i - 3;
			}
			minifig = minifig + tmpMini;
			j++;
		}

		cout << "Total number of sets: " << j << endl << endl;

		cout << "Average number of minifigures: " << minifig / j << endl;

		cout << "Set with the most minifigures:" << endl;
		tmpItr += 2;
		cout << "Name: " << data[tmpItr] << endl;
		tmpItr -= 2;
		cout << "Number: " << data[tmpItr] << endl;
		tmpItr++;
		cout << "Theme: " << data[tmpItr] << endl;
		tmpItr += 4;
		cout << "Price: $" << fixed << setprecision(2) << stod(data[tmpItr]) << endl;
		tmpItr -= 2;
		cout << "Minifigures: " << data[tmpItr] << endl;
		tmpItr++;
		cout << "Piece count: " << data[tmpItr] << endl;

	}

	void buyEverything()
	{
		float totalPrice = 0;
		int totalPieces = 0, totalMinis = 0, j = 0;
		
		for (unsigned int i = 11; i < size; i += 6)
		{
			totalPrice = totalPrice + stof(data[i]);
			totalPieces = totalPieces + stod(data[--i]);
			totalMinis = totalMinis + stod(data[--i]);
			i += 2;
			j++;
		}

		cout << "Total number of sets: " << j << endl << endl;

		cout << "If you bought one of everything..." << endl;
		cout << "It would cost: $" << fixed << setprecision(2) << totalPrice << endl;
		cout << "You would have " << totalPieces << " pieces in your collection" << endl;
		cout << "You would have an army of " << totalMinis << " minifigures!" << endl;
	}
};


int main()
{
	cout << std::fixed << setprecision(2);
	cout << "Which file(s) to open?\n";
	cout << "1. lego1.csv" << endl;
	cout << "2. lego2.csv" << endl;
	cout << "3. lego3.csv" << endl;
	cout << "4. All 3 files" << endl;
	int option;
	cin >> option;

	/*======= Load data from file(s) =======*/
	LegoSets<string> Lego;

	if (option == 1)
	{
		string line;
		ifstream file1("lego1.csv");

		if (file1.is_open())
		{
			while (getline(file1, line))
			{
				// Number
				string data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());
				
				// Theme
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Name
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Minifigs
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Pieces
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// USPrice
				Lego.push(line);

				//cout << Lego.peek() << endl;
			}
		}

		file1.close();
	}

	else if (option == 2)
	{
		string line;
		ifstream file2("lego2.csv");

		if (file2.is_open())
		{
			while (getline(file2, line))
			{
				// Number
				string data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Theme
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Name
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Minifigs
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Pieces
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// USPrice
				Lego.push(line);
			}
		}

		file2.close();
	}

	else if (option == 3)
	{
		string line;
		ifstream file3("lego3.csv");
		

		if (file3.is_open())
		{
			while (getline(file3, line))
			{
				// Number
				string data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Theme
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Name
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Minifigs
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Pieces
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// USPrice
				Lego.push(line);
			}
		}

		file3.close();
	}

	else if (option == 4)
	{
	string line;
	ifstream file1("lego1.csv");
	int i = 0;

	if (file1.is_open())
	{
		while (getline(file1, line))
		{
			// Number
			string data = line.substr(0, line.find(','));
			Lego.push(data);
			line = line.substr(line.find(',') + 1, line.size());

			// Theme
			data = line.substr(0, line.find(','));
			Lego.push(data);
			line = line.substr(line.find(',') + 1, line.size());

			// Name
			data = line.substr(0, line.find(','));
			Lego.push(data);
			line = line.substr(line.find(',') + 1, line.size());

			// Minifigs
			data = line.substr(0, line.find(','));
			Lego.push(data);
			line = line.substr(line.find(',') + 1, line.size());

			// Pieces
			data = line.substr(0, line.find(','));
			Lego.push(data);
			line = line.substr(line.find(',') + 1, line.size());

			// USPrice
			Lego.push(line);

			//cout << Lego.peek() << endl;
		}
	}

	file1.close();

	ifstream file2("lego2.csv");

	if (file2.is_open())
	{
		while (getline(file2, line))
		{
			if (i > 0)
			{


				// Number
				string data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Theme
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Name
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Minifigs
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Pieces
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// USPrice
				Lego.push(line);
			}
			i++;
		}
	}

	file2.close();

	ifstream file3("lego3.csv");

	if (file3.is_open())
	{
		i = 0;
		while (getline(file3, line))
		{
			if (i > 0)
			{


				// Number
				string data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Theme
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Name
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Minifigs
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// Pieces
				data = line.substr(0, line.find(','));
				Lego.push(data);
				line = line.substr(line.find(',') + 1, line.size());

				// USPrice
				Lego.push(line);
			}
			i++;
		}
	}

	file3.close();
	}
	
	/*======= Print out how many sets were loaded =======*/
	
	/* Imagine your program had a menu like this:*/
	/*cout << "1. Most Expensive set" << endl;
	 cout << "2. Largest piece count" << endl;
	 cout << "3. Search for set name containing..." << endl;
	 cout << "4. Search themes..." << endl;
	 cout << "5. Part count information" << endl;
	 cout << "6. Price information" << endl;
	 cout << "7. Minifigure information" << endl;
	 cout << "8. If you bought one of everything..." << endl;
	 cout << "0. Exit" << endl;*/
	int choice;
	cin >> choice;
	cin.get();  // Clear newline character for any later input

	/*======= Based on the choice, execute the appropriate task and show the results =======*/

	if ((choice >= 1) && (choice <= 4))
	{
		/* Most Expensive set */
		if (choice == 1)
		{
			Lego.mostExpensive();
		}

		/* Largest piece count */
		else if (choice == 2)
		{
			Lego.largestPiece();
		}

		/* Search for set name containing... */
		else if (choice == 3)
		{
			string set;

			getline(cin, set);
			//cin >> set;

			Lego.searchSet(set);
		}
		 /* Search themes... */
		else
		{
			string set;

			getline(cin, set);
			//cin >> set;

			Lego.searchTheme(set);
		}
	}

	else if ((choice >= 5) && (choice <= 8))
	{
		/* Part count information */
		if (choice == 5)
		{
			Lego.pieceInfo();
		}

		/* Price information */
		else if (choice == 6)
		{
			Lego.priceInfo();
		}

		/* Minifigure information */
		else if (choice == 7)
		{
			Lego.miniInfo();
		}

		/* If you bought one of everything... */
		else
		{
			Lego.buyEverything();
		}
	}

	/* Exit */
	else
	{
		
	}
	system("pause");
	return 0;
}



