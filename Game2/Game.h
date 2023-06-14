#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>
#include "Player.h"
#include "SwagBall.h"
class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;
	Player player;
	std::vector<SwagBall> swagBalls;

	int points;
	sf::Font font;
	sf::Text guiText;
	float spawnTimerMax;
	float spawnTimer;
	int maxSwapBalls;
	void initFonts();
	void initText();
	void initVariables();
	void initWindow();

public:
	//Constructor and destructor
	Game();
	~Game();

	//Accessors

	//Modifiers

	//Functions
	const bool running() const;
	const bool checkCollision() const;
	const bool getEndGame() const;
	const int randBallType();
	void pollEvents();
	void spawnSwagBall();

	void updatePlayer();
	void updateCollision();
	void updateGui();
	void update();

	void renderGui(sf::RenderTarget* target);
	void render();
};

