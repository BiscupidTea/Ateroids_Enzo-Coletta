#include "game.h"

void Game()
{
	PLAYER P1 = CreatePlayer();
	Texture2D ship_idle = LoadTexture("rec/textures/Ship_idle (1).png");
	Texture2D scope = LoadTexture("rec/textures/scope.png");
	const int amountAsteroids = 8;
	ASTEROIDS arrayAsteroid[amountAsteroids];

	for (int i = 0; i < amountAsteroids; i++)
	{
		CreateAsteroids(arrayAsteroid[i]);
	}

	const int maxAmmo = 20;
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
			//PlayerF::PlayerAsteroidColision(P1, arrayAsteroid, amountAsteroids, ship_idle);
			AsteroidF::AsteroidMovement(arrayAsteroid, amountAsteroids);
			AsteroidF::AsteroidWallColition(arrayAsteroid, amountAsteroids);
		}

		DrawF::DrawGame(P1, ship_idle, scope, arrayAsteroid, amountAsteroids, arrayBulets, maxAmmo);

	}

}

namespace DrawF
{

	void DrawGame(PLAYER P1, Texture2D ship_idle, Texture2D scope, ASTEROIDS arrayAsteroid[], int amountAsteroids, BULLETS arrayBulets[], int maxAmmo)
	{
		Rectangle sourceShip = { 0.0f, 0.0f, ship_idle.width, ship_idle.height };
		Rectangle destRec = { P1.ship.x, P1.ship.y, ship_idle.width, ship_idle.height };

		BeginDrawing();
		ClearBackground(BLACK);

		//asteroids
		for (int x = 0; x < 10; x++)
		{
			DrawCircle(arrayAsteroid[x].center.x, arrayAsteroid[x].center.y, arrayAsteroid[x].radius, WHITE);
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
		DrawText(TextFormat("%02i", P1.score), GetScreenWidth() / 2, 0, 50, GREEN);

	}

	void DrawPause()
	{

	}
}

namespace AsteroidF
{
	void AsteroidMovement(ASTEROIDS arrayAsteroids[], int amountAsteroids)
	{
		for (int x = 0; x < amountAsteroids; x++)
		{
			arrayAsteroids[x].center.x += arrayAsteroids[x].speed.x * GetFrameTime();
			arrayAsteroids[x].center.y += arrayAsteroids[x].speed.y * GetFrameTime();
		}
	}

	void AsteroidWallColition(ASTEROIDS arrayAsteroids[], int amountAsteroids)
	{
		for (int x = 0; x < amountAsteroids; x++)
		{
			if (arrayAsteroids[x].center.x > GetScreenWidth())
			{
				CreateAsteroids(arrayAsteroids[x]);
			}
			else if (arrayAsteroids[x].center.x < 0)
			{
				CreateAsteroids(arrayAsteroids[x]);
			}
			else if (arrayAsteroids[x].center.y > GetScreenHeight())
			{
				CreateAsteroids(arrayAsteroids[x]);
			}
			else if (arrayAsteroids[x].center.y < 75)
			{
				CreateAsteroids(arrayAsteroids[x]);
			}
		}
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

		
		if (P1.shipAcceleration.x > 300 && P1.shipAcceleration.x > 0)
		{
			P1.shipAcceleration.x = 300;
		}
		else if (P1.shipAcceleration.x < -300 && P1.shipAcceleration.x < 0)
		{
			P1.shipAcceleration.x = -300;
		}

		if (P1.shipAcceleration.y > 300 && P1.shipAcceleration.y > 0)
		{
			P1.shipAcceleration.y = 300;
		}
		else if (P1.shipAcceleration.y < -300 && P1.shipAcceleration.y < 0)
		{
			P1.shipAcceleration.y = -300;
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
			if (arrayBulets[i].isShoted )
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

		vectorDirection.x = GetMouseX() - arrayBulets[counter].Pos.x;
		vectorDirection.y = GetMouseY() - arrayBulets[counter].Pos.y;

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
			arrayBulets[counter].speed.x *= 200;
			arrayBulets[counter].speed.y *= 200;
			arrayBulets[counter].isShoted = true;
			cout << "shot " << counter << endl;
			//cout << normalizeDirection.x << " " << normalizeDirection.y << endl;
		}
		
		//cout << arrayBulets[counter-1].Pos.x << " " << arrayBulets[counter - 1].Pos.y << endl;

		for (int i = 0; i < maxAmmo; i++)
		{
			if (arrayBulets[i].isShoted)
			{
				arrayBulets[i].Pos.x = arrayBulets[i].Pos.x + (arrayBulets[i].speed.x * GetFrameTime());
				arrayBulets[i].Pos.y = arrayBulets[i].Pos.y + (arrayBulets[i].speed.y * GetFrameTime());
				//cout << arrayBulets[i].Pos.x << " " << arrayBulets[i].Pos.y << endl;
				//cout << arrayBulets[i].speed.x << " " << arrayBulets[i].speed.y << endl;
			}
		}

	}

	void PlayerAsteroidColision(PLAYER& P1, ASTEROIDS arrayAsteroids[], int amountAsteroids, Texture2D ship_idle)
	{
		for (int i = 0; i < amountAsteroids; i++)
		{
			float distX = P1.ship.x - arrayAsteroids[i].center.x;
			float distY = P1.ship.y - arrayAsteroids[i].center.y;
			float distance = sqrt((distX * distX) + (distY * distY));

			if (distance <= (ship_idle.width / 2 + 2) + arrayAsteroids[i].radius)
			{
				P1.lives--;
				P1.speed.x = 0;
				P1.speed.y = 0;
				P1.ship.x = GetScreenWidth()/2;
				P1.ship.y = GetScreenHeight()/2;
			}

		}
	}
}