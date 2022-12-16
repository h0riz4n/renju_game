#include "./includes/AI.h"

// Конструктор, здесь задаём значения переменным
AI::AI()
{
	AI::isNotPaused = false;
}

// Метод проверки состояния игры
void AI::checkGameState(bool state)
{
	AI::isNotPaused = state;
}

// Функция реакции на событие Enter с задействием бота
void AI::enterEvent(sf::Event &event, GameEngine &eng)
{
	if (AI::isNotPaused)
	{
		if (event.key.code == sf::Keyboard::Enter)
		{
			sf::Vector2i tempPos;

			tempPos.x = eng.posX;
			tempPos.y = eng.posY;

			int tempX = (tempPos.x - ZEROPOS)/DIST;
			int tempY = (tempPos.y - ZEROPOS)/DIST;

			if (eng.desk[tempY][tempX] == 0)
			{
				eng.insert(tempPos);

				if (!eng.winFunc())
				{
					AI::moveBotFunc(tempPos.x, tempPos.y, eng);
				}

				eng.posX = 67;
				eng.posY = 67;
			}
		}
	}
}

/*
	Оценочная функция. Мы по последней шашке(т.е. чёрной), начинаем проходить по 8-ми сторонам
	(4-диагонали и 4 стороны(верх, вниз, вправо, налево))

	В завимости от опасности хода противника, наша функция возвращает число. Чем выше опасность
	- тем выше число. 
*/
int AI::evalFunc(GameEngine &eng)
{
	int score = 0;

	int oX[] = {1, 1, 1, 0, 0, -1, -1, -1};
	int oY[] = {0, 1, -1, 1, -1, 0, 1, -1};

	for (int k = 0; k < eng.eCounter; k++)
	{
		int tempY = (eng.eArray[k]->pos.y - ZEROPOS)/DIST;
		int tempX = (eng.eArray[k]->pos.x - ZEROPOS)/DIST;

		int tempColor = 1;

		for (int i = 0; i < 8; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				int y = tempY + oY[i]*j;
				int x = tempX + oX[i]*j;

				if (!eng.checkPos(x, y) || eng.desk[y][x] != tempColor)
				{
					break;
				}

				if (desk[y][x] == tempColor)
				{
					score += 1;
				}
			}
		}
	}

	return score;
}

void AI::checkBotTurn(int x, int y, GameEngine &eng)
{
	int tempColor = 0;

	int counter = 0;

	sf::Vector2i positions[32];

	int tempX = (x - ZEROPOS) / DIST;
	int tempY = (y - ZEROPOS) / DIST;

	int oX[] = {1, 1, 1, 0, 0, -1, -1, -1};
	int oY[] = {0, 1, -1, 1, -1, 0, 1, -1};

	for (int i = 0; i < 8; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			int y = tempY + oY[i]*j;

			int x = tempX + oX[i]*j;

			if (!eng.checkPos(x, y) || eng.desk[y][x] != tempColor)
			{
				break;
			}

			if (eng.desk[y][x] == tempColor)
			{
				eng.botPos.x = x*DIST + ZEROPOS;
				eng.botPos.y = y*DIST + ZEROPOS;
				counter += 1;
				positions[counter] = eng.botPos;
			}
		}
	}

	if (counter % 2 == 0)
	{
		eng.botPos = positions[counter/2];
	}
	else
	{
		eng.botPos = positions[counter];
	}
}

void AI::moveBotFunc(int x, int y, GameEngine &eng)
{
	int score = evalFunc(eng);

	if (score >= 0)
	{
		checkBotTurn(x, y, eng);
		eng.insert(eng.botPos);
		eng.winFunc();
		return;
	}
}

AI::~AI()
{
	std::cout << "It's working" << std::endl;
}