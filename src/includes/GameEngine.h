#ifndef __GameEngine_H
#define __GameEngine_H
#define DESKSIZE 15
#define ZEROPOS 67

#include <SFML/Graphics.hpp>

/*
	Создаём класс нашего игрового движка
*/
class GameEngine
{
	private:

		/*
			Объявляем закрытые переменные
		*/
		sf::CircleShape mainShape;
		sf::Image blackImage, whiteImage;
		sf::Texture blackTexture, whiteTexture;

		sf::Texture *black, *white;

		/*
			Создаём нашу структуру, и туда будем заносить:
			- чёрная ли шашка
			- позиция шашки
			- объект шашки(для его отображения)
		*/

		typedef struct
		{
			bool black;
			sf::Vector2i pos;
			sf::CircleShape shape;
		} desk_element_t;

		int line;					// Кол-во линий 15х15

		int dist;					// Переменная дистанции

		/*
			Объявляем закрытые методы
		*/
		void fillDesk();					// Функция зануления доски

		// Создаём перегрузку
		void resize();						// Функция ресайза массива шашек
		void resize(int size);				// Функция рейсайза массива шашек

		void color();						// Функция изменения цвета ведущей шашки

	public:

		/*
			Объявляем открытые переменные
		*/
		bool isNotPaused;			// Состояние игры
		bool isAi;

		int arraySize;				// Размер массива с шашками
		int eCounter;				// Счётчик кол-ва шашек на поле

		int colorCounter; 			// Счётчик для определения цвета (чётные - чёрные, нечётные - белые)

		sf::Vector2i botPos;

		int desk[DESKSIZE][DESKSIZE];			// Двумерный массив нашей доски

		desk_element_t** eArray;				// Массив указателей на нашу структуру

		int posX;	// Позиция по Х
		int posY;	// Позиция по Y

		/*
			Объявляем открытые методы
		*/
		GameEngine();

		~GameEngine();

		void insert(sf::Vector2i deskPos);		// Функция вставки

		bool winFunc();							// Функция определения победы

		void gameToNull();						// Функция зануления игры

		bool checkPos(int x, int y);			// Функция на проверку позиции и выхода за пределы доски

		void checkState(bool state);			// Функция проверки состояния игры

		void userTurn(sf::Event &event);		// Функция хода пользователя

		void enterEvent(sf::Event &event);		// Функция захвата события Enter

		void drawCheckers(sf::RenderWindow &window);	// Функция зарисовки шашек

		void drawChecker(sf::RenderWindow &window);		// Функция зарисовки ведущей шашки
};

#endif