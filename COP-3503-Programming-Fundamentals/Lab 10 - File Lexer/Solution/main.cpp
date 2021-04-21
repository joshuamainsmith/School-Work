#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
	map<string, int> words;

	cout << "Select a file to open (1-4)" << endl;
	int option;
	cin >> option;
	string filename = "ipsum";
	filename.append(to_string(option));
	filename.append(".txt");
	cout << "File name: " << filename << endl;

	/*===== Trimming and Converting =====*/

	ifstream file(filename);
	string line, word;
	vector<string> vecWords;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			for (unsigned int i = 0; i <= line.size(); i++)
			{
				if(line[i] != ' ')
					word += line[i];
				else
				{
					transform(word.begin(), word.end(), word.begin(), ::tolower);
					word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }), word.end());
					vecWords.push_back(word);
					word.clear();
				}
			}
			transform(word.begin(), word.end(), word.begin(), ::tolower);
			word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }), word.end());
			vecWords.push_back(word);
			word.clear();
		}



		//while (getline(file, line,' '))
		//{
		//	if (line.find('\n'))
		//	{
		//		cout << "here" << endl;
		//		string data = line.substr(0, line.find('\n'));

		//		transform(data.begin(), data.end(), data.begin(), ::tolower);
		//		data.erase(remove_if(data.begin(), data.end(), [](char c) { return !isalpha(c); }), data.end());

		//		line = line.substr(line.find(',') + 1, line.size());
		//	}
		//	//	Convert to lowercase
		//	transform(line.begin(), line.end(), line.begin(), ::tolower);

		//	// Trim non-alphabetical characters
		//	line.erase(remove_if(line.begin(), line.end(), [](char c) { return !isalpha(c); }), line.end());

		//	vecWords.push_back(line);
		//	
		//}

		unsigned int count = 0;

		for (unsigned int i = 0; i < vecWords.size(); i++)
		{
			for (unsigned int j = 0; j < vecWords.size(); j++)
			{
				if (vecWords[j] == vecWords[i])
				{
					count++;
				}
			}
			words.emplace(vecWords[i], count);
			count = 0;
		}
	}


	cout << "Choose an operation: " << endl;

	cout << "1. Display word list" << endl;
	cout << "2. Most common word" << endl;
	cout << "3. Words longer than (X) characters" << endl;
	cout << "4. Search for a particular word (ignore case!)" << endl;

	cin >> option;
	if (option == 1)
	{
		unsigned int count = 0;

		for (auto iter = words.begin(); iter != words.end(); iter++)
		{
			if (iter->second != 11 || count != 0)
			{
				cout << iter->first << " " << iter->second << endl;
				count++;
			}
		}

		cout << "Word count: " << count << endl;
	}

	else if (option == 2)
	{
		unsigned int value = 0;
		string str;

		for (auto iter = words.begin(); iter != words.end(); iter++)
		{
			if ((unsigned) iter->second > value)
			{
				str = iter->first;
				value = iter->second;
			}
		}

		cout << "Most commonly used word: " << str << " " << value << endl;
	}

	else if (option == 3)
	{
		unsigned int input = 0;
		string key;
		vector<string> vec;

		cin >> input;

		for (auto iter = words.begin(); iter != words.end(); iter++)
		{
			string str = iter->first;
			for (unsigned int i = 0; i < str.size(); i++)
			{
				if (i >= input)
				{
					i = str.size();
					vec.push_back(str);
				}
			}
		}

		cout << "Words longer than " << input << ": " << endl;

		for (unsigned int i = 0; i < vec.size(); i++)
		{
			cout << vec[i] << endl;
		}
	}

	else if (option == 4)
	{
		string str;
		cin >> str;

		transform(str.begin(), str.end(), str.begin(), ::tolower);

		cout << str << " found in file " << words[str] << " times." << endl;
	}

	file.close();
	system("pause");
		return 0;
}