#pragma once
#include "raylib.h"

struct ASTEROIDS
{
	Vector2 XY;
	float radius;
	int tipe;
};

ASTEROIDS CreateAsteroids();