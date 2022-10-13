#include "powerUp.h"

POWERUP CreatePowerUp()
{
	POWERUP powerUp{};

	powerUp.shot3r = false;
	powerUp.invincible = false;

	powerUp.center.x = static_cast<float>(GetRandomValue(0, GetScreenWidth()));
	powerUp.center.y = static_cast<float>(GetRandomValue(0, GetScreenHeight()));

	if (GetRandomValue(1, 2) == 1)
	{
		powerUp.shot3r = true;
		powerUp.invincible = false;
	}
	else
	{
		powerUp.shot3r = false;
		powerUp.invincible = true;
	}

	powerUp.radius = 15;
	powerUp.timerC = 0;
	powerUp.timerMaxC = 10;
	powerUp.timerA = 0;
	powerUp.timerMaxA = 10;
	powerUp.picked = false;
	powerUp.isActive = false;

	return powerUp;
}