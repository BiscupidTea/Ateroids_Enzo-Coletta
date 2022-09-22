#include "player.h"

PLAYER CreatePlayer()
{
	PLAYER P1{};

	P1.ship.width = 50;
	P1.ship.height = 50;
	P1.ship.x = static_cast<float>(GetScreenWidth()/2) - (P1.ship.width / 2);
	P1.ship.y = static_cast<float>(GetScreenHeight()/2) - (P1.ship.height / 2);

	P1.center.x = P1.ship.x + (P1.ship.width / 2);
	P1.center.y = P1.ship.y + (P1.ship.height / 2);

	P1.XY.x = P1.ship.x - 120;
	P1.XY.y = P1.ship.y - 63;

	P1.origin.x = (P1.ship.width / 2);
	P1.origin.y = (P1.ship.height / 2);

	P1.rotation = 0;

	P1.color = RED;
	P1.lives = 3;
	P1.score = 0;

	P1.shipAccelerationX = 0;
	P1.shipAccelerationY = 0;

	return P1;
}