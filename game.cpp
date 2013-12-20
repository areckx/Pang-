#include "stdafx.h"
#include "Game.h"

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
	_mainWindow.create(sf::VideoMode(640,480,32), "Pang!");
	_gameState = Game::Playing; // switch states

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
	sf::Event currentEvent;
while(_mainWindow.pollEvent(currentEvent))
{

	switch(_gameState)
	{
	case Game::Playing:
		{
			_mainWindow.clear(sf::Color(255,0,0));
			_mainWindow.display();

			if (currentEvent.type == sf::Event::Closed)
			{
				_gameState = Game::Exiting;
			}
			break;
		}
	}
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
