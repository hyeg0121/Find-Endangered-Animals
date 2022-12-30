#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.hpp>

using namespace sf;

const int ROW = 4;
const int COL = 4;
const int C_WIDTH = 270, C_HEIGHT = 180;

struct Cards {
	RectangleShape sprite;
	int id;
};

int main(void) {
	RenderWindow window(VideoMode(1500, 1000), "AfterSchool2");
	window.setFramerateLimit(60);

	Vector2i mouse_pos;
	int click_cnt = 0;
	char img_name[100];

	Texture t[8 + 1];
	t[0].loadFromFile("./resources/images/card_back.png");
	t[1].loadFromFile("./resources/images/card_1.png");
	t[2].loadFromFile("./resources/images/card_2.png");
	t[3].loadFromFile("./resources/images/card_3.png");
	t[4].loadFromFile("./resources/images/card_4.png");
	t[5].loadFromFile("./resources/images/card_5.png");
	t[6].loadFromFile("./resources/images/card_6.png");
	t[7].loadFromFile("./resources/images/card_7.png");
	t[8].loadFromFile("./resources/images/card_8.png");


	Font font;
	font.loadFromFile("c:/Windows/Fonts/arial.ttf");

	Text text;
	text.setCharacterSize(30);
	text.setFont(font);
	text.setFillColor(Color::White);
	text.setPosition(10, 10);
	text.setOutlineThickness(1);
	text.setOutlineColor(Color::Black);

	char info[100];

	struct Cards cards[ROW][COL];
	int n = 0;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			cards[i][j].sprite.setSize(Vector2f(C_WIDTH, C_HEIGHT));
			cards[i][j].sprite.setPosition(j * C_WIDTH + 200, i * C_HEIGHT + 200);
			cards[i][j].sprite.setTexture(&t[1+n/2]);
			n++;
		}
	}

		while (window.isOpen())
		{
			mouse_pos = Mouse::getPosition(window);
			Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::Closed:
					window.close();
					break;
					//한 번 누르면 한 번만 적용
				case Event::MouseButtonPressed:
					if (event.mouseButton.button == Mouse::Left) {
						click_cnt++;
					}

				}//switch
			}//event

			sprintf(info, "(%4d, %4d), click_cnt : %d", mouse_pos.x, mouse_pos.y, click_cnt); //좌표 확인
			text.setString(info);

			window.clear(Color::White);

			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					window.draw(cards[i][j].sprite);
				}
			}
			window.draw(text);

			window.display();
		}
	
	return 0;
}