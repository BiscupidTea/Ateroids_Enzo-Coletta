#pragma once
#include "raylib.h"

struct PLAYER
{
	Rectangle ship;
	Vector2 origin;
	float rotation;
	Color color;
	int lives;
	int score;
	float shipAccelerationX;
	float shipAccelerationY;
};

PLAYER CreatePlayer();