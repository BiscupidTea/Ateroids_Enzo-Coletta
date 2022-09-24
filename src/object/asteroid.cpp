#include "asteroid.h"

ASTEROIDS CreateAsteroids(ASTEROIDS& asteroid)
{
	//asignar donde salen
	asteroid.radius = 10;
	if (GetRandomValue(1,2) == 1)
	{
		if (GetRandomValue(1, 2) == 1)
		{
			asteroid.center.x = GetScreenWidth() - 10;
		}
		else
		{
			asteroid.center.x = 10;
		}

		asteroid.center.y = GetRandomValue(0, GetScreenHeight());
	}
	else
	{
		if (GetRandomValue(1, 2) == 1)
		{
			asteroid.center.y = GetScreenHeight() - 10;
		}
		else
		{
			asteroid.center.y = 10;
		}

		asteroid.center.x = GetRandomValue(0, GetScreenWidth());
	}

	asteroid.tipe = 3;
	asteroid.speed.x = GetRandomValue(-200, 200);
	asteroid.speed.y = GetRandomValue(-200, 200);
	asteroid.rotation = GetRandomValue(0, 359);

	return asteroid;
}
