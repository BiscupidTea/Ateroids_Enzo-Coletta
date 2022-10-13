#pragma once
#include "raylib.h"

enum class Size
{
	Big = 1,
	Medium,
	Small
};


struct ASTEROID
{
	Size size;
	Vector2 center;
	Vector2 speed;
	float radius;
	float rotation;
	bool isDestroyed;

};

void CreateAsteroidsBig(
	ASTEROID& asteroid,
	Texture2D asteroidB
);

void CreateAsteroidsMedium(
	ASTEROID& asteroid,
	Texture2D asteroidM
);

void CreateAsteroidsSmall(
	ASTEROID& asteroid,
	Texture2D asteroidS
);