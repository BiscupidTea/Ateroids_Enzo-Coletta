#include "game.h"

void Game()
{
	PLAYER P1 = CreatePlayer();
	Texture2D ship_idle = LoadTexture("rec/textures/Ship_idle (1).png");
	Texture2D scope = LoadTexture("rec/textures/scope.png");

	ASTEROIDS arrayAsteroid[10];
	for (int i = 0; i < 10; i++)
	{
		CreateAsteroids(arrayAsteroid[i]);
	}

	bool pause = false;

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
			PlayerF::PlayerWallColition(P1);
			PlayerF::PlayerMovement(P1);
			AsteroidF::AsteroidMovement(arrayAsteroid);
			AsteroidF::AsteroidWallColition(arrayAsteroid);
		}

		DrawF::DrawGame(P1, ship_idle, scope, arrayAsteroid);

	}

}

namespace DrawF
{

	void DrawGame(PLAYER P1, Texture2D ship_idle, Texture2D scope, ASTEROIDS arrayAsteroid[])
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

		//player 
		//DrawCircle(P1.ship.x, P1.ship.y, (ship_idle.width / 2 + 2), RED);
		DrawTexturePro(ship_idle, sourceShip, destRec, P1.origin, P1.rotation, WHITE);
		DrawTexture(scope, GetMouseX() - 19.5, GetMouseY() - 19.5, WHITE);
		DrawLine(P1.ship.x, P1.ship.y, GetMouseX(), GetMouseY(), DARKGRAY);

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

}

namespace AsteroidF
{
	void AsteroidMovement(ASTEROIDS arrayAsteroids[])
	{
		for (int x = 0; x < 10; x++)
		{
			arrayAsteroids[x].center.x += arrayAsteroids[x].speed.x * GetFrameTime();
			arrayAsteroids[x].center.y += arrayAsteroids[x].speed.y * GetFrameTime();
		}
	}

	void AsteroidWallColition(ASTEROIDS arrayAsteroids[])
	{
		for (int x = 0; x < 10; x++)
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

		vectorDirection.x = GetMouseX() - (P1.ship.x);
		vectorDirection.y = GetMouseY() - (P1.ship.y);
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
			normalizeDirection.x = vectorDirection.x / abs(vectorDirection.x);
			normalizeDirection.y = vectorDirection.y / abs(vectorDirection.y);

			P1.shipAcceleration.x += normalizeDirection.x;
			P1.shipAcceleration.y += normalizeDirection.y;
		}

		if (P1.shipAcceleration.x > 400 && P1.shipAcceleration.x > 0)
		{
			P1.shipAcceleration.x = 400;
		}
		else if (P1.shipAcceleration.x < -400 && P1.shipAcceleration.x < 0)
		{
			P1.shipAcceleration.x = -400;
		}

		if (P1.shipAcceleration.y > 400 && P1.shipAcceleration.y > 0)
		{
			P1.shipAcceleration.y = 400;
		}
		else if (P1.shipAcceleration.y < -400 && P1.shipAcceleration.y < 0)
		{
			P1.shipAcceleration.y = -400;
		}

		cout << P1.shipAcceleration.x << " " << P1.shipAcceleration.y << endl;
		cout << P1.speed.x << " " << P1.speed.y << endl;

		P1.speed.x = P1.shipAcceleration.x;
		P1.speed.y = P1.shipAcceleration.y;

		P1.ship.x += P1.speed.x * GetFrameTime();
		P1.ship.y += P1.speed.y * GetFrameTime();

		P1.center.x = P1.ship.x + (P1.ship.width / 2);
		P1.center.y = P1.ship.y + (P1.ship.height / 2);

		P1.XY.x = P1.ship.x - 120;
		P1.XY.y = P1.ship.y - 63;

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

	void PlayerShoot(PLAYER& P1)
	{
		
	}
}