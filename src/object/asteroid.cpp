#include "asteroid.h"

ASTEROIDS CreateAsteroids(ASTEROIDS& asteroid)
{

	asteroid.rotation = GetRandomValue(0, 359);
	//asignar que tipo de asteroide es 
	asteroid.tipe = 3;

	//asignar el radio
	if (asteroid.tipe == 3)
	{
		asteroid.radius = 50;
	}
	else
	{
		asteroid.radius = 25;
	}

	//asignar donde salen
	if (GetRandomValue(1, 2) == 1)
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

	//asignar velocidad
	do
	{
		asteroid.speed.x = GetRandomValue(-200, 200);
	} while (asteroid.speed.x > -50 && asteroid.speed.x < 50);
	
	do
	{
		asteroid.speed.y = GetRandomValue(-200, 200);
	} while (asteroid.speed.y > -50 && asteroid.speed.y < 50);

	return asteroid;
}
