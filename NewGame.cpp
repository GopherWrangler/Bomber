//======================== Bomber-like Game ============================//
//======================================================================//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <time.h>
#include "GameObject.h"

#define MAX_SPEED 300

//=================================== Game Class ==================================//
class Game
{
public:
	Game(sf::RenderWindow* window);

	void Update(sf::RenderWindow* window, sf::Time dt);
	void Draw(sf::RenderWindow* window);

private:
	std::vector <GameObject*> gameManager;
};

Game::Game(sf::RenderWindow* window)
{
	for (int i = 0; i < 800; i+=100)
	{
		gameManager.push_back(new Spawner(sf::Vector2f(200 + i, -20)));
	}

	gameManager.push_back(new Player());
}

void Game::Update(sf::RenderWindow* window, sf::Time dt)
{
	for (int i = 0; i < gameManager.size(); i++)
	{
		gameManager[i]->Update(window, dt);
	}
}

void Game::Draw(sf::RenderWindow* window)
{
	for (int i = 0; i < gameManager.size(); i++)
	{
		gameManager[i]->Draw(window);
	}
}





//================================= Main Function =================================//

int _tmain(int argc, _TCHAR* argv[])
{
	sf::RenderWindow window(sf::VideoMode(1280, 840), "Bomber Game");

	Game myGame(&window);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}


		sf::Time dt = clock.restart();
		window.clear();

		myGame.Update(&window, dt);
		myGame.Draw(&window);

		window.display();
	}

	return 0;
}