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
	int type;
	int is_clicked;
};

int main(void) {
	RenderWindow window(VideoMode(1500, 1000), "AfterSchool2");
	window.setFramerateLimit(60);

	Vector2i mouse_pos;
	int flipped_num = 0;
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

	RectangleShape background;
	Texture background_texture;
	background_texture.loadFromFile("./resources/images/background.png");
	background.setTexture(&background_texture);

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
	for (int i = 0; i < ROW; i++) 
	{
		for (int j = 0; j < COL; j++) 
		{
			cards[i][j].sprite.setSize(Vector2f(C_WIDTH, C_HEIGHT));
			cards[i][j].sprite.setPosition(j * C_WIDTH + 200, i * C_HEIGHT + 200);
			cards[i][j].sprite.setTexture(&t[0]);
			cards[i][j].is_clicked = 0;
			cards[i][j].type = 1 + n / 2;
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
					if (event.mouseButton.button == Mouse::Left) 
					{
						for (int i = 0; i < ROW; i++) 
						{
							for (int j = 0; j < COL; j++) 
							{
								if (cards[i][j].sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) 
								{
									cards[i][j].is_clicked = 1;
									flipped_num++;
								}
							}
						}
					}

				}//switch
			}//event

			//클릭시 카드 뒤집기 
			for (int i = 0; i < ROW; i++) 
			{
				for (int j = 0; j < COL; j++) 
				{
					if (cards[i][j].is_clicked)
					{
						cards[i][j].sprite.setTexture(&t[cards[i][j].type]);
					}
				}
			}

			//뒤집힌 카드가 두개일 때 
			if (flipped_num > 2) 
			{
				for (int i = 0; i < ROW; i++) 
				{
					for (int j = 0; j < COL; j++)
					{
						cards[i][j].sprite.setTexture(&t[0]); //카드를 원래 상태로 뒤집음
						cards[i][j].is_clicked = 0;
						flipped_num = 0;
					}
				}
			}
			sprintf(info, "(%4d, %4d), click_cnt : %d", mouse_pos.x, mouse_pos.y, flipped_num); //좌표 확인
			text.setString(info);

			window.clear(Color::White);
			window.draw(background);
			for (int i = 0; i < ROW; i++) 
			{
				for (int j = 0; j < COL; j++) 
				{
					window.draw(cards[i][j].sprite);
				}
			}
			window.draw(text);

			window.display();
		}
	
	return 0;
}