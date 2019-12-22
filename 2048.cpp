// 2048.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Game.h"
#include <iostream>
#include <thread>
#include <conio.h>




int main()
{
	srand((unsigned int)time(0));
    Game *newGame = new Game;


    
	

	do {

		system("CLS");
		newGame->displayCells();

		char choice;

		std::cout << "Enter a choice to continue:" << std::endl;
		std::cout << std::endl;
		std::cout << "W or w to slide up" << std::endl;
		std::cout << "X or x to slide down" << std::endl;
		std::cout << "A or a to slide left" << std::endl;
		std::cout << "D or d to slide right" << std::endl;
		std::cout << "------------------------------------" << std::endl;
		std::cout << std::endl;
		std::cout << "N or n start a new game" << std::endl;
		std::cout << "S or s to save game" << std::endl;
		std::cout << "L or l to load game" << std::endl;
		std::cout << "h or H to Dislay hall of fame" << std::endl;
		std::cout << "Q or q to quit" << std::endl;
		std::cin >> choice;


		switch (choice)
		{
		case 'w' :
			newGame->moveUp();
			newGame->randomTileGenerator(Game::mineSwitch::ON);
			break;

		case 'W':
			newGame->moveUp();
			newGame->randomTileGenerator(Game::mineSwitch::ON);
			break;
		case 'x':
			newGame->moveDown();
			newGame->randomTileGenerator(Game::mineSwitch::ON);
			break;

		case 'a':
			newGame->moveLeft();
			newGame->randomTileGenerator(Game::mineSwitch::ON);
			break;
		case 'A':
			newGame->moveLeft();
			newGame->randomTileGenerator(Game::mineSwitch::ON);
			break;
		case 'd':
			newGame->moveRight();
			newGame->randomTileGenerator(Game::mineSwitch::ON);
			break;
		case 'D':
			newGame->moveRight();
			newGame->randomTileGenerator(Game::mineSwitch::ON);
			break;
		case 'L':
			std::cout << "Are you sure you want to load game?: y/n" << std::endl;
			std::cin >> choice;
			if (choice == 'y' || choice == 'Y') {
				newGame->LoadGame();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				break;
			}
			else {


				break;
			}
		case 'l':
			std::cout << "Are you sure you want to load game?: y/n" << std::endl;
			std::cin >> choice;
			if (choice == 'y' || choice == 'Y') {
				newGame->LoadGame();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				break;
			}
			else {


				break;
			}
		
		case 's':
			newGame->saveGame();
			std::this_thread::sleep_for(std::chrono::seconds(2));
			break;
		case 'S':
			newGame->saveGame();
			std::this_thread::sleep_for(std::chrono::seconds(2));
			break;
		case 'q':

			std::cout << "Are you sure you want to quit game?: y/n" << std::endl;
			std::cin >> choice;
			if (choice == 'y') {
				exit(EXIT_SUCCESS);
			}
			else {


				break;
			}
			
			
		case 'Q':
			std::cout << "Are you sure you want to quit game?: y/n" << std::endl;
			std::cin >> choice;
			if (choice == 'y') {
				exit(EXIT_SUCCESS);
			}
			else {


				break;
			}
		
		case 'n':
			
			std::cout << "Are you sure you want to start a new game?: y/n" << std::endl;
			std::cin >> choice;
			if (choice == 'y' || choice == 'Y') {
				newGame = new Game;
				break;
			}
			else {


				break;
			}

		case 'N':
			std::cout << "Are you sure you want to start a new game?: y/n" << std::endl;
			std::cin >> choice;
			if (choice == 'y' || choice == 'Y') {
				newGame = new Game;
				break;
			}
			else {


				break;
			}
		case 'h':
			newGame->displayHallOfFame();
			std::this_thread::sleep_for(std::chrono::seconds(3));
			break;
		case 'H':
			newGame->displayHallOfFame();
			std::this_thread::sleep_for(std::chrono::seconds(3));
			break;

		default:
			std::cout << "Invalid move";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			break;
		}



	} while (newGame->isLost() != true && newGame->isWon() != true);
	


	












    if (newGame->isWon() == true) {
		system("CLS");
		newGame->displayCells();

        std::cout << "You won"<<std::endl;
		newGame->addToHallOfFame();
		newGame->displayHallOfFame();

    }
	else if (newGame->isLost() == true) {
		system("CLS");
		newGame->displayCells();

		std::cout << "You Lost" << std::endl;

		newGame->displayHallOfFame();
	}












}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
