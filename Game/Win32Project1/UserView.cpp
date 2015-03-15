#include "UserView.h"
using namespace sf;

static const int VIEW_SPEED = 3;


UserView::UserView() :View()
{
}

UserView::UserView(FloatRect x) : View(x)
{

}

UserView::~UserView()
{
}


void UserView::Update()
{
	if (updateClock.getElapsedTime() >= Time(milliseconds(10)))
	{
		updateClock.restart();
		move((float)VIEW_SPEED, 0);
	}

}