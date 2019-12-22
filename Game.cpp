#include "Game.h"
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <queue>
#include "player.h"

/**
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
**/




Game::Game()
{
	 
	 m_score = 0;




	//creation of first two initialisation tiles which cannot be mine tiles
	randomTileGenerator(Game::mineSwitch::OFF);
	randomTileGenerator(Game::mineSwitch::OFF);





}




void Game::displayCells() {
	int i;//row
	int j;//column
	

	std::cout << "+----+----+----+----+";
	std::cout << std::endl;
	int value;
	for (i = 0; i < 4; ++i) {//loop through rows
		
		std::cout << "|";
		for (j = 0; j < 4; ++j) {//loop through columns

			if (m_cells[i][j].m_tile == nullptr) {
				
				 value = -1;
			}
			else{
				
				value = m_cells[i][j].m_tile->value;
		}



			if (value > 0 && value < 10) {//one digit value
				std::cout << "   ";
				std::cout<<value;
			}
			else if (value >= 10 && value < 100) {
				std::cout << "  ";
				std::cout << value;
			}
			else if (value >= 100 && value < 1000) {
				std::cout << " ";
				std::cout << value;
			}
			else if (value >= 1000) {
				std::cout << value;//four digit value

			}
			else if (value == 0) {//mine display
				std::cout << "   *";

			}
			else{
				std::cout << "    ";
			
		}
		
			std::cout << "|";
		}
		
		std::cout << std::endl;
		std::cout << "+----+----+----+----+";
		std::cout << std::endl;
	}

	std::cout << "Score:";
	std::cout << m_score;
	std::cout << std::endl;

}



void Game::randomTileGenerator(mineSwitch control)
{
	

	int randomrow;
	int randomcolumn;
	Tile* randomtile = new Tile; //create an empty tile

	//generate two pair of integers whose position in the cells array is a null pointer
	do {

		//generate random numbers from 0 to  3
		randomrow = rand() % 4;
		randomcolumn = rand() % 4;
		

	} while (m_cells[randomrow][randomcolumn].m_tile != nullptr);

	
	//Generate a random value between 0 and 100

	//unsigned int currentTime = static_cast<unsigned int>(3223);
	int randomValue = rand()% 100;

	//std::cout << randomValue << std::endl;

//	std::cout << randomrow << "and";
	//std::cout << randomcolumn << std::endl;


	//check if  mine generation is enabled
	if (control == Game::mineSwitch::ON)
	{
		//create a 2 4 or mine tile using probability
		if (randomValue <= 40) {

			randomtile->value = 2;

		}
		else if (randomValue > 40 && randomValue <= 60){
			randomtile->value = 0;
		}
		else if(randomValue >60 && randomValue <= 100) {
			randomtile->value = 4;
		}

		
		
	}
	else {//if mine tile generation is deactivated

		if (randomValue <= 50) {

			randomtile->value = 2;

		}
		else if (randomValue > 50) {

			randomtile->value = 4;
		}


		
	}

	//instert tile into empty cell

	m_cells[randomrow][randomcolumn].insert(randomtile);


}

bool Game::isWon()
{
	int row;
	int column;
	bool winningstatus=false;

	for (row = 0; row < 4; ++row)
	{

		for (column = 0; column < 4; ++column)
		{
			if (m_cells[row][column].m_tile == nullptr) {
				continue;
			}
			if (m_cells[row][column].m_tile->value == 2048) {
				winningstatus = true;
			}
		
		
		}

	}
		
	return winningstatus;

}



bool Game::isLost()
{
   bool losingstatus = false;
	if (isWon() == false && freeCell() == false) {
		losingstatus = true;
	}


	return losingstatus;
}



bool Game::freeCell()
{
	int row;
	int column;
	bool state = false;


	for (row = 0; row < 4; ++row)
	{

		for (column = 0; column < 4; ++column)
		{
			if (m_cells[row][column].m_tile == nullptr) {
				state = true;
			}
		}

	}



	return state;

}

void Game::saveGame()
{
	//request saved game namme
	std::string name;
	std::cout << "Enter a name to save game file" << std::endl;
	std::cin >> name;


	//create output file to stream using name given

//	std::filebuf fb;
//	fb.open(name, std::ios::out);
	//std::ostream os(&fb);

	std::ofstream os;
	os.open(name+ ".txt");


	//store the score m_score
	std::string scorestringbuffer;
	scorestringbuffer = std::to_string(m_score);

	os << "Score:";
	os<< scorestringbuffer;
	os<<std::endl;



	//store tile values into file
			//loop through every row and column and on each loop store the value of the tile with the help of a function which stores cell number

	int row;
	int column;




	for (row = 0; row < 4; ++row)
	{

		for (column = 0; column < 4; ++column)
		{
			os << getCellNumber(row, column);
			os << ":";
			if (m_cells[row][column].m_tile == nullptr) {

				os << "NULL";
			}else if (m_cells[row][column].m_tile->value == 0) {
				os << "*";

			}
			else {
				os << m_cells[row][column].m_tile->value;
				
			}

			os << std::endl;
		}

	}

	//fb.close();
	os.close();
	//close file buffer

	std::cout << "Game saved successfully" << std::endl;
}

void Game::addToHallOfFame()
{
	std::string playername;
	//create empty HallofFame text file
		std::ofstream osd;

		osd.open("HallOfFame",std::ios::app);

		std::cout << "Enter your name:" << std::endl;
		std::cin >> playername;


		osd << playername + ":" + std::to_string(m_score)<<std::endl;
		osd.close();

}

void Game::displayHallOfFame()
{ ///sort the outputted display
	std::ifstream osd;
	osd.open("HallOfFame");
	std::string line;


//create a palyers priority queue

	std::priority_queue<player> players;
	
	int value;
	std::string values;
	std::string name;

	int i = 0;
    int j = 0;
	int pos;

	
	getline(osd, line);
	while (osd.eof() != true ) {
	

		

	    pos = line.find(":");
		name = line.substr(0, pos);
		values = line.substr(pos + 1);
		value = stoi(values);
		

		players.emplace(value ,name);

		getline(osd, line);
		++i;


	}


	std::cout << "***************Hall of Fame**************";
	std::cout << std::endl;
	for (j = 0; j < i; ++j) {
		std::cout << players.top().name;
		std::cout << ":";
		std::cout << players.top().score;
		std::cout << std::endl;
	   players.pop();
  }


}






void Game::LoadGame()
{
	int row;
	int column;
	std::string name;
	std::string line;

	std::cout << "Enter name of saved game to load " << std::endl;
	std::cin >> name;

	std::string filename = name+".txt";


	std::ifstream osd;
	osd.open(filename);

	if (osd.fail()) {
		std::cout << "failed loading game.\n";

	}
	else {

		//get first line which is the score

		getline(osd, line);

		int pos = line.find(":");
		std::string score = line.substr(pos + 1);
		m_score = stoi(score);


		//use for loop to store values into m_cells

		std::string tilevalue;



		//		for (row = 0; row< 4;++row) {//looping through rows

		//			for (column = 0; column < 4; ++column) {//looping through columns
		row = 0;
		column = 0;
		while (osd.eof() != true) {

			getline(osd, line);
			int pos = line.find(":");
			tilevalue = line.substr(pos + 1);

			std::string strCellNum = line.substr(0, pos);
			if (pos > 0) {
				int cellnum = stoi(strCellNum);
				row = cellnum / 4;
				column = cellnum % 4;
			}

			if (tilevalue.compare("NULL") == 0) {
				/**  std::cout << "NULL" << std::endl;
				  std::cout << row;
				  std::cout << "," ;
				  std::cout << column << std::endl;**/



				Tile* temptile = new Tile;
				temptile = nullptr;
				m_cells[row][column].m_tile = temptile;


			}
			else if (tilevalue.compare("*") == 0) {

				/** std::cout << "mine" <<std::endl;

				 std::cout << row ;
				 std::cout << "," ;
				 std::cout << column << std::endl;**/

				Tile* temptile1 = new Tile;
				temptile1->value = 0;
				m_cells[row][column].m_tile = temptile1;

			}
			else if (tilevalue.compare("") != 0 && tilevalue.compare("*") != 0 && tilevalue.compare("NULL") != 0 && tilevalue.compare(" ") != 0) {
				/** std::cout << tilevalue<< std::endl;
				 std::cout << row ;
				 std::cout << ",";
				 std::cout << column << std::endl;**/


				Tile* temptile2 = new Tile;
				temptile2->value = stoi(tilevalue);
				m_cells[row][column].m_tile = temptile2;

			}


		}



	}






	osd.close();

}



















int Game::getCellNumber(int row, int column)
{
	
	switch (row)
	{
	
	case 0:

			switch (column){
			
				case 0:
					return 0;
					break;

				case 1:
					return 1;
					break;
				
				case 2:
					return 2;
					break;

				case 3:
					return 3;
					break;

			default:
				break;
			}//end of row 1
		


	case 1:


		switch (column) {

		case 0:
			return 4;
			break;

		case 1:
			return 5;
			break;

		case 2:
			return 6;
			break;

		case 3:
			return 7;
			break;

		default:
			break;
		}//end of row 2
			
		
	case 2:
		switch (column) {

		case 0:
			return 8;
			break;

		case 1:
			return 9;
			break;

		case 2:
			return 10;
			break;

		case 3:
			return 11;
			break;

		default:
			break;
		}//end of row 3

		
	case 3:
			
		switch (column) {

		case 0:
			return 12;
			break;

		case 1:
			return 13;
			break;

		case 2:
			return 14;
			break;

		case 3:
			return 15;
			break;

		default:
			break;
		}//end of row 4

	}
	
	
	return 0;
}



void Game::moveRight() {


	

	int row;
	int column;
	int compcolumn;

	for (row = 0; row < 4 ; ++ row) {

		for (column = 3; column > 0; column--) { //select the last on the tile on the far right


			//std::cout <<row ;
			//std::cout << ",";
			//std::cout <<column;
			//std::cout << std::endl;


			for (compcolumn = column-1; compcolumn >= 0; --compcolumn) {//compare it against all the columns in front of it


				if (m_cells[row][column].m_tile != nullptr && m_cells[row][compcolumn].m_tile != nullptr) {//if two tiles are not null


					if (m_cells[row][column].m_tile->value != 0 && m_cells[row][compcolumn].m_tile->value != 0) {//if the two tiles are not mines


						if (m_cells[row][column].m_tile->equals(m_cells[row][compcolumn].m_tile) == true) { //if two tiles contain the same values

							m_cells[row][column].m_tile->add(m_cells[row][compcolumn].m_tile);
							m_cells[row][compcolumn].m_tile = nullptr;

							m_score += m_cells[row][column].m_tile->value;


							break;
						}
						else {    //if they dont contain the same value move to the next column
							break;
						}


					}
					else {//adding if one is a mine 


						if (m_cells[row][column].m_tile->value == 0 || m_cells[row][compcolumn].m_tile->value == 0) {

							m_score -= (m_cells[row][column].m_tile->value + m_cells[row][compcolumn].m_tile->value);

							m_cells[row][column].m_tile = nullptr;
							m_cells[row][compcolumn].m_tile = nullptr;
							
							

								++compcolumn;
							
							
						}

					}


				}
				else if (m_cells[row][compcolumn].m_tile != nullptr && m_cells[row][column].m_tile == nullptr) {//if the left tile is not a null

					m_cells[row][column].m_tile = m_cells[row][compcolumn].m_tile;
					m_cells[row][compcolumn].m_tile = nullptr;
				
				}

			}

		}
	}

}











void Game::moveLeft() {




	int row;
	int column;
	int compcolumn;

	for (row = 0; row < 4; ++row) {

		for (column = 0; column <4 ; column++) { //select the last on the tile on the far left 


			//std::cout << row;
			//std::cout << ",";
			//std::cout << column;
			//std::cout << std::endl;


			for (compcolumn = column + 1; compcolumn <= 3 ; ++compcolumn) {//compare it against all the columns in front of it


				if (m_cells[row][column].m_tile != nullptr && m_cells[row][compcolumn].m_tile != nullptr) {//if two tiles are not null


					if (m_cells[row][column].m_tile->value != 0 && m_cells[row][compcolumn].m_tile->value != 0) {//if the two tiles are note mines


						if (m_cells[row][column].m_tile->equals(m_cells[row][compcolumn].m_tile) == true) { //if two tiles contain the same values

							m_cells[row][column].m_tile->add(m_cells[row][compcolumn].m_tile);
							m_cells[row][compcolumn].m_tile = nullptr;


							m_score += m_cells[row][column].m_tile->value;

							break;
						}
						else {    //if they dont contain the same value move to the next column
							break;
						}


					}
					else {//adding if one is a mine 


						if (m_cells[row][column].m_tile->value == 0 || m_cells[row][compcolumn].m_tile->value == 0) {


							m_score -= (m_cells[row][column].m_tile->value + m_cells[row][compcolumn].m_tile->value);

							m_cells[row][column].m_tile = nullptr;
							m_cells[row][compcolumn].m_tile = nullptr;

							--compcolumn;


						}

					}


				}
				else if (m_cells[row][compcolumn].m_tile != nullptr && m_cells[row][column].m_tile == nullptr) {//if the left tile is not a null

					m_cells[row][column].m_tile = m_cells[row][compcolumn].m_tile;
					m_cells[row][compcolumn].m_tile = nullptr;

				}

			}

		}
	}

}























void Game::moveDown() {




	int row;
	int column;
	int comprow;

	for (column = 0; column < 4; column++) {

		for (row = 3; row >= 0; --row) { //select the last on the tile on the far left 


			//std::cout << row;
		//	std::cout << ",";
			//std::cout << column;
		//	std::cout << std::endl;


			for (comprow = row - 1; comprow >= 0; --comprow) {//compare it against all the columns in front of it


				if (m_cells[row][column].m_tile != nullptr && m_cells[comprow][column].m_tile != nullptr) {//if two tiles are not null


					if (m_cells[row][column].m_tile->value != 0 && m_cells[comprow][column].m_tile->value != 0) {//if the two tiles are note mines


						if (m_cells[row][column].m_tile->equals(m_cells[comprow][column].m_tile) == true) { //if two tiles contain the same values

							m_cells[row][column].m_tile->add(m_cells[comprow][column].m_tile);
							m_cells[comprow][column].m_tile = nullptr;

							m_score += m_cells[row][column].m_tile->value;

							break;
						}
						else {    //if they dont contain the same value move to the next column
							break;
						}


					}
					else {//adding if one is a mine 


						if (m_cells[row][column].m_tile->value == 0 || m_cells[comprow][column].m_tile->value == 0) {


							m_score -= (m_cells[row][column].m_tile->value + m_cells[comprow][column].m_tile->value);

							m_cells[row][column].m_tile = nullptr;
							m_cells[comprow][column].m_tile = nullptr;

							++comprow;


						}

					}


				}
				else if (m_cells[comprow][column].m_tile != nullptr && m_cells[row][column].m_tile == nullptr) {//if the left tile is not a null

					m_cells[row][column].m_tile = m_cells[comprow][column].m_tile;
					m_cells[comprow][column].m_tile = nullptr;

				}

			}

		}
	}

}


















void Game::moveUp() {




	int row;
	int column;
	int comprow;

	for (column = 0; column < 4; column++) {

		for (row = 0; row <4; ++row) { //select the last on the tile on the far left 


			//std::cout << row;
			//std::cout << ",";
			//std::cout << column;
			//std::cout << std::endl;


			for (comprow = row + 1; comprow <=3 ; ++comprow) {//compare it against all the columns in front of it


				if (m_cells[row][column].m_tile != nullptr && m_cells[comprow][column].m_tile != nullptr) {//if two tiles are not null


					if (m_cells[row][column].m_tile->value != 0 && m_cells[comprow][column].m_tile->value != 0) {//if the two tiles are note mines


						if (m_cells[row][column].m_tile->equals(m_cells[comprow][column].m_tile) == true) { //if two tiles contain the same values

							m_cells[row][column].m_tile->add(m_cells[comprow][column].m_tile);
							m_cells[comprow][column].m_tile = nullptr;

							m_score += m_cells[row][column].m_tile->value;

							break;
						}
						else {    //if they dont contain the same value move to the next column
							break;
						}


					}
					else {//adding if one is a mine 


						if (m_cells[row][column].m_tile->value == 0 || m_cells[comprow][column].m_tile->value == 0) {


							m_score -= (m_cells[row][column].m_tile->value + m_cells[comprow][column].m_tile->value);

							m_cells[row][column].m_tile = nullptr;
							m_cells[comprow][column].m_tile = nullptr;

							--comprow;


						}

					}


				}
				else if (m_cells[comprow][column].m_tile != nullptr && m_cells[row][column].m_tile == nullptr) {//if the left tile is not a null

					m_cells[row][column].m_tile = m_cells[comprow][column].m_tile;
					m_cells[comprow][column].m_tile = nullptr;

				}

			}

		}
	}

}