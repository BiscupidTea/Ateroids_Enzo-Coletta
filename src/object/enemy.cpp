#include "enemy.h"

ENEMY CreateEnemy()
{
	ENEMY E1{};

	E1.enemy.width = 150;
	E1.enemy.height = 50;
	if (GetRandomValue(1, 2) == 1)
	{
		E1.enemy.x = 0 - E1.enemy.width;
	}
	else
	{
		E1.enemy.x = static_cast<float>(GetScreenWidth());
	}

	E1.enemy.y = static_cast<float>(GetRandomValue(75, (GetScreenHeight() - (static_cast<int> (E1.enemy.height)))));

	E1.center.x = E1.enemy.x + (E1.enemy.width / 2);
	E1.center.y = E1.enemy.y + (E1.enemy.height / 2);

	E1.origin.x = (E1.enemy.width / 2);
	E1.origin.y = (E1.enemy.height / 2);

	E1.rotation = 0;

	if (E1.enemy.x > GetScreenWidth())
	{
		E1.speed = -800;
	}
	else
	{
		E1.speed = 800;
	}

	E1.isDead = true;

	return E1;
}