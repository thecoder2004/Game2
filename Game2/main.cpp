#include "Game.h"
int main()
{
	//Initialize random seed
	std::srand(static_cast<unsigned>(time(NULL)));
	//Initialize game object
	Game game;

	//Game loop
	while (game.running())
	{
		game.update();
		game.render();
		if (game.getEndGame())
		{
			sf::sleep(sf::seconds(3));
			break;
		}
	}
	//End of application
	
	return 0;
}