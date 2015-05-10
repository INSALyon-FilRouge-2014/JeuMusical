#include "Map.h"
#include "XMLReader.h"
#include <iostream>
#include <vector>

using namespace std;

const std::string MAP_TEXTURE = "fond.png";
const std::string PLATFORM_TEXTURE1 = "box2.png";
const std::string PLATFORM_TEXTURE2 = "cloud.png";
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
	platTexture = new Texture[2];
	if (!platTexture[0].loadFromFile(PLATFORM_TEXTURE1))
	{
		// error...
	}

	if (!platTexture[1].loadFromFile(PLATFORM_TEXTURE2))
	{
		// error...
	}

	XMLReader* reader = new XMLReader("Level2.xml");
	platformtab = reader->read();
	for (unsigned int i = 0; i < platformtab->size(); i++)
	{
		platformtab->at(i).SetTexture(&platTexture[(platformtab->at(i)).GetType()]);
	}
	delete reader;
}


Map::~Map()
{
	
	delete platformtab;
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
	for (unsigned int i = 0; i < platformtab->size(); i++)
	{
		posp = platformtab->at(i).GetPos().x;
		if ((posp >(pos) - 60) && (posp < (pos + MAP_SIZE + 60)))
		{
			platformtab->at(i).Draw(window);
		}
	}
}

bool Map::Collision(Character& hero)
{
	int poshero =(int) hero.GetPos().x;
	FloatRect herobox = hero.GetHitbox();
	for (int i =(int) poshero/64; i <(int) poshero/64 +5; i++)
	{
		if (i < platformtab->size() && herobox.intersects(platformtab->at(i).GetHitBox()))
		{

			if (hero.GetPos().y >(platformtab->at(i).GetPos().y) - 32)
			{
				//cout << "collision ! " << endl;
				return true;
			}
			else
			{
				//cout << "etat run" << endl;
				if (hero.GetState()->AscOrDesc())
				{
					hero.SetPos(poshero, platformtab->at(i).GetPos().y - 63);
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