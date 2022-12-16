#ifndef __Map_H
#define __Map_H

#include <SFML/Graphics.hpp>

class Map
{
	private:
		int lines;
		int distance;
		int pos;

		bool mainState;

		sf::RectangleShape rect_vert;
		sf::RectangleShape rect_hor;

	public:

		Map()
		{
			lines = 15;
			distance = 35;
			pos = 80;

			mainState = false;

			rect_vert.setSize(sf::Vector2f(490, 2));
			rect_vert.setFillColor(sf::Color::Black);
			rect_hor.setSize(sf::Vector2f(492, 2));
			rect_hor.setFillColor(sf::Color::Black);
			rect_hor.rotate(90);
		}

		bool checkStatus(bool state)
		{
			mainState = state;
			return state;
		}

		void drawMap(sf::RenderWindow &window)
		{
			int x_pos = pos;
			int y_pos = pos;

			if (mainState)
			{
				for (int i = 0; i < lines; i++, y_pos += distance, x_pos += distance)
				{
					rect_vert.setPosition(pos, y_pos);
					rect_hor.setPosition(x_pos, pos);
					window.draw(rect_vert);
					window.draw(rect_hor);
				}
			}
		}
};

#endif