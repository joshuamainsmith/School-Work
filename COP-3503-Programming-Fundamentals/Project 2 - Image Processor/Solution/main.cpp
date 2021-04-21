#include "ImageProcessing.h"

void tasks(int option);

int main()
{
	int option = 1;
	//cin >> option;

	vector<string> files = { "layer1.tga" /*[0]*/, "layer2.tga" /*[1]*/, "layer_blue.tga" /*[2]*/, "layer_green.tga" /*[3]*/, "layer_red.tga" /*[4]*/,
		"pattern1.tga" /*[5]*/, "pattern2.tga" /*[6]*/,
		"text.tga" /*[7]*/, "text2.tga" /*[8]*/,
		"car.tga" /*[9]*/, "circles.tga", /*[10]*/};
	Image image1, image2, image3, newImage;
	

	string FilePath = "input/";
	do
	{
		if (option == 1)
		{
			tasks(option);
		}

		else if (option == 2)
		{
			tasks(option);
		}

		else if (option == 3)
		{
			tasks(option);
		}

		else if (option == 4)
		{			
			tasks(option);
		}

		else if (option == 5)
		{
			tasks(option);
		}

		else if (option == 6)
		{			
			tasks(option);
		}

		else if (option == 7)
		{			
			tasks(option);

		}

		else if (option == 8)
		{		
			tasks(option);
		}

		else if (option == 9)
		{			
			tasks(option);
		}

		else if (option == 10)
		{			
			tasks(option);
		}

		option++;
	} while (option >= 1 && option <= 10);

	//cin >> option;

	option = 1;

	do {


		char byte1, byte2;
		if (option == 1)
		{
			ifstream madeFile("output/part1.tga", ios::in | ios::binary);
			ifstream originalFile("examples/EXAMPLE_part1.tga", ios::in | ios::binary);

			if (madeFile.is_open() && originalFile.is_open())
			{
				while (true)
				{
					madeFile.read(&byte1, sizeof(byte1));
					originalFile.read(&byte2, sizeof(byte2));

					if (!madeFile || !originalFile)
						break;

					if (byte1 != byte2)
					{
						cout << "No" << endl;
					}
				}
			}
			else
			{
				cout << "Couldn't open" << endl;
			}

			cout << "Test 1 Complete" << endl;

			madeFile.close();
			originalFile.close();

		}

		else if (option == 2)
		{
			ifstream madeFile("output/part2.tga", ios::in | ios::binary);
			ifstream originalFile("examples/EXAMPLE_part2.tga", ios::in | ios::binary);

			if (madeFile.is_open() && originalFile.is_open())
			{
				while (true)
				{
					madeFile.read(&byte1, sizeof(byte1));
					originalFile.read(&byte2, sizeof(byte2));

					if (!madeFile || !originalFile)
						break;

					if (byte1 != byte2)
					{
						cout << "No" << endl;
					}
				}
			}
			else
			{
				cout << "Couldn't open" << endl;
			}

			cout << "Test 2 Complete" << endl;

			madeFile.close();
			originalFile.close();
		}

		else if (option == 3)
		{
			ifstream madeFile("output/part3.tga", ios::in | ios::binary);
			ifstream originalFile("examples/EXAMPLE_part3.tga", ios::in | ios::binary);

			if (madeFile.is_open() && originalFile.is_open())
			{
				while (true)
				{
					madeFile.read(&byte1, sizeof(byte1));
					originalFile.read(&byte2, sizeof(byte2));

					if (!madeFile || !originalFile)
						break;

					if (byte1 != byte2)
					{
						cout << "No" << endl;
					}
				}
			}
			else
			{
				cout << "Couldn't open" << endl;
			}

			cout << "Test 3 Complete" << endl;

			madeFile.close();
			originalFile.close();
		}

		else if (option == 4)
		{
			ifstream madeFile("output/part4.tga", ios::in | ios::binary);
			ifstream originalFile("examples/EXAMPLE_part4.tga", ios::in | ios::binary);

			if (madeFile.is_open() && originalFile.is_open())
			{
				while (true)
				{
					madeFile.read(&byte1, sizeof(byte1));
					originalFile.read(&byte2, sizeof(byte2));

					if (!madeFile || !originalFile)
						break;

					if (byte1 != byte2)
					{
						cout << "No" << endl;
					}
				}
			}
			else
			{
				cout << "Couldn't open" << endl;
			}

			cout << "Test 4 Complete" << endl;

			madeFile.close();
			originalFile.close();
		}

		else if (option == 5)
		{
			ifstream madeFile("output/part5.tga", ios::in | ios::binary);
			ifstream originalFile("examples/EXAMPLE_part5.tga", ios::in | ios::binary);

			if (madeFile.is_open() && originalFile.is_open())
			{
				while (true)
				{
					madeFile.read(&byte1, sizeof(byte1));
					originalFile.read(&byte2, sizeof(byte2));

					if (!madeFile || !originalFile)
						break;

					if (byte1 != byte2)
					{
						cout << "No" << endl;
					}
				}
			}
			else
			{
				cout << "Couldn't open" << endl;
			}

			cout << "Test 5 Complete" << endl;

			madeFile.close();
			originalFile.close();
		}

		else if (option == 6)
		{
			ifstream madeFile("output/part6.tga", ios::in | ios::binary);
			ifstream originalFile("examples/EXAMPLE_part6.tga", ios::in | ios::binary);

			if (madeFile.is_open() && originalFile.is_open())
			{
				while (true)
				{
					madeFile.read(&byte1, sizeof(byte1));
					originalFile.read(&byte2, sizeof(byte2));

					if (!madeFile || !originalFile)
						break;

					if (byte1 != byte2)
					{
						cout << "No" << endl;
					}
				}
			}
			else
			{
				cout << "Couldn't open" << endl;
			}

			cout << "Test 6 Complete" << endl;

			madeFile.close();
			originalFile.close();
		}

		else if (option == 7)
		{
			ifstream madeFile("output/part7.tga", ios::in | ios::binary);
			ifstream originalFile("examples/EXAMPLE_part7.tga", ios::in | ios::binary);

			if (madeFile.is_open() && originalFile.is_open())
			{
				while (true)
				{
					madeFile.read(&byte1, sizeof(byte1));
					originalFile.read(&byte2, sizeof(byte2));

					if (!madeFile || !originalFile)
						break;

					if (byte1 != byte2)
					{
						cout << "No" << endl;
					}
				}
			}
			else
			{
				cout << "Couldn't open" << endl;
			}

			cout << "Test 7 Complete" << endl;

			madeFile.close();
			originalFile.close();
		}

		else if (option == 8)
		{
			ifstream madeFile("output/part8_r.tga", ios::in | ios::binary);
			ifstream originalFile("examples/EXAMPLE_part8_r.tga", ios::in | ios::binary);

			if (madeFile.is_open() && originalFile.is_open())
			{
				while (true)
				{
					madeFile.read(&byte1, sizeof(byte1));
					originalFile.read(&byte2, sizeof(byte2));

					if (!madeFile || !originalFile)
						break;

					if (byte1 != byte2)
					{
						cout << "No" << endl;
					}
				}
			}
			else
			{
				cout << "Couldn't open" << endl;
			}

			madeFile.close();
			originalFile.close();

			ifstream madeFile2("output/part8_b.tga", ios::in | ios::binary);
			ifstream originalFile2("examples/EXAMPLE_part8_b.tga", ios::in | ios::binary);

			if (madeFile2.is_open() && originalFile2.is_open())
			{
				while (true)
				{
					madeFile2.read(&byte1, sizeof(byte1));
					originalFile2.read(&byte2, sizeof(byte2));

					if (!madeFile2 || !originalFile2)
						break;

					if (byte1 != byte2)
					{
						cout << "No" << endl;
					}
				}
			}
			else
			{
				cout << "Couldn't open" << endl;
			}

			madeFile2.close();
			originalFile2.close();

			ifstream madeFile3("output/part8_g.tga", ios::in | ios::binary);
			ifstream originalFile3("examples/EXAMPLE_part8_g.tga", ios::in | ios::binary);

			if (madeFile3.is_open() && originalFile3.is_open())
			{
				while (true)
				{
					madeFile3.read(&byte1, sizeof(byte1));
					originalFile3.read(&byte2, sizeof(byte2));

					if (!madeFile3 || !originalFile3)
						break;

					if (byte1 != byte2)
					{
						cout << "No" << endl;
					}
				}
			}
			else
			{
				cout << "Couldn't open" << endl;
			}

			cout << "Test 8 Complete" << endl;

			madeFile3.close();
			originalFile3.close();
		}

		else if (option == 9)
		{
			ifstream madeFile("output/part9.tga", ios::in | ios::binary);
			ifstream originalFile("examples/EXAMPLE_part9.tga", ios::in | ios::binary);

			if (madeFile.is_open() && originalFile.is_open())
			{
				while (true)
				{
					madeFile.read(&byte1, sizeof(byte1));
					originalFile.read(&byte2, sizeof(byte2));

					if (!madeFile || !originalFile)
						break;

					if (byte1 != byte2)
					{
						cout << "No" << endl;
					}
				}
			}
			else
			{
				cout << "Couldn't open" << endl;
			}

			cout << "Test 9 Complete" << endl;

			madeFile.close();
			originalFile.close();
		}

		else if (option == 10)
		{
			ifstream madeFile("output/part10.tga", ios::in | ios::binary);
			ifstream originalFile("examples/EXAMPLE_part10.tga", ios::in | ios::binary);

			if (madeFile.is_open() && originalFile.is_open())
			{
				while (true)
				{
					madeFile.read(&byte1, sizeof(byte1));
					originalFile.read(&byte2, sizeof(byte2));

					if (!madeFile || !originalFile)
						break;

					if (byte1 != byte2)
					{
						cout << "No" << endl;
					}
				}
			}
			else
			{
				cout << "Couldn't open" << endl;
			}

			cout << "Test 10 Complete" << endl;

			madeFile.close();
			originalFile.close();
		}
		option++;
	} while (option >= 1 && option <= 10);

	return 0;
}

void tasks(int option)
{
	vector<string> files = { "layer1.tga" /*[0]*/, "layer2.tga" /*[1]*/, "layer_blue.tga" /*[2]*/, "layer_green.tga" /*[3]*/, "layer_red.tga" /*[4]*/,
		"pattern1.tga" /*[5]*/, "pattern2.tga" /*[6]*/,
		"text.tga" /*[7]*/, "text2.tga" /*[8]*/,
		"car.tga" /*[9]*/, "circles.tga", /*[10]*/ };
	Image image1, image2, image3, newImage;
	string FilePath = "input/";


	if (option == 1)
	{
		image1.loadHeader(files[0].insert(0, FilePath), image1);
		image2.loadHeader(files[5].insert(0, FilePath), image2);

		newImage.tasks(image1, image2, image3, newImage, option, "");

		cout << "Task 1 Complete" << endl;

	}

	else if (option == 2)
	{
		image1.loadHeader(files[1].insert(0, FilePath), image1);
		image2.loadHeader(files[9].insert(0, FilePath), image2);

		newImage.tasks(image1, image2, image3, newImage, option, "");

		cout << "Task 2 Complete" << endl;

	}

	else if (option == 3)
	{

		image1.loadHeader(files[0].insert(0, FilePath), image1);
		image2.loadHeader(files[6].insert(0, FilePath), image2);

		newImage.tasks(image1, image2, image3, newImage, option, "");

		cout << "Task 3 Complete" << endl;

	}

	else if (option == 4)
	{
		image1.loadHeader(files[1].insert(0, FilePath), image1);
		image2.loadHeader(files[10].insert(0, FilePath), image2);

		newImage.tasks(image1, image2, image3, newImage, option, "");

		cout << "Task 4 Complete" << endl;

	}

	else if (option == 5)
	{
		image1.loadHeader(files[0].insert(0, FilePath), image1);
		image2.loadHeader(files[5].insert(0, FilePath), image2);

		newImage.tasks(image1, image2, image3, newImage, option, "");

		cout << "Task 5 Complete" << endl;

	}

	else if (option == 6)
	{
		image1.loadHeader(files[9].insert(0, FilePath), image1);

		newImage.tasks(image1, image1, image1, newImage, option, "");

		cout << "Task 6 Complete" << endl;


	}

	else if (option == 7)
	{
		image1.loadHeader(files[9].insert(0, FilePath), image1);

		newImage.tasks(image1, image1, image1, newImage, option, "");

		cout << "Task 7 Complete" << endl;

	}

	else if (option == 8)
	{
		image1.loadHeader(files[9].insert(0, FilePath), image1);

		newImage.tasks(image1, image1, image1, newImage, option, "_r");
		newImage.tasks(image1, image1, image1, newImage, option, "_g");
		newImage.tasks(image1, image1, image1, newImage, option, "_b");
		cout << "Task 8 Complete" << endl;

	}

	else if (option == 9)
	{
		image1.loadHeader(files[4].insert(0, FilePath), image1);
		image2.loadHeader(files[3].insert(0, FilePath), image2);
		image3.loadHeader(files[2].insert(0, FilePath), image3);

		newImage.tasks(image1, image2, image3, newImage, option, "");
		cout << "Task 9 Complete" << endl;

	}

	else if (option == 10)
	{
		image1.loadHeader(files[8].insert(0, FilePath), image1);
		newImage.tasks(image1, image1, image1, newImage, option, "");
		cout << "Task 10 Complete" << endl;

	}
}