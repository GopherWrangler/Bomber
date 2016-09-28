#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <time.h>

enum CheeseType {
	SMALL,
	LARGE,
	SPECIAL,
	TRAP,
};


//============================= GameObject Class ============================//
class GameObject
{
public:
	GameObject();
	~GameObject();
	bool collision(sf::RectangleShape* obj1, sf::RectangleShape* obj2);
	float gravity(sf::RectangleShape* obj, sf::Time dt);
	virtual void Update(sf::RenderWindow* window, sf::Time dt);
	virtual void Draw(sf::RenderWindow* window);
	sf::RectangleShape* m_Object;
	std::vector <GameObject*> m_Cheeses;
	sf::Sprite* publicSprite;
	CheeseType cheeseType;
	bool deadBomb;
	bool onPlatform;
	bool platformTouched;
	bool onGround;
	bool spaceBar;
	bool trapped;
	bool isTrap;
	bool isBottomGround;
	bool reverseMotion;
	bool m_bigCheese;
	int objType;
	int speed;
	int gameLevel;
	int cheeseScore;
	float vel;
	float bounceVel;
	float gravVel;
protected:

};


//=============================== Cheese Class ==============================//

class Cheese : public GameObject
{
public:
	Cheese(sf::Vector2f pos, CheeseType type, int level, sf::Texture* cheeseText);
	sf::Vector2f getPosition();
	void animate();
	void Update(sf::RenderWindow* window, sf::Time dt);
	void Draw(sf::RenderWindow* window);
	sf::RectangleShape* m_Cheese;
	sf::Texture* m_cheeseTexture;
	sf::Texture* m_poisonTexture;
	sf::Texture* m_trapTexture;
	sf::Sprite* m_cheeseSprite;
	sf::Sprite* m_poisonSprite;
private:
	bool m_colorChange;
	bool m_bounce;
	bool m_bounceUp;
	int m_poisonCount;
	int m_bounceDir;
	int m_cheeseCols;
	int m_cheeseRows;
	CheeseType cheeseID;
	sf::Texture* m_cheeseBlockTexture;
	sf::RectangleShape* m_trapSquare;
	sf::Vector2f m_pos;
	sf::Clock m_animClock;
	sf::Time m_animTime;
	//sf::Clock m_Time;
	//sf::Time m_Timer;
	float m_animTimer;
	float m_cheeseTime;
	float m_pointMultiplier;
};


//============================= Spawner Class =============================//
class Spawner : public GameObject
{
public:
	Spawner();
	Spawner(sf::Vector2f pos, int speed, int level, sf::Texture* cheeseText, sf::Texture* poisonText, sf::Texture* mouseTrapText);
	sf::Vector2f getPosition();
	void collisionAndDeath();
	void Update(sf::RenderWindow* window, sf::Time dt);
	void Draw(sf::RenderWindow* window);

private:
	bool reverse;
	int m_speed;
	int m_level;
	int m_cheeseCols;
	int m_cheeseRows;
	sf::Texture* m_cheese;
	sf::Texture* m_poison;
	sf::Texture* m_trap;
	sf::RectangleShape* m_Spawner;
	sf::Vector2f m_pos;
	sf::Clock m_Time;
	sf::Time m_Timer;
	//sf::Clock m_animClock;
	//sf::Time m_animTimer;
	int m_randomNum;
	int m_randSpawn;
	int m_spawnTimer;
	int m_animTimeReset;
	float m_spawnTime;
};


//=========================== Player Class ================================//
class Player : public GameObject
{
public:
	Player(int level);
	void keyUp();
	void keyDown();
	void Update(sf::RenderWindow* window, sf::Time dt);
	void Draw(sf::RenderWindow* window);
	sf::RectangleShape* m_player;
private:
	bool mLeft;
	bool mRight;
	bool mSpace;
	bool up;
	bool spacePressed;
	bool jumpReset;
	bool m_counting;
	bool m_facingRight;
	bool m_facingLeft;
	bool m_justReleasedRight;
	bool m_justReleasedLeft;
	bool m_justLanded;
	int colCount;
	float m_trapReset;
	float m_animReset;
	sf::Texture* mouseTexture;
	sf::Sprite* mouseSprite;
	sf::Vector2f m_playerPos;
	sf::Vector2f m_vel;
	sf::Clock m_Time;
	sf::Time m_Timer;
	sf::Clock m_animTime;
	sf::Time m_animTimer;
};


//=========================== Ground Class =============================//
class Ground : public GameObject
{
public:
	Ground(sf::Vector2f pos, int length, int width, int level, bool grnd);
	void Update(sf::RenderWindow* window, sf::Time dt);
	void Draw(sf::RenderWindow* window);
	bool reverse;
	sf::RectangleShape* m_ground;
	sf::Vector2f m_pos;
private:
	bool m_isBaseGround;
	int m_level;
	int m_speed;
	sf::Texture* m_movingPlatformTex;
};

//=========================== Cat Class =================================//
class Cat : public GameObject
{
public:
	Cat(sf::Texture* cat);
	void Update(sf::RenderWindow* window, sf::Time dt);
	void Draw(sf::RenderWindow* window);
	void Death();
private:
	const int CAT_COLS = 2;
	const int CAT_ROWS = 4;
	int catCols;
	int catRows;
	float timer;
	sf::RectangleShape* m_cat;
	sf::Vector2f m_pos;
	sf::Clock m_time;
	sf::Time m_animTimer;
	sf::Texture* catTexture;
	sf::Sprite* catSprite;
};

