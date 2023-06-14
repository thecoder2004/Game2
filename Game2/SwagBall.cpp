#include "SwagBall.h"

void SwagBall::initShape(const sf::RenderWindow& window)
{
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
	sf::Color color;
	if (this->type == DEFAULT)
	{
		color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
	}
	else if (this->type == DAMAGING)
	{
		color = sf::Color(sf::Color::Red);
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2);
	}
	else if (this->type == HEALING)
	{
		color = sf::Color(sf::Color::Green);
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2);
	}
	
	this->shape.setFillColor(color);
	this->shape.setPosition(
		static_cast<float>(rand() %(window.getSize().x - (int)this->shape.getGlobalBounds().width)),
		static_cast<float>(rand() %(window.getSize().y - (int)this->shape.getGlobalBounds().height))
	);
}



SwagBall::SwagBall(const sf::RenderWindow& window, int type)
	:type(type)
{
	this->initShape(window);
}

SwagBall::~SwagBall()
{
	
}

const sf::CircleShape& SwagBall::getShape() const
{
	return this->shape;
}

const int& SwagBall::getType() const
{
	return this->type;
}

void SwagBall::update()
{
}

void SwagBall::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
