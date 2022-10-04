#include "game.h"

void Game()
{
	PLAYER P1 = CreatePlayer();
	//textures
	Texture2D ship_idle = LoadTexture("rec/textures/Ship_idle (1).png");
	Texture2D scope = LoadTexture("rec/textures/scope.png");
	Texture2D AsteroidTipe_1 = LoadTexture("rec/textures/asteroid_1.png");

	//asteroids
	const int amountAsteroidsBig = 8;
	const int amountAsteroidsMedium = 16;
	const int amountAsteroidsSmall = 32;
	const int maxAsteroids = 56;
	ASTEROID arrayAsteroid[58];
	int counterMidAsteroid = 0;
	int counterSmallAsteroids = 0;

	for (int i = 0; i < amountAsteroidsBig; i++)
	{
		CreateAsteroidsBig(arrayAsteroid[i]);
	}

	for (int i = amountAsteroidsBig + 1; i < amountAsteroidsBig + amountAsteroidsMedium + 2; i++)
	{
		CreateAsteroidsMedium(arrayAsteroid[i]);
	}

	for (int i = amountAsteroidsBig + amountAsteroidsMedium + 1; i < amountAsteroidsBig + amountAsteroidsMedium + amountAsteroidsSmall + 2; i++)
	{
		CreateAsteroidsSmall(arrayAsteroid[i]);
	}


	//bulets
	const int maxAmmo = 30;
	BULLETS arrayBulets[maxAmmo];

	for (int i = 0; i < maxAmmo; i++)
	{
		CreateBullets(arrayBulets[i], P1);
	}

	bool pause = false;
	int counterBullet = 0;
	P1.ship.width = ship_idle.width;
	P1.ship.height = ship_idle.height;

	HideCursor();
	while (!WindowShouldClose() && P1.lives > 0)
	{
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
			PlayerF::PlayerShoot(arrayBulets, counterBullet, P1, maxAmmo);
			PlayerF::PlayerWallColition(P1);
			PlayerF::PlayerMovement(P1);
			PlayerF::BulletAsteroidColition(arrayAsteroid, amountAsteroidsBig, amountAsteroidsMedium, amountAsteroidsSmall, arrayBulets, maxAmmo, P1, counterMidAsteroid, counterSmallAsteroids, maxAsteroids);
			PlayerF::PlayerAsteroidColision(P1, ship_idle, arrayAsteroid, amountAsteroidsBig, amountAsteroidsMedium, amountAsteroidsSmall, counterMidAsteroid, counterSmallAsteroids, maxAsteroids);
			AsteroidF::AsteroidMovement(arrayAsteroid, amountAsteroidsBig, amountAsteroidsMedium, amountAsteroidsSmall, maxAsteroids);
			AsteroidF::AsteroidWallColition(arrayAsteroid, amountAsteroidsBig, amountAsteroidsMedium, amountAsteroidsSmall, maxAsteroids);
			AsteroidF::AsteroidReset(arrayAsteroid, amountAsteroidsBig, amountAsteroidsMedium, amountAsteroidsSmall, counterMidAsteroid, counterSmallAsteroids, maxAsteroids);
		}

		if (IsKeyPressed(KEY_M))
		{
			for (int i = 0; i < maxAsteroids; i++)
			{
				arrayAsteroid[i].isDestroyed = true;
			}
		}

		DrawF::DrawGame(P1, ship_idle, scope, arrayBulets, maxAmmo, arrayAsteroid, amountAsteroidsBig, amountAsteroidsMedium, amountAsteroidsSmall, maxAsteroids);

	}
}

namespace DrawF
{

	void DrawGame(PLAYER P1, Texture2D ship_idle, Texture2D scope, BULLETS arrayBulets[], int maxAmmo, ASTEROID arrayAsteroid[], int amountAsteroidsBig, int amountAsteroidsMedium, int amountAsteroidsSmall, int maxAsteroids)
	{
		Rectangle sourceShip = { 0.0f, 0.0f, ship_idle.width, ship_idle.height };
		Rectangle destRec = { P1.ship.x, P1.ship.y, ship_idle.width, ship_idle.height };

		BeginDrawing();
		ClearBackground(WHITE);

		//asteroids
		for (int x = 0; x < maxAsteroids; x++)
		{
			if (arrayAsteroid[x].isDestroyed == false && arrayAsteroid[x].size == Size::Big)
			{
				//Rectangle sourceAsteroid = { 0.0f, 0.0f, AsteroidTipe_1.width , AsteroidTipe_1.height };
				//Rectangle dest = { arrayAsteroid[x].center.x, arrayAsteroid[x].center.y, AsteroidTipe_1.width, AsteroidTipe_1.height };

				DrawCircle(arrayAsteroid[x].center.x, arrayAsteroid[x].center.y, arrayAsteroid[x].radius, RED);
				//DrawTexturePro(AsteroidTipe_1, sourceAsteroid, dest, arrayAsteroid[x].center , arrayAsteroid[x].rotation , WHITE);
			}
			else if (arrayAsteroid[x].isDestroyed == false && arrayAsteroid[x].size == Size::Medium)
			{
				//Rectangle sourceAsteroid = { 0.0f, 0.0f, AsteroidTipe_1.width , AsteroidTipe_1.height };
				//Rectangle dest = { arrayAsteroid[x].center.x, arrayAsteroid[x].center.y, AsteroidTipe_1.width, AsteroidTipe_1.height };

				DrawCircle(arrayAsteroid[x].center.x, arrayAsteroid[x].center.y, arrayAsteroid[x].radius, RED);
				//DrawTexturePro(AsteroidTipe_1, sourceAsteroid, dest, arrayAsteroid[x].center , arrayAsteroid[x].rotation , WHITE);
			}
			else if (arrayAsteroid[x].isDestroyed == false && arrayAsteroid[x].size == Size::Small)
			{
				//Rectangle sourceAsteroid = { 0.0f, 0.0f, AsteroidTipe_1.width , AsteroidTipe_1.height };
				//Rectangle dest = { arrayAsteroid[x].center.x, arrayAsteroid[x].center.y, AsteroidTipe_1.width, AsteroidTipe_1.height };

				DrawCircle(arrayAsteroid[x].center.x, arrayAsteroid[x].center.y, arrayAsteroid[x].radius, RED);
				//DrawTexturePro(AsteroidTipe_1, sourceAsteroid, dest, arrayAsteroid[x].center , arrayAsteroid[x].rotation , WHITE);
			}
		}

		//bulets
		for (int i = 0; i < maxAmmo; i++)
		{
			if (arrayBulets[i].isShoted)
			{
				DrawCircle(arrayBulets[i].Pos.x, arrayBulets[i].Pos.y, arrayBulets[i].radius, RED);
			}
		}

		//player 
		DrawTexturePro(ship_idle, sourceShip, destRec, P1.origin, P1.rotation, WHITE);
		DrawTexture(scope, GetMouseX() - 19.5, GetMouseY() - 19.5, WHITE);

		//draw extra info
		//DrawCircle(P1.ship.x, P1.ship.y, (ship_idle.width / 2 + 2), RED);
		//DrawLine(P1.ship.x, P1.ship.y, GetMouseX(), GetMouseY(), DARKGRAY);
		//DrawCircle(P1.ship.x, P1.ship.y, 5, GREEN);


		//score/lives/
		DrawInfo(ship_idle, P1);

		EndDrawing();
	}

	void DrawInfo(Texture2D ship_idle, PLAYER P1)
	{
		//table
		DrawRectangle(0, 0, GetScreenWidth(), 75, WHITE);

		//lives
		if (P1.lives == 3)
		{
			DrawTexture(ship_idle, 50, 5, GREEN);
			DrawTexture(ship_idle, 50 + ship_idle.width, 5, GREEN);
			DrawTexture(ship_idle, 50 + ship_idle.width * 2, 5, GREEN);
		}
		else if (P1.lives == 2)
		{
			DrawTexture(ship_idle, 50, 5, GREEN);
			DrawTexture(ship_idle, 50 + ship_idle.width, 5, GREEN);
		}
		else
		{
			DrawTexture(ship_idle, 50, 5, GREEN);
		}

		//score
		DrawText(TextFormat("%05i", P1.score), (GetScreenWidth() / 2), 0, 50, GREEN);

	}

	void DrawPause()
	{

	}
}

namespace PlayerF
{
	void PlayerMovement(PLAYER& P1)
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

		}


		if (P1.shipAcceleration.x > 200 && P1.shipAcceleration.x > 0)
		{
			P1.shipAcceleration.x = 200;
		}
		else if (P1.shipAcceleration.x < -200 && P1.shipAcceleration.x < 0)
		{
			P1.shipAcceleration.x = -200;
		}

		if (P1.shipAcceleration.y > 200 && P1.shipAcceleration.y > 0)
		{
			P1.shipAcceleration.y = 200;
		}
		else if (P1.shipAcceleration.y < -200 && P1.shipAcceleration.y < 0)
		{
			P1.shipAcceleration.y = -200;
		}

		//cout << P1.speed.x << " " << P1.speed.y << endl;

		P1.speed.x = P1.shipAcceleration.x;
		P1.speed.y = P1.shipAcceleration.y;

		P1.ship.x += P1.speed.x * GetFrameTime();
		P1.ship.y += P1.speed.y * GetFrameTime();

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
			P1.ship.x = GetScreenWidth() - 1;
		}

		if (P1.ship.y > GetScreenHeight())
		{
			P1.ship.y = 76;
		}
		else if (P1.ship.y < 75)
		{
			P1.ship.y = GetScreenHeight() - 1;
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

				else if (arrayBulets[i].Pos.y < 75 || arrayBulets[i].Pos.y > GetScreenHeight())
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

	void PlayerShoot(BULLETS arrayBulets[], int& counter, PLAYER& P1, int maxAmmo)
	{
		Vector2 vectorDirection;
		Vector2 normalizeDirection;

		vectorDirection.x = GetMouseX() - P1.ship.x;
		vectorDirection.y = GetMouseY() - P1.ship.y;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			counter++;
			if (counter == maxAmmo)
			{
				counter = 0;
			}

			normalizeDirection = Vector2Normalize(vectorDirection);

			arrayBulets[counter].speed.x += normalizeDirection.x;
			arrayBulets[counter].speed.y += normalizeDirection.y;
			arrayBulets[counter].speed.x *= 500;
			arrayBulets[counter].speed.y *= 500;
			arrayBulets[counter].isShoted = true;
			//cout << "shot " << counter << endl;
			//cout << normalizeDirection.x << " " << normalizeDirection.y << endl;
		}

		//cout << arrayBulets[counter-1].Pos.x << " " << arrayBulets[counter - 1].Pos.y << endl;

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

	void PlayerAsteroidColision(PLAYER& P1, Texture2D ship_idle, ASTEROID arrayAsteroid[], int amountAsteroidsBig, int amountAsteroidsMedium, int amountAsteroidsSmall, int& counterMidAsteroid, int& counterSmallAsteroid, int maxAsteroids)
	{
		for (int i = 0; i < maxAsteroids; i++)
		{
			float distX = P1.ship.x - arrayAsteroid[i].center.x;
			float distY = P1.ship.y - arrayAsteroid[i].center.y;
			float distance = sqrt((distX * distX) + (distY * distY));

			if (distance <= (ship_idle.width / 2 + 2) + arrayAsteroid[i].radius)
			{
				P1.lives--;
				P1.speed.x = 0;
				P1.speed.y = 0;
				P1.ship.x = GetScreenWidth() / 2;
				P1.ship.y = GetScreenHeight() / 2;

				for (int i = 0; i < amountAsteroidsBig; i++)
				{
					CreateAsteroidsBig(arrayAsteroid[i]);

				}

				for (int i = amountAsteroidsBig + 1; i < amountAsteroidsMedium; i++)
				{
					CreateAsteroidsMedium(arrayAsteroid[i]);
				}

				for (int i = amountAsteroidsMedium + 1; i < maxAsteroids; i++)
				{
					CreateAsteroidsSmall(arrayAsteroid[i]);
				}

				counterMidAsteroid = 0;
				counterSmallAsteroid = 0;
			}
		}
	}

	void BulletAsteroidColition(ASTEROID arrayAsteroid[], int amountAsteroidsBig, int amountAsteroidsMedium, int amountAsteroidsSmall, BULLETS arrayBulets[], int maxAmmo, PLAYER& P1, int& counterMidAsteroid, int& counterSmallAsteroid, int maxAsteroids)
	{
		for (int i = 0; i < maxAsteroids; i++)
		{
			for (int x = 0; x < maxAmmo; x++)
			{
				float distX = arrayBulets[x].Pos.x - arrayAsteroid[i].center.x;
				float distY = arrayBulets[x].Pos.y - arrayAsteroid[i].center.y;
				float distance = sqrt((distX * distX) + (distY * distY));

				if (distance <= arrayBulets[x].radius + arrayAsteroid[i].radius)
				{
					cout << "colision detectada" << endl;
					arrayAsteroid[i].isDestroyed = true;
					arrayBulets[x].isShoted = false;
					P1.score++;


					if (arrayAsteroid[i].isDestroyed && arrayAsteroid[i].size == Size::Big)
					{
						cout << "crados 2 medium" << endl;
						counterMidAsteroid += 2;
						arrayAsteroid[amountAsteroidsBig + counterMidAsteroid].center = arrayAsteroid[i].center;
						arrayAsteroid[amountAsteroidsBig + counterMidAsteroid - 1].center = arrayAsteroid[i].center;
						arrayAsteroid[amountAsteroidsBig + counterMidAsteroid].isDestroyed = false;
						arrayAsteroid[amountAsteroidsBig + counterMidAsteroid - 1].isDestroyed = false;

						do
						{
							arrayAsteroid[amountAsteroidsBig + counterMidAsteroid].speed.x = GetRandomValue(-200, 200);
						} while (arrayAsteroid[amountAsteroidsBig + counterMidAsteroid].speed.x > -100 && arrayAsteroid[amountAsteroidsBig + counterMidAsteroid].speed.x < 100);

						do
						{
							arrayAsteroid[amountAsteroidsBig + counterMidAsteroid - 1].speed.y = GetRandomValue(-200, 200);
						} while (arrayAsteroid[amountAsteroidsBig + counterMidAsteroid - 1].speed.y < -100 && arrayAsteroid[amountAsteroidsBig + counterMidAsteroid - 1].speed.y < 100);

					}
					else if (arrayAsteroid[i].isDestroyed && arrayAsteroid[i].size == Size::Medium)
					{
						cout << "crados 2 small" << endl;
						counterSmallAsteroid += 2;
						arrayAsteroid[amountAsteroidsMedium + counterSmallAsteroid].center = arrayAsteroid[i].center;
						arrayAsteroid[amountAsteroidsMedium + counterSmallAsteroid - 1].center = arrayAsteroid[i].center;
						arrayAsteroid[amountAsteroidsMedium + counterSmallAsteroid].isDestroyed = false;
						arrayAsteroid[amountAsteroidsMedium + counterSmallAsteroid - 1].isDestroyed = false;

						do
						{
							arrayAsteroid[amountAsteroidsMedium + counterSmallAsteroid].speed.x = GetRandomValue(-200, 200);
						} while (arrayAsteroid[amountAsteroidsMedium + counterSmallAsteroid].speed.x > -100 && arrayAsteroid[amountAsteroidsMedium + counterSmallAsteroid].speed.x < 100);

						do
						{
							arrayAsteroid[amountAsteroidsMedium + counterSmallAsteroid - 1].speed.y = GetRandomValue(-200, 200);
						} while (arrayAsteroid[amountAsteroidsMedium + counterSmallAsteroid - 1].speed.y < -100 && arrayAsteroid[amountAsteroidsMedium + counterSmallAsteroid - 1].speed.y < 100);

					}
					x = maxAmmo;
				}
			}

		}
	}
}

namespace AsteroidF
{
	void AsteroidMovement(ASTEROID arrayAsteroid[], int amountAsteroidsBig, int amountAsteroidsMedium, int amountAsteroidsSmall, int maxAsteroids)
	{
		for (int x = 0; x < maxAsteroids; x++)
		{
			if (arrayAsteroid[x].isDestroyed && arrayAsteroid[x].size == Size::Big)
			{
				arrayAsteroid[x].center.x = -50;
				arrayAsteroid[x].center.y = -50;
			}
			else if (arrayAsteroid[x].isDestroyed && arrayAsteroid[x].size == Size::Medium)
			{
				arrayAsteroid[x].center.x = -50;
				arrayAsteroid[x].center.y = -50;
			}
			else if (arrayAsteroid[x].isDestroyed && arrayAsteroid[x].size == Size::Small)
			{
				arrayAsteroid[x].center.x = -50;
				arrayAsteroid[x].center.y = -50;
			}
			else
			{
				arrayAsteroid[x].center.x += arrayAsteroid[x].speed.x * GetFrameTime();
				arrayAsteroid[x].center.y += arrayAsteroid[x].speed.y * GetFrameTime();
			}
		}


	}

	void AsteroidWallColition(ASTEROID arrayAsteroid[], int amountAsteroidsBig, int amountAsteroidsMedium, int amountAsteroidsSmall, int maxAsteroids)
	{
		for (int x = 0; x < maxAsteroids; x++)
		{
			if ((arrayAsteroid[x].center.x > GetScreenWidth() || arrayAsteroid[x].center.x < 0))
			{
				arrayAsteroid[x].speed.x *= -1;
			}
			else if (arrayAsteroid[x].center.y > GetScreenHeight() || arrayAsteroid[x].center.y < 75)
			{
				arrayAsteroid[x].speed.y *= -1;
			}
		}
	}

	void AsteroidReset(ASTEROID arrayAsteroid[], int amountAsteroidsBig, int amountAsteroidsMedium, int amountAsteroidsSmall, int& counterMidAsteroid, int& counterSmallAsteroid, int maxAsteroids)
	{
		int counter = 0;

		for (int i = 0; i < maxAsteroids; i++)
		{
			if (arrayAsteroid[i].isDestroyed)
			{
				counter++;
			}

			if (counter == maxAsteroids)
			{
				for (int i = 0; i < amountAsteroidsBig; i++)
				{
					CreateAsteroidsBig(arrayAsteroid[i]);

				}

				for (int i = amountAsteroidsBig; i < 24; i++)
				{
					CreateAsteroidsMedium(arrayAsteroid[i]);
				}

				for (int i = 24; i < 56; i++)
				{
					CreateAsteroidsSmall(arrayAsteroid[i]);
				}

				counterMidAsteroid = 0;
				counterSmallAsteroid = 0;
			}

			if (arrayAsteroid[i].center.x < -5 || arrayAsteroid[i].center.x > GetScreenWidth() + 5)
			{
				arrayAsteroid[i].isDestroyed = false;
			}
			else if (arrayAsteroid[i].center.y < 50 || arrayAsteroid[i].center.y > GetScreenHeight() + 5)
			{
				arrayAsteroid[i].isDestroyed = false;
			}
		}
	}
}