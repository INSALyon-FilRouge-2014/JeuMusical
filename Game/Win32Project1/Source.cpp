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
	vue.setCenter(512, 320);

	Map m1;

	window.setView(vue);
	Clock cl;
	while (window.isOpen())
    {
		c1.HandleEvent(window);
		/*if (cl.getElapsedTime()>Time(seconds(1)))
		{
			sleep(Time(seconds(5)));
			cl.restart();
		}*/
		c1.Update(m1);
        window.clear();
		m1.Draw(window);
		c1.Draw(window);
		if (m1.Collision(c1))
		{
			cout << "perdu" << endl;
			c1.Replace();
			//sleep(seconds(1));
		}
		window.display();
    }

    return 0;


}