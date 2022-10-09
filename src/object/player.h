#pragma once
#include "raylib.h"

struct PLAYER
{
	Rectangle ship;
	Vector2 origin;
	Vector2 center;
	float rotation;
	Color color;
	int lives;
	int score;
	Vector2 shipAcceleration;
	Vector2 speed;

};

struct BULLETS
{
	Vector2 Pos;
	Vector2 speed;
	float rotation;
	float radius;
	bool isShoted;
};

PLAYER CreatePlayer();

void CreateBullets(
	BULLETS& bulet, 
	PLAYER P1
);