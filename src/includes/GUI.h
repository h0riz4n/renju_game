#ifndef __GUI_H
#define __GUI_H

#include "GameEngine.h"
#include <SFML/Graphics.hpp>

class GUI
{
	private:
		/*
			Объявляем закрытые переменные
		*/
		sf::Font mainFont, font;						// Шрифты

		sf::Text player, botPlayer, restart, exit;		// Меню

		sf::Text text;									// Тексты

		sf::CircleShape bCircle, wCircle;				// Объекты кругов

		sf::Image bImg, wImg;							// Объекты изображений

		sf::Texture bTexture, wTexture;					// Объекты текстур
		sf::Texture *black, *white;						// Объекты указателей на текстур

		sf::Text user1, user2, gameTitle;				// Тексты

		/*
			Объявляем закрытые методы
		*/
		void fillCircles();								// Метод заполнения кругов в меню-блоке

		void fillUsersBlock();							// Метод заполнения меню блоков

		void defaultSetting();							// Функция перехода к дефолтным настройкам

		void nullGame(GameEngine &eng);					// Функция обнуления игры

		void setImg(sf::Image &img, std::string src, sf::Texture &texture);			// Функция для задания изображений

		void fillSet(sf::Text &text, std::string txt, int x, int y, int charSize);	// Функция заполнения текстов

		void changeTxtByPos(sf::Text &txt, int x, int y, int width, int height, sf::RenderWindow &window);	// Функция реакции текстов на положении мыши

	public:

		/*
			Объявляем открытые переменные
		*/
		bool isPaused;						// Состояние игры
		bool isAi;							// Тип игры (ИИ или 2 игрока)

		/*
			Объявляем открытые методы
		*/
		GUI();

		void drawUsersBlock(sf::RenderWindow &window);			// Метод зарисовки меню-блоков

		void drawMainMenu(sf::RenderWindow &window);			// Функция зарисовки меню

		void pauseGame(sf::RenderWindow &window);				// Функция паузы игры

		// Перегрузка
		void clickMenu(sf::RenderWindow &window);				// Функция реакции на клик
		void clickMenu(sf::Event &event, sf::RenderWindow &window, GameEngine &eng);	// Функция реакции на клик

		void startGame();										// Функция старта игры

		void stopGame();										// Функция остановки игры
};

#endif