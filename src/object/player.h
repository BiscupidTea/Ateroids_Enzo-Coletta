#pragma once
#include "raylib.h"

struct PLAYER
{
	Rectangle ship;
	Vector2 origin;
	Vector2 center;
	Vector2 XY;
	float rotation;
	Color color;
	int lives;
	int score;
	Vector2 shipAcceleration;
	Vector2 speed;
};

PLAYER CreatePlayer();