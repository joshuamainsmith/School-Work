//#include <time.h>
//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "Object.h"
//#include "Minesweeper.h"
using namespace sf;
using namespace std;


int main()
{
	srand(time(0));
	int pixLength = 32;
	int w = 25, h = 16;
	int countMines = 50, countFlags = 0, clockCount;
	char chDebug;
	bool keysPressed[sf::Keyboard::KeyCount];
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
		keysPressed[i] = false; // No keys pressed
	int grid[27][18];
	bool bgrid[27][18], bflag[27][18], bmines[27][18], debugMines = false, gameLost = false, gameWon = false;
	bool t1 = false, t2 = false, t3 = false;
	bool allChecked = false, needsChecked[27][18], alreadyChecked[27][18];
	vector<int> vecCheck;
	ifstream fDebug;
	

	/*===== Setting Grid Type Items to False =====*/
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			bgrid[i][j] = false;
			bflag[i][j] = false;
			bmines[i][j] = false;
			needsChecked[i][j] = false;
			alreadyChecked[i][j] = false;
		}
	}

	/*===== Generating 50 Mines Randomly =====*/
	for (int i = 0; i < countMines; i++)
	{
		int randx = rand() % 25;
		int randy = rand() % 16;
		if (bmines[randx][randy] == false)
			bmines[randx][randy] = true;
		else
			i--;
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	Object ship("images/ship.png");
	sf::Vector2u windowSize = window.getSize();
	ship.SetPosition(windowSize.x / 2, windowSize.y - 100);
	Object tile_hidden("images/tile_hidden.png"), tile_revealed("images/tile_revealed.png");
	Object flag("images/flag.png"), mines("images/mine.png");
	Object debug("images/debug.png"), test_1("images/test_1.png"), test_2("images/test_2.png"), test_3("images/Test_3.png");
	Object face_happy("images/face_happy.png"), face_win("images/face_win.png"), face_lose("images/face_lose.png");
	Object one("images/number_1.png"), two("images/number_2.png"), three("images/number_3.png"), four("images/number_4.png"), 
		five("images/number_5.png"), six("images/number_6.png"), seven("images/number_7.png"), eight("images/number_8.png");
	
	
	Texture clock;
	clock.loadFromFile("images/digits.png");	
	Sprite sClock(clock);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonReleased:
				cout << "Mouse Pressed" << endl;
				if (event.key.code == sf::Mouse::Right)
				{
					cout << "Right Mouse Clicked" << endl;
					sf::Vector2i pos = sf::Mouse::getPosition(window);
					int x = pos.x / pixLength;
					int y = pos.y / pixLength;
					if (bgrid[x][y] == false && !gameLost && !gameWon)
					{
						if (bflag[x][y] == false)
						{
							bflag[x][y] = true;
							countFlags++;
						}
						else
						{
							bflag[x][y] = false;
							countFlags--;
						}
					}
				}

				else if (event.key.code == sf::Mouse::Left)
				{
					cout << "Left Mouse Clicked" << endl;
					sf::Vector2i pos = sf::Mouse::getPosition(window);
					int x = pos.x / pixLength;
					int y = pos.y / pixLength;
					allChecked = false;

					//	Smiley/Sad Face
					if (pos.y > 512 && pos.y < 576)
					{
						if (pos.x > 368 && pos.x < 432)
						{
							window.close();
							main();
						}
					}

					//	Test 1
					if (pos.y > 512 && pos.y < 576)
					{
						if (pos.x > 560 && pos.x < 624)
						{
							for (int i = 0; i < w; i++)
							{
								for (int j = 0; j < h; j++)
								{
									needsChecked[i][j] = false;
									alreadyChecked[i][j] = false;
								}
							}
							fDebug.open("boards/testboard1.brd", fstream::in);
							int i = 0, j = 0;
							t1 = true;
							gameLost = false;
							while (fDebug >> noskipws >> chDebug)
							{
								if (chDebug == '1')
								{
									bmines[i][j] = true;
								}
								else
								{
									bmines[i][j] = false;
								}


								if (i == w)
								{
									j++;
									i = 0;
								}
								if (chDebug != '\n')
									i++;
							}

							for (int i = 0; i < w; i++)
							{
								for (int j = 0; j < h; j++)
								{
									bflag[i][j] = false;
									bgrid[i][j] = false;
								}
							}
						}
					}

					//	Test 2
					if (pos.y > 512 && pos.y < 576)
					{
						if (pos.x > 624 && pos.x < 688)
						{
							for (int i = 0; i < w; i++)
							{
								for (int j = 0; j < h; j++)
								{
									needsChecked[i][j] = false;
									alreadyChecked[i][j] = false;
								}
							}
							fDebug.open("boards/testboard2.brd");
							int i = 0, j = 0;
							gameLost = false;

							while (fDebug >> noskipws >> chDebug)
							{
								if (chDebug == '1')
								{
									bmines[i][j] = true;
								}
								else
								{
									bmines[i][j] = false;
								}


								if (i == w)
								{
									j++;
									i = 0;
								}
								if (chDebug != '\n')
									i++;
							}

							for (int i = 0; i < w; i++)
							{
								for (int j = 0; j < h; j++)
								{
									bgrid[i][j] = false;
									bflag[i][j] = false;
								}
							}
						}
					}

					//	Test 3
					if (pos.y > 512 && pos.y < 576)
					{
						if (pos.x > 688 && pos.x < 752)
						{
							for (int i = 0; i < w; i++)
							{
								for (int j = 0; j < h; j++)
								{
									needsChecked[i][j] = false;
									alreadyChecked[i][j] = false;
								}
							}
							fDebug.open("boards/testboard3.brd");
							int i = 0, j = 0;
							gameLost = false;

							while (fDebug >> noskipws >> chDebug)
							{
								if (chDebug == '1')
								{
									bmines[i][j] = true;
								}
								else
								{
									bmines[i][j] = false;
								}


								if (i == w)
								{
									j++;
									i = 0;
								}
								if (chDebug != '\n')
									i++;
							}

							for (int i = 0; i < w; i++)
							{
								for (int j = 0; j < h; j++)
								{
									bgrid[i][j] = false;
									bflag[i][j] = false;
								}
							}
						}
					}

					if (!gameLost && !gameWon)
					{
						bgrid[x][y] = true;

						//	Debug
						if (pos.y > 512 && pos.y < 576)
						{
							if (pos.x > 496 && pos.x < 560)
							{
								if (debugMines == false)
									debugMines = true;
								else
									debugMines = false;
							}
						}

						if (fDebug.is_open())
						{
							fDebug.close();
						}
					}

					cout << "Pos X: " << pos.x << endl;
					cout << "Pos Y: " << pos.y << endl;
					cout << "X: " << x << endl;
					cout << "Y: " << y << endl;
				}
				break;

			case sf::Event::MouseButtonPressed:
				
				break;
			}


			
		}
		window.clear();	

		for (int i = 0; i < pixLength * w; i += pixLength)
		{			
			for (int j = 0; j < pixLength * h; j += pixLength)
			{
				if (bgrid[i / pixLength][j / pixLength] == false)
				{
					/*===== Hidden =====*/
					tile_hidden.SetPosition(i, j);
					window.draw(tile_hidden.GetSprite());

					if (debugMines || gameLost || gameWon)
					{
						/*===== Mines =====*/ //	For Debugging
						if (bmines[i / pixLength][j / pixLength] == true)
						{
							mines.SetPosition(i, j);
							window.draw(mines.GetSprite());
						}
					}

					/*===== Flags =====*/
					if (bflag[i / pixLength][j / pixLength] == true)
					{
						flag.SetPosition(i, j);
						window.draw(flag.GetSprite());
					}
				}

				/*===== Revealed =====*/
				else if (bgrid[i / pixLength][j / pixLength] == true)
				{
					if (bflag[i / pixLength][j / pixLength] == false)
					{
						tile_revealed.SetPosition(i, j);
						window.draw(tile_revealed.GetSprite());


						/*===== Mines =====*/
						if (bmines[i / pixLength][j / pixLength] == true)
						{
							mines.SetPosition(i, j);
							window.draw(mines.GetSprite());
							gameLost = true;
						}
						else
						{
							/*=== Multiple Tiles Revealed ===*/
							int tmpX = i / pixLength, tmpY = j / pixLength;							

							needsChecked[tmpX][tmpY + 1] = true, needsChecked[tmpX + 1][tmpY + 1] = true, needsChecked[tmpX + 1][tmpY] = true, needsChecked[tmpX + 1][tmpY - 1] = true,
								needsChecked[tmpX][tmpY - 1] = true, needsChecked[tmpX - 1][tmpY - 1] = true, needsChecked[tmpX - 1][tmpY] = true, needsChecked[tmpX - 1][tmpY + 1] = true;

							while (!allChecked)
							{
								allChecked = true;
								
								for (int r = 0; r < 25; r++)
								{
									for (int s = 0; s < 16; s++)
									{
										if ((needsChecked[r][s] == true && bmines[r][s] == false && alreadyChecked[r][s] == false) && 
											((bmines[r + 1][s + 1] == false && bmines[r + 1][s - 1] == false) || 
											(bmines[r - 1][s - 1] == false && bmines[r - 1][s + 1] == false) ||
											(bmines[r + 1][s + 1] == false && bmines[r - 1][s + 1] == false) ||
											bmines[r + 1][s - 1] == false && bmines[r - 1][s - 1] == false))
										{											
											bgrid[r][s] = true;
											allChecked = false;
											needsChecked[r][s] = false;
											alreadyChecked[r][s] = true;
											
											/*if ((r == 0 && s == 0) || (r == 0 && s == 15) || (r == 24 && s == 15) || (r == 24 && s == 0))
											{
												if (bmines[r][s] != true)
												{
													if((r == 0 && s == 0 && (bgrid[r + 1][s] == true || bgrid[r + 1][s - 1] == true || bgrid[r][s - 1] == true)))
														bgrid[r][s] = true;
												}
											}*/

											if ((r == 0 || r == 24) && (s > 0 || s < 15))
											{
												//needsChecked[r][s + 1] = true, needsChecked[r][s - 1] = true;
												vecCheck.push_back(r);
												vecCheck.push_back(s + 1);
												vecCheck.push_back(r);												
												vecCheck.push_back(s - 1);
												

												if (r == 0)
												{
													//needsChecked[r + 1][s] = true;
													vecCheck.push_back(r + 1);
													vecCheck.push_back(s);													
												}
												else
												{
													//needsChecked[r - 1][s] = true;
													vecCheck.push_back(r - 1);
													vecCheck.push_back(s);													
												}													
											}

											else if ((r > 0 || r < 24) && (s == 0 || s == 15))
											{
												//needsChecked[r + 1][s] = true, needsChecked[r - 1][s] = true;
												vecCheck.push_back(r + 1);
												vecCheck.push_back(s);
												vecCheck.push_back(r - 1);
												vecCheck.push_back(s);												

												if (s == 0)
												{
													//needsChecked[r][s - 1] = true;
													vecCheck.push_back(r);
													vecCheck.push_back(s + 1);	
												}
												else
												{
													//needsChecked[r][s + 1] = true;
													vecCheck.push_back(r);
													vecCheck.push_back(s - 1);	
													
												}
											}
											else if ((r == 0 || r == 24) && (s == 0 || s == 15))
											{													
												if (r == 0 && s == 0)
												{
													//needsChecked[r + 1][s] = true, needsChecked[r + 1][s - 1] = true, needsChecked[r][s - 1] = true;
													vecCheck.push_back(r + 1);
													vecCheck.push_back(s);
												//	vecCheck.push_back(r + 1);
													//vecCheck.push_back(s - 1);
													vecCheck.push_back(r);
													vecCheck.push_back(s + 1);													
												}
												else if (r == 0 && s != 0)
												{
													//needsChecked[r + 1][s] = true, needsChecked[r + 1][s + 1] = true, needsChecked[r][s + 1] = true;
													vecCheck.push_back(r + 1);
													vecCheck.push_back(s);
													//vecCheck.push_back(r + 1);
													//vecCheck.push_back(s + 1);
													vecCheck.push_back(r);
													vecCheck.push_back(s - 1);													
												}
												else if (r != 0 && s == 0)
												{
													//needsChecked[r - 1][s] = true, needsChecked[r - 1][s - 1] = true, needsChecked[r][s - 1] = true;
													vecCheck.push_back(r - 1);
													vecCheck.push_back(s);
													//vecCheck.push_back(r - 1);
													//vecCheck.push_back(s - 1);
													vecCheck.push_back(r);
													vecCheck.push_back(s + 1);													
												}
												else // r != 0 && s != 0
												{
													//needsChecked[r - 1][s] = true, needsChecked[r - 1][s + 1] = true, needsChecked[r][s + 1] = true;
													vecCheck.push_back(r - 1);
													vecCheck.push_back(s);
													//vecCheck.push_back(r - 1);
													//vecCheck.push_back(s + 1);
													vecCheck.push_back(r);
													vecCheck.push_back(s - 1);													
												}
											}
											
											else
											{											
												/*needsChecked[r][s + 1] = true, needsChecked[r + 1][s + 1] = true, needsChecked[r + 1][s] = true, needsChecked[r + 1][s - 1] = true,
													needsChecked[r][s - 1] = true, needsChecked[r - 1][s - 1] = true, needsChecked[r - 1][s] = true, needsChecked[r - 1][s + 1] = true;*/

												vecCheck.push_back(r);
												vecCheck.push_back(s + 1);
												//vecCheck.push_back(r + 1);
												//vecCheck.push_back(s + 1);
												vecCheck.push_back(r + 1);
												vecCheck.push_back(s);
												//vecCheck.push_back(r + 1);
												//vecCheck.push_back(s - 1);
												vecCheck.push_back(r);
												vecCheck.push_back(s - 1);
												//vecCheck.push_back(r - 1);
												//vecCheck.push_back(s - 1);
												vecCheck.push_back(r - 1);
												vecCheck.push_back(s);
												//vecCheck.push_back(r - 1);
												//vecCheck.push_back(s + 1);

												
											}
										}											
									}
								}

								int iter = 0;
								while (iter < vecCheck.size())
								{
									needsChecked[vecCheck[iter]][vecCheck[iter + 1]] = true;
									iter+=2;  
								}								
							}

							vecCheck.clear();
							allChecked = false;

							

							int count = 0;
							if (t1 == true && (i / pixLength) != 0 && (j / pixLength) != 0)
							{
								bgrid[0][15] = true;								
								t1 = false;
							}
							if (bmines[(i / pixLength) + 1][j / pixLength] == true)
								count++;
							if (bmines[(i / pixLength) - 1][j / pixLength] == true)
								count++;
							if (bmines[i / pixLength][(j / pixLength) + 1] == true)
								count++;
							if (bmines[i / pixLength][(j / pixLength) - 1] == true)
								count++;
							if (bmines[(i / pixLength) + 1][(j / pixLength) + 1] == true)
								count++;
							if (bmines[(i / pixLength) - 1][(j / pixLength) + 1] == true)
								count++;
							if (bmines[(i / pixLength) + 1][(j / pixLength) - 1] == true)
								count++;
							if (bmines[(i / pixLength) - 1][(j / pixLength) - 1] == true)
								count++;

							if (count > 0)
							{
								if (count == 1)
								{
									one.SetPosition(i, j);
									window.draw(one.GetSprite());
								}
								else if (count == 2)
								{
									two.SetPosition(i, j);
									window.draw(two.GetSprite());
								}
								else if (count == 3)
								{
									three.SetPosition(i, j);
									window.draw(three.GetSprite());
								}
								else if (count == 4)
								{
									four.SetPosition(i, j);
									window.draw(four.GetSprite());
								}
								else if (count == 5)
								{
									five.SetPosition(i, j);
									window.draw(five.GetSprite());
								}
								else if (count == 6)
								{
									six.SetPosition(i, j);
									window.draw(six.GetSprite());
								}
								else if (count == 7)
								{
									seven.SetPosition(i, j);
									window.draw(seven.GetSprite());
								}
								else if (count == 8)
								{
									eight.SetPosition(i, j);
									window.draw(eight.GetSprite());
								}
							}
						}

					}

					else
					{
						bgrid[i / pixLength][j / pixLength] = false;
					}
				}
			}
		}		

		debug.SetPosition((w * pixLength + 192) / 2, (h * pixLength));
		window.draw(debug.GetSprite());

		test_1.SetPosition((w * pixLength + 320) / 2, (h * pixLength));
		window.draw(test_1.GetSprite());

		test_2.SetPosition((w * pixLength + 448) / 2, (h * pixLength));
		window.draw(test_2.GetSprite());

		test_3.SetPosition((w * pixLength + 576) / 2, (h * pixLength));
		window.draw(test_3.GetSprite());

		gameWon = true;
		// Comparing unrevealed tiles with placement of mines
		for (int i = 0; i < pixLength * w; i += pixLength)
		{
			for (int j = 0; j < pixLength * h; j += pixLength)
			{
				if (bmines[i / pixLength][j / pixLength] == bgrid[i / pixLength][j / pixLength])
				{
					gameWon = false;
				}								
			}
		}

		if (gameLost == true)
		{
			face_lose.SetPosition((w * pixLength - 64) / 2, (h * pixLength));
			window.draw(face_lose.GetSprite());
		}

		else if (gameWon == true)
		{
			face_win.SetPosition((w * pixLength - 64) / 2, (h * pixLength));
			window.draw(face_win.GetSprite());
		}

		else
		{
			face_happy.SetPosition((w * pixLength - 64) / 2, (h * pixLength));
			window.draw(face_happy.GetSprite());
		}
		
		//window.draw(ship.GetSprite());
		/*for (unsigned int i = 0; i < projectiles.size(); i++)
			window.draw(projectiles[i]->GetSprite());*/

		clockCount = countMines - countFlags;

		if (clockCount < 0)
		{
			sClock.setTextureRect(IntRect(21 * 10, 0, 21, 32));
			sClock.setPosition(0, h * pixLength);
			window.draw(sClock);

			clockCount *= -1;

		}

		else
		{
			sClock.setTextureRect(IntRect(0, 0, 21, 32));
			sClock.setPosition(0, h * pixLength);
			window.draw(sClock);
		}

		sClock.setTextureRect(IntRect(21 * (clockCount % 10), 0, 21, 32));
		sClock.setPosition(42, h * pixLength);
		window.draw(sClock);

		clockCount /= 10;

		sClock.setTextureRect(IntRect(21 * (clockCount % 10), 0, 21, 32));
		sClock.setPosition(21, h * pixLength);
		window.draw(sClock);
		

		window.display();
	}

	system("pause");
	return 0;
}
