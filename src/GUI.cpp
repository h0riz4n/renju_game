#include "./includes/GUI.h"

/*
	В конструкторе задаём значения переменным
	И вызываем функции настройки текстов и приведения к дефолтным настройкам
*/
GUI::GUI()
{
	isPaused = false;
	isAi = false;

	font.loadFromFile("C:\\instruments\\course_work_2\\src\\res\\font\\RobotoMono-Bold.ttf");

	fillSet(text, "push SPACE to START", 300, 500, 20);

	fillCircles();

	fillUsersBlock();

	defaultSetting();
}

/*
	Функция зануления игры, необходим в методе clickMenu()
*/
void GUI::nullGame(GameEngine &eng)
{
	eng.gameToNull();
	isPaused = true;
}

/*
	Метод реакции на клик мыши. В зависимости от положения мыши действует та или иная кнопка в меню.
*/
void GUI::clickMenu(sf::Event &event, sf::RenderWindow &window, GameEngine &eng)
{
	if (!isPaused)
	{
		if (event.mouseButton.button == sf::Mouse::Button::Left && sf::IntRect(300, 200, 400, 35).contains(sf::Mouse::getPosition(window)))
		{
			isAi = false;
			nullGame(eng);
		}

		if (event.mouseButton.button == sf::Mouse::Button::Left && sf::IntRect(300, 275, 400, 35).contains(sf::Mouse::getPosition(window)))
		{
			isAi = true;
			nullGame(eng);
		}

		if (event.mouseButton.button == sf::Mouse::Button::Left && sf::IntRect(300, 350, 400, 35).contains(sf::Mouse::getPosition(window)))
		{
			nullGame(eng);
		}

		if (event.mouseButton.button == sf::Mouse::Button::Left && sf::IntRect(300, 425, 400, 35).contains(sf::Mouse::getPosition(window)))
		{
			window.close();
		}
	}
}

/*
	Метод реакции текста на действие мыши. Метод необходим в clickMenu()
*/
void GUI::changeTxtByPos(sf::Text &txt, int x, int y, int width, int height, sf::RenderWindow &window)
{
	if (sf::IntRect(x, y, width, height).contains(sf::Mouse::getPosition(window)))
	{
		txt.setCharacterSize(39);
	}
	if (!sf::IntRect(x, y, width, height).contains(sf::Mouse::getPosition(window)))
	{
		txt.setCharacterSize(35);
	}
}

/*
	Реакции на движение мыши
*/
void GUI::clickMenu(sf::RenderWindow &window)
{
	if (!isPaused)
	{
		changeTxtByPos(restart, 300, 350, 400, 35, window);
		changeTxtByPos(player, 300, 200, 400, 35, window);
		changeTxtByPos(botPlayer, 300, 275, 400, 35, window);
		changeTxtByPos(exit, 300, 425, 400, 35, window);
	}
}

/*
	Приведение меню к дефолтным настройкам
*/
void GUI::defaultSetting()
{
	mainFont.loadFromFile("C:\\instruments\\course_work_2\\src\\res\\font\\Play-Bold.ttf");
	fillSet(player, "Two players", 300, 200, 35);
	fillSet(botPlayer, "One player", 300, 275, 35);
	fillSet(restart, "Restart the game", 300, 350, 35);
	fillSet(exit, "EXIT", 300, 425, 35);
}

/*
	Метод заполнения меню-блоков в игре
*/
void GUI::fillUsersBlock()
{
	fillSet(user1, "Player 1", 120, 705, 30);
	fillSet(user2, "Player 2", 120, 775, 30);
	fillSet(gameTitle, "Renju", 700, 70, 65);
}

/*
	Метод вызова стандартных настроек для задания параметров к тексту
*/
void GUI::fillSet(sf::Text &text, std::string txt, int x, int y, int charSize)
{
	text.setString(txt);
	text.setFont(font);
	text.setCharacterSize(charSize);
	text.setPosition(x, y);
	text.setStyle(sf::Text::Bold);
}

/*
	Задание изображений
*/
void GUI::setImg(sf::Image &img, std::string src, sf::Texture &texture)
{
	img.loadFromFile(src);
	texture.loadFromImage(img);
}

/*
	Заполнение кругов, которые находятся в меню-блоке(не игровые)
*/
void GUI::fillCircles()
{
	setImg(bImg, "C:\\instruments\\course_work_2\\src\\res\\texture\\black_checker.png", bTexture);
	setImg(wImg, "C:\\instruments\\course_work_2\\src\\res\\texture\\white_checker.png", wTexture);

	bCircle.setRadius(25);
	wCircle.setRadius(25);

	black = &bTexture;
	white = &wTexture;

	bCircle.setTexture(black);
	wCircle.setTexture(white);

	bCircle.setPosition(60, 700);
	wCircle.setPosition(60, 770);
}

// Функция старта игры
void GUI::startGame()
{
	isPaused = true;
}

// Функция паузы
void GUI::stopGame()
{
	isPaused = false;
}

// Функция зарисовки главного меню
void GUI::drawMainMenu(sf::RenderWindow &window)
{
	window.draw(player);
	window.draw(botPlayer);
	window.draw(restart);
	window.draw(exit);
}

// Функция паузы игры
void GUI::pauseGame(sf::RenderWindow &window)
{
	if (!isPaused)
	{
		drawMainMenu(window);
		window.draw(text);
	}
}

// Функция зарисовки меню-блоков в игре
void GUI::drawUsersBlock(sf::RenderWindow &window)
{
	if (isPaused)
	{
		window.draw(gameTitle);
		window.draw(user1);
		window.draw(user2);
		window.draw(bCircle);
		window.draw(wCircle);
	}
}