#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.hpp>

using namespace sf;

int main(void) {
	RenderWindow window(VideoMode(1200, 800), "AfterSchool2");
	window.setFramerateLimit(60);

	Vector2i mouse_pos;
	int click_cnt = 0;

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

		printf("(%d, %d), click_cnt : %d\n", mouse_pos.x, mouse_pos.y, click_cnt); //좌표 확인

	}

	return 0;
}