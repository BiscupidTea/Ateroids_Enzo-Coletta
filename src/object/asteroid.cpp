#include "asteroid.h"

void CreateAsteroidsBig(ASTEROID& asteroid, Texture2D asteroidB)
{
	asteroid.size = Size::Big;
	asteroid.rotation = static_cast<float>(GetRandomValue(0, 359));
	//asignar el radio
	asteroid.radius = static_cast<float>(asteroidB.width/2);

	//asignar donde salen
	if (GetRandomValue(1, 2) == 1)
	{
		if (GetRandomValue(1, 2) == 1)
		{
			asteroid.center.x = GetScreenWidth() - asteroid.radius;
		}
		else
		{
			asteroid.center.x = 50 + asteroid.radius;
		}

		asteroid.center.y = static_cast<float>(GetRandomValue(0, GetScreenHeight()));
	}
	else
	{
		if (GetRandomValue(1, 2) == 1)
		{
			asteroid.center.y = GetScreenHeight() - asteroid.radius;
		}
		else
		{
			asteroid.center.y = 100 + asteroid.radius;
		}

		asteroid.center.x = static_cast<float>(GetRandomValue(0, GetScreenWidth()));
	}

	//asignar velocidad
	do
	{
		asteroid.speed.x = static_cast<float>(GetRandomValue(-100, 100));
	} while (asteroid.speed.x > -50 && asteroid.speed.x < 50);
	
	do
	{
		asteroid.speed.y = static_cast<float>(GetRandomValue(-100, 100));
	} while (asteroid.speed.y < -50 && asteroid.speed.y < 50);

	asteroid.isDestroyed = false;
}

void CreateAsteroidsMedium(ASTEROID& asteroid, Texture2D asteroidM)
{
	asteroid.size = Size::Medium;
	asteroid.rotation = static_cast<float>(GetRandomValue(0, 359));
	//asignar el radio
	asteroid.radius = static_cast<float>(asteroidM.width/2);

	//asignar donde salen
	asteroid.center.x = - 50;
	asteroid.center.y = - 50;
	
	//asignar velocidad
	asteroid.speed.x = 0;
	asteroid.speed.y = 0;

	asteroid.isDestroyed = true;
}

void CreateAsteroidsSmall(ASTEROID& asteroid, Texture2D asteroidS)
{	
	asteroid.size = Size::Small;
	asteroid.rotation = static_cast<float>(GetRandomValue(0, 359));
	//asignar el radio
	asteroid.radius = static_cast<float>(asteroidS.width/2);

	//asignar donde salen
	asteroid.center.x = -50;
	asteroid.center.y = -50;


	//asignar velocidad
	asteroid.speed.x = 0;
	asteroid.speed.y = 0;

	asteroid.isDestroyed = true;
}