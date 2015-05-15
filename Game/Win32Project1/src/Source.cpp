#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InGame.h"
#include <iostream>
using namespace std;
using namespace sf;
int main()
{
	cout << "bonjour" << endl;
	sf::RenderWindow window(sf::VideoMode(1024, 640), "Le jeu !");

	window.setFramerateLimit(120);
	View vue(FloatRect(0,320,1024,640));
	vue.setCenter(512, 320);
	window.setView(vue);
	InGame gameState(10);
	while (window.isOpen())
    {
		window.clear();
		gameState.Update(window);
		window.display();
		
    }

    return 0;


}