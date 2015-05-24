#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "InGame.h"
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
	string name = "face-to-face";
	InGame gameState(10, name);
	while (window.isOpen())
    {
		window.clear();
		gameState.Update(window);
		window.display();
		
    }

    return 0;


}