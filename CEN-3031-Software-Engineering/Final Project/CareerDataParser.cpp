#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>


using namespace std;

int main()
{
	ifstream iFile, iFile2;
	ofstream oFile;
	string str, str2, soccode, soctitle, clusterTitle, strTmp,
		soccmpr;
	int itr = 1;
	double entryWage, meanWage;


	iFile.open("Career_Path_Jobs.csv");
	oFile.open("output.csv");

	while (getline(iFile, str, '\n')) {

		if (str.find('\"') != string::npos) {
			while (str.find('\"') != string::npos) {
				getline(iFile, str, '\n');
			}
		}

		stringstream ss(str);
		while (getline(ss, str, ',')) {
			
			if (itr == 2 || (itr >= 4 && itr <= 7) && str[0] != '\"' && str[str.length()] != '\"') {

				if (str[0] == '\"') {
					str[0] = ' ';
					oFile << str << ",";

					while (str[str.length() - 1] != '\"') {
						getline(ss, str, ',');
						/*oFile << str;
						if (str[str.length() - 1] != '\"')
							oFile << " | ";
						else
							oFile << ",";*/
					}
				}
				else {
					oFile << str;
					if (itr != 7)
						oFile << ",";

				}
			}
			itr++;
		}

		oFile << "\n";
		itr = 1;
	}

	iFile.close();
	oFile.close();

	itr = 1;
	iFile.open("output.csv");
	oFile.open("output2.csv");

	// Long-term...csv line
	while (getline(iFile, str, '\n')) {

		stringstream ss(str);
		string strLine = str;
		
		// Long-term...csv element
		while (getline(ss, str, ',')) {

			if (itr == 3) {

				iFile2.open("Long-Term_Occupational_Employment_Projections.csv");
				
				int tmp = itr;

				itr = 1;

				// output.csv line
				while (getline(iFile2, str2, '\n')) {
					//cout << "#1" << endl;

					stringstream ss(str2);

					bool match = false;

					// output.csv element
					while (getline(ss, str2, ',')) {						

						if (itr == 5 && str == str2) {
							match = true;							
							cout << "#2" << endl;
							cout << strLine << endl;
						}

						else if (itr == 10 && match == true) {
							strLine.append(",");
							strLine.append(str2);
							strLine.append(",");

							if (str2[0] == '\"') {
								str2[0] = ' ';

								while (str2[str2.length() - 1] != '\"') {
									getline(ss, str2, ',');
								}

								str2[str2.length()] = ' ';
							}


							cout << "#3" << endl;

						}

						else if ((itr == 16 || itr == 17) && match == true) {

							if (str2[0] == '\"') {
								str2[0] = ' ';
							}

							/*if (strLine[strLine.length()] != ',')
								strLine.append(",");*/


							strLine.append(str2);

							if (str2[0] == '\"') {

								while (str2[str2.length() - 1] != '\"') {
									getline(ss, strTmp, ',');										
								}

								str2[str2.length()] = ' ';
							}

							if (itr != 19)
								strLine.append(",");

							cout << "#4" << endl;

						}
						//cout << "Itr = " << itr << endl;
						itr++;
					}

					if (match == true && itr >= 20) {
						oFile << strLine << "\n";
						cout << "#5" << endl;

						break;
					}

					itr = 1;
				}
				itr = tmp;
				iFile2.close();
				//str.append(str2);
				//str.append(",");
			}

			

			itr++;
		}

		itr = 1;
	}

	iFile.close();
	oFile.close();




	itr = 1;
	iFile.open("output2.csv");
	oFile.open("output3.csv");

	// Long-term...csv line
	while (getline(iFile, str, '\n')) {

		stringstream ss(str);
		string strLine = str;
		
		// Long-term...csv element
		while (getline(ss, str, ',')) {

			if (itr == 3) {

				iFile2.open("soc_2018_definitions.csv");
				
				int tmp = itr;

				itr = 1;

				// output.csv line
				while (getline(iFile2, str2, '\n')) {
					//cout << "#1" << endl;

					stringstream ss(str2);

					bool match = false;

					// output.csv element
					while (getline(ss, str2, ',')) {						

						if (itr == 2 && str == str2) {
							//match = true;

							getline(ss, str2, '\"');
							getline(ss, str2, '\"');
							strLine.append("\"");
							strLine.append(str2);
							strLine.append("\"");
							strLine.append("\n");

							oFile << strLine;

							cout << "#2" << endl;
						}

						else if (itr == 4 && match == true) {
							strLine.append(str2);
							
							oFile << strLine;
							
							cout << "#3" << endl;

							if (str2[0] == '\"') {
								strLine.append(",");
								
								getline(ss, str2, '\"');
								
								strLine.append(str2);
								strLine.append("");
							}

							oFile << "\n";
						}
						
						itr++;
					}					

					itr = 1;
				}
				itr = tmp;
				iFile2.close();
				//str.append(str2);
				//str.append(",");
			}

			

			itr++;
		}

		itr = 1;
	}

	iFile.close();
	oFile.close();

	return 0;
}