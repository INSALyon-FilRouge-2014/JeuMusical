#ifndef USERVIEW_H

#define USERVIEW_H

#include "D:\programmation\SFML-2.2\include\SFML\Graphics\View.hpp"
#include <SFML\Graphics.hpp>
class UserView :
	public sf::View
{
public:
	UserView();
	UserView(sf::FloatRect);
	~UserView();
	void Update();
private:
	sf::Clock updateClock;


};

#endif