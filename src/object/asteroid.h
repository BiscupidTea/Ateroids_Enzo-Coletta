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
	int rotation;
	bool isDestroyed;

};

void CreateAsteroidsBig(ASTEROID& asteroid);
void CreateAsteroidsMedium(ASTEROID& asteroid);
void CreateAsteroidsSmall(ASTEROID& asteroid);