#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <time.h>

//============================= GameObject Class ============================//
class GameObject
{
public:
	GameObject();
	~GameObject();
	virtual void Update(sf::RenderWindow* window, sf::Time dt);
	virtual void Draw(sf::RenderWindow* window);

protected:

};


//=============================== Bombs Class ==============================//
enum bombType {
	SMALL,
	LARGE,
	SPECIAL,
};

class Bombs : public GameObject
{
public:
	Bombs(sf::Vector2f pos, bombType type);
	sf::Vector2f getPosition();
	void Update(sf::RenderWindow* window, sf::Time dt);
	void Draw(sf::RenderWindow* window);
	bool deadBomb;
private:
	sf::RectangleShape* m_Bomb;
	sf::Vector2f m_pos;

};


//============================= Spawner Class =============================//
class Spawner : public GameObject
{
public:
	Spawner();
	Spawner(sf::Vector2f pos);
	sf::Vector2f getPosition();
	void collisionAndDeath();
	void Update(sf::RenderWindow* window, sf::Time dt);
	void Draw(sf::RenderWindow* window);
private:
	sf::RectangleShape* m_Spawner;
	sf::Clock m_Time;
	sf::Time m_Timer;
	std::vector <Bombs*> m_Bombs;
	int m_randomNum;
	float m_randSpawn;
	float m_spawnTime;
};


//=========================== Player Class ================================//
class Player : public GameObject
{
public:
	Player();
	void keyUp();
	void keyDown();
	void Update(sf::RenderWindow* window, sf::Time dt);
	void Draw(sf::RenderWindow* window);
private:
	bool mLeft;
	bool mRight;
	sf::RectangleShape* m_player;
	sf::Vector2f m_playerPos;
	sf::Vector2f m_vel;
};

