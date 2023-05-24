#include<sfml/Graphics.hpp>
#include"iostream"
#include "ctime"

using namespace std;
using namespace sf;

const int height = 6;
const int width = 7;
int checkerboard[height][width];
int colMax[width];
int counter, p1_Counter, p2_Counter;
bool p2_side = true;



// p1 Red,p2 Blue/green


//change the lib to 64.

//assets

Texture BoardTexture;
Texture p1_checker;
Texture	p2_checker;

Sprite p1[21]; //red
Sprite p2[21]; //green/blue

//void reset();
void set();
void draw();
void p1_play(Vector2i a);
void p2_play(Vector2i a);
bool continueGame();
bool p1_turn = true;

//Renders a Window 
int main()
{
	//check directory
	/*system("dir");*/
		//assets not loading  this checks the directory of the project.

	RenderWindow window(sf::VideoMode(770, 660), "Connect 4");
	set();
	while (window.isOpen())
	{
		Event event;
		Vector2i pos;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.key.code == Mouse::Left)
				{
					if (continueGame())
					{
						pos = Mouse::getPosition(window);
						pos.x = ceil(pos.x / 100) + 1;
						pos.y = ceil(pos.y / 100) + 1;

						cout << "X: " << pos.x << ", Y: " << pos.y << "\n";
						if (p2_side)
						{
							p2_play(pos);
							p2_side = false;

						}
						else
						{
							p1_play(pos);
							p2_side = true;
						}
					}
				}
				break;
			default:
				break;
			}
			//Restart Game
			/*if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Space)
			{

				counter++;

			}				}
			return 0;*/
		}

		window.clear(sf::Color::White);

		// Draw Game board
		sf::Sprite game_board(BoardTexture);
		window.draw(game_board);

		// Draw Pieces
		for (int i = 0; i < 21; i++)
		{
			window.draw(p1[i]);
			window.draw(p2[i]);
		}

		// Display window
		window.display();

		// Check game status
		if (!continueGame())
		{
			break;
		}
	}
	std::getchar(); //typesomething in the cli window to exit the game
	return 0;
}

void set()
{

	BoardTexture.loadFromFile("BoardTextureBlue.png");

	p1_checker.loadFromFile("Red.png");
	p2_checker.loadFromFile("blue.png");


	if (!BoardTexture.loadFromFile("BoardTexture.png")) {
		std::cout << "Failed to load BoardTexture.png" << std::endl;
	}

	if (!p2_checker.loadFromFile("blue.png")) {
		std::cout << "Failed to load blue.png" << std::endl;
	}

	if (!p1_checker.loadFromFile("Red.png")) {
		std::cout << "Failed to load Red.png" << std::endl;
	}

	for (int i = 0; i < 21; i++)
	{
		p2[i].setTexture(p2_checker);
		p1[i].setTexture(p1_checker);
	}

	p2_side = true;
	counter = 0;
	p1_Counter = 0;
	p2_Counter = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			checkerboard[i][j] = 0;
		}
	}
}

//THIS FUNCTION IS CURRENTLY EMPTY, Add Player messages
void draw() {
	system("CLS");
	if (p1_turn)
	{
		if (p2_side) {
			cout << "Blue's Turn\n";
		}
		else
		{
			cout << "Red's Turn\n";
		}
	}
	else
	{
		p1_turn = true;
	}

}




//game_state(Draw,Wins)
bool continueGame()
{
	if (counter == 42) {
		return false;
	}

	for (int i = 0; i < height; ++i)//check_row
	{
		for (int j = 0; j <= width - 4; ++j)
		{
			if (checkerboard[i][j] == 1 && checkerboard[i][j + 1] == 1 && checkerboard[i][j + 2] == 1 && checkerboard[i][j] == 1)
			{
				std::cout << "Blue Wins, Congratulations \n";
				return false;
			}
			if (checkerboard[i][j] == 2 && checkerboard[i][j + 1] == 2 && checkerboard[i][j + 2] == 2 && checkerboard[i][j] == 2)
			{
				std::cout << "Red Wins, Congratulations \n";
				return false;
			}

		}
	}
	//checking cols

	for (int i = 0; i <= height - 4; ++i)//check_row
	{
		for (int j = 0; j < width; ++j)
		{
			if (checkerboard[i][j] == 1 && checkerboard[i + 1][j] == 1 && checkerboard[i + 2][j] == 1 && checkerboard[i + 3][j] == 1)
			{
				std::cout << "Blue Wins, Congratulations \n";
				return false;
			}
			if (checkerboard[i][j] == 2 && checkerboard[i + 1][j] == 2 && checkerboard[i + 2][j] == 2 && checkerboard[i + 3][j] == 2)
			{
				std::cout << "Red Wins, Congratulations \n";
				return false;
			}

		}
	}
	//diagonals
	for (int i = 0; i <= height - 4; ++i)//check_row
	{
		for (int j = 0; j <= width - 4; ++j)
		{
			if (checkerboard[i][j] == 1 && checkerboard[i + 1][j + 1] == 1 && checkerboard[i + 2][j + 2] == 1 && checkerboard[i + 3][j + 3] == 1)
			{
				std::cout << "Blue Wins, Congratulations \n";
				return false;
			}
			if (checkerboard[i][j] == 2 && checkerboard[i + 1][j + 1] == 2 && checkerboard[i + 2][j + 2] == 2 && checkerboard[i + 3][j + 3] == 2)
			{
				std::cout << "Red Wins, Congratulations \n";
				return false;
			}
		}

	}
	for (int i = 0; i <= height - 4; ++i)//check_row
	{
		for (int j = 0; j <= width - 4; ++j)
		{
			if (checkerboard[i][j] == 1 && checkerboard[i + 1][j + 1] == 1 && checkerboard[i + 2][j + 2] == 1 && checkerboard[i + 3][j + 3] == 1)
			{
				std::cout << "Blue Wins, Congratulations \n";
				return false;
			}
			if (checkerboard[i][j] == 2 && checkerboard[i + 1][j + 1] == 2 && checkerboard[i + 2][j + 2] == 2 && checkerboard[i + 3][j + 3] == 2)
			{
				std::cout << "Red Wins, Congratulations \n";
				return false;

			}
		}
	}
	return true;
}

void p2_play(Vector2i a)
{
	int line = a.x;
	colMax[line - 1]++;
	if (colMax[line - 1] < height)
	{
		for (int i = 5; i >= 0; i--) {
			if (checkerboard[i][line - 1] == 0) {
				checkerboard[i][line - 1] = 1;
				p2[p2_Counter].setPosition(static_cast<float>((line - 1) * 110), static_cast<float>(i * 110)); // Fix this line
				p2_Counter++;
				break;
			}
		}
	}
	else
		colMax[line - 1]--;
}

void p1_play(Vector2i a) {
	int line = a.x;
	colMax[line - 1]++;
	if (colMax[line - 1] < height)
	{
		for (int i = 5; i >= 0; i--) {
			if (checkerboard[i][line - 1] == 0) {
				checkerboard[i][line - 1] = 2;
				p1[p1_Counter].setPosition(static_cast<float>((line - 1) * 110), static_cast<float>(i * 110)); // Fix this line
				p1_Counter++;
				break;
			}
		}
	}
	else
		colMax[line - 1]--;
}

//game AI

//int AIman()
//{
//	float chance[2] = { 999999,0 };
//	for (int col = 1; col <= 7; col++)
//	{
//		Playout = 0;
//
//	}
//}
//
////minimax_algorithm
//	int minmax() 
//	{
//			
//	}
//
//	
//}
//bool continueGame()
//{
//	return false;
//}


