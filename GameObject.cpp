#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <time.h>
#include "GameObject.h"

// Game Constants
#define GROUND 775
#define GRAVITY 7000
#define ACCEL 2000
#define MAX_VELOCITY 900
#define FALL_VELOCITY 700
#define JUMP_VELOCITY -2000
#define BOUNCE_VEL -1500
#define ROLL_VEL 500
#define COLS 6


//================================ GameObject Class ===================================//
GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

bool GameObject::collision(sf::RectangleShape* obj1, sf::RectangleShape* obj2)
{

	return obj1->getGlobalBounds().intersects(obj2->getGlobalBounds());
}

float GameObject::gravity(sf::RectangleShape* obj, sf::Time dt)
{
	sf::Vector2f pos = obj->getPosition();
	float time = dt.asSeconds();

	gravVel += GRAVITY * time;

	pos.y += gravVel * time;

	return pos.y;
}

void GameObject::Update(sf::RenderWindow* window, sf::Time dt)
{

}

void GameObject::Draw(sf::RenderWindow* window)
{

}


//======================================== Cheeses Class ====================================//
#define CHEESE_COLS 5
#define CHEESE_ROWS 2

Cheese::Cheese(sf::Vector2f pos, CheeseType type, int level, sf::Texture* cheeseText)
{
	// Defining local variables
	m_cheeseBlockTexture = cheeseText;
	m_pointMultiplier = level * 0.5;
	deadBomb = false;
	m_bounce = false;
	m_bigCheese = false;
	m_poisonCount = 0;
	objType = 0;
	bounceVel = 0;
	m_cheeseCols = 0;
	m_cheeseRows = 0;
	vel = 0;
	cheeseID = type;
	m_colorChange = false;
	m_animClock.restart();

	// Create Cheese or poison block RectangleShape and set cheeseScore and cheeseID based on type
	switch (type)
	{
	case SMALL:
		m_cheeseSprite = new sf::Sprite;
		m_cheeseSprite->setTexture(*m_cheeseBlockTexture);
		m_cheeseSprite->setTextureRect(sf::IntRect(0, 0, 205, 130));
		isTrap = false;
		cheeseScore = 20 * m_pointMultiplier;
		cheeseID = type;
		m_Cheese = new sf::RectangleShape();
		m_Cheese->setSize(sf::Vector2f(10, 10));
		m_Cheese->setFillColor(sf::Color::Transparent);
		m_Cheese->setPosition(pos.x, pos.y);
		m_Cheese->setOrigin(sf::Vector2f(0, 10));
		m_pos = m_Cheese->getPosition();
		m_cheeseSprite->setOrigin(sf::Vector2f(100, 75));
		m_cheeseSprite->setPosition(m_pos);
		m_cheeseSprite->setScale(0.2, 0.2);
		publicSprite = m_cheeseSprite;
		break;
	case LARGE:
		m_cheeseSprite = new sf::Sprite;
		m_cheeseSprite->setTexture(*m_cheeseBlockTexture);
		m_cheeseSprite->setTextureRect(sf::IntRect(0, 0, 205, 130));
		isTrap = false;
		cheeseScore = 10 * m_pointMultiplier;
		cheeseID = type;
		m_Cheese = new sf::RectangleShape();
		m_Cheese->setSize(sf::Vector2f(20, 38));
		m_Cheese->setFillColor(sf::Color::Transparent);
		m_Cheese->setPosition(pos.x, pos.y);
		m_Cheese->setOrigin(sf::Vector2f(0, 15));
		m_pos = m_Cheese->getPosition();
		m_cheeseSprite->setOrigin(sf::Vector2f(100, 75));
		m_cheeseSprite->setPosition(m_pos);
		m_cheeseSprite->setScale(0.4, 0.4);
		publicSprite = m_cheeseSprite;
		break;
	case SPECIAL:
		m_poisonSprite = new sf::Sprite;
		m_poisonSprite->setTexture(*m_cheeseBlockTexture);
		m_poisonSprite->setTextureRect(sf::IntRect(0, 0, 205, 207));
		isTrap = false;
		cheeseScore = -50 * m_pointMultiplier;
		cheeseID = type;
		m_Cheese = new sf::RectangleShape();
		m_Cheese->setSize(sf::Vector2f(40, 80));
		m_Cheese->setFillColor(sf::Color::Transparent);
		m_Cheese->setPosition(pos.x, pos.y);
		m_Cheese->setOrigin(sf::Vector2f(0, 80));
		m_pos = m_Cheese->getPosition();
		m_poisonSprite->setOrigin(sf::Vector2f(55, 198));
		m_poisonSprite->setPosition(m_pos);
		m_poisonSprite->setScale(0.5, 0.5);
		publicSprite = m_poisonSprite;
		break;
	case TRAP:
		isTrap = true;
		cheeseScore = 0;
		cheeseID = type;
		m_Cheese = new sf::RectangleShape();
		m_Cheese->setTexture(m_cheeseBlockTexture);
		m_Cheese->setSize(sf::Vector2f(70, 70));
		m_Cheese->setPosition(pos.x, pos.y);
		m_Cheese->setOrigin(sf::Vector2f(0, 50));
		m_pos = m_Cheese->getPosition();
	}

	m_Object = m_Cheese;

	if (level == 12)
	{
		m_bigCheese = true;
	}

	// 50-50 random chance to pick which way cheese will bounce when it hits the ground
	int randomNum = rand();
	m_bounceDir = (randomNum % 100) + 1;
}

sf::Vector2f Cheese::getPosition()
{
	return m_Cheese->getPosition();
}

void Cheese::animate()
{
	if (cheeseID == SPECIAL)
	{
		if (m_cheeseCols < CHEESE_COLS)
		{
			m_poisonSprite->setTextureRect(sf::IntRect(m_cheeseCols * 205, m_cheeseRows * 207, 205, 207));
			m_cheeseCols++;
		}
		else
		{
			m_cheeseCols = 1;
			m_cheeseRows++;

			if (m_cheeseRows >= CHEESE_ROWS)
			{
				m_cheeseRows = 0;
			}
			m_poisonSprite->setTextureRect(sf::IntRect(0, m_cheeseRows * 207, 205, 207));
		}
	}
	else
	{
		if (m_cheeseCols < CHEESE_COLS)
		{
			m_cheeseSprite->setTextureRect(sf::IntRect(m_cheeseCols * 205, m_cheeseRows * 130, 205, 130));
			m_cheeseCols++;
		}
		else
		{
			m_cheeseCols = 1;
			m_cheeseRows++;

			if (m_cheeseRows >= CHEESE_ROWS)
			{
				m_cheeseRows = 0;
			}
			m_cheeseSprite->setTextureRect(sf::IntRect(0, m_cheeseRows * 130, 205, 130));
		}
	}
}

void Cheese::Update(sf::RenderWindow* window, sf::Time dt)
{
	float time = dt.asSeconds();

	if (m_bigCheese)
	{
		if (!reverseMotion)
		{
			m_pos.x += speed * time;
			//m_pos.y = 85;
		}
		else if (reverseMotion)
		{
			m_pos.x -= speed * time;
			//m_pos.y = 85;
		}
	}
	
	// If m_bounce is false, let cheese fall normally
	if (!m_bounce)
	{
		vel += GRAVITY * time;
		m_pos.y += vel * time;
		// If cheese block goes lower than 640 and m_bounce is false, set m_bounce and m_bounceUp to true to start bounce movement
		if (m_pos.y >= GROUND && !m_bounce)
		{
			m_bounce = true;
		}
		// Set the position of the cheese block on the screen according to previous movement
		if (m_bigCheese)
		{
			m_pos.y = 150;
		}
		m_Cheese->setPosition(m_pos);
		if (cheeseID == SPECIAL)
		{
			m_poisonSprite->setPosition(m_pos);
		}
		else if (cheeseID == TRAP)
		{
			
		}
		else
		{
			m_cheeseSprite->setPosition(m_pos);
		}
	}
	// If m_bounce is true, start bounce movement
	else if (m_bounce)
	{
		// If previously chosen random num is > 50, bounce to the right
		if (m_bounceDir > 50)
		{
			bounceVel += GRAVITY * time;
			m_pos.y += (BOUNCE_VEL + bounceVel) * time;
			m_pos.x += ROLL_VEL * time;
			m_Cheese->setPosition(m_pos);
			if (cheeseID == SPECIAL)
			{
				m_poisonSprite->setPosition(m_pos);
			}
			else if (cheeseID == TRAP)
			{
	
			}
			else
			{
				m_cheeseSprite->setPosition(m_pos);
			}
	
			// If the cheese block goes off the screen, kill it
			if (m_pos.x > 1280)
			{
				deadBomb = true;
			}
			// If the Cheese block hits the gound, bounce back up
			if (m_pos.y >= GROUND)
			{
				bounceVel = 0;
			}
		}
		// If previously chosen random number is <= 50, roll cheese block to the left
		else if (m_bounceDir <= 50)
		{
			bounceVel += GRAVITY * time;
			m_pos.y += (BOUNCE_VEL + bounceVel) * time;
			m_pos.x -= ROLL_VEL * time;
			m_Cheese->setPosition(m_pos);
			if (cheeseID == SPECIAL)
			{
				m_poisonSprite->setPosition(m_pos);
			}
			else if (cheeseID == TRAP)
			{
	
			}
			else
			{
				m_cheeseSprite->setPosition(m_pos);
			}
	
			// If cheese block goes off screen, kill it
			if (m_pos.x < 0)
			{
				deadBomb = true;
			}
			// If Cheese block hits the ground, bounce back upward
			if (m_pos.y >= GROUND)
			{
				bounceVel = 0;
			}
			//printf("\nRolling Left");
		}
	}
	
	if (m_bigCheese)
	{
		m_pos.y = 150;
	}
	
	// Animate the Cheese Sprites
	m_animTime = m_animClock.getElapsedTime();
	m_animTimer = m_animTime.asSeconds();
	
	if (m_animTimer > 0.12)
	{
		if (cheeseID == SPECIAL)
		{
			if (m_cheeseCols < CHEESE_COLS)
			{
				m_poisonSprite->setTextureRect(sf::IntRect(m_cheeseCols * 205, m_cheeseRows * 207, 205, 207));
				m_cheeseCols++;
			}
			else
			{
				m_cheeseCols = 1;
				m_cheeseRows++;
	
				if (m_cheeseRows >= CHEESE_ROWS)
				{
					m_cheeseRows = 0;
				}
				m_poisonSprite->setTextureRect(sf::IntRect(0, m_cheeseRows * 207, 205, 207));
			}
		}
		else if (cheeseID == TRAP)
		{
	
		}
		else
		{
			if (m_cheeseCols < CHEESE_COLS)
			{
				m_cheeseSprite->setTextureRect(sf::IntRect(m_cheeseCols * 205, m_cheeseRows * 130, 205, 130));
				m_cheeseCols++;
			}
			else
			{
				m_cheeseCols = 1;
				m_cheeseRows++;
	
				if (m_cheeseRows >= CHEESE_ROWS)
				{
					m_cheeseRows = 0;
				}
				m_cheeseSprite->setTextureRect(sf::IntRect(0, m_cheeseRows * 130, 205, 130));
			}
		}
		m_animClock.restart();
	}

	if (m_bigCheese)
	{
		m_pos.y = 85;
	}
}

void Cheese::Draw(sf::RenderWindow* window)
{
	window->draw(*m_Cheese);
	if (cheeseID == SPECIAL)
	{
		window->draw(*m_poisonSprite);
	}
	else if (cheeseID != TRAP)
	{
		window->draw(*m_cheeseSprite);
	}
}

//================================== Spawner Class =====================================//
#define SPAWNER1_VEL 400
#define SPAWNER2_VEL 100

Spawner::Spawner()
{

}

Spawner::Spawner(sf::Vector2f pos, int speed, int level, sf::Texture* cheeseText, sf::Texture* poisonText, sf::Texture* mouseTrapText)
{
	// Local Variables
	bool reverse = false;
	isTrap = false;
	deadBomb = false;
	objType = 1;
	m_cheeseCols = 0;
	m_cheeseRows = 0;
	m_level = level;
	m_speed = speed;
	m_cheese = cheeseText;
	m_poison = poisonText;
	m_trap = mouseTrapText;

	// Restart Timer clock and create Spawner shape
	m_Time.restart();
	m_Spawner = new sf::RectangleShape;
	m_Spawner->setSize(sf::Vector2f(50, 50));
	m_Spawner->setFillColor(sf::Color::Transparent);
	m_Spawner->setPosition(pos.x, pos.y);
	m_pos = m_Spawner->getPosition();
	m_Object = m_Spawner;

	// Set the random spawn timer for cheese spawn interval
	m_spawnTimer = (rand() % 10) + 2;

	if (m_level == 5)
	{
		m_Cheeses.push_back(new Cheese(sf::Vector2f(530, 85), LARGE, 12, m_cheese));
	}

	printf("\nspawnTimer: %d", m_spawnTimer);
}

sf::Vector2f Spawner::getPosition()
{
	return m_Spawner->getPosition();
}

void Spawner::collisionAndDeath()
{
	// If there are cheese objects in the m_Cheeses vector, begin iterating through the vector
	if (m_Cheeses.size() != 0)
	{
		for (int i = 0; i < m_Cheeses.size(); i++)
		{
			// If the deadBomb variable in any of the Cheese objects in m_Cheeses is true, kill the cheese block
			if (m_Cheeses[i]->deadBomb == true)
			{
				delete m_Cheeses[i];
				m_Cheeses.erase(m_Cheeses.begin() + i);
				i--;
				printf("\nDead Cheese erased.");
			}
		}
	}
}

void Spawner::Update(sf::RenderWindow* window, sf::Time dt)
{
	// Get elapsed time for spawn timer to compare to random spawn time number
	m_Timer = m_Time.getElapsedTime();
	m_spawnTime = m_Timer.asSeconds();

	// Check for any cheese blocks labeled for death
	collisionAndDeath();

	float time = dt.asSeconds();
	// Move spawner toward the right
	if (!reverse)
	{
		m_pos.x += m_speed * time;
		if (m_pos.x >= 1100)
		{
			reverse = true;
		}
	}
	// Move spawner toward the left
	else if (reverse)
	{
		m_pos.x -= m_speed * time;
		if (m_pos.x <= 100)
		{
			reverse = false;
		}
	}

	m_Spawner->setPosition(m_pos);

	// ================= If the current time > random spawn time interval, spawn a cheese block ======================//
	if (m_spawnTime > m_spawnTimer)
	{
		// Create a random number to determine type of cheese block to spawn
		m_randomNum = rand();
		m_randSpawn = (m_randomNum % 100) + 1;
		printf("\nrandSpawn: %d", m_randSpawn);

		// Spawn LARGE cheese block
		if (m_randSpawn <= 40)
		{
			m_Cheeses.push_back(new Cheese(m_Spawner->getPosition(), LARGE, m_level, m_cheese));
			m_Time.restart();
		}
		// Spawn SMALL cheese block
		if (m_randSpawn > 40 && m_randSpawn <= 85)
		{
			m_Cheeses.push_back(new Cheese(m_Spawner->getPosition(), SMALL, m_level, m_cheese));
			m_Time.restart();
		}
		// Spawn SPECIAL poison block or TRAP block
		else if (m_randSpawn > 85)
		{
			// If the game is running higher than level 2, have a chance to spawn a poison or trap block
			if (m_level > 2)
			{
				// Roll a random number to pick to spawn a poison block or trap block
				printf("\nSpawning a SPECIAL or TRAP");
				m_randomNum = rand();
				m_randSpawn = (m_randomNum % 100) + 1;

				// If random number is <= 50, spawn a poison block
				if (m_randSpawn <= 50)
				{
					m_Cheeses.push_back(new Cheese(m_Spawner->getPosition(), SPECIAL, m_level, m_poison));
					m_Time.restart();
				}
				// If random number is > 50, spawn a trap block
				else if (m_randSpawn > 50)
				{
					m_Cheeses.push_back(new Cheese(m_Spawner->getPosition(), TRAP, m_level, m_trap));
					m_Time.restart();
				}
			}
			// If the game is running at level 2 or lower, just spawn a poison block
			else
			{
				printf("\nSpawning SPECIAL");
				m_Cheeses.push_back(new Cheese(m_Spawner->getPosition(), SPECIAL, m_level, m_poison));
				m_Time.restart();
			}
		}
	}

	// If m_Cheeses vector is not empty, update all Cheese objects in vector

	if (m_Cheeses.size() != NULL)
	{
		for (int i = 0; i < m_Cheeses.size(); i++)
		{
			m_Cheeses[i]->Update(window, dt);
		}
	}
}

void Spawner::Draw(sf::RenderWindow* window)
{
	window->draw(*m_Spawner);

	for (int i = 0; i < m_Cheeses.size(); i++)
	{
		m_Cheeses[i]->Draw(window);
	}
}


//======================================= Player Class ===================================//
Player::Player(int level)
{
	// Define local variables for Player object
	trapped = false;
	m_counting = false;
	spaceBar = false;
	onPlatform = true;
	m_facingRight = true;
	m_facingLeft = false;
	m_justReleasedRight = false;
	m_justReleasedLeft = false;
	m_justLanded = false;
	objType = 2;
	vel = 0;
	gravVel = 0;
	bounceVel = 0;
	colCount = 0;
	gameLevel = level;
	deadBomb = false;
	mSpace = false;
	spacePressed = false;
	jumpReset = true;
	onGround = true;
	reverseMotion = false;
	isBottomGround = false;
	mouseTexture = new sf::Texture;
	mouseSprite = new sf::Sprite;

	if (!mouseTexture->loadFromFile("RU4By.png", sf::IntRect(0, 0, 600, 100)));
	{
		printf("\nCould not load image file");
	}

	mouseTexture->setSmooth(true);
	mouseSprite->setTexture(*mouseTexture);
	mouseSprite->setTextureRect(sf::IntRect(0, 0, 100, 100));
	mouseSprite->setScale(sf::Vector2f(1.5, 1.5));
	mouseSprite->setOrigin(sf::Vector2f(65, 78));
	publicSprite = mouseSprite;

	m_player = new sf::RectangleShape();
	m_player->setSize(sf::Vector2f(55, 50));
	m_player->setFillColor(sf::Color::Transparent);
	m_player->setPosition(sf::Vector2f(800, GROUND));
	m_player->setOrigin(sf::Vector2f(26, 50));
	m_playerPos = m_player->getPosition();
	mouseSprite->setPosition(m_playerPos);
	m_Object = m_player;

	m_animTime.restart();
}

void Player::keyUp()
{
	// Check to see if Left arrow key, Right arrow key, or Space bar are NOT being pressed
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mLeft = false;
		vel = 0;

		if (!m_justReleasedLeft)
		{
			mouseSprite->setTextureRect(sf::IntRect(500, 0, 100, 100));
			m_justReleasedLeft = true;
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mRight = false;
		vel = 0;

		if (!m_justReleasedRight)
		{
			mouseSprite->setTextureRect(sf::IntRect(500, 0, 100, 100));
			m_justReleasedRight = true;
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		jumpReset = true;
		spaceBar = false;
	}
}

void Player::keyDown()
{
	// Check to see if Left arrow key, Right arrow key, and Space bar ARE being pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mLeft = true;
		m_facingRight = false;
		m_justReleasedLeft = false;
		if (!m_facingLeft)
		{
			mouseSprite->scale(-1, 1);
			m_facingLeft = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mRight = true;
		m_facingLeft = false;
		m_justReleasedRight = false;
		if (!m_facingRight)
		{
			mouseSprite->scale(-1, 1);
			m_facingRight = true;
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !mSpace && jumpReset)
	{
		// Set values for bool variables used in jumping behavior
		spaceBar = true;
		mSpace = true;
		jumpReset = false;
		onPlatform = false;
		printf("\nSpace Bar Pressed");
	}
}

void Player::Update(sf::RenderWindow* window, sf::Time dt)
{
	m_Timer = m_Time.getElapsedTime();
	m_trapReset = m_Timer.asSeconds();
	m_animTimer = m_animTime.getElapsedTime();
	m_animReset = m_animTimer.asSeconds();

	//spaceBar = false;

	// Save current position of Player object before changes are made
	sf::Vector2f prevPos = m_playerPos;
	
	// Check for Keyboard events
	keyUp();
	keyDown();

	// If the player has not hit a trap block, allow player movement
	if (!trapped)
	{
		float time = dt.asSeconds();

		// If the player is not on a platform and free falling, apply gravity
		if (!onGround && !mSpace)
		{
			m_playerPos.y = gravity(m_player, dt);
			mouseSprite->setTextureRect(sf::IntRect(0, 0, 100, 100));
			m_justLanded = false;
			//spaceBar = false;
		}
		//if (!onGround && mSpace)
		//{
		//	spaceBar = false;
		//}
		// Else, if the player is on the ground, set the fall velocity to 0
		else if (onGround)
		{
			gravVel = 0;

			if (!m_justLanded)
			{
				mouseSprite->setTextureRect(sf::IntRect(500, 0, 100, 100));
				m_justLanded = true;
			}

			if (gameLevel > 4 && isBottomGround)
			{
				if (!reverseMotion)
				{
					m_playerPos.x += speed * time;
				}
				else if (reverseMotion)
				{
					m_playerPos.x -= speed * time;
				}

				isBottomGround = false;
			}
		}

		// Left arrow key pressed for Leftward Movement
		if (mLeft && !mRight)
		{
			vel += ACCEL * time;
			m_playerPos.x -= (vel + MAX_VELOCITY) * time;

			if (vel < MAX_VELOCITY)
			{
				vel = MAX_VELOCITY;
			}

			// Apply collsion so player stops at edge of screen and does not go off screen
			if (m_playerPos.x < 5)
			{
				m_playerPos.x = prevPos.x;
			}

			// Mouse Left movement animation
			if (m_animReset > 0.08 && !mSpace)
			{
				if (colCount < COLS)
				{
					mouseSprite->setTextureRect(sf::IntRect(colCount * 100, 0, 100, 100));
					colCount++;
				}
				else
				{
					colCount = 1;
					mouseSprite->setTextureRect(sf::IntRect(0, 0, 100, 100));
				}
				m_animTime.restart();
			}
		}
		// Right arrow key pressed for Rightward Movement
		else if (mRight && !mLeft)
		{
			vel += ACCEL * time;
			m_playerPos.x += (vel + MAX_VELOCITY) * time;

			if (vel > MAX_VELOCITY)
			{
				vel = MAX_VELOCITY;
			}

			// Apply collsion so player stops at edge of screen and does not go off screen
			if (m_playerPos.x > 1250)
			{
				m_playerPos.x = prevPos.x;
			}

			// Mouse Right movement animation
			if (m_animReset > 0.08 && !mSpace)
			{
				if (colCount < COLS)
				{
					mouseSprite->setTextureRect(sf::IntRect(colCount * 100, 0, 100, 100));
					colCount++;
				}
				else
				{
					colCount = 1;
					mouseSprite->setTextureRect(sf::IntRect(0, 0, 100, 100));
				}
				m_animTime.restart();
			}
		}

		// Jump Movement if Space bar pressed
		if (mSpace)
		{
			bounceVel += GRAVITY * time;
			m_playerPos.y += (JUMP_VELOCITY + bounceVel) * time;
			mouseSprite->setTextureRect(sf::IntRect(0, 0, 100, 100));
			printf("\nJumped");

			// When Player hits the ground, end jump action and reset bounceVel to 0
			if (onPlatform)
			{
				printf("\nMouse has Landed");
				mouseSprite->setTextureRect(sf::IntRect(500, 0, 100, 100));
				bounceVel = 0;
				mSpace = false;
			}
		}


		if (!onGround && mSpace)
		{
			spaceBar = false;
		}
	}
	// If the player has just hit a trap block, start the trap timer and set m_counting to true so timer is not reset every frame
	else if (trapped && !m_counting)
	{
		m_Time.restart();
		m_counting = true;
	}
	// If the player has already hit a trap block, check timer to see if trap timer is up. If so, set trapped to false to allow player movement once more 
	// and set m_counting to false
	else if (trapped && m_counting)
	{
		m_Timer = m_Time.getElapsedTime();
		m_trapReset = m_Timer.asSeconds();

		if (m_trapReset > 3)
		{
			trapped = false;
			m_counting = false;
		}
	}

	// Set position of Player object after changes are made
	m_player->setPosition(m_playerPos);
	mouseSprite->setPosition(m_playerPos);
}

void Player::Draw(sf::RenderWindow* window)
{
	window->draw(*m_player);
	window->draw(*mouseSprite);
}

//======================================= Ground Class ==========================================//

Ground::Ground(sf::Vector2f pos, int length, int width, int level, bool grnd)
{
	m_movingPlatformTex = new sf::Texture;
	platformTouched = true;
	reverseMotion = false;
	m_isBaseGround = grnd;
	isBottomGround = m_isBaseGround;
	objType = 3;
	m_level = level;
	m_ground = new sf::RectangleShape;
	m_ground->setSize(sf::Vector2f(length, width));

	if (m_level == 5)
	{
		if (m_isBaseGround)
		{
			m_ground->setFillColor(sf::Color::Transparent);
		}
	}
	else if (m_level < 5)
	{
		m_ground->setFillColor(sf::Color::Transparent);
	}
	
	m_ground->setPosition(sf::Vector2f(pos));
	m_ground->setOrigin(sf::Vector2f(0, 15));
	m_pos = m_ground->getPosition();

	m_Object = m_ground;
	m_speed = (rand() % 500) + 300;
	speed = m_speed;

	if (m_speed >= 250)
	{
		reverse = false;
	}
	else if (m_speed < 250)
	{
		reverse = true;
	}
}

void Ground::Update(sf::RenderWindow* window, sf::Time dt)
{
	if (!m_isBaseGround)
	{
		if (m_level == 5)
		{
			if (!m_movingPlatformTex->loadFromFile("MovingPlatform.png", sf::IntRect(0, 0, 200, 25)))
			{
				printf("\nCould not load Platform image file");
			}

			m_ground->setTexture(m_movingPlatformTex);

			float time = dt.asSeconds();
			// Move ground toward the right
			if (!reverse)
			{
				m_pos.x += m_speed * time;
				if (m_pos.x >= 1100)
				{
					reverse = true;
					reverseMotion = true;
				}
			}
			// Move ground toward the left
			else if (reverse)
			{
				m_pos.x -= m_speed * time;
				if (m_pos.x <= 200)
				{
					reverse = false;
					reverseMotion = false;
				}
			}
		}
	}

	speed = m_speed;
	m_ground->setPosition(m_pos);

	platformTouched = false;
}

void Ground::Draw(sf::RenderWindow* window)
{
	window->draw(*m_ground);
}

//======================================= Cat Class =================================//
Cat::Cat(sf::Texture* cat)
{
	objType = 4;
	bounceVel = 0;

	m_cat = new sf::RectangleShape();
	m_cat->setSize(sf::Vector2f(300, 125));
	m_cat->setFillColor(sf::Color::Transparent);
	m_cat->setOrigin(sf::Vector2f(0, 125));
	m_cat->setPosition(sf::Vector2f(1300, 400));

	catTexture = new sf::Texture;
	catTexture = cat;

	catSprite = new sf::Sprite;
	catSprite->setTexture(*catTexture);
	catSprite->setTextureRect(sf::IntRect(0, 0, 512, 256));
	catSprite->setScale(0.75, 0.75);
	catSprite->scale(-1, 1);
	catSprite->setOrigin(sf::Vector2f(512, 256));

	m_pos = m_cat->getPosition();
	catSprite->setPosition(m_pos);
	publicSprite = catSprite;
	m_Object = m_cat;

	m_time.restart();
}

void Cat::Death()
{
	if (m_pos.x < -100)
	{
		delete m_cat;
		printf("\nDeleted Cat");
	}
}

void Cat::Update(sf::RenderWindow* window, sf::Time dt)
{
	float time = dt.asSeconds();
	m_animTimer = m_time.getElapsedTime();
	timer = m_animTimer.asSeconds();

	bounceVel += GRAVITY * time;
	m_pos.y += (BOUNCE_VEL + bounceVel) * time;
	m_pos.x -= (ROLL_VEL * 1.7) * time;

	// If Cat block hits the ground, bounce back upward
	if (m_pos.y >= GROUND)
	{
		//bounceVel = 0;
		m_pos.y = GROUND;

		// Cat Animation
		if (timer > 0.08)
		{
			if (catCols < CAT_COLS)
			{
				catSprite->setTextureRect(sf::IntRect(catCols * 512, catRows * 256, 512, 256));
				catCols++;
			}
			else
			{
				catCols = 1;
				catRows++;

				if (catRows >= CAT_ROWS)
				{
					catRows = 0;
				}
				catSprite->setTextureRect(sf::IntRect(0, catRows * 256, 512, 256));
			}
			m_time.restart();
		}
	}

	m_cat->setPosition(m_pos);

	catSprite->setPosition(m_pos);
}

void Cat::Draw(sf::RenderWindow* window)
{
	window->draw(*m_cat);
	window->draw(*catSprite);
}
