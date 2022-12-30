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

	while (window.isOpen())
	{
		mouse_pos = Mouse::getPosition();
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed: 
				window.close();
				break;
			}//switch
		}//event

		printf("(%d, %d)\n", mouse_pos.x, mouse_pos.y);

	}

	return 0;
}