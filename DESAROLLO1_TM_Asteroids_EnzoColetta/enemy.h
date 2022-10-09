#pragma once
#include "raylib.h"

struct ENEMY
{

};

struct BULLETENEMY
{

};

ENEMY CreateEnemy();

void CreateBulletsEnemy(
	BULLETENEMY& buletE,
	ENEMY Enemy
);