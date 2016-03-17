#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <time.h>
#include "GameObject.h"


//================================ GameObject Class ===================================//
GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Update(sf::RenderWindow* window, sf::Time dt)
{

}

void GameObject::Draw(sf::RenderWindow* window)
{

}

//================================== Spawner Class =====================================//
Spawner::Spawner()
{

}

Spawner::Spawner(sf::Vector2f pos)
{
	sf::Clock Time;
	//srand(static_cast<unsigned int>(time(0)));

	Time.restart();
	m_Spawner = new sf::RectangleShape;
	m_Spawner->setSize(sf::Vector2f(50,50));
	m_Spawner->setFillColor(sf::Color::Transparent);
	m_Spawner->setPosition(pos.x, pos.y);
}

sf::Vector2f Spawner::getPosition()
{
	return m_Spawner->getPosition();
}

void Spawner::collisionAndDeath()
{
	if (m_Bombs.size() != NULL)
	{
		for (int i = 0; i < m_Bombs.size(); i++)
		{
			if (m_Bombs[i]->deadBomb == true)
			{
				m_Bombs[i] = 0;
				delete m_Bombs[i];
				m_Bombs.erase(m_Bombs.begin() + i);
			}
		}
	}
}

void Spawner::Update(sf::RenderWindow* window, sf::Time dt)
{
	srand(static_cast<unsigned int>(time(0)));
	m_Timer = m_Time.getElapsedTime();
	m_spawnTime = m_Timer.asSeconds();
	collisionAndDeath();

	if (m_spawnTime / 3 >= 0.9 && m_spawnTime / 3 <= 1.0)
	{
		m_randomNum = rand();
		m_randSpawn = (m_randomNum % 100) + 1;

		if (m_randSpawn <= 40)
		{
			m_Bombs.push_back(new Bombs(m_Spawner->getPosition(), LARGE));
		}
		else if (m_randSpawn > 40 && m_randSpawn <= 80)
		{
			m_Bombs.push_back(new Bombs(m_Spawner->getPosition(), SMALL));
		}
		else
		{
			m_Bombs.push_back(new Bombs(m_Spawner->getPosition(), SPECIAL));
		}
	}

	if (m_Bombs.size() != NULL)
	{
		for (int i = 0; i < m_Bombs.size(); i++)
		{
			m_Bombs[i]->Update(window, dt);
		}
	}	
}

void Spawner::Draw(sf::RenderWindow* window)
{
	window->draw(*m_Spawner);

	for (int i = 0; i < m_Bombs.size(); i++)
	{
		m_Bombs[i]->Draw(window);
	}
}


//======================================== Bombs Class ====================================//
#define VELOCITY 600
Bombs::Bombs(sf::Vector2f pos, bombType type)
{
	deadBomb = false;

	switch (type)
	{
	case SMALL:
		m_Bomb = new sf::RectangleShape();
		m_Bomb->setSize(sf::Vector2f(5, 5));
		m_Bomb->setFillColor(sf::Color::Blue);
		m_Bomb->setPosition(pos.x, pos.y);
		m_pos = m_Bomb->getPosition();
		break;
	case LARGE:
		m_Bomb = new sf::RectangleShape();
		m_Bomb->setSize(sf::Vector2f(15, 25));
		m_Bomb->setFillColor(sf::Color::Red);
		m_Bomb->setPosition(pos.x, pos.y);
		m_pos = m_Bomb->getPosition();
		break;
	case SPECIAL:
		m_Bomb = new sf::RectangleShape();
		m_Bomb->setSize(sf::Vector2f(10, 10));
		m_Bomb->setFillColor(sf::Color::Yellow);
		m_Bomb->setPosition(pos.x, pos.y);
		m_pos = m_Bomb->getPosition();
		break;
	}
}

sf::Vector2f Bombs::getPosition()
{
	return m_Bomb->getPosition();
}

void Bombs::Update(sf::RenderWindow* window, sf::Time dt)
{
	float time = dt.asSeconds();
	m_pos.y += VELOCITY * time;

	m_Bomb->setPosition(m_pos);

	if (m_pos.y > 900)
	{
		deadBomb = true;
	}
}

void Bombs::Draw(sf::RenderWindow* window)
{
	window->draw(*m_Bomb);
}


//======================================= Player Class ===================================//
Player::Player()
{
	m_player = new sf::RectangleShape();
	m_player->setSize(sf::Vector2f(40, 10));
	m_player->setFillColor(sf::Color::White);
	m_player->setPosition(sf::Vector2f(800, 640));
	m_playerPos = m_player->getPosition();
}

void Player::keyUp()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mLeft = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mRight = false;
	}
}

void Player::keyDown()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mLeft = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mRight = true;
	}
}

void Player::Update(sf::RenderWindow* window, sf::Time dt)
{
	keyUp();
	keyDown();

	float time = dt.asSeconds();

	if (mLeft && !mRight)
	{
		time = dt.asSeconds();
		m_playerPos.x -= VELOCITY * time;
	}
	else if (mRight && !mLeft)
	{
		time = dt.asSeconds();
		m_playerPos.x += VELOCITY * time;
	}

	m_player->setPosition(m_playerPos);
}

void Player::Draw(sf::RenderWindow* window)
{
	window->draw(*m_player);
}