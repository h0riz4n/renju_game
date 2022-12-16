#include "./includes/GUI.h"
#include "./includes/GameEngine.h"
#include "./includes/Map.h"
#include "./includes/AI.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 900), "Renju Game");

	GUI gui;
	Map map;
	GameEngine eng;
	AI ai;

	while (window.isOpen())
	{
		sf::Event event;

		window.clear(sf::Color(199, 173, 173));

		gui.pauseGame(window);

		map.checkStatus(gui.isPaused);
		eng.checkState(gui.isPaused);
		ai.checkGameState(gui.isPaused);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					gui.startGame();
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					gui.stopGame();
				}
				else
				{
					eng.userTurn(event);

					if (gui.isAi)
					{
						ai.enterEvent(event, eng);
					}
					else
					{
						eng.enterEvent(event);
					}
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				gui.clickMenu(event, window, eng);
			}
		}

		map.drawMap(window);

		gui.drawUsersBlock(window);

		eng.drawChecker(window);

		gui.clickMenu(window);

		eng.drawCheckers(window);

		window.display();
	}

	return 0;
}
