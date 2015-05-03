#include "Menu.h"
#include "globals.h"
#include <string.h>
#include <iostream>

int selectedItemIndex;
sf::Font font;
sf::Text menu[MAX_NUMBER_OF_ITEMS];
sf::RenderWindow window1;
void init(float width, float height) {
	if (!font.loadFromFile("arial.ttf")) { //Danoisemedium
		// handle error
	}

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Host A Game");
	menu[0].setCharacterSize(50);
	menu[0].setPosition(sf::Vector2f(width / 1.75, height / (4 + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Join A Game");
	menu[1].setCharacterSize(50);
	menu[1].setPosition(sf::Vector2f(width / 1.75, height / (4 + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Options");
	menu[2].setCharacterSize(50);
	menu[2].setPosition(sf::Vector2f(width / 1.75, height / (4 + 1) * 3));

	menu[3].setFont(font);
	menu[3].setColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setCharacterSize(50);
	menu[3].setPosition(sf::Vector2f(width / 1.75, height / (4 + 1) * 4));

	menu[5].setFont(font);
	menu[5].setColor(sf::Color::White);
	menu[5].setString("No. Of Human players");
	menu[5].setCharacterSize(50);
	menu[5].setPosition(sf::Vector2f(width / 4, height / 4));

	menu[4].setFont(font);
	menu[4].setColor(sf::Color::Red);
	menu[4].setString("Total no. Of players");
	menu[4].setCharacterSize(50);
	menu[4].setPosition(sf::Vector2f(width / 4, height / 12));

	menu[6].setFont(font);
	menu[6].setColor(sf::Color::White);
	menu[6].setString("Host");
	menu[6].setCharacterSize(50);
	menu[6].setPosition(sf::Vector2f(width / 4, height / 2.4));
	selectedItemIndex = 0;

	menu[7].setFont(font);
	menu[7].setColor(sf::Color::White);
	menu[7].setString("0");
	menu[7].setCharacterSize(55);
	menu[7].setPosition(sf::Vector2f(width / 1.40, height / 4));

	menu[8].setFont(font);
	menu[8].setColor(sf::Color::White);
	menu[8].setString("0");
	menu[8].setCharacterSize(55);
	menu[8].setPosition(sf::Vector2f(width / 1.40, height / 12));
}
/*
 Menu::~Menu() {
 }*/
int x11 = 0;
int y11 = 0;
void draw(sf::RenderWindow &window) {
	for (int i = 0; i < 4; i++) {
		window.draw(menu[i]);
	}
}

void MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		if (selectedItemIndex == 5) {
			menu[7].setColor(sf::Color::Red);
		}
		menu[selectedItemIndex].setColor(sf::Color::White);
		menu[selectedItemIndex].setCharacterSize(50);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
		menu[selectedItemIndex].setCharacterSize(55);
	}
}
void changeValue() {
	//y=x;
	if (selectedItemIndex == 4) {
		x11 = x11 + 1;
		stringstream ss;
		ss << x11;
		string str = ss.str();
		//string s = to_string(x);

		menu[8].setString(str);
		//menu[7].setString(str);
		//y=x;

	} else if (selectedItemIndex == 5) {
		y11 = y11 + 1;
		stringstream ss;
		ss << y11;
		string str = ss.str();
		menu[7].setString(str);
	}

}

void changeValue1() {
	//y=x;
	if (selectedItemIndex == 4) {
		x11 = x11 - 1;

		stringstream ss;
		ss << x11;
		string str = ss.str();

		menu[8].setString(str);
		//menu[7].setString(str);
		//y=x;

	} else if (selectedItemIndex == 5) {
		y11 = y11 - 1;
		stringstream ss;
		ss << y11;
		string str = ss.str();
		menu[7].setString(str);
	}

}
void MoveDown() {
	//cout<<selectedItemIndex<<endl;
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setColor(sf::Color::White);
		menu[selectedItemIndex].setCharacterSize(50);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
		menu[selectedItemIndex].setCharacterSize(55);
	}
}
int GetPressedItem() {
	return selectedItemIndex;
}

void Menu::init_window() {
	sf::RenderWindow window(sf::VideoMode(1024, 768), "QUIDDITCH: MENU",
			sf::Style::Default);
	bool isFullscreen = false;
	init(window.getSize().x, window.getSize().y);
	sf::Music music;

	if (!music.openFromFile("MainMusic.ogg")) { //1stWindow.ogg
		std::cout << "ERROR" << std::endl;
	}

	music.play();

	//music.setPlayingOffset(sf::seconds(10));

	music.setVolume(100);

	sf::Texture image;
	image.loadFromFile("background.jpg");
	sf::Sprite mySpriteName;
	mySpriteName.setTexture(image);
	int co = 1;

	while (window.isOpen()) {
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
			window.create(sf::VideoMode(window_width, window_height),
					"QUIDDITCH: PLAY IT MY WAY", sf::Style::Default);
		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Up:
					MoveUp();
					break;

				case sf::Keyboard::Down:
					MoveDown();
					break;

				case sf::Keyboard::Escape:
					if (true == isFullscreen) {
						window.create(sf::VideoMode(1024, 768), "SFML WORK!",
								sf::Style::Default);

						isFullscreen = false;
					} else {
						window.create(sf::VideoMode(1024, 768), "SFML WORK!",
								sf::Style::Default);

						isFullscreen = true;
					}

				case sf::Keyboard::Return:
					switch (GetPressedItem()) {
					case 0:
						std::cout << "Host A Game button has been pressed"
								<< std::endl;
						music.stop();
						isHost = 1;
						window.close();

						isHost = 1;
						break;

					case 1:
						std::cout << "Join A Game button has been pressed"
								<< std::endl;
						music.stop();
						isHost = 0;
						window.close();
						break;

					case 2:
						std::cout << "Option button has been pressed"
								<< std::endl;
						break;

					case 3:
						exit(0);
						window.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();
				music.stop();

				break;

			}
		}

		window.clear();
		window.draw(mySpriteName);
		draw(window);

		window.display();

	}
	//new window1
	if (isHost == 1) {
		window1.create(sf::VideoMode(1024, 768), "QUIDDITCH: MENU",
				sf::Style::Default);
		bool isFullscreen1 = false;
		init(window1.getSize().x, window1.getSize().y);
		sf::Music music1;
		if (!music1.openFromFile("MainMusic.ogg")) { //1stWindow.ogg
			std::cout << "ERROR" << std::endl;
		}
		music1.play();

		//music.setPlayingOffset(sf::seconds(10));
		music1.setVolume(100);
		sf::Texture image1;
		image1.loadFromFile("background1.jpg");
		sf::Sprite mySpriteName1;
		mySpriteName1.setTexture(image1);
		selectedItemIndex = 4;
		while (window1.isOpen() && co == 1) {
			sf::Event event1;
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				window1.create(sf::VideoMode(1024, 768),
						"QUIDDITCH: PLAY IT MY WAY", sf::Style::Default);
			while (window1.pollEvent(event1)) {
				switch (event1.type) {
				case sf::Event::KeyReleased:
					switch (event1.key.code) {
					case sf::Keyboard::Up:

						MoveUp();
						break;

					case sf::Keyboard::Down:

						MoveDown();
						break;

					case sf::Keyboard::Right:

						changeValue();
						break;

					case sf::Keyboard::Left:

						changeValue1();
						break;

					case sf::Keyboard::Return:
						switch (GetPressedItem()) {
						case 6:
							cout << "Ready button has been pressed" << endl;
							co = 0;
							//window1.close();
							//exit(0);
						}
						break;
					}
					break;
				case sf::Event::Closed:
					window1.close();
					music1.stop();

					break;
				}

			}

			window1.clear();
			window1.draw(mySpriteName1);
			window1.draw(menu[6]);
			window1.draw(menu[5]);
			window1.draw(menu[4]);
			window1.draw(menu[7]);
			window1.draw(menu[8]);
			//draw(window1);
			window1.display();


		}

	}
}
