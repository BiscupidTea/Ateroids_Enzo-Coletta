#pragma once
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "object/player.h"
#include "object/asteroid.h"
#include "object/enemy.h"
#include "object/powerUp.h"

using namespace std;

void Game(
	bool& closeGame, 
	float& masterVolume,
	int& maxScore
);

void LooseScreen(PLAYER& P1, int maxScore);

namespace DrawF
{
	void DrawGame(
		PLAYER P1,
		BULLETS arrayBulets[],
		int maxAmmo,
		ASTEROID arrayAsteroid[],
		int maxAsteroids,
		bool pause,
		float masterVolume,
		ENEMY E1,
		POWERUP powerUp,
		bool moving
	);

	void DrawInfo(
		PLAYER P1
	);
}

namespace PlayerF
{
	void PlayerMovement(
		PLAYER& P1,
		bool& moving
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
		int maxAmmo,
		POWERUP powerUp
	);

	void PlayerAsteroidColision(
		PLAYER& P1,
		ASTEROID arrayAsteroid[],
		int amountAsteroidsBig,
		int amountAsteroidsMedium,
		int& counterMidAsteroid,
		int& counterSmallAsteroid,
		int maxAsteroids,
		POWERUP powerUp
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

namespace PauseF
{
	void PauseLogic(
		float& masterVolume,
		bool& quit,
		bool& pause,
		bool& closeGame
	);

	void DrawPause(
		float masterVolume
	);
}

namespace PowerUpF
{
	void PowerUpPlayerColision(
		POWERUP& powerUp,
		PLAYER& P1
	);
}

namespace EnemyF
{
	void EnemyTimer(
		ENEMY& E1,
		float& timer,
		float& maxTimer
	);


	void EnemyMovement(
		ENEMY& E1
	);

	void EnemyWallColition(
		ENEMY& E1
	);

	void EnemyPlayerColition(
		ENEMY& E1,
		PLAYER& P1,
		POWERUP powerUp
	);

	void EnemyBulletColition(
		PLAYER& P1,
		ENEMY& E1,
		BULLETS arrayBulets[],
		int maxAmmo
	);

	void EnemyReset(
		ENEMY& E1
	);

}