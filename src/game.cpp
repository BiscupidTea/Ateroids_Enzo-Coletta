#include "game.h"

Texture2D ship_move;
Texture2D scope;
Texture2D background;
Texture2D ship_stop;
Texture2D asteroidB;
Texture2D asteroidM;
Texture2D asteroidS;
Texture2D enemyB;
Texture2D playB;
Texture2D rulesB;
Texture2D optionsB;
Texture2D creditsB;
Texture2D escapeB;
Texture2D continueB;
Texture2D disparo;

Sound asteroidSound;
Sound dead;
Sound shieldPiked;
Sound shoterPiked;
Sound shot1;
Music gamemusic;

void Game(bool& closeGame, float& masterVolume, int& maxScore)
{
	//declaraciones//
	PLAYER P1 = CreatePlayer();
	ENEMY E1 = CreateEnemy(enemyB);

	masterVolume = 0.5f;
	float timer = 0;
	float maxTimer = 7;
	P1.radius = ship_move.width / static_cast <float>(3);
	bool quit = false;
	bool moving = false;

	//asteroids
	const int amountAsteroidsBig = 8;
	const int amountAsteroidsMedium = amountAsteroidsBig * 2;
	const int amountAsteroidsSmall = amountAsteroidsMedium * 2;
	const int maxAsteroids = amountAsteroidsBig + amountAsteroidsMedium + amountAsteroidsSmall;
	ASTEROID arrayAsteroid[maxAsteroids];
	int counterMidAsteroid = 0;
	int counterSmallAsteroids = 0;

	for (int i = 0; i < amountAsteroidsBig; i++)
	{
		CreateAsteroidsBig(arrayAsteroid[i], asteroidB);
	}

	for (int i = amountAsteroidsBig; i < amountAsteroidsBig + amountAsteroidsMedium; i++)
	{
		CreateAsteroidsMedium(arrayAsteroid[i], asteroidM);
	}

	for (int i = amountAsteroidsBig + amountAsteroidsMedium; i < maxAsteroids; i++)
	{
		CreateAsteroidsSmall(arrayAsteroid[i], asteroidS);
	}


	//bulets
	const int maxAmmo = 300;
	BULLETS arrayBulets[maxAmmo];

	for (int i = 0; i < maxAmmo; i++)
	{
		CreateBullets(arrayBulets[i], P1);
	}

	//power ups
	POWERUP powerUp = CreatePowerUp();

	//others
	bool pause = false;
	int counterBullet = 0;
	P1.ship.width = static_cast<float>(ship_move.width);
	P1.ship.height = static_cast<float>(ship_move.height);
	HideCursor();

	///////////start game/////////////
	PlayMusicStream(gamemusic);
	while (P1.lives > 0 && !WindowShouldClose())
	{
		UpdateMusicStream(gamemusic);
		if (P1.score > maxScore)
		{
			maxScore = P1.score;
		}

		if (IsKeyPressed(KEY_P))
		{
			if (pause == false)
			{
				pause = true;
			}
			else
			{
				pause = false;
			}
		}

		if (pause == false)
		{
			PlayerF::BulletState(arrayBulets, maxAmmo, P1);
			PlayerF::PlayerShoot(arrayBulets, counterBullet, P1, maxAmmo, powerUp);
			PlayerF::PlayerWallColition(P1);
			PlayerF::PlayerMovement(P1, moving);
			PlayerF::BulletAsteroidColition(arrayAsteroid, amountAsteroidsBig, amountAsteroidsMedium, arrayBulets, maxAmmo, P1, counterMidAsteroid, counterSmallAsteroids, maxAsteroids);
			PlayerF::PlayerAsteroidColision(P1, arrayAsteroid, amountAsteroidsBig, amountAsteroidsMedium, counterMidAsteroid, counterSmallAsteroids, maxAsteroids, powerUp);
			AsteroidF::AsteroidMovement(arrayAsteroid, maxAsteroids);
			AsteroidF::AsteroidWallColition(arrayAsteroid, maxAsteroids);
			AsteroidF::AsteroidReset(arrayAsteroid, amountAsteroidsBig, amountAsteroidsMedium, counterMidAsteroid, counterSmallAsteroids, maxAsteroids);
			EnemyF::EnemyMovement(E1);
			EnemyF::EnemyWallColition(E1);
			EnemyF::EnemyPlayerColition(E1, P1, powerUp);
			EnemyF::EnemyBulletColition(P1, E1, arrayBulets, maxAmmo);

			//powerup
			if (!powerUp.picked && !powerUp.isActive)
			{
				powerUp.timerC += GetFrameTime();
				if (powerUp.timerC >= powerUp.timerMaxC)
				{
					powerUp.isActive = true;
					powerUp.picked = false;
				}
			}

			if (powerUp.isActive)
			{
				PowerUpF::PowerUpPlayerColision(powerUp, P1);
			}

			if (powerUp.picked)
			{
				powerUp.timerA += GetFrameTime();
				if (powerUp.timerA >= powerUp.timerMaxA)
				{
					powerUp.isActive = false;
					powerUp.picked = false;
					powerUp.timerC = 0;
					powerUp = CreatePowerUp();
				}
			}
			cout << powerUp.timerC << endl;

			//enemy
			EnemyF::EnemyTimer(E1, timer, maxTimer);

		}

		if (pause == true)
		{
			PauseF::PauseLogic(masterVolume, quit, pause, closeGame);
			if (quit == true)
			{
				return;
			}
		}



		//draw
		DrawF::DrawGame(P1, arrayBulets, maxAmmo, arrayAsteroid, maxAsteroids, pause, masterVolume, E1, powerUp, moving);

		if (P1.lives <= 0)
		{
			Rectangle exit;
			exit.x = static_cast<float>(GetScreenWidth() / 2 - 100);
			exit.y = static_cast<float>(GetScreenHeight() / 2 - GetScreenHeight() / 4 + 300);
			exit.width = 200;
			exit.height = 40;

			while (!CheckCollisionPointRec(GetMouseDelta(), exit) && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				LooseScreen(P1, maxScore);
			}
			closeGame = false;
			return;
		}
	}

}

namespace DrawF
{
	void DrawGame(PLAYER P1, BULLETS arrayBulets[], int maxAmmo, ASTEROID arrayAsteroid[], int maxAsteroids, bool pause, float masterVolume, ENEMY E1, POWERUP powerUp, bool moving)
	{
		BeginDrawing();
		ClearBackground(WHITE);
		DrawTexture(background, 0, 0, WHITE);

		//asteroids
		for (int x = 0; x < maxAsteroids; x++)
		{
			if (arrayAsteroid[x].isDestroyed == false && arrayAsteroid[x].size == Size::Big)
			{
				Rectangle sourceAsteroid = { 0.0f, 0.0f, static_cast<float>(asteroidB.width), static_cast<float>(asteroidB.height) };
				Rectangle dest = { arrayAsteroid[x].center.x, arrayAsteroid[x].center.y, static_cast<float>(asteroidB.width), static_cast<float>(asteroidB.height) };

				DrawCircle(static_cast<int>(arrayAsteroid[x].center.x), static_cast<int>(arrayAsteroid[x].center.y), arrayAsteroid[x].radius, RED);
				DrawTexturePro(asteroidB, sourceAsteroid, dest, { static_cast<float>(asteroidB.width / 2),static_cast<float>(asteroidB.height / 2) }, arrayAsteroid[x].rotation, WHITE);
			}
			else if (arrayAsteroid[x].isDestroyed == false && arrayAsteroid[x].size == Size::Medium)
			{
				Rectangle sourceAsteroid = { 0.0f, 0.0f, static_cast<float>(asteroidM.width) , static_cast<float>(asteroidM.height) };
				Rectangle dest = { arrayAsteroid[x].center.x, arrayAsteroid[x].center.y, static_cast<float>(asteroidM.width), static_cast<float>(asteroidM.height) };

				DrawCircle(static_cast<int>(arrayAsteroid[x].center.x), static_cast<int>(arrayAsteroid[x].center.y), arrayAsteroid[x].radius, RED);
				DrawTexturePro(asteroidM, sourceAsteroid, dest, { static_cast<float>(asteroidM.width / 2),static_cast<float>(asteroidM.height / 2) }, arrayAsteroid[x].rotation, WHITE);
			}
			else if (arrayAsteroid[x].isDestroyed == false && arrayAsteroid[x].size == Size::Small)
			{
				Rectangle sourceAsteroid = { 0.0f, 0.0f, static_cast<float>(asteroidS.width) , static_cast<float>(asteroidS.height) };
				Rectangle dest = { arrayAsteroid[x].center.x, arrayAsteroid[x].center.y, static_cast<float>(asteroidS.width), static_cast<float>(asteroidS.height) };

				DrawCircle(static_cast<int>(arrayAsteroid[x].center.x), static_cast<int>(arrayAsteroid[x].center.y), arrayAsteroid[x].radius, RED);
				DrawTexturePro(asteroidS, sourceAsteroid, dest, { static_cast<float>(asteroidS.width / 2),static_cast<float>(asteroidS.height / 2) }, arrayAsteroid[x].rotation, WHITE);
			}
		}

		//bulets
		for (int i = 0; i < maxAmmo; i++)
		{
			if (arrayBulets[i].isShoted)
			{
				Rectangle source = { 0.0f, 0.0f, static_cast<float>(disparo.width), static_cast<float>(disparo.height) };
				Rectangle destRec = { arrayBulets[i].Pos.x, arrayBulets[i].Pos.y, static_cast<float>(disparo.width), static_cast<float>(disparo.height) };	
				Vector2 origin = { static_cast<float>(disparo.width / 2), static_cast<float>(disparo.height / 2) };

				//DrawCircle(static_cast<int>(arrayBulets[i].Pos.x), static_cast<int>(arrayBulets[i].Pos.y), arrayBulets[i].radius, RED);
				DrawTexturePro(disparo, source, destRec, origin, arrayBulets[i].rotation, WHITE);
			}
		}

		//player 
		if (powerUp.picked && powerUp.invincible)
		{
			DrawCircle(static_cast<int>(P1.ship.x), static_cast<int>(P1.ship.y), P1.radius, SKYBLUE);
		}

		if (moving == true)
		{
			Rectangle source = { 0.0f, 0.0f, static_cast<float>(ship_move.width), static_cast<float>(ship_move.height) };
			Rectangle destRec = { P1.ship.x, P1.ship.y, static_cast<float>(ship_move.width), static_cast<float>(ship_move.height) };

			DrawTexturePro(ship_move, source, destRec, P1.origin, P1.rotation, WHITE);
		}
		else
		{
			Rectangle source = { 0.0f, 0.0f, static_cast<float>(ship_stop.width), static_cast<float>(ship_stop.height) };
			Rectangle destRec = { P1.ship.x, P1.ship.y, static_cast<float>(ship_stop.width), static_cast<float>(ship_stop.height) };

			DrawTexturePro(ship_stop, source, destRec, P1.origin, P1.rotation, WHITE);
		}
		DrawTexture(scope, static_cast<int>(GetMouseX() - 19.5), static_cast<int>(GetMouseY() - 19.5), WHITE);

		//enemy
		if (!E1.isDead)
		{
			//DrawRectangle(static_cast<int>(E1.enemy.x), static_cast<int>(E1.enemy.y), static_cast<int>(E1.enemy.width), static_cast<int>(E1.enemy.height), RED);
			DrawTexture(enemyB, static_cast<int>(E1.enemy.x), static_cast<int>(E1.enemy.y), WHITE);
		}

		//draw powerups
		if (powerUp.isActive && powerUp.invincible)
		{
			DrawCircle(static_cast<int>(powerUp.center.x), static_cast<int>(powerUp.center.y), powerUp.radius, BLUE);
		}
		else if (powerUp.isActive && powerUp.shot3r)
		{
			DrawCircle(static_cast<int>(powerUp.center.x), static_cast<int>(powerUp.center.y), powerUp.radius, VIOLET);
		}

		//score/lives/
		DrawInfo(P1);

		if (pause == true)
		{
			PauseF::DrawPause(masterVolume);
			DrawTexture(scope, static_cast<int>(GetMouseX() - 19.5), static_cast<int>(GetMouseY() - 19.5), WHITE);
		}

		EndDrawing();
	}

	void DrawInfo(PLAYER P1)
	{
		//lives
		if (P1.lives == 3)
		{
			DrawTexture(ship_move, 0, 5, WHITE);
			DrawTexture(ship_move, ship_move.width, 5, WHITE);
			DrawTexture(ship_move, ship_move.width * 2, 5, WHITE);
		}
		else if (P1.lives == 2)
		{
			DrawTexture(ship_move, 0, 5, WHITE);
			DrawTexture(ship_move, ship_move.width, 5, WHITE);
		}
		else
		{
			DrawTexture(ship_move, 0, 5, WHITE);
		}

		//score
		DrawText(TextFormat("%05i", P1.score), GetScreenWidth() - MeasureText("00000", 50) - 50, 0, 50, BLACK);

	}
}

namespace PlayerF
{
	void PlayerMovement(PLAYER& P1, bool& moving)
	{
		//logic rotation
		Vector2 vectorDirection;
		Vector2 normalizeDirection;
		float arcotan;
		float angulo;

		vectorDirection.x = GetMouseX() - P1.ship.x;
		vectorDirection.y = GetMouseY() - P1.ship.y;
		arcotan = atan(vectorDirection.y / vectorDirection.x);
		angulo = arcotan * 180 / PI;

		if (vectorDirection.x < 0)
		{
			angulo += 180;
		}

		P1.rotation = angulo;

		//logic movement
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			normalizeDirection = Vector2Normalize(vectorDirection);

			P1.shipAcceleration.x += normalizeDirection.x;
			P1.shipAcceleration.y += normalizeDirection.y;
			moving = true;

		}
		else
		{
			moving = false;
		}

		//cout << P1.speed.x << " " << P1.speed.y << endl;

		P1.speed.x = P1.shipAcceleration.x;
		P1.speed.y = P1.shipAcceleration.y;

		P1.ship.x += P1.speed.x * GetFrameTime() / 4;
		P1.ship.y += P1.speed.y * GetFrameTime() / 4;

		P1.center.x = P1.ship.x + (P1.ship.width / 2);
		P1.center.y = P1.ship.y + (P1.ship.height / 2);

		P1.origin.x = (P1.ship.width / 2);
		P1.origin.y = (P1.ship.height / 2);

	}

	void PlayerWallColition(PLAYER& P1)
	{
		if (P1.ship.x > GetScreenWidth())
		{
			P1.ship.x = 1;
		}
		else if (P1.ship.x < 0)
		{
			P1.ship.x = static_cast<float>(GetScreenWidth() - 1);
		}

		if (P1.ship.y > GetScreenHeight())
		{
			P1.ship.y = 0;
		}
		else if (P1.ship.y < 0)
		{
			P1.ship.y = static_cast<float>(GetScreenHeight() - 1);
		}
	}

	void BulletState(BULLETS arrayBulets[], int maxAmmo, PLAYER& P1)
	{
		for (int i = 0; i < maxAmmo; i++)
		{
			if (arrayBulets[i].isShoted)
			{
				if (arrayBulets[i].Pos.x < 0 || arrayBulets[i].Pos.x > GetScreenWidth())
				{
					arrayBulets[i].isShoted = false;
				}

				else if (arrayBulets[i].Pos.y < 0 || arrayBulets[i].Pos.y > GetScreenHeight())
				{
					arrayBulets[i].isShoted = false;
				}
			}
			else
			{
				arrayBulets[i].Pos.x = P1.ship.x;
				arrayBulets[i].Pos.y = P1.ship.y;
				arrayBulets[i].speed.x = 0;
				arrayBulets[i].speed.y = 0;
			}

		}
	}

	void PlayerShoot(BULLETS arrayBulets[], int& counter, PLAYER& P1, int maxAmmo, POWERUP powerUp)
	{
		Vector2 vectorDirection;
		Vector2 normalizeDirection;
		vectorDirection.x = GetMouseX() - P1.ship.x;
		vectorDirection.y = GetMouseY() - P1.ship.y;


		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			normalizeDirection = Vector2Normalize(vectorDirection);
			PlaySound(shot1);
			if (counter >= maxAmmo)
			{
				counter = 0;
			}

			if (powerUp.picked && powerUp.shot3r)
			{
				arrayBulets[counter].speed.x += normalizeDirection.x;
				arrayBulets[counter].speed.y += normalizeDirection.y;
				arrayBulets[counter].speed.x *= 500;
				arrayBulets[counter].speed.y *= 500;
				arrayBulets[counter].isShoted = true;

				arrayBulets[counter + 1].speed.x += (normalizeDirection.x);
				arrayBulets[counter + 1].speed.y += normalizeDirection.y;
				arrayBulets[counter + 1].speed.x *= 400;
				arrayBulets[counter + 1].speed.y *= 400;
				arrayBulets[counter + 1].isShoted = true;

				arrayBulets[counter + 2].speed.x += normalizeDirection.x;
				arrayBulets[counter + 2].speed.y += normalizeDirection.y;
				arrayBulets[counter + 2].speed.x *= 300;
				arrayBulets[counter + 2].speed.y *= 300;
				arrayBulets[counter + 2].isShoted = true;
				counter += 3;
			}
			else
			{
				arrayBulets[counter].speed.x += normalizeDirection.x;
				arrayBulets[counter].speed.y += normalizeDirection.y;
				arrayBulets[counter].speed.x *= 500;
				arrayBulets[counter].speed.y *= 500;
				arrayBulets[counter].isShoted = true;
				counter++;
			}

			//cout << "normal shot " << counter << endl;
			//cout << normalizeDirection.x << " " << normalizeDirection.y << endl;

		}

		for (int i = 0; i < maxAmmo; i++)
		{
			if (arrayBulets[i].isShoted)
			{
				arrayBulets[i].Pos.x += (arrayBulets[i].speed.x * GetFrameTime());
				arrayBulets[i].Pos.y += (arrayBulets[i].speed.y * GetFrameTime());
				//cout << arrayBulets[i].Pos.x << " " << arrayBulets[i].Pos.y << endl;
				//cout << arrayBulets[i].speed.x << " " << arrayBulets[i].speed.y << endl;
			}
		}

	}

	void PlayerAsteroidColision(PLAYER& P1, ASTEROID arrayAsteroid[], int amountAsteroidsBig, int amountAsteroidsMedium, int& counterMidAsteroid, int& counterSmallAsteroid, int maxAsteroids, POWERUP powerUp)
	{
		if (powerUp.picked && powerUp.invincible)
		{

		}
		else
		{

			for (int i = 0; i < maxAsteroids; i++)
			{
				float distX = P1.ship.x - arrayAsteroid[i].center.x;
				float distY = P1.ship.y - arrayAsteroid[i].center.y;
				float distance = sqrt((distX * distX) + (distY * distY));

				if (distance <= P1.radius + arrayAsteroid[i].radius)
				{
					P1.lives--;
					P1.speed.x = 0;
					P1.speed.y = 0;
					P1.ship.x = static_cast<float>(GetScreenWidth() / 2);
					P1.ship.y = static_cast<float>(GetScreenHeight() / 2);
					PlaySound(dead);

					for (int x = 0; x < amountAsteroidsBig; x++)
					{
						CreateAsteroidsBig(arrayAsteroid[x], asteroidB);

					}

					for (int x = amountAsteroidsBig + 1; x < amountAsteroidsBig + amountAsteroidsMedium; x++)
					{
						CreateAsteroidsMedium(arrayAsteroid[x], asteroidM);
					}

					for (int x = amountAsteroidsBig + amountAsteroidsMedium + 1; x < maxAsteroids; x++)
					{
						CreateAsteroidsSmall(arrayAsteroid[x], asteroidS);
					}

					counterMidAsteroid = 0;
					counterSmallAsteroid = 0;
				}
			}
		}
	}

	void BulletAsteroidColition(ASTEROID arrayAsteroid[], int amountAsteroidsBig, int amountAsteroidsMedium, BULLETS arrayBulets[], int maxAmmo, PLAYER& P1, int& counterMidAsteroid, int& counterSmallAsteroid, int maxAsteroids)
	{
		for (int i = 0; i < maxAsteroids; i++)
		{
			if (arrayAsteroid[i].isDestroyed == false)
			{
				for (int x = 0; x < maxAmmo; x++)
				{
					if (arrayBulets[x].isShoted)
					{


						float distX = arrayBulets[x].Pos.x - arrayAsteroid[i].center.x;
						float distY = arrayBulets[x].Pos.y - arrayAsteroid[i].center.y;
						float distance = sqrt((distX * distX) + (distY * distY));

						if (distance <= arrayBulets[x].radius + arrayAsteroid[i].radius)
						{
							//cout << "colision detectada" << endl;
							arrayAsteroid[i].isDestroyed = true;
							arrayBulets[x].isShoted = false;
							P1.score++;
							PlaySound(asteroidSound);


							if (arrayAsteroid[i].isDestroyed && arrayAsteroid[i].size == Size::Big)
							{
								//cout << "creados 2 medium" << endl;
								counterMidAsteroid += 2;
								arrayAsteroid[amountAsteroidsBig + counterMidAsteroid].center = arrayAsteroid[i].center;
								arrayAsteroid[amountAsteroidsBig + counterMidAsteroid - 1].center = arrayAsteroid[i].center;
								arrayAsteroid[amountAsteroidsBig + counterMidAsteroid].isDestroyed = false;
								arrayAsteroid[amountAsteroidsBig + counterMidAsteroid - 1].isDestroyed = false;
								//asteroid 1
								do
								{
									arrayAsteroid[amountAsteroidsBig + counterMidAsteroid].speed.x = static_cast<float>(GetRandomValue(-200, 200));
								} while (arrayAsteroid[amountAsteroidsBig + counterMidAsteroid].speed.x > -100 && arrayAsteroid[amountAsteroidsBig + counterMidAsteroid].speed.x < 100);
								do
								{
									arrayAsteroid[amountAsteroidsBig + counterMidAsteroid].speed.y = static_cast<float>(GetRandomValue(-200, 200));
								} while (arrayAsteroid[amountAsteroidsBig + counterMidAsteroid].speed.y > -100 && arrayAsteroid[amountAsteroidsBig + counterMidAsteroid].speed.y < 100);
								//asteroid 2
								do
								{
									arrayAsteroid[amountAsteroidsBig + counterMidAsteroid - 1].speed.x = static_cast<float>(GetRandomValue(-200, 200));
								} while (arrayAsteroid[amountAsteroidsBig + counterMidAsteroid - 1].speed.x < -100 && arrayAsteroid[amountAsteroidsBig + counterMidAsteroid - 1].speed.x < 100);
								do
								{
									arrayAsteroid[amountAsteroidsBig + counterMidAsteroid - 1].speed.y = static_cast<float>(GetRandomValue(-200, 200));
								} while (arrayAsteroid[amountAsteroidsBig + counterMidAsteroid - 1].speed.y < -100 && arrayAsteroid[amountAsteroidsBig + counterMidAsteroid - 1].speed.y < 100);

							}
							else if (arrayAsteroid[i].isDestroyed && arrayAsteroid[i].size == Size::Medium)
							{
								//	cout << "creados 2 small" << endl;
								counterSmallAsteroid += 2;
								arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid].center = arrayAsteroid[i].center;
								arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid - 1].center = arrayAsteroid[i].center;
								arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid].isDestroyed = false;
								arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid - 1].isDestroyed = false;

								do
								{
									arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid].speed.x = static_cast<float>(GetRandomValue(-200, 200));
								} while (arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid].speed.x > -100 && arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid].speed.x < 100);
								do
								{
									arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid].speed.y = static_cast<float>(GetRandomValue(-200, 200));
								} while (arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid].speed.y > -100 && arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid].speed.y < 100);

								do
								{
									arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid - 1].speed.x = static_cast<float>(GetRandomValue(-200, 200));
								} while (arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid - 1].speed.x < -100 && arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid - 1].speed.x < 100);
								do
								{
									arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid - 1].speed.y = static_cast<float>(GetRandomValue(-200, 200));
								} while (arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid - 1].speed.y < -100 && arrayAsteroid[amountAsteroidsBig + amountAsteroidsMedium + counterSmallAsteroid - 1].speed.y < 100);

							}
							x = maxAmmo;
						}
					}
				}
			}

		}
	}
}

namespace AsteroidF
{
	void AsteroidMovement(ASTEROID arrayAsteroid[], int maxAsteroids)
	{
		for (int x = 0; x < maxAsteroids; x++)
		{
			if (arrayAsteroid[x].isDestroyed)
			{
				arrayAsteroid[x].center.x = -300;
				arrayAsteroid[x].center.y = -300;
			}
			else
			{
				arrayAsteroid[x].center.x += arrayAsteroid[x].speed.x * GetFrameTime();
				arrayAsteroid[x].center.y += arrayAsteroid[x].speed.y * GetFrameTime();
			}
		}
	}

	void AsteroidWallColition(ASTEROID arrayAsteroid[], int maxAsteroids)
	{
		for (int x = 0; x < maxAsteroids; x++)
		{
			if (arrayAsteroid[x].isDestroyed == false)
			{
				if (arrayAsteroid[x].center.x > GetScreenWidth())
				{
					arrayAsteroid[x].center.x = 1;
				}
				else if (arrayAsteroid[x].center.x < 0)
				{
					arrayAsteroid[x].center.x = static_cast<float>(GetScreenWidth() - 1);
				}
				else if (arrayAsteroid[x].center.y > GetScreenHeight())
				{
					arrayAsteroid[x].center.y = 0;
				}
				else if (arrayAsteroid[x].center.y < 0)
				{
					arrayAsteroid[x].center.y = static_cast<float>(GetScreenHeight() - 1);
				}
			}
		}
	}

	void AsteroidReset(ASTEROID arrayAsteroid[], int amountAsteroidsBig, int amountAsteroidsMedium, int& counterMidAsteroid, int& counterSmallAsteroid, int maxAsteroids)
	{
		int counter = 0;

		for (int i = 0; i < maxAsteroids; i++)
		{
			if (arrayAsteroid[i].isDestroyed)
			{
				counter++;
			}
		}

		if (counter == maxAsteroids)
		{
			for (int i = 0; i < amountAsteroidsBig; i++)
			{
				CreateAsteroidsBig(arrayAsteroid[i], asteroidB);
			}

			for (int i = amountAsteroidsBig; i < amountAsteroidsBig + amountAsteroidsMedium; i++)
			{
				CreateAsteroidsMedium(arrayAsteroid[i], asteroidM);
			}

			for (int i = amountAsteroidsBig + amountAsteroidsMedium; i < maxAsteroids; i++)
			{
				CreateAsteroidsSmall(arrayAsteroid[i], asteroidS);
			}

			counterMidAsteroid = 0;
			counterSmallAsteroid = 0;
		}

	}
}

namespace PauseF
{
	void PauseLogic(float& masterVolume, bool& quit, bool& pause, bool& closeGame)
	{
		cout << masterVolume << endl;
		Rectangle con = {};
		Rectangle mas = {};
		Rectangle menos = {};
		Rectangle exit = {};

		con.x = static_cast<float>(GetScreenWidth() / 2 - continueB.width / 2);
		con.y = static_cast<float>((GetScreenHeight() / 2) - 200);
		con.width = static_cast<float>(continueB.width);
		con.height = static_cast<float>(continueB.height);

		mas.x = static_cast<float>(GetScreenWidth() / 2 - 50 - 50);
		mas.y = static_cast<float>(GetScreenHeight() / 2 - 25);
		mas.width = static_cast<float>(50);
		mas.height = static_cast<float>(50);

		menos.x = static_cast<float>(GetScreenWidth() / 2 + 50);
		menos.y = static_cast<float>(GetScreenHeight() / 2 - 25);
		menos.width = static_cast<float>(50);
		menos.height = static_cast<float>(50);

		exit.x = static_cast<float>(GetScreenWidth() / 2 - escapeB.width / 2);
		exit.y = static_cast<float>((GetScreenHeight() / 2) + 150);
		exit.width = static_cast<float>(escapeB.width);
		exit.height = static_cast<float>(escapeB.height);


		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (CheckCollisionPointRec(GetMousePosition(), con))
			{
				pause = false;
			}
			if (CheckCollisionPointRec(GetMousePosition(), mas))
			{
				masterVolume += static_cast <float>(0.1);
				cout << "+" << endl;
				SetMasterVolume(masterVolume);
			}
			if (CheckCollisionPointRec(GetMousePosition(), menos))
			{
				masterVolume -= static_cast <float>(0.1);
				cout << "-" << endl;
				SetMasterVolume(masterVolume);
			}
			if (CheckCollisionPointRec(GetMousePosition(), exit))
			{
				quit = true;
				closeGame = false;
			}
			cout << "hola" << endl;
		}

		if (masterVolume > 1.0)
		{
			masterVolume = 1.0;
		}

		if (masterVolume < 0.0)
		{
			masterVolume = 0.0;
		}
	}

	void DrawPause(float masterVolume)
	{
		int volumedraw = static_cast<int>(masterVolume * 10);
		Rectangle Option;
		Option.height = 80;
		Option.width = 80;
		Option.x = static_cast<float>((GetScreenWidth() / 2) - 40);

		//draw background
		DrawRectangle(GetScreenWidth() / 2 - 250, GetScreenHeight() / 2 - 250, 500, 500, MAROON);
		//options

		//--resume--
		DrawTexture(continueB, GetScreenWidth() / 2 - continueB.width / 2, (GetScreenHeight() / 2) - 200, WHITE);

		//--sound--
		DrawText("SOUND", (GetScreenWidth() / 2) - (MeasureText("SOUND", 40) / 2), (GetScreenHeight() / 2) - 100, 40, BLACK);
		DrawRectangle(static_cast<int>(Option.x), static_cast<int>((GetScreenHeight() / 2) - Option.height / 2), static_cast<int>(Option.width), static_cast<int>(Option.height), BLACK);
		DrawText(TextFormat("%i", volumedraw), (GetScreenWidth() / 2) - 39, (GetScreenHeight() / 2) - 35, 70, WHITE);

		DrawRectangle(GetScreenWidth() / 2 - 50 - 50, GetScreenHeight() / 2 - 25, 50, 50, BLACK);
		DrawText("+", GetScreenWidth() / 2 - 40 - 50, GetScreenHeight() / 2 - 25, 50, WHITE);

		DrawRectangle(GetScreenWidth() / 2 + 50, GetScreenHeight() / 2 - 25, 50, 50, BLACK);
		DrawText("-", GetScreenWidth() / 2 + 65, GetScreenHeight() / 2 - 25, 50, WHITE);

		//--exit--
		DrawTexture(escapeB, GetScreenWidth() / 2 - escapeB.width / 2, (GetScreenHeight() / 2) + 150, WHITE);
	}
}

namespace PowerUpF
{
	void PowerUpPlayerColision(POWERUP& powerUp, PLAYER& P1)
	{
		float distX = P1.ship.x - powerUp.center.x;
		float distY = P1.ship.y - powerUp.center.y;
		float distance = sqrt((distX * distX) + (distY * distY));

		if (distance <= (ship_move.width / 2 + 2) + powerUp.radius)
		{
			powerUp.picked = true;
			powerUp.isActive = false;
			powerUp.timerA = 0;
			if (powerUp.isActive && powerUp.invincible)
			{
				PlaySound(shieldPiked);
			}
			else
			{
				PlaySound(shoterPiked);
			}
		}

	}
}

namespace EnemyF
{
	void EnemyTimer(ENEMY& E1, float& timer, float& maxTimer)
	{
		if (E1.isDead && (timer >= maxTimer))
		{
			EnemyF::EnemyReset(E1);
		}

		if ((timer >= maxTimer) && !E1.isDead)
		{
			timer = 0;
		}

		if (E1.isDead)
		{
			timer += GetFrameTime();
		}
	}

	void EnemyMovement(ENEMY& E1)
	{
		E1.enemy.x += E1.speed * GetFrameTime();

		E1.center.x = E1.enemy.x + (E1.enemy.width / 2);
		E1.center.y = E1.enemy.y + (E1.enemy.height / 2);

		E1.origin.x = (E1.enemy.width / 2);
		E1.origin.y = (E1.enemy.height / 2);
	}

	void EnemyWallColition(ENEMY& E1)
	{
		if (E1.enemy.x < 0 - E1.enemy.width || E1.enemy.x > GetScreenWidth())
		{
			E1.speed *= -1;
			E1.enemy.y = static_cast<float>(GetRandomValue(75, (GetScreenHeight() - (static_cast<int> (E1.enemy.height)))));
		}

	}

	void EnemyPlayerColition(ENEMY& E1, PLAYER& P1, POWERUP powerUp)
	{
		Rectangle save;
		save.x = P1.ship.x;
		save.y = P1.ship.y;
		save.width = static_cast<float>(ship_move.width);
		save.height = static_cast<float>(ship_move.height);

		if (powerUp.picked && powerUp.invincible)
		{

		}
		else
		{
			if (!E1.isDead)
			{
				if (CheckCollisionRecs(save, E1.enemy))
				{
					PlaySound(dead);
					cout << " colition detected" << endl;
					P1.lives--;
					P1.speed.x = 0;
					P1.speed.y = 0;
					P1.ship.x = static_cast<float>(GetScreenWidth() / 2);
					P1.ship.y = static_cast<float>(GetScreenHeight() / 2);
					E1.isDead = true;
				}
			}
		}
	}

	void EnemyBulletColition(PLAYER& P1, ENEMY& E1, BULLETS arrayBulets[], int maxAmmo)
	{
		if (!E1.isDead)
		{
			for (int x = 0; x < maxAmmo; x++)
			{
				if (CheckCollisionCircleRec(arrayBulets[x].Pos, arrayBulets[x].radius, E1.enemy))
				{
					E1.isDead = true;
					arrayBulets[x].isShoted = false;
					x = maxAmmo;
					P1.score += 5;
				}
			}
		}
	}

	void EnemyReset(ENEMY& E1)
	{
		E1.isDead = false;
		if (GetRandomValue(1, 2) == 1)
		{
			E1.enemy.x = 0 - E1.enemy.width;
		}
		else
		{
			E1.enemy.x = static_cast<float>(GetScreenWidth());
		}

		E1.enemy.y = static_cast<float>(GetRandomValue(75, (GetScreenHeight() - (static_cast<int> (E1.enemy.height)))));
	}
}

void LooseScreen(PLAYER& P1, int maxScore)
{
	BeginDrawing();
	DrawTexture(background, 0, 0, WHITE);
	DrawRectangle((GetScreenWidth() / 2) - GetScreenWidth() / 4, GetScreenHeight() / 2 - GetScreenHeight() / 4, GetScreenWidth() / 2, GetScreenHeight() / 2, YELLOW);
	DrawText("you've lost the rhythm!", (GetScreenWidth() / 2) - MeasureText("you've lost the rhythm!", 40) / 2, GetScreenHeight() / 2 - GetScreenHeight() / 4, 40, BLACK);
	DrawText("High Score", (GetScreenWidth() / 2) - MeasureText("High Score", 30) / 2, GetScreenHeight() / 2 - GetScreenHeight() / 4 + 50, 30, BLACK);
	DrawText(TextFormat("%05i", maxScore), (GetScreenWidth() / 2) - MeasureText(TextFormat("%05i", P1.score), 30) / 2, GetScreenHeight() / 2 - GetScreenHeight() / 4 + 100, 30, BLACK);
	DrawText("Your Score", (GetScreenWidth() / 2) - MeasureText("Your Score", 30) / 2, GetScreenHeight() / 2 - GetScreenHeight() / 4 + 150, 30, BLACK);
	DrawText(TextFormat("%05i", P1.score), (GetScreenWidth() / 2) - MeasureText(TextFormat("%05i", P1.score), 30) / 2, GetScreenHeight() / 2 - GetScreenHeight() / 4 + 200, 30, BLACK);

	DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - GetScreenHeight() / 4 + 300, 200, 40, RED);
	DrawText("Return", GetScreenWidth() / 2 - MeasureText("Return", 40) / 2, GetScreenHeight() / 2 - GetScreenHeight() / 4 + 300, 40, BLACK);
	DrawTexture(scope, static_cast<int>(GetMouseX() - 19.5), static_cast<int>(GetMouseY() - 19.5), WHITE);
	EndDrawing();
}