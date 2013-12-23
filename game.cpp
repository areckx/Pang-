#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include <stdio.h> 
#include <iostream>



// Game::Start called publicly
// since it is available globally there should not be more than one
// as it can cause all kinds of bad things to happen
//
// this is why we check if _gameState is uninitialized
//
void Game::Start(void)
{
	if(_gameState != Uninitialized)
		return; // usually put up an error, but this program closes so redunant

// set the window resolution to 1024x768 at 32bpp color with the title Pang!
	_mainWindow.create(sf::VideoMode(1024,768,32), "Pang!");
	_gameState = Game::ShowingSplash; // switch states

	while(!IsExiting())
	{
		GameLoop(); // continues until Game::Exiting and will exit the program
	}
	_mainWindow.close();
}

bool Game::IsExiting()
{
	if(_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{ 
	switch(_gameState)
	{
	case Game::ShowingMenu:
		{ 
			ShowMenu();
			break;
		}
	case Game::ShowingSplash:
	{
		ShowSplashScreen();
		break;
	}

	case Game::Playing:
		{
			sf::Event currentEvent;		
			while(_mainWindow.pollEvent(currentEvent))
				{
				_mainWindow.clear(sf::Color(38, 38, 38));
				_mainWindow.display();

				if(currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;
			
				if(currentEvent.type == sf::Event::KeyPressed)
			{
				if(currentEvent.key.code== sf::Keyboard::Escape) ShowMenu();
			}
		     }
		break;
	    }
	}
  }




void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}	

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
		case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			break;
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;

// lines above are Game's two member variables
// As a quirk of being static, they need to be instanced manually
// since we don't have a constructor variable
// this is a convenient time to set a default value Uninitialized to _gameState
//
// This means when Game is created, its _gameState value will start as uninitialized
//
