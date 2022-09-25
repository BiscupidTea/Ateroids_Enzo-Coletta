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
	void DrawGame(PLAYER P1, Texture2D ship_idle, Texture2D scope, ASTEROIDS arrayAsteroid[], int amountAsteroids, BULLETS arrayBulets[], int maxAmmo);
	void DrawInfo(Texture2D consol1, PLAYER P1);
}

namespace PlayerF
{
	void PlayerMovement(PLAYER& P1);
	void PlayerWallColition(PLAYER& P1);
	void PlayerShoot(BULLETS arrayBulets[], int& counter, PLAYER& P1, int maxAmmo);
	void BulletState(BULLETS arrayBulets[], int maxAmmo, PLAYER& P1);
	void PlayerAsteroidColision(PLAYER& P1, ASTEROIDS arrayAsteroids[], int amountAsteroids, Texture2D ship_idle);
}

namespace AsteroidF
{
	void AsteroidMovement(ASTEROIDS arrayAsteroids[], int amountAsteroids);
	void AsteroidWallColition(ASTEROIDS arrayAsteroids[], int amountAsteroids);
}