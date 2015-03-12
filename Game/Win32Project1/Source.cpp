#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Character.h"
#include "Map.h"

#include <iostream>
using namespace std;
using namespace sf;
int main()
{
	cout << "bonjour" << endl;
	sf::RenderWindow window(sf::VideoMode(1024, 640), "SFML works!");

	window.setFramerateLimit(60);


	Character c1;
	c1.Draw(window);
	View vue(FloatRect(0,320,1024,640));

	Map m1;

	window.setView(vue);
	Clock cl;
	while (window.isOpen())
    {
		c1.HandleEvent(window);
		c1.Update();
	
        window.clear();
		m1.Draw(window);
		c1.Draw(window);
		if (m1.Collision(c1))
		{
			return 0;

		}
		window.display();
    }

    return 0;


}