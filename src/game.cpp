#include "game.h"

Texture2D ship_idle;
Texture2D scope;
Texture2D AsteroidTipe_1;
Sound shot1;

void Game(bool& closeGame, float& SFXvolume, float& MusicVolume)
{
	//declaraciones//
	PLAYER P1 = CreatePlayer();
	ENEMY E1 = CreateEnemy();
	SFXvolume = 0.5f;
	MusicVolume = 0.5f;
	float timer = 0;
	float maxTimer = 7;

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
		CreateAsteroidsBig(arrayAsteroid[i]);
	}

	for (int i = amountAsteroidsBig; i < amountAsteroidsBig + amountAsteroidsMedium; i++)
	{
		CreateAsteroidsMedium(arrayAsteroid[i]);
	}

	for (int i = amountAsteroidsBig + amountAsteroidsMedium; i < maxAsteroids; i++)
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

	//others
	bool pause = false;
	int counterBullet = 0;
	P1.ship.width = static_cast<float>(ship_idle.width);
	P1.ship.height = static_cast<float>(ship_idle.height);

	HideCursor();

	///////////start game/////////////

	while (P1.lives > 0 && !WindowShouldClose())
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
			PlayerF::BulletAsteroidColition(arrayAsteroid, amountAsteroidsBig, amountAsteroidsMedium, arrayBulets, maxAmmo, P1, counterMidAsteroid, counterSmallAsteroids, maxAsteroids);
			PlayerF::PlayerAsteroidColision(P1, arrayAsteroid, amountAsteroidsBig, amountAsteroidsMedium, counterMidAsteroid, counterSmallAsteroids, maxAsteroids);
			AsteroidF::AsteroidMovement(arrayAsteroid, maxAsteroids);
			AsteroidF::AsteroidWallColition(arrayAsteroid, maxAsteroids);
			AsteroidF::AsteroidReset(arrayAsteroid, amountAsteroidsBig, amountAsteroidsMedium, counterMidAsteroid, counterSmallAsteroids, maxAsteroids);
			EnemyF::EnemyMovement(E1);
			EnemyF::EnemyWallColition(E1);
			EnemyF::EnemyPlayerColition(E1, P1);
			EnemyF::EnemyBulletColition(P1, E1, arrayBulets, maxAmmo);

		}
		else
		{
			PauseF::PauseLogic(SFXvolume, MusicVolume, closeGame);
		}

		if (E1.isDead && (timer >= maxTimer))
		{
			EnemyF::EnemyReset(E1);
		}

		if (timer >= maxTimer + 1)
		{
			timer = 0;
		}

		timer += GetFrameTime();

		DrawF::DrawGame(P1, arrayBulets, maxAmmo, arrayAsteroid, maxAsteroids, pause, SFXvolume, MusicVolume, E1);

		if (P1.lives <= 0)
		{
			closeGame = false;
			return;
		}
		cout << timer << endl;
	}

}

namespace DrawF
{

	void DrawGame(PLAYER P1, BULLETS arrayBulets[], int maxAmmo, ASTEROID arrayAsteroid[], int maxAsteroids, bool pause, float SFXvolume, float MusicVolume, ENEMY E1)
	{
		Rectangle sourceShip = { 0.0f, 0.0f, static_cast<float>(ship_idle.width), static_cast<float>(ship_idle.height) };
		Rectangle destRec = { P1.ship.x, P1.ship.y, static_cast<float>(ship_idle.width), static_cast<float>(ship_idle.height) };

		BeginDrawing();
		ClearBackground(WHITE);

		//asteroids
		for (int x = 0; x < maxAsteroids; x++)
		{
			if (arrayAsteroid[x].isDestroyed == false && arrayAsteroid[x].size == Size::Big)
			{
				//Rectangle sourceAsteroid = { 0.0f, 0.0f, AsteroidTipe_1.width , AsteroidTipe_1.height };
				//Rectangle dest = { arrayAsteroid[x].center.x, arrayAsteroid[x].center.y, AsteroidTipe_1.width, AsteroidTipe_1.height };

				DrawCircle(static_cast<int>(arrayAsteroid[x].center.x), static_cast<int>(arrayAsteroid[x].center.y), arrayAsteroid[x].radius, RED);
				//DrawTexturePro(AsteroidTipe_1, sourceAsteroid, dest, arrayAsteroid[x].center , arrayAsteroid[x].rotation , WHITE);
			}
			else if (arrayAsteroid[x].isDestroyed == false && arrayAsteroid[x].size == Size::Medium)
			{
				//Rectangle sourceAsteroid = { 0.0f, 0.0f, AsteroidTipe_1.width , AsteroidTipe_1.height };
				//Rectangle dest = { arrayAsteroid[x].center.x, arrayAsteroid[x].center.y, AsteroidTipe_1.width, AsteroidTipe_1.height };

				DrawCircle(static_cast<int>(arrayAsteroid[x].center.x), static_cast<int>(arrayAsteroid[x].center.y), arrayAsteroid[x].radius, RED);
				//DrawTexturePro(AsteroidTipe_1, sourceAsteroid, dest, arrayAsteroid[x].center , arrayAsteroid[x].rotation , WHITE);
			}
			else if (arrayAsteroid[x].isDestroyed == false && arrayAsteroid[x].size == Size::Small)
			{
				//Rectangle sourceAsteroid = { 0.0f, 0.0f, AsteroidTipe_1.width , AsteroidTipe_1.height };
				//Rectangle dest = { arrayAsteroid[x].center.x, arrayAsteroid[x].center.y, AsteroidTipe_1.width, AsteroidTipe_1.height };

				DrawCircle(static_cast<int>(arrayAsteroid[x].center.x), static_cast<int>(arrayAsteroid[x].center.y), arrayAsteroid[x].radius, RED);
				//DrawTexturePro(AsteroidTipe_1, sourceAsteroid, dest, arrayAsteroid[x].center , arrayAsteroid[x].rotation , WHITE);
			}
		}

		//bulets
		for (int i = 0; i < maxAmmo; i++)
		{
			if (arrayBulets[i].isShoted)
			{
				DrawCircle(static_cast<int>(arrayBulets[i].Pos.x), static_cast<int>(arrayBulets[i].Pos.y), arrayBulets[i].radius, RED);
			}
		}

		//player 
		DrawTexturePro(ship_idle, sourceShip, destRec, P1.origin, P1.rotation, WHITE);
		DrawTexture(scope, static_cast<int>(GetMouseX() - 19.5), static_cast<int>(GetMouseY() - 19.5), WHITE);

		//enemy
		if (!E1.isDead)
		{
			DrawRectangle(static_cast<int>(E1.enemy.x), static_cast<int>(E1.enemy.y), static_cast<int>(E1.enemy.width), static_cast<int>(E1.enemy.height), RED);
		}

		//draw extra info
		//DrawCircle(P1.ship.x, P1.ship.y, (ship_idle.width / 2 + 2), RED);
		//DrawLine(P1.ship.x, P1.ship.y, GetMouseX(), GetMouseY(), DARKGRAY);
		//DrawCircle(P1.ship.x, P1.ship.y, 5, GREEN);

		//score/lives/
		DrawInfo(P1);

		if (pause == true)
		{
			PauseF::DrawPause(SFXvolume, MusicVolume);
			DrawTexture(scope, static_cast<int>(GetMouseX() - 19.5), static_cast<int>(GetMouseY() - 19.5), WHITE);
		}

		EndDrawing();
	}

	void DrawInfo(PLAYER P1)
	{
		//table
		DrawRectangle(0, 0, GetScreenWidth(), 75, BLACK);

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
			P1.ship.y = 76;
		}
		else if (P1.ship.y < 75)
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
			PlaySound(shot1);
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

	void PlayerAsteroidColision(PLAYER& P1, ASTEROID arrayAsteroid[], int amountAsteroidsBig, int amountAsteroidsMedium, int& counterMidAsteroid, int& counterSmallAsteroid, int maxAsteroids)
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
				P1.ship.x = static_cast<float>(GetScreenWidth() / 2);
				P1.ship.y = static_cast<float>(GetScreenHeight() / 2);

				for (int x = 0; x < amountAsteroidsBig; x++)
				{
					CreateAsteroidsBig(arrayAsteroid[x]);

				}

				for (int x = amountAsteroidsBig + 1; x < amountAsteroidsBig + amountAsteroidsMedium; x++)
				{
					CreateAsteroidsMedium(arrayAsteroid[x]);
				}

				for (int x = amountAsteroidsBig + amountAsteroidsMedium + 1; x < maxAsteroids; x++)
				{
					CreateAsteroidsSmall(arrayAsteroid[x]);
				}

				counterMidAsteroid = 0;
				counterSmallAsteroid = 0;
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
					arrayAsteroid[x].center.y = 76;
				}
				else if (arrayAsteroid[x].center.y < 75)
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
				CreateAsteroidsBig(arrayAsteroid[i]);
			}

			for (int i = amountAsteroidsBig; i < amountAsteroidsBig + amountAsteroidsMedium; i++)
			{
				CreateAsteroidsMedium(arrayAsteroid[i]);
			}

			for (int i = amountAsteroidsBig + amountAsteroidsMedium; i < maxAsteroids; i++)
			{
				CreateAsteroidsSmall(arrayAsteroid[i]);
			}

			counterMidAsteroid = 0;
			counterSmallAsteroid = 0;
		}

	}
}

namespace PauseF
{
	void PauseLogic(float& SFXvolume, float& MusicVolume, bool& closeGame)
	{
		closeGame;
		SFXvolume = 0.5f;
		MusicVolume = 0.5f;
	}

	void DrawPause(float SFXvolume, float MusicVolume)
	{
		float numberSFX = SFXvolume;
		float numberMusic = MusicVolume;

		numberSFX *= 10;
		numberMusic *= 10;

		Vector2 backPauseWH = { 700, 700 };
		Vector2 backPauseXY = { (GetScreenWidth() / 2) - (backPauseWH.x / 2),  (GetScreenHeight() / 2) - (backPauseWH.y) / 2 };
		//draw background
		DrawRectangle(static_cast<int>(backPauseXY.x), static_cast<int>(backPauseXY.y), static_cast<int>(backPauseWH.x), static_cast<int>(backPauseWH.y), YELLOW);
		//options

		//--resume--
		DrawRectangle((GetScreenWidth() / 2) - 40, (GetScreenHeight() / 2) - 250, 80, 80, RED);
		DrawText("RESUME", (GetScreenWidth() / 2) - 40, (GetScreenHeight() / 2) - 250, 40, BLACK);

		//--sound--
		DrawText("SOUND", (GetScreenWidth() / 2) - (MeasureText("SOUND", 40) / 2), (GetScreenHeight() / 2) - 100, 40, BLACK);
		//DrawRectangle();
		//DrawText();
		DrawRectangle((GetScreenWidth() / 2) - 40, (GetScreenHeight() / 2) - 60, 80, 80, RED);
		//DrawText(TextFormat("%02i", numberSFX), (GetScreenWidth() / 2) - 35, (GetScreenHeight() / 2)+70, 70, WHITE);
		//DrawRectangle();
		//DrawText();

		//--music--
		DrawText("MUSIC", (GetScreenWidth() / 2) - (MeasureText("MUSIC", 40) / 2), (GetScreenHeight() / 2) + 40, 40, BLACK);
		//DrawRectangle();
		//DrawText();
		DrawRectangle((GetScreenWidth() / 2) - 40, (GetScreenHeight() / 2) + 40 + 50, 80, 80, RED);
		//DrawText(TextFormat("%02i", numberMusic), (GetScreenWidth() / 2) - 35, (GetScreenHeight() / 2)-70, 70, WHITE);
		//DrawRectangle();
		//DrawText();

		//--exit--
		DrawRectangle((GetScreenWidth() / 2) - 40, (GetScreenHeight() / 2) + 250, 80, 80, RED);
		DrawText("EXIT", (GetScreenWidth() / 2) - 40, (GetScreenHeight() / 2) + 250, 40, BLACK);


		DrawLine((GetScreenWidth() / 2), 0, (GetScreenWidth() / 2), GetScreenHeight(), BLACK);
		DrawLine(0, GetScreenHeight() / 2, GetScreenWidth(), GetScreenHeight() / 2, BLACK);
	}
}

namespace PowerUpF
{

}

namespace EnemyF
{
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

	void EnemyPlayerColition(ENEMY& E1, PLAYER& P1)
	{
		if (!E1.isDead)
		{
			if (CheckCollisionCircleRec(P1.center, 5, E1.enemy))
			{
				P1.lives--;
				P1.speed.x = 0;
				P1.speed.y = 0;
				P1.ship.x = static_cast<float>(GetScreenWidth() / 2);
				P1.ship.y = static_cast<float>(GetScreenHeight() / 2);
				E1.isDead = true;
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