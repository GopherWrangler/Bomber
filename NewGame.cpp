//======================== Cheese Chaser Game ============================//
//========================================================================//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include "GameObject.h"

#define MAX_SPEED 300
#define LEVEL_TIME 45


//===================================== UI Class ====================================//
struct Button
{
	sf::RectangleShape shape;
	sf::Text text;
	bool selected;
	int type;
};

class UI
{
public:
	UI(bool startScreen, bool endScreen, int score, sf::Font& font, sf::Texture& buttonTexture, sf::Texture& buttonPressedTexture, sf::Texture& backgroundScreen, sf::Texture& rulesBackground);
	void Update(sf::RenderWindow* window, int score);
	void Draw(sf::RenderWindow* window);
	void keyUp();
	void keyDown();
	bool mStartScreen;
	bool mEndScreen;
	bool mQuit;
	Button* buttons[4];
private:
	bool mPage1;
	bool mPage2;
	bool mRules;
	bool mUp;
	bool mDown;
	bool mEnter;
	bool mUpPressed;
	bool mDownPressed;
	bool mEnterPressed;
	sf::RectangleShape* scoreBoard;
	sf::Font* uiFont;
	//sf::Color mHighlightColor;
	sf::Text* mScoreStatic;
	sf::Text* mStartDisplay;
	sf::Text* mScore;
	sf::Texture* mButtonTexture;
	sf::Texture* mButtonPressedTexture;
	sf::Texture* mBackgroundScreen;
	sf::Texture* mRulesBackground;
	std::string mScoreString;
};

UI::UI(bool startScreen, bool endScreen, int score, sf::Font& font, sf::Texture& buttonTexture, sf::Texture& buttonPressedTexture, sf::Texture& backgroundScreen, sf::Texture& rulesBackground)
{
	mStartScreen = startScreen;
	mEndScreen = endScreen;
	mButtonTexture = new sf::Texture;
	mButtonPressedTexture = new sf::Texture;
	mRulesBackground = new sf::Texture;
	mBackgroundScreen = new sf::Texture;
	mButtonTexture = &buttonTexture;
	mButtonPressedTexture = &buttonPressedTexture;
	mRulesBackground = &rulesBackground;
	mBackgroundScreen = &backgroundScreen;

	// Display the End Screen
	if (mEndScreen && !mStartScreen)
	{
		mUpPressed = false;
		mDownPressed = false;
		mEnterPressed = false;
		mQuit = false;
		mPage1 = false;
		mPage2 = true;
		mRules = false;
		mStartScreen = true;
		scoreBoard = new sf::RectangleShape;

		// Building the End Display Box
		scoreBoard->setSize(sf::Vector2f(1000, 650));
		scoreBoard->setTexture(&backgroundScreen);
		scoreBoard->setOrigin(sf::Vector2f(500, 325));
		scoreBoard->setPosition(640, 420);

		// Building the Static Ending Text Message
		mStartDisplay = new sf::Text;
		mStartDisplay->setString("You've Caught All The Cheese!");
		mStartDisplay->setFont(font);
		mStartDisplay->setCharacterSize(62);
		mStartDisplay->setColor(sf::Color::Black);
		mStartDisplay->setPosition(sf::Vector2f(245, 250));

		// Building the Static Score Value-Based Text Message
		mScoreStatic = new sf::Text;
		mScoreStatic->setFont(font);
		mScoreStatic->setCharacterSize(22);
		mScoreStatic->setColor(sf::Color::Black);
		if (score <= 0)
		{
			mScoreStatic->setString("Too much poison and too many Cat Claws!\nYou're a dead Mouse!");
			mScoreStatic->setPosition(sf::Vector2f(400, 375));
		}
		else if (score > 0 && score <= 50)
		{
			mScoreStatic->setString("Hardly any cheese at all!\nYou're a starving Mouse!");
			mScoreStatic->setPosition(sf::Vector2f(400, 375));
		}
		else if (score > 50 && score <= 100)
		{
			mScoreStatic->setString("You got a lot of cheese!\nYou're a well-fed Mouse!");
			mScoreStatic->setPosition(sf::Vector2f(400, 375));
		}
		else if (score > 100 && score <= 150)
		{
			mScoreStatic->setString("You got so much cheese!\nYou're a fat Mouse!");
			mScoreStatic->setPosition(sf::Vector2f(400, 375));
		}
		else if (score > 151)
		{
			mScoreStatic->setString("You're the Fat Cat of Mice!");
			mScoreStatic->setPosition(sf::Vector2f(400, 375));
		}

		// Building the Score Value Display	
		mScore = new sf::Text;
		mScore->setFont(font);
		mScore->setCharacterSize(35);
		mScore->setColor(sf::Color::Black);
		mScoreString = std::to_string(score);
		mScore->setString(mScoreString);
		mScore->setPosition(sf::Vector2f(400, 430));

		// Building the Buttons
		for (int i = 0; i < 4; i++)
		{
			buttons[i] = new Button;
			buttons[i]->shape.setSize(sf::Vector2f(172, 55));
			buttons[i]->shape.setTexture(&buttonTexture);
			buttons[i]->text.setFont(font);
			buttons[i]->text.setCharacterSize(35);
			buttons[i]->text.setColor(sf::Color::Black);
			buttons[i]->selected = false;
		}

		buttons[0]->shape.setPosition(sf::Vector2f(560, 375));
		buttons[0]->shape.setTexture(&buttonPressedTexture);
		buttons[0]->text.setString("Play");
		buttons[0]->text.setPosition(sf::Vector2f(610, 380));
		buttons[0]->selected = true;
		buttons[0]->type = 0;

		buttons[1]->shape.setPosition(sf::Vector2f(560, 450));
		buttons[1]->text.setString("Rules");
		buttons[1]->text.setPosition(sf::Vector2f(602, 455));
		buttons[1]->type = 1;

		buttons[2]->shape.setPosition(sf::Vector2f(560, 525));
		buttons[2]->text.setString("Quit");
		buttons[2]->text.setPosition(sf::Vector2f(610, 530));
		buttons[2]->type = 2;

		buttons[3]->shape.setPosition(sf::Vector2f(560, 525));
		buttons[3]->text.setString("Back");
		buttons[3]->text.setPosition(sf::Vector2f(610, 530));
		buttons[3]->type = 3;


		buttons[0]->shape.setTexture(&buttonTexture);
		buttons[0]->selected = false;

		buttons[2]->shape.setTexture(&buttonPressedTexture);
		buttons[2]->text.setString("Back");
		buttons[2]->selected = true;

	}
	// Display the Start Screen
	else if (mStartScreen && !mEndScreen)
	{
		mUpPressed = false;
		mDownPressed = false;
		mEnterPressed = false;
		mQuit = false;
		mPage1 = true;
		mPage2 = false;
		mRules = true;
		scoreBoard = new sf::RectangleShape;

		// Building the Start Display
		scoreBoard->setSize(sf::Vector2f(1000, 650));
		scoreBoard->setTexture(&backgroundScreen);
		scoreBoard->setOrigin(sf::Vector2f(500, 325));
		scoreBoard->setPosition(640, 420);

		// Building the Static Text
		mStartDisplay = new sf::Text;
		mStartDisplay->setString("Cheese Chaser");
		mStartDisplay->setFont(font);
		mStartDisplay->setCharacterSize(98);
		mStartDisplay->setColor(sf::Color::Black);
		mStartDisplay->setPosition(sf::Vector2f(325, 200));

		// Building the Buttons
		for (int i = 0; i < 4; i++)
		{
			buttons[i] = new Button;
			buttons[i]->shape.setSize(sf::Vector2f(172, 55));
			buttons[i]->shape.setTexture(&buttonTexture);
			buttons[i]->text.setFont(font);
			buttons[i]->text.setCharacterSize(35);
			buttons[i]->text.setColor(sf::Color::Black);
			buttons[i]->selected = false;
		}

		buttons[0]->shape.setPosition(sf::Vector2f(560, 375));
		buttons[0]->shape.setTexture(&buttonPressedTexture);
		buttons[0]->text.setString("Play");
		buttons[0]->text.setPosition(sf::Vector2f(610, 380));
		buttons[0]->selected = true;
		buttons[0]->type = 0;

		buttons[1]->shape.setPosition(sf::Vector2f(560, 450));
		buttons[1]->text.setString("Rules");
		buttons[1]->text.setPosition(sf::Vector2f(602, 455));
		buttons[1]->type = 1;

		buttons[2]->shape.setPosition(sf::Vector2f(560, 525));
		buttons[2]->text.setString("Quit");
		buttons[2]->text.setPosition(sf::Vector2f(615, 530));
		buttons[2]->type = 2;

		buttons[3]->shape.setPosition(sf::Vector2f(560, 525));
		buttons[3]->text.setString("Back");
		buttons[3]->text.setPosition(sf::Vector2f(610, 530));
		buttons[3]->type = 3;


		// Building the Static Score Text
		mScoreStatic = new sf::Text;
		mScoreStatic->setString("Score");
		mScoreStatic->setFont(font);
		mScoreStatic->setCharacterSize(22);
		mScoreStatic->setColor(sf::Color::Black);
		mScoreStatic->setPosition(sf::Vector2f(40, 37));

		// Building the Initial Score Display
		mScore = new sf::Text;
		mScore->setFont(font);
		mScore->setCharacterSize(22);
		mScore->setColor(sf::Color::Black);
		mScore->setString("0");
		mScore->setPosition(sf::Vector2f(170, 37));
	}
	// Display the Main Game Display
	else
	{
		scoreBoard = new sf::RectangleShape;

		// Building the Scoreboard
		scoreBoard->setSize(sf::Vector2f(250, 50));
		scoreBoard->setOutlineColor(sf::Color::Black);
		scoreBoard->setOutlineThickness(3);
		scoreBoard->setFillColor(sf::Color::White);
		scoreBoard->setPosition(25, 25);

		// Building the Static Score Text
		mScoreStatic = new sf::Text;
		mScoreStatic->setString("Score");
		mScoreStatic->setFont(font);
		mScoreStatic->setCharacterSize(44);
		mScoreStatic->setColor(sf::Color::Black);
		mScoreStatic->setPosition(sf::Vector2f(40, 22));

		// Building the Initial Score Display
		mScore = new sf::Text;
		mScore->setFont(font);
		mScore->setCharacterSize(44);
		mScore->setColor(sf::Color::Black);
		mScore->setString("0");
		mScore->setPosition(sf::Vector2f(195, 22));
	}
}

void UI::keyUp()
{
	// Check to see if Up arrow key, Down arrow key are NOT being pressed
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mUp = false;
		mUpPressed = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mDown = false;
		mDownPressed = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		mEnter = false;
		mEnterPressed = false;
	}
}

void UI::keyDown()
{
	// Check to see if Up arrow key, Down arrow key ARE being pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mUp = true;
		printf("\nPressed Up");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mDown = true;
		printf("\nPressed Down");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		mEnter = true;
		printf("\nSelection Chosen");
	}
}

void UI::Update(sf::RenderWindow* window, int score)
{
	//=======================  CHANGE mStartScreen TO FALSE TO START MAIN GAME  ===========================//
	// Button Interaction on Ending Screen
	if (mStartScreen && mPage2)
	{
		buttons[0]->shape.setPosition(sf::Vector2f(560, 600));
		buttons[0]->text.setPosition(sf::Vector2f(610, 605));

		keyUp();
		keyDown();

		if (mDown && !mUp && !mDownPressed)
		{
			printf("\nDown!");

			if (buttons[0]->selected)
			{
				printf("\nFound Selected Button");

				buttons[0]->shape.setTexture(mButtonTexture);
				buttons[0]->selected = false;
				buttons[2]->shape.setTexture(mButtonPressedTexture);
				buttons[2]->selected = true;
				mDownPressed = true;
				//break;
			}
			else if (buttons[2]->selected)
			{
				buttons[2]->shape.setTexture(mButtonTexture);
				buttons[2]->selected = false;
				buttons[0]->shape.setTexture(mButtonPressedTexture);
				buttons[0]->selected = true;
				mDownPressed = true;
				//break;	
			}
		}
		if (!mDown && mUp && !mUpPressed)
		{
			if (buttons[0]->selected)
			{
				printf("\nFound Selected Button");
				buttons[0]->shape.setTexture(mButtonTexture);
				buttons[0]->selected = false;
				buttons[2]->shape.setTexture(mButtonPressedTexture);
				buttons[2]->selected = true;
				mUpPressed = true;
				//break;
			}
			else if (buttons[2]->selected)
			{
				buttons[2]->shape.setTexture(mButtonTexture);
				buttons[2]->selected = false;
				buttons[0]->shape.setTexture(mButtonPressedTexture);
				buttons[0]->selected = true;
				mUpPressed = true;
				//break;	
			}
		}
		if (mEnter && !mEnterPressed)
		{
			if (buttons[0]->selected)
			{
				mStartScreen = false;
			}
			else if (buttons[2]->selected)
			{
				mPage1 = true;
				mPage2 = false;
			}

			mEnterPressed = true;
		}
	}
	// Button Interaction on Opening Screen
	else if (mStartScreen && mPage1)
	{
		buttons[0]->shape.setPosition(sf::Vector2f(560, 375));
		buttons[0]->text.setPosition(sf::Vector2f(610, 380));

		buttons[2]->text.setString("Quit");

		mStartDisplay->setString("Cheese Chaser");
		mStartDisplay->setCharacterSize(98);
		mStartDisplay->setPosition(sf::Vector2f(325, 200));

		keyUp();
		keyDown();

		mRules = true;

		// Down Arrow Pressed
		if (mDown && !mUp && !mDownPressed)
		{
			printf("\nDown!");
			for (int i = 0; i < 3; i++)
			{
				if (buttons[i]->selected)
				{
					printf("\nFound Selected Button");
					if (i == 2)
					{
						buttons[i]->shape.setTexture(mButtonTexture);
						buttons[i]->selected = false;
						buttons[0]->shape.setTexture(mButtonPressedTexture);
						buttons[0]->selected = true;
						mDownPressed = true;
						break;
					}
					else if (i < 2)
					{
						buttons[i]->shape.setTexture(mButtonTexture);
						buttons[i]->selected = false;
						buttons[i + 1]->shape.setTexture(mButtonPressedTexture);
						buttons[i + 1]->selected = true;
						mDownPressed = true;
						break;
					}
				}
			}
		}
		// Up Arrow Pressed
		if (!mDown && mUp && !mUpPressed)
		{
			printf("\nDown!");
			for (int i = 0; i < 3; i++)
			{
				if (buttons[i]->selected)
				{
					printf("\nFound Selected Button");
					if (i == 0)
					{
						buttons[i]->shape.setTexture(mButtonTexture);
						buttons[i]->selected = false;
						buttons[2]->shape.setTexture(mButtonPressedTexture);
						buttons[2]->selected = true;
						mUpPressed = true;
						break;
					}
					else if (i > 0)
					{
						buttons[i]->shape.setTexture(mButtonTexture);
						buttons[i]->selected = false;
						buttons[i - 1]->shape.setTexture(mButtonPressedTexture);
						buttons[i - 1]->selected = true;
						mUpPressed = true;
						break;
					}
				}
			}
		}
		if (mEnter && !mEnterPressed)
		{
			printf("\nEnter has been Pressed");
			for (int i = 0; i < 3; i++)
			{
				if (buttons[i]->selected)
				{
					printf("\nFound Selected Button");
					if (buttons[i]->type == 0)
					{
						mStartScreen = false;
						printf("\nPlay Selected");
					}
					else if (buttons[i]->type == 1)
					{
						mPage1 = false;
						printf("\nRules Selected");
					}
					else if (buttons[i]->type == 2)
					{
						printf("\nQuit Selected");
						mQuit = true;
					}
				}
			}

			mEnterPressed = true;
		}
	}
	// Button Interaction on Rules Screen
	else if (mStartScreen && !mPage1)
	{
		keyUp();
		keyDown();

		if (mRules)
		{
			scoreBoard->setTexture(mRulesBackground);

			buttons[0]->shape.setPosition(sf::Vector2f(560, 600));
			buttons[0]->text.setPosition(sf::Vector2f(610, 605));

			buttons[3]->shape.setTexture(mButtonPressedTexture);
			buttons[3]->selected = true;
			mRules = false;
		}

		if (mDown && !mUp && !mDownPressed)
		{
			printf("\nDown!");

			if (buttons[0]->selected)
			{
				printf("\nFound Selected Button");

				buttons[0]->shape.setTexture(mButtonTexture);
				buttons[0]->selected = false;
				buttons[3]->shape.setTexture(mButtonPressedTexture);
				buttons[3]->selected = true;
				mDownPressed = true;
				//break;
			}
			else if (buttons[3]->selected)
			{
				buttons[3]->shape.setTexture(mButtonTexture);
				buttons[3]->selected = false;
				buttons[0]->shape.setTexture(mButtonPressedTexture);
				buttons[0]->selected = true;
				mDownPressed = true;
				//break;	
			}
		}
		if (!mDown && mUp && !mUpPressed)
		{
			if (buttons[0]->selected)
			{
				printf("\nFound Selected Button");
				buttons[0]->shape.setTexture(mButtonTexture);
				buttons[0]->selected = false;
				buttons[3]->shape.setTexture(mButtonPressedTexture);
				buttons[3]->selected = true;
				mUpPressed = true;
				//break;
			}
			else if (buttons[3]->selected)
			{
				buttons[3]->shape.setTexture(mButtonTexture);
				buttons[3]->selected = false;
				buttons[0]->shape.setTexture(mButtonPressedTexture);
				buttons[0]->selected = true;
				mUpPressed = true;
				//break;	
			}
		}
		if (mEnter && !mEnterPressed)
		{
			if (buttons[0]->selected)
			{
				mStartScreen = false;
			}
			else if (buttons[3]->selected)
			{
				scoreBoard->setTexture(mBackgroundScreen);
				mPage1 = true;
			}

			mEnterPressed = true;
		}
	}
	else if (!mStartScreen)
	{
		// Convert the int score to a String and set for Display
		mScoreString = std::to_string(score);
		mScore->setString(mScoreString);
	}
}

void UI::Draw(sf::RenderWindow* window)
{
	// Display the Opening Screen
	if (mStartScreen && mPage1 && !mPage2)
	{
		window->draw(*scoreBoard);
		window->draw(*mStartDisplay);

		for (int i = 0; i < 3; i++)
		{
			window->draw(buttons[i]->shape);
			window->draw(buttons[i]->text);
		}
	}
	// Display the End Screen
	else if (mStartScreen && mPage2 && !mPage1)
	{
		window->draw(*scoreBoard);
		window->draw(*mStartDisplay);

		window->draw(buttons[0]->shape);
		window->draw(buttons[0]->text);
		window->draw(buttons[2]->shape);
		window->draw(buttons[2]->text);

		window->draw(*mScoreStatic);
		window->draw(*mScore);
	}
	// Display the Rules Screen
	else if (mStartScreen && !mPage1)
	{
		window->draw(*scoreBoard);
		for (int i = 0; i < 6; i += 3)
		{
			window->draw(buttons[i]->shape);
			window->draw(buttons[i]->text);
		}
	}
	// Dispaly the Main Game Screen
	else
	{
		window->draw(*scoreBoard);
		window->draw(*mScoreStatic);
		window->draw(*mScore);
	}
}

//=================================== LevelScreen Class============================//
// Display to announce new Level has begun
class LevelScreen
{
public:
	LevelScreen(int level, int score, sf::Texture& background, sf::Font& font);
	void Draw(sf::RenderWindow* window);

private:
	sf::RectangleShape* m_textBox;
	sf::Text* m_message;
	sf::Text* m_levelMessage;
	std::string m_level;
};

LevelScreen::LevelScreen(int level, int score, sf::Texture& background, sf::Font& font)
{
	// Local Variables
	m_textBox = new sf::RectangleShape;
	m_levelMessage = new sf::Text;

	// Convert Current Level from int to string
	m_level = std::to_string(level);

	// Building the Display Text Box
	m_textBox->setSize(sf::Vector2f(500, 250));
	m_textBox->setTexture(&background);
	m_textBox->setOrigin(sf::Vector2f(250, 125));
	m_textBox->setPosition(sf::Vector2f(640, 420));

	// Building the Static and Dynamic Level Text Displays
	m_message = new sf::Text;
	m_message->setString("LEVEL ");
	m_message->setFont(font);
	m_message->setCharacterSize(40);
	m_message->setColor(sf::Color::Black);
	m_message->setPosition(sf::Vector2f(530, 395));
	m_levelMessage->setString(m_level);
	m_levelMessage->setFont(font);
	m_levelMessage->setCharacterSize(40);
	m_levelMessage->setColor(sf::Color::Black);
	m_levelMessage->setPosition(sf::Vector2f(720, 395));

	//if (level == 5)
	//{
	//	m_textBox->setSize(sf::Vector2f(900, 700));
	//	m_textBox->setOrigin(sf::Vector2f(450, 350));
	//}
}

void LevelScreen::Draw(sf::RenderWindow* window)
{
	window->draw(*m_textBox);
	window->draw(*m_message);
	window->draw(*m_levelMessage);
}


//=================================== Game Class ==================================// 

class Game
{
public:
	Game(sf::RenderWindow* window, int level, int score, bool strtScreen, bool endOfGame, sf::Font& font, sf::Texture& cheeseTexture, sf::Texture& poisonTexture, sf::Texture& mouseTrapTexture, sf::Texture& playerTexture, sf::Texture& runningCatTexture, sf::Texture& buttonTexture, sf::Texture& buttonTexturePressed, sf::Texture& openingBackgroundTexture, sf::Texture* backgrounds[], sf::Texture& rulesBackground);
	bool collision(sf::RectangleShape* obj1, sf::RectangleShape* obj2);
	bool groundCheck(sf::RectangleShape* obj1, sf::RectangleShape* obj2);
	void Update(sf::RenderWindow* window, sf::Time dt, sf::Sound* catSound, sf::Sound* pickUpSound, sf::Sound* trapSound);
	void Draw(sf::RenderWindow* window);
	int m_score;
	bool m_startScreen;
	bool m_startGame;
	bool yesQuit;
	bool endGame;
private:
	bool m_grounded;
	bool hitByCat;
	std::vector <GameObject*> gameManager;
	UI* gameUI;
	sf::Clock m_Time;
	sf::Time m_Timer;
	sf::Texture* m_backgrounds[5];
	sf::Texture* m_level1Texture;
	sf::Texture* m_level2Texture;
	sf::Texture* m_level3Texture;
	sf::Texture* m_level4Texture;
	sf::Texture* m_level5Texture;
	sf::Texture m_catTexture;
	sf::RectangleShape m_levelBackground;
	int m_level;
	float m_levelTime;
	int m_groundXPos;
	int m_groundYPos;
	int m_platformLength;
};


Game::Game(sf::RenderWindow* window, int level, int score, bool strtScreen, bool endOfGame, sf::Font& font, sf::Texture& cheeseTexture, sf::Texture& poisonTexture, sf::Texture& mouseTrapTexture, sf::Texture& playerTexture, sf::Texture& runningCatTexture, sf::Texture& buttonTexture, sf::Texture& buttonTexturePressed, sf::Texture& openingBackgroundTexture, sf::Texture* backgrounds[], sf::Texture& rulesBackground)
{
	m_catTexture = runningCatTexture;

	m_level1Texture = new sf::Texture;
	m_level2Texture = new sf::Texture;
	m_level3Texture = new sf::Texture;
	m_level4Texture = new sf::Texture;
	m_level5Texture = new sf::Texture;

	if (!m_level1Texture->loadFromFile("Level1.png", sf::IntRect(0, 0, 1280, 840)))
	{
		printf("\nFailed to load Level 1 Texture");
	}
	if (!m_level2Texture->loadFromFile("Level2.png", sf::IntRect(0, 0, 1280, 840)))
	{
		printf("\nFailed to load Level 2 Texture");
	}
	if (!m_level3Texture->loadFromFile("Level3.png", sf::IntRect(0, 0, 1280, 840)))
	{
		printf("\nFailed to load Level 3 Texture");
	}
	if (!m_level4Texture->loadFromFile("Level4.png", sf::IntRect(0, 0, 1280, 840)))
	{
		printf("\nFailed to load Level 4 Texture");
	}
	if (!m_level5Texture->loadFromFile("Level5.png", sf::IntRect(0, 0, 1280, 840)))
	{
		printf("\nFailed to load Level 5 Texture");
	}

	m_startGame = false;
	yesQuit = false;
	endGame = endOfGame;
	m_startScreen = strtScreen;

	// If Starting Screen or Ending Screen
	if (m_startScreen)
	{
		if (endGame)
		{
			gameUI = new UI(false, true, score, font, buttonTexture, buttonTexturePressed, openingBackgroundTexture, rulesBackground);
		}
		else if (!endGame)
		{
			gameUI = new UI(true, false, 0, font, buttonTexture, buttonTexturePressed, openingBackgroundTexture, rulesBackground);
		}
	}
	else
	{
		m_levelBackground.setSize(sf::Vector2f(1280, 840));
		endGame = false;
		delete gameUI;
		// Local Variables
		srand(static_cast<unsigned int>(time(0)));
		m_level = level;
		m_score = score;
		gameUI = new UI(false, false, 0, font, buttonTexture, buttonTexturePressed, openingBackgroundTexture, rulesBackground);
		m_grounded = false;
		hitByCat = false;
		// Restart the Clock for use in Update Function
		m_Time.restart();

		// Create the gameManager vector and fill with Spawners and the Player
		for (int i = 200; i < 500; i += 200)
		{
			int randomNumber = rand();
			int roll = (randomNumber % 800) + 100;
			gameManager.push_back(new Spawner(sf::Vector2f(200 + i, -20), roll, m_level, &cheeseTexture,  &poisonTexture,  &mouseTrapTexture));
		}

		gameManager.push_back(new Ground(sf::Vector2f(0, 775), 1300, 35, m_level, true));

		// Create new Platforms for Level 1
		if (m_level == 1)
		{
			m_levelBackground.setTexture(m_level1Texture);
			gameManager.push_back(new Ground(sf::Vector2f(270, 535), 280, 15, m_level, false));
			//gameManager.push_back(new Ground(sf::Vector2f(300, 300), 200, 15, m_level, false));
			gameManager.push_back(new Ground(sf::Vector2f(0, 342), 175, 15, m_level, false));
			gameManager.push_back(new Ground(sf::Vector2f(605, 230), 350, 15, m_level, false));
			gameManager.push_back(new Ground(sf::Vector2f(955, 620), 150, 15, m_level, false));
		}
		else if (m_level == 2)
		{
			m_levelBackground.setTexture(m_level2Texture);
			gameManager.push_back(new Ground(sf::Vector2f(410, 607), 475, 15, m_level, false));
			gameManager.push_back(new Ground(sf::Vector2f(980, 435), 200, 15, m_level, false));
			//gameManager.push_back(new Ground(sf::Vector2f(400, 100), 125, 15, m_level, false));
			gameManager.push_back(new Ground(sf::Vector2f(100, 630), 235, 15, m_level, false));
			gameManager.push_back(new Ground(sf::Vector2f(950, 275), 250, 15, m_level, false));
		}
		else if (m_level == 3)
		{
			m_levelBackground.setTexture(m_level3Texture);
			gameManager.push_back(new Ground(sf::Vector2f(30, 495), 300, 15, m_level, false));
			gameManager.push_back(new Ground(sf::Vector2f(505, 590), 300, 15, m_level, false));
			gameManager.push_back(new Ground(sf::Vector2f(30, 220), 270, 15, m_level, false));
			gameManager.push_back(new Ground(sf::Vector2f(1175, 400), 100, 15, m_level, false));
		}
		else if (m_level == 4)
		{
			m_levelBackground.setTexture(m_level4Texture);
			gameManager.push_back(new Ground(sf::Vector2f(665, 550), 470, 15, m_level, false));
			gameManager.push_back(new Ground(sf::Vector2f(35, 480), 250, 15, m_level, false));
			gameManager.push_back(new Ground(sf::Vector2f(380, 335), 820, 15, m_level, false));
		}
		else if (m_level == 5)
		{
			m_levelBackground.setTexture(m_level5Texture);
			gameManager.push_back(new Ground(sf::Vector2f(70, 495), 100, 15, m_level, true));
			gameManager.push_back(new Ground(sf::Vector2f(425, 175), 300, 15, m_level, false));
			gameManager.push_back(new Ground(sf::Vector2f(500, 495), 155, 15, m_level, true));
			gameManager.push_back(new Ground(sf::Vector2f(660, 545), 210, 15, m_level, true));
			gameManager.push_back(new Ground(sf::Vector2f(970, 272), 80, 15, m_level, true));
		}

		gameManager.push_back(new Player(m_level));
	}
}

bool Game::collision(sf::RectangleShape* obj1, sf::RectangleShape* obj2)
{
	return obj1->getGlobalBounds().intersects(obj2->getGlobalBounds());
}

bool Game::groundCheck(sf::RectangleShape* obj1, sf::RectangleShape* obj2)
{
	return obj1->getGlobalBounds().intersects(obj2->getGlobalBounds());
}

void Game::Update(sf::RenderWindow* window, sf::Time dt, sf::Sound* catSound, sf::Sound* pickUpSound, sf::Sound* trapSound)
{
	if (gameUI->mStartScreen)
	{
		gameUI->Update(window, m_score);

		if (gameUI->mQuit)
		{
			yesQuit = true;
		}

		if (!gameUI->mStartScreen)
		{
			m_startGame = true;
		}
	}
	else
	{
		// Get elapsed time and set value as a float
		m_Timer = m_Time.getElapsedTime();
		m_levelTime = m_Timer.asSeconds();

		m_grounded = false;

		if (m_level > 1)
		{
			if (m_levelTime > 15)
			{
				hitByCat = false;
				gameManager.push_back(new Cat(&m_catTexture));
				m_Time.restart();
			}
		}

		// Update all objects in gameManager vector, and test for individual collisions
		for (int i = 0; i < gameManager.size(); i++)
		{
			gameManager[i]->Update(window, dt);

			// If current gameManager object is the player, start comparing to the rest of the gameManager objects
			if (gameManager[i]->objType == 2)
			{
				for (int j = 0; j < gameManager.size(); j++)
				{
					// If current gameManager object is a Spawner, access m_Cheeses vector to compare individual Cheese objects
					if (gameManager[j]->objType == 1)
					{
						for (int z = 0; z < gameManager[j]->m_Cheeses.size(); z++)
						{
							// Cycle through m_Cheeses vector of the selected Spawner and test for collision with Player
							if (collision(gameManager[i]->m_Object, gameManager[j]->m_Cheeses[z]->m_Object))
							{
								printf("\nKilled a Cheese");
								gameManager[j]->m_Cheeses[z]->deadBomb = true;
								m_score += gameManager[j]->m_Cheeses[z]->cheeseScore;
								pickUpSound->play();

								// Test if Cheese is a trap block, if so, set player trapped variable to true
								if (gameManager[j]->m_Cheeses[z]->isTrap)
								{
									gameManager[i]->trapped = true;
									trapSound->play();
									printf("\nTrapped set to true");
								}
							}
						}
					}

					// Check if player object is touching a ground platform
					if (!gameManager[i]->spaceBar) // =========================>>>>>  If player is holding space bar down: does not complete ground check and player object falls through ground
					{
						if (gameManager[j]->objType == 3 && groundCheck(gameManager[i]->m_Object, gameManager[j]->m_Object))
						{
							// If player object is colliding with the platform, hold its Y position to keep player object on the platform
							gameManager[i]->onPlatform = true;
							gameManager[i]->onGround = true;
							m_grounded = true;
							gameManager[i]->m_Object->setPosition(gameManager[i]->m_Object->getPosition().x, gameManager[j]->m_Object->getPosition().y - 15);
							gameManager[i]->publicSprite->setPosition(gameManager[i]->m_Object->getPosition().x, gameManager[j]->m_Object->getPosition().y - 15);
							//printf("\nOn Ground");
							// If the player object is colliding with a platform and not the Base Ground, set motion to match speed and motion of 
							// moving platform
							if (!gameManager[j]->isBottomGround)
							{
								gameManager[i]->reverseMotion = gameManager[j]->reverseMotion;
								gameManager[i]->speed = gameManager[j]->speed;
								gameManager[i]->isBottomGround = true;
							}
							else
							{
								gameManager[i]->speed = 0;
							}
						}
					}

					// If Player Object not colliding with the ground platform, onGround = false
					if (gameManager[j]->objType == 3 && !groundCheck(gameManager[i]->m_Object, gameManager[j]->m_Object) && !m_grounded)
					{
						gameManager[i]->onGround = false;
						//printf("\nNot on Ground");
					}

					// If Player Object collides with the cat, m_score -= 100
					if (gameManager[j]->objType == 4 && collision(gameManager[i]->m_Object, gameManager[j]->m_Object) && !hitByCat)
					{
						hitByCat = true;
						catSound->play();
						m_score -= 100;
					}
				}
			}
		}

		gameUI->Update(window, m_score);
	}
}

void Game::Draw(sf::RenderWindow* window)
{
	window->draw(m_levelBackground);

	for (int i = 0; i < gameManager.size(); i++)
	{
		gameManager[i]->Draw(window);
	}

	gameUI->Draw(window);
}


sf::Font font;

sf::Texture cheeseTexture;
sf::Texture poisonTexture;
sf::Texture mouseTrapTexture;
sf::Texture playerTexture;
sf::Texture runningCatTexture;
sf::Texture ButtonTexture;
sf::Texture ButtonTexturePressed;
sf::Texture openingBackgroundTexture;
sf::Texture rulesBackgroundTexture;
sf::Texture level1Texture;
sf::Texture level2Texture;
sf::Texture level3Texture;
sf::Texture level4Texture;
sf::Texture level5Texture;
sf::Texture* backgrounds[5];

sf::SoundBuffer mouseJumpBuffer;
sf::SoundBuffer pickUpBuffer;
sf::SoundBuffer trapBuffer;
sf::SoundBuffer catBuffer;
sf::Sound mouseJumpSound;
sf::Sound pickUpSound;
sf::Sound trapSound;
sf::Sound catSound;
sf::Music gameMusic;


bool InitTextures();
bool InitSounds();

//================================= Main Function =================================//


int _tmain(int argc, _TCHAR* argv[])
{
	if (!InitTextures())
	{
		printf("\nFailed to load Textures");
		return 0;
	}
	if (!InitSounds())
	{
		printf("\nFailed to load Sounds");
		return 0;
	}


	// Create the Game Window and seed the random number generator
	sf::RenderWindow window(sf::VideoMode(1280, 840), "Cheese Chaser");
	srand(static_cast<unsigned int>(time(0)));

	// Create the Game object and LevelScreen object
	Game* myGame = new Game(&window, 1, 0, true, false, font, cheeseTexture, poisonTexture, mouseTrapTexture, playerTexture, runningCatTexture, ButtonTexture, ButtonTexturePressed, openingBackgroundTexture, backgrounds, rulesBackgroundTexture);
	LevelScreen* newLevel;

	// Game clocks and timers, and local variables
	sf::Clock clock;
	sf::Clock time;
	sf::Time timer;
	bool levelUp = false;
	bool mStartScreen = true;
	bool endingGame = false;
	bool spaceBarPressed = false;
	int level = 1;
	int score = 0;
	float levelTimer;
	newLevel = new LevelScreen(level, score, openingBackgroundTexture, font);

	time.restart();
	gameMusic.play();

	// While the window is not closed by the user:
	while (window.isOpen())
	{
		sf::Event event;
		// Check to see if close-window button has been pushed
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space && !spaceBarPressed)
				{
					mouseJumpSound.play();
					spaceBarPressed = true;
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					spaceBarPressed = false;
				}
			}
		}

		// Get the elapsed time for game timer in seconds as a float variable
		timer = time.getElapsedTime();
		levelTimer = timer.asSeconds();

		// Restart the internal Game clock and clear the window of previous displays
		sf::Time dt = clock.restart();
		window.clear();

		if (mStartScreen)
		{
			myGame->Update(&window, dt, &catSound, &pickUpSound, &trapSound);
			myGame->Draw(&window);

			// If the Player has selected to Play the game, Create new Game with all the Game objects
			if (myGame->m_startGame)
			{
				time.restart();
				mStartScreen = false;
				myGame->endGame = false;
				endingGame = false;
				levelUp = false;
				levelTimer = 0.0f;
				level = 1;
				score = 0;
				delete myGame;
				myGame = new Game(&window, 1, 0, false, false, font, cheeseTexture, poisonTexture, mouseTrapTexture, playerTexture, runningCatTexture, ButtonTexture, ButtonTexturePressed, openingBackgroundTexture, backgrounds, rulesBackgroundTexture);
			}
			// If the Player has selected to quit, return 0 to exit loop and exit program
			if (myGame->yesQuit)
			{
				return 0;
			}
			// If the Player has finished the last level of the game, Create new Game with appropriate displays for Final Screen
			if (myGame->endGame && !endingGame)
			{
				endingGame = true;
				myGame->m_startGame = false;
				delete myGame;
				myGame = new Game(&window, 5, score, true, true, font, cheeseTexture, poisonTexture, mouseTrapTexture, playerTexture, runningCatTexture, ButtonTexture, ButtonTexturePressed, openingBackgroundTexture, backgrounds, rulesBackgroundTexture);
			}
		}
		else
		{
			// If the level timer is over LEVEL_TIME, save current score in variable, set levelUp to true, and create a new LevelScreen
			if (levelTimer > LEVEL_TIME && !levelUp)
			{
				score = myGame->m_score;
				levelUp = true;
				level++;
				newLevel = new LevelScreen(level, score, openingBackgroundTexture, font);
			}
			// If levelUp is true, display the LevelScreen
			if (levelUp)
			{
				if (level > 5)
				{
					// Display End Screen
					mStartScreen = true;
					myGame->endGame = true;
				}

				newLevel->Draw(&window);
				// if player presses Enter key, Create new level with passed on score value from last level
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					myGame = new Game(&window, level, score, false, false, font, cheeseTexture, poisonTexture, mouseTrapTexture, playerTexture, runningCatTexture, ButtonTexture, ButtonTexturePressed, openingBackgroundTexture, backgrounds, rulesBackgroundTexture);
					levelUp = false;
					time.restart();
					delete newLevel;
				}
			}
			// If levelUp is false, run current version of game
			else if (!levelUp)
			{
				myGame->Update(&window, dt, &catSound, &pickUpSound, &trapSound);
				myGame->Draw(&window);
			}
		}

		window.display();
	}

	return 0;
}


bool InitTextures()
{
	backgrounds[0] = new sf::Texture;
	backgrounds[1] = new sf::Texture;
	backgrounds[2] = new sf::Texture;
	backgrounds[3] = new sf::Texture;
	backgrounds[4] = new sf::Texture;

	if (!cheeseTexture.loadFromFile("normalcheese_sprites.png", sf::IntRect(0, 0, 1024, 261)))
	{
		printf("\nFailed to load Cheese Texture");
		return false;
	}
	if (!poisonTexture.loadFromFile("poisoncheese_sprites.png", sf::IntRect(0, 0, 1024, 417)))
	{
		printf("\nFailed to load Poison Texture");
		return false;
	}
	if (!mouseTrapTexture.loadFromFile("mousetrap.png", sf::IntRect(0, 0, 800, 837)))
	{
		printf("\nFailed to load Mouse Trap Texture");
		return false;
	}
	if (!playerTexture.loadFromFile("RU4By.png", sf::IntRect(0, 0, 641, 119)))
	{
		printf("\nFailed to load Mouse Texture");
		return false;
	}
	if (!runningCatTexture.loadFromFile("runningcat.png", sf::IntRect(0, 0, 1024, 1024)))
	{
		printf("\nFailed to load Cat Texture");
		return false;
	}
	if (!ButtonTexture.loadFromFile("ButtonTexture.png", sf::IntRect(0, 0, 172, 55)))
	{
		printf("\nFailed to load Button Texture");
		return false;
	}
	if (!ButtonTexturePressed.loadFromFile("ButtonTexture_Pressed.png", sf::IntRect(0, 0, 172, 55)))
	{
		printf("\nFailed to load Button Pressed Texture");
		return false;
	}
	if (!openingBackgroundTexture.loadFromFile("OpeningScreen.png", sf::IntRect(0, 0, 1280, 840)))
	{
		printf("\nFailed to load Opening Background Texture");
		return false;
	}
	if (!rulesBackgroundTexture.loadFromFile("RulesScreen.png", sf::IntRect(0, 0, 1280, 840)))
	{
		printf("\nFailed to load Opening Background Texture");
		return false;
	}
	if (!level1Texture.loadFromFile("Level1.png", sf::IntRect(0, 0, 1280, 840)))
	{
		printf("\nFailed to load Level 1 Texture");
		return false;
	}
	if (!level2Texture.loadFromFile("Level2.png", sf::IntRect(0, 0, 1280, 840)))
	{
		printf("\nFailed to load Level 2 Texture");
		return false;
	}
	if (!level3Texture.loadFromFile("Level3.png", sf::IntRect(0, 0, 1280, 840)))
	{
		printf("\nFailed to load Level 3 Texture");
		return false;
	}
	if (!level4Texture.loadFromFile("Level4.png", sf::IntRect(0, 0, 1280, 840)))
	{
		printf("\nFailed to load Level 4 Texture");
		return false;
	}
	if (!level5Texture.loadFromFile("Level5.png", sf::IntRect(0, 0, 1280, 840)))
	{
		printf("\nFailed to load Level 5 Texture");
		return false;
	}

	if (!font.loadFromFile("Disko.ttf"))
	{
		printf("\nFailed to load Font");
		return false;
	}

	backgrounds[0] = &level1Texture;
	backgrounds[1] = &level1Texture;
	backgrounds[2] = &level1Texture;
	backgrounds[3] = &level1Texture;
	backgrounds[4] = &level1Texture;

	return true;
}

bool InitSounds()
{
	if (!mouseJumpBuffer.loadFromFile("MouseJump.wav"))
	{
		printf("\nFailed to load Mouse Jump");
		return false;
	}
	if (!pickUpBuffer.loadFromFile("PickUp.wav"))
	{
		printf("\nFailed to load Mouse Jump");
		return false;
	}
	if (!trapBuffer.loadFromFile("Trap.wav"))
	{
		printf("\nFailed to load Mouse Jump");
		return false;
	}
	if (!catBuffer.loadFromFile("Cat.wav"))
	{
		printf("\nFailed to load Mouse Jump");
		return false;
	}
	if (!gameMusic.openFromFile("GameMusic.ogg"))
	{
		printf("\nFailed to load Game Music");
		return false;
	}
	
	mouseJumpSound.setBuffer(mouseJumpBuffer);
	pickUpSound.setBuffer(pickUpBuffer);
	trapSound.setBuffer(trapBuffer);
	catSound.setBuffer(catBuffer);

	gameMusic.setVolume(35);
	gameMusic.setLoop(true);

	return true;
}
