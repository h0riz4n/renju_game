#ifndef __AI_H
#define __AI_H
#define DIST 35

#include "GameEngine.h"

/*
	Создаём производный класс ИИ от игрового движка.
*/
class AI : public GameEngine
{
	private:
		/*
			Объявляем закрытые переменные
		*/
		bool isNotPaused;											// Значение для проверки состояния игры

		/*
			Объявляем закрытые методы
		*/
		int evalFunc(GameEngine &eng);								// Оценочная функция

		void checkBotTurn(int x, int y, GameEngine &eng);			// Функция для определения хода бота

		void moveBotFunc(int x, int y, GameEngine &eng);			// Функция движения бота

		sf::Vector2i botPosToMove(GameEngine &eng);					// Фукнция изменения хода бота

	public:
		/*
			Объявляем открытые переменные
		*/


		/*
			Объявляем открытые методы
		*/
		AI();						// Конструктор

		~AI();										// Деструктор

		void checkGameState(bool state);

		void enterEvent(sf::Event &event, GameEngine &eng);
};

#endif