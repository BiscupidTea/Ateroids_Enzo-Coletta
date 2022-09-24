#pragma once
#include "raylib.h"

struct ASTEROIDS
{
	Vector2 center;
	Vector2 speed;
	float radius;
	int rotation;
	int tipe;
};

ASTEROIDS CreateAsteroids(ASTEROIDS& asteroid);