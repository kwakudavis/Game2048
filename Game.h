#pragma once
#include "Cell.h"
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>




class Game
{

private:
	int m_score;
	Cell m_cells[4][4];
	int getCellNumber(int row, int column);

public:

	enum class mineSwitch
	{
		ON,
		OFF

	};


	
	Game();
	void displayCells();
    void randomTileGenerator(mineSwitch control = Game::mineSwitch::OFF);
	
	bool isWon();

	bool isLost();

	bool freeCell();

	void saveGame();
	void addToHallOfFame();
	
	void displayHallOfFame();



	void moveRight();

	void moveLeft();

	void moveDown();

	void moveUp();


	void LoadGame();

};

