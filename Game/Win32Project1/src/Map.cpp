#include "Map.h"

#include <iostream>

using namespace std;

const std::string MAP_TEXTURE = "fond.png";
const std::string PLATFORM_TEXTURE = "box2.png";
const std::string SOL_TEXTURE = "Sol.png";
const int MAP_SIZE = 6000;
const int SIZE_WINDOW_Y = 640;
using namespace sf;
Map::Map()
{
	if (!mapTexture.loadFromFile(MAP_TEXTURE))
	{
		cout << "erreur de chargement de MAP" << endl;
		// error...
	}
	mapSprite1.setTexture(mapTexture);
	mapSprite1.setPosition(0, 0);
	mapSprite2.setTexture(mapTexture);
	mapSprite2.setPosition(MAP_SIZE, 0);

	if (!platTexture.loadFromFile(PLATFORM_TEXTURE))
	{
		// error...
	}
	platformtab = new Platform*[500];

	for (int i = 0; i < 15; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 3);

	}
	for (int i = 15; i < 20; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 8);

	}
	for (int i = 20; i < 23; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 7);

	}
	for (int i = 23; i < 25; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 6);

	}
	for (int i = 25; i < 32; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 5);

	}
	for (int i = 32; i < 34; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 4);

	}
	for (int i = 34; i < 50; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 6);

	}
	for (int i = 50; i < 52; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 5);

	}
	for (int i = 52; i < 65; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 7);

	}
	for (int i = 65; i < 68; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 6);

	}

	for (int i = 68; i < 70; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 5);

	}

	for (int i = 70; i < 80; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 6);

	}

	for (int i = 80; i < 83; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 5);

	}

	for (int i = 83; i < 90; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 4);

	}

	for (int i = 90; i < 100; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 6);

	}

	for (int i = 100; i < 500; i++)
	{
		platformtab[i] = new Platform(&platTexture, i, 8);

	}

}


Map::~Map()
{

	for (int i = 0; i < 64; i++)
	{
		delete platformtab[i];

	}
	delete[] platformtab;
}

void Map::Draw(sf::RenderWindow &window)
{
	sf::View currentView = window.getView();
	Vector2f centre = currentView.getCenter();
	float pos = currentView.getCenter().x - currentView.getSize().x / 2;
	if (pos > mapSprite2.getPosition().x)
	{
		mapSprite1 = mapSprite2;
		mapSprite2.setPosition(mapSprite1.getPosition().x + MAP_SIZE , 0);
	}

	window.draw(mapSprite1);
	window.draw(mapSprite2);

	float posp;
	for (int i = 0; i < 500; i++)
	{
		posp = platformtab[i]->GetPos().x;
		if ((posp >(pos) - 60) && (posp < (pos + MAP_SIZE + 60)))
		{
			platformtab[i]->Draw(window);
		}
	}
}

bool Map::Collision(Character& hero)
{
	int poshero =(int) hero.GetPos().x;
	FloatRect herobox = hero.GetHitbox();
	for (int i =(int) poshero/64; i <(int) poshero/64 +5; i++)
	{
		if (i < 500 && herobox.intersects(platformtab[i]->GetHitBox()))
		{

			if (hero.GetPos().y >(platformtab[i]->GetPos().y) - 32)
			{
				//cout << "collision ! " << endl;
				return true;
			}
			else
			{
				//cout << "etat run" << endl;
				if (hero.GetState()->AscOrDesc())
				{
					hero.SetPos(poshero, platformtab[i]->GetPos().y - 63);
					hero.SetRunState();
				}
				return false;
			}
		}

	}
	//cout << "pas de collision" << endl;
	if (hero.GetPos().y < SIZE_WINDOW_Y - 128)
	{
		hero.SetJumpState(0);
	}
	return false;


}