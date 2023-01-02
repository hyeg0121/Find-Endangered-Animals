#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.hpp>

using namespace sf;

const int ROW = 4, COL = 4;
const int C_WIDTH = 270, C_HEIGHT = 180;
const int W_WIDTH = 1500, W_HEIGHT = 1000;

struct Cards {
	RectangleShape sprite;
	int id_i, id_j;
	int type;
	int is_clicked;
	int is_cleared;
};

struct SBuffer {
	SoundBuffer BGM;
};

int main(void) 
{
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "AfterSchool2");
	window.setFramerateLimit(60);

	Vector2i mouse_pos;
	int flipped_num = 0;

	long start_time = clock();
	long spent_time;
	long delay_time = 0; //�ٷ� ?�� ���������� �ʵ��� �����̸� ��

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

	struct SBuffer sb;
	sb.BGM.loadFromFile("./resources/sounds/backgroundmusic.wav");

	/* background image & music */
	RectangleShape background;
	Texture background_texture;
	background.setSize(Vector2f(W_WIDTH, W_HEIGHT));
	background_texture.loadFromFile("./resources/images/background.png");
	background.setTexture(&background_texture);
	Sound bgm;
	bgm.setBuffer(sb.BGM);
	bgm.setLoop(1);
	bgm.play();

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

	struct Cards compare_card; //ù ��°�� ������ ī�� 
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
			cards[i][j].id_i = i;
			cards[i][j].id_j = j;
			cards[i][j].is_cleared = 0;
			n++;
		}
	}

	/* ���α׷� ���� �� */
	while (window.isOpen())
	{
		mouse_pos = Mouse::getPosition(window); //���콺 ��ġ

		spent_time = clock() - start_time;

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			//�� �� ������ �� ���� ����
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{
					for (int i = 0; i < ROW; i++)
					{
						for (int j = 0; j < COL; j++)
						{
							if (flipped_num < 2)
							{
								// ���콺 ��ġ�� cards[i][j]�� ��ġ�� �ش��Ѵٸ�?
								if (cards[i][j].sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
								{
									// ���������� ���� ī�常 �����ڴ�.
									if (cards[i][j].is_clicked == 0)
									{
										cards[i][j].is_clicked = 1;
										flipped_num++;

										// �������� ī�尡 �� �����
										if (flipped_num == 1)
										{
											compare_card = cards[i][j];
										}
										// �� ���� �������ٸ�
										else if (flipped_num == 2)
										{
											// �� ī�尡 ���� ������
											if (compare_card.type == cards[i][j].type)
											{
												cards[i][j].is_cleared = 1;
												cards[compare_card.id_i][compare_card.id_j].is_cleared = 1;
											}
											// �� ī�尡 �ٸ� �����̸�
											else
											{
												delay_time = spent_time;
											}
										}//else if
									}//if
								}//if
							}//if
						}//for
					}//for
				}//if
			}//switch
		}//while

		//Ŭ���� ī�� ������ 
		for (int i = 0; i < ROW; i++) 
		{
			for (int j = 0; j < COL; j++) 
			{
				//Ŭ���� �� �����̰ų�, ������ ���� ī���̸�
				if (cards[i][j].is_clicked || cards[i][j].is_cleared)
				{
					//�׸��� �ִ� ���·� ����
					cards[i][j].sprite.setTexture(&t[cards[i][j].type]);
				}
				else
				{
					cards[i][j].sprite.setTexture(&t[0]);
				}
			}
		}

		//������ ī�尡 �ΰ��̰�, �� ī�尡 �������� 1�ʰ� ������
		if (flipped_num == 2 &&
			spent_time - delay_time > 1000) 
		{
			for (int i = 0; i < ROW; i++) 
			{
				for (int j = 0; j < COL; j++)
				{
					cards[i][j].is_clicked = 0;
				}
			}
			flipped_num = 0;
		}

		sprintf(info, "(%4d, %4d), time : %d %d", mouse_pos.x, mouse_pos.y, (spent_time/1000), (delay_time/1000)); //��ǥ Ȯ��
		text.setString(info);

		window.clear();
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