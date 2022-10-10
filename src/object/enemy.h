#pragma once
#include "raylib.h"

struct ENEMY
{
	Rectangle enemy;
	Vector2 origin;
	Vector2 center;
	float rotation;
	int speed;
	bool isDead;
};

ENEMY CreateEnemy();