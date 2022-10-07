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
	void DrawGame(
		PLAYER P1,
		Texture2D ship_idle,
		Texture2D scope,
		BULLETS arrayBulets[],
		int maxAmmo,
		ASTEROID arrayAsteroid[],
		int maxAsteroids
	);

	void DrawInfo(
		Texture2D consol1, 
		PLAYER P1
	);
}

namespace PlayerF
{
	void PlayerMovement(
		PLAYER& P1
	);

	void PlayerWallColition(
		PLAYER& P1
	);

	void BulletState(
		BULLETS arrayBulets[], 
		int maxAmmo, 
		PLAYER& P1
	);

	void PlayerShoot(
		BULLETS arrayBulets[], 
		int& counter, 
		PLAYER& P1, 
		int maxAmmo
	);

	void PlayerAsteroidColision(
		PLAYER& P1, 
		Texture2D ship_idle,
		ASTEROID arrayAsteroid[],
		int amountAsteroidsBig,
		int amountAsteroidsMedium,
		int& counterMidAsteroid,
		int& counterSmallAsteroid,
		int maxAsteroids
	);

	void BulletAsteroidColition(
		ASTEROID arrayAsteroid[],
		int amountAsteroidsBig,
		int amountAsteroidsMedium,
		BULLETS arrayBulets[],
		int maxAmmo,
		PLAYER& P1,
		int& counterMidAsteroid,
		int& counterSmallAsteroid,
		int maxAsteroids
	);
}

namespace AsteroidF
{
	void AsteroidMovement(
		ASTEROID arrayAsteroid[],
		int maxAsteroids
	);

	void AsteroidWallColition(
		ASTEROID arrayAsteroid[],
		int maxAsteroids
	);

	void AsteroidReset(
		ASTEROID arrayAsteroid[],
		int amountAsteroidsBig,
		int amountAsteroidsMedium,
		int& counterMidAsteroid,
		int& counterSmallAsteroid,
		int maxAsteroids
	);
}