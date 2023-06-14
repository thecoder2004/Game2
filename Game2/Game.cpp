#include "Game.h"


void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "ERROE::GAME::INITFONTS::Failed to load the fonts" << std::endl;
	};
}

void Game::initText()
{
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(32);
	this->guiText.setString("None");
}

void Game::initVariables()
{
	this->endGame = false;
	this->window = nullptr;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->points = 0;
	this->maxSwapBalls = 15;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "My game", sf::Style::Close |sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

//Constructor and destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}


const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::checkCollision() const
{
	return false;
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

const int Game::randBallType() 
{
	int type = SwagBallTypes::DEFAULT;
	int randValue = rand() % 100;
	if (randValue >= 80)
	{
		type = SwagBallTypes::HEALING;
	}
	else if(randValue >= 60)
	{
		type = SwagBallTypes::DAMAGING;
	}
	return type;
}



//Function
void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		if (sfmlEvent.type == sf::Event::KeyPressed)
		{
			if (sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
		}
		if (sfmlEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::spawnSwagBall()
{
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		if (this->swagBalls.size() < this->maxSwapBalls)
		{
			this->spawnTimerMax = 0.f;
			this->swagBalls.push_back(SwagBall(*this->window, this->randBallType()));
		}
		
	}
	else
		this->spawnTimer += 1.f;
}

void Game::updatePlayer()
{
}

void Game::updateCollision()
{
	for (int i = 0; i < this->swagBalls.size(); ++i)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds()))
		{
			int type = this->swagBalls[i].getType();
			if (type == SwagBallTypes::DEFAULT)
			{
				++this->points;
			}
			else if (type == SwagBallTypes::DAMAGING)
			{
				this->player.takeDamage(1);
			}
			else if (type == SwagBallTypes::HEALING)
			{
				this->player.gainHealth(1);
			}
			this->swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
}

void Game::updateGui()
{
	std::stringstream ss;
	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->player.getHP() << '/' << this->player.getHPMax() << '\n';
		
	this->guiText.setString(ss.str());

}


void Game::update()
{
	this->pollEvents();
	if (this->player.getHP() > 0)
	{
		this->spawnSwagBall();
		this->updatePlayer();
		this->player.update(this->window);
		this->updateCollision();
		this->updateGui();
	}
	
	
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
	//Render stuff
	this->player.render(this->window);
	for (int i = 0; i < this->swagBalls.size(); ++i)
	{
		this->swagBalls[i].render(this->window);
	}
	if (this->player.getHP() <= 0)
	{
		sf::Font endFont;
		endFont.loadFromFile("Fonts/Dosis-Light.ttf");
		sf::Text endText("Game Over!", endFont, 50);
		endText.setFillColor(sf::Color::Magenta);

		sf::FloatRect textRect = endText.getLocalBounds();
		endText.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);


		endText.setPosition(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
		window->draw(endText);
	}
}

void Game::render()
{
	this->window->clear();

	
	this->renderGui(this->window);
	this->window->display();
}
