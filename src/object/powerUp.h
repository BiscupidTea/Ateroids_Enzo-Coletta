#pragma once
#include "raylib.h"

struct POWERUP
{
	Vector2 center;
	int id;
	bool shot3r;
	bool invincible;
	bool isActive;
	bool picked;
	float radius;
	float timerC;
	float timerMaxC;
	float timerA;
	float timerMaxA;
};

POWERUP CreatePowerUp();
