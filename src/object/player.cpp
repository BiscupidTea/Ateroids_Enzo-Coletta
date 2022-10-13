#include "player.h"

PLAYER CreatePlayer()
{
	PLAYER P1{};
	P1.ship.width = 0;
	P1.ship.height = 0;
	P1.ship.x = static_cast<float>(GetScreenWidth() / 2) - (P1.ship.width / 2);
	P1.ship.y = static_cast<float>(GetScreenHeight() / 2) - (P1.ship.height / 2);

	P1.center.x = P1.ship.x + (P1.ship.width / 2);
	P1.center.y = P1.ship.y + (P1.ship.height / 2);

	P1.origin.x = (P1.ship.width / 2);
	P1.origin.y = (P1.ship.height / 2);

	P1.rotation = 0;

	P1.color = RED;
	P1.lives = 3;
	P1.score = 0;

	P1.shipAcceleration.x = 0;
	P1.shipAcceleration.y = 0;

	return P1;
}

void CreateBullets(BULLETS& bulet, PLAYER P1)
{
	bulet.radius = 5;
	bulet.isShoted = false;
	bulet.Pos.x = P1.center.x;
	bulet.Pos.y = P1.center.y;
	bulet.speed.x = 0;
	bulet.speed.y = 0;
	bulet.rotation = 0;
}