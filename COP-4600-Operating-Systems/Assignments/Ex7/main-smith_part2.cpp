#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	ifstream inPipe(argv[1]);
	cout << "Program failed on operation ";
	cout << count(istreambuf_iterator<char>(inPipe), istreambuf_iterator<char>(), '\n') << endl;
	return 0;
}
