#pragma once
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "object/player.h"
#include "object/asteroid.h"

using namespace std;

void Game();

namespace DrawF
{
	void DrawGame(PLAYER P1, Texture2D ship_idle, Texture2D scope, ASTEROIDS arrayAsteroid[]);
	void DrawInfo(Texture2D consol1, PLAYER P1);
}

namespace PlayerF
{
	void PlayerMovement(PLAYER& P1);
	void PlayerWallColition(PLAYER& P1);
	void PlayerShoot(PLAYER& P1);
}

namespace AsteroidF
{
	void AsteroidMovement(ASTEROIDS arrayAsteroids[]);
	void AsteroidWallColition(ASTEROIDS arrayAsteroids[]);
}