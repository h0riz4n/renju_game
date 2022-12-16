#include "./includes/GameEngine.h"

/*
	Создаём структуру, в ней заполняются объекты графики(изображения, текстуры, круги)
	Даём переменным значения и вызоваем функцию зануления доски и ресайза размера нашего массива
*/
GameEngine::GameEngine()
{
	mainShape.setRadius(13);

	blackImage.loadFromFile("C:\\instruments\\course_work_2\\src\\res\\texture\\black_checker.png");
	whiteImage.loadFromFile("C:\\instruments\\course_work_2\\src\\res\\texture\\white_checker.png");

	blackTexture.loadFromImage(blackImage);
	whiteTexture.loadFromImage(whiteImage);

	black = &blackTexture;
	white = &whiteTexture;

	line = 15;

	dist = 35;

	posX = 67;
	posY = 67;

	isNotPaused = false;

	mainShape.setPosition(posX, posY);
	mainShape.setTexture(black);

	arraySize = 32;
	eCounter = 0;

	fillDesk();

	resize();
	resize(arraySize * 2);
}

/*
	Двумерный массив доски заполняется нулями.
	Очистка карты.
*/
void GameEngine::fillDesk()
{
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < line; j++)
		{
			desk[i][j] = 0;
		}
	}
}

// Проверка состояния игры
void GameEngine::checkState(bool state)
{
	isNotPaused = state;
}

// Деструктор на очистку памяти
GameEngine::~GameEngine()
{
	for (int i = 0; i < arraySize; i++)
	{
		delete eArray[i];
	}

	delete [] eArray;
}

// Ресайз нашего массива, выделяя в начале для него память
void GameEngine::resize()
{
	eArray = new desk_element_t*[arraySize];

	for (int i = 0; i < arraySize; i++)
	{
		eArray[i] = new desk_element_t;
	}

	for (int i = 0; i < arraySize; i++)
	{
		eArray[i] = 0;
	}
}

// Ресайз нашего массива, если кол-во шашек превышает его размер
void GameEngine::resize(int size)
{
	int oldSize = arraySize;
	arraySize = size;

	desk_element_t** newArray = new desk_element_t*[arraySize];

	for (int i = 0; i < arraySize; i++)
	{
		newArray[i] = 0;
	}

	if (oldSize)
	{
		memcpy(newArray, eArray, oldSize * sizeof(desk_element_t*));
		delete[] eArray;
	}

	eArray = newArray;
}

// Функция зарисовки ведущей шашки
void GameEngine::drawChecker(sf::RenderWindow& window)
{
	if (isNotPaused)
	{
		mainShape.setPosition(posX, posY);
		window.draw(mainShape);
	}
}

// Функция движения ведущей шашки
void GameEngine::userTurn(sf::Event &event)
{
	if (isNotPaused)
	{
		if (event.key.code == sf::Keyboard::A)
		{
			if (posX != 67)
			{
				posX -= dist;
			}
		}

		if (event.key.code == sf::Keyboard::W)
		{
			if (posY  != 67)
			{
				posY  -= dist;
			}
		}

		if (event.key.code == sf::Keyboard::S)
		{
			if (posY != 557)
			{
				posY  += dist;
			}
		}

		if (event.key.code == sf::Keyboard::D)
		{
			if (posX != 557)
			{
				posX += dist;
			}
		}
	}
}

// Функция изменения цвета ведущей шашки
void GameEngine::color()
{
	if (colorCounter % 2 == 0)
	{
		mainShape.setTexture(black);
	}
	else
	{
		mainShape.setTexture(white);
	}
}

/*
	Функция захвата события на Enter.
	Мы проверяем состояние игры(есть ли пауза)
	Создаём временную переменую с типом координаты,
	а дальше по ней обращаемся к расположения на нашем
	двумерном массиве доски и проверка на пустоту в этой клетке,
	а дальше происходит функция вставки, и проверки на победу.
*/
void GameEngine::enterEvent(sf::Event &event)
{
	if (isNotPaused)
	{
		if (event.key.code == sf::Keyboard::Enter)
		{
			sf::Vector2i tempPos;

			tempPos.x = posX;
			tempPos.y = posY;

			int tempX = (tempPos.x - ZEROPOS)/dist;
			int tempY = (tempPos.y - ZEROPOS)/dist;

			if (desk[tempY][tempX] == 0)
			{
				insert(tempPos);

				winFunc();

				posX = 67;
				posY = 67;
			}
		}
	}
}

/*
	Функция вставки шашки в массив и вставки занятости
	в двумерный массив доски

	Проверяем превышает ли число шашек размер массива.

	Проходимся по массиву и находим пустой элемент и заполняем его
	динамически и заполняем массив доски.
*/
void GameEngine::insert(sf::Vector2i deskPos)
{
	eCounter += 1;
	colorCounter += 1;

	if (eCounter >= arraySize)
	{
		resize(arraySize*2);
	}

	for (int i = 0; i < eCounter; i++)
	{
		if (!eArray[i])
		{
			eArray[i] = new desk_element_t;
			eArray[i]->pos = deskPos;

			eArray[i]->shape.setRadius(13);
			eArray[i]->shape.setPosition(deskPos.x, deskPos.y);

			if (i % 2 == 0)
			{
				eArray[i]->black = true;
				eArray[i]->shape.setTexture(black);
			}
			else
			{
				eArray[i]->black = false;
				eArray[i]->shape.setTexture(white);
			}

			int tempX = (deskPos.x - ZEROPOS) / dist;
			int tempY = (deskPos.y - ZEROPOS) / dist;

			if (eArray[i]->black)
			{
				desk[tempY][tempX] = 1;
			}
			else
			{
				desk[tempY][tempX] = 2;
			}
		}
	}

	color();
}

// Функция зарисовки всех шашек
void GameEngine::drawCheckers(sf::RenderWindow &window)
{
	if (isNotPaused)
	{
		for (int i = 0; i < eCounter; i++)
		{
			window.draw(eArray[i]->shape);
		}
	}
}

// Функция на проверку позиции и выхода за пределы массива
bool GameEngine::checkPos(int x, int y)
{
	return x >= 0 && y >= 0 && x < DESKSIZE && y < DESKSIZE;
}

/*
	Функция определения победы.
	Создаются массивы, которые определяют направление,
	по которому будет происходить проверка.
	Мы создаём цикл по кол-ву шашек, и дальше цикл по направлениям
	и по кол-ву необходимых шашек в совершении победы(5)

	Если находим шашку, которая прерывает победу, цикл прерывается и переходим на другую сторону.
*/
bool GameEngine::winFunc()
{
	int oX[] = {1, 1, 1, 0, 0, -1, -1, -1};
	int oY[] = {0, 1, -1, 1, -1, 0, 1, -1};

	for (int k = 0; k < eCounter; k++)
	{
		int tempY = (eArray[k]->pos.y - ZEROPOS)/dist;
		int tempX = (eArray[k]->pos.x - ZEROPOS)/dist;

		int tempColor = eArray[k]->black ? 1 : 2;

		for (int i = 0; i < 8; i++)
		{
			bool win = true;
			for (int j = 1; j <= 4; j++)
			{
				int y = tempY + oY[i]*j;
				int x = tempX + oX[i]*j;

				if (!checkPos(x, y) || desk[y][x] != tempColor)
				{
					win = false;
					break;
				}
			}

			if (win)
			{
				gameToNull();
				return win;
			}
		}
	}

	return false;
}

// Функция возвращения игры к дефолтным настройкам
void GameEngine::gameToNull()
{
	fillDesk();

	for (int i = 0; i < eCounter; i++)
	{
		delete eArray[i];
		eArray[i] = 0;
	}

	eCounter = 0;

	colorCounter = 0;

	color();
}
