#include "Cookie.h"
#include "Game.h"
#include "Constants.h"

void Cookie::update()
{
	Game::getHero()->setHP(HERO_BASE_HP);
}