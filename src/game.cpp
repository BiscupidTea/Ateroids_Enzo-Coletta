#include "game.h"

void Game()
{
	PLAYER P1 = CreatePlayer();

	Texture2D ship_idle = LoadTexture("rec/Ship_idle (1).png");
	Texture2D scope = LoadTexture("rec/scope.png");

	HideCursor();
	while (!WindowShouldClose() && P1.lives > 0)
	{
		PlayerWallColition(P1);
		PlayerMovement(P1);
		DrawGame(P1, ship_idle, scope);
	}	
	
}

void DrawGame(PLAYER P1, Texture2D ship_idle, Texture2D scope)
{
	Rectangle sourceShip = { 0.0f, 0.0f, 40.0, 36.0 };
	Rectangle destRec = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, 40.0 * 2.0f, 36.0 * 2.0f };

	BeginDrawing();
	ClearBackground(WHITE);
	//player 
	DrawRectanglePro(P1.ship, P1.origin, P1.rotation, P1.color);
	DrawTexturePro(ship_idle, sourceShip, destRec, P1.origin, P1.rotation, WHITE);
	DrawTexture(scope, GetMouseX()-19.5, GetMouseY()-19.5, WHITE);
	DrawLine(P1.ship.x, P1.ship.y, GetMouseX(), GetMouseY(), DARKGRAY);

	EndDrawing();
}

void PlayerMovement(PLAYER& P1)
{
	//logic rotation
	float vectorDirectionX;
	float vectorDirectionY;
	float angulo;
	float normalizeDirectionX;
	float normalizeDirectionY;

	vectorDirectionX = GetMouseX() - (P1.ship.x);
	vectorDirectionY = GetMouseY() - (P1.ship.y);
	angulo = atan(vectorDirectionY / vectorDirectionX);
	angulo = angulo* 180 / PI;

	if (angulo >= 90 && angulo < 270)
	{
		angulo += 180;
	}
	else if (angulo >= 270 && angulo <= 360)
	{
		angulo += 360;
	}
	P1.rotation = angulo;

	//logic movement
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		normalizeDirectionX = vectorDirectionX / abs(vectorDirectionX);
		normalizeDirectionY = vectorDirectionY / abs(vectorDirectionY);

		P1.shipAccelerationX += normalizeDirectionX;
		P1.shipAccelerationY += normalizeDirectionY;
	}

	if (P1.shipAccelerationX > 600)
	{
		P1.shipAccelerationX = 600;
	}
	else if (P1.shipAccelerationX < -600)
	{
		P1.shipAccelerationX = -600;
	}

	if (P1.shipAccelerationY > 600)
	{
		P1.shipAccelerationY = 600;
	}
	else if (P1.shipAccelerationY < -600)
	{
		P1.shipAccelerationY = -600;
	}

	cout << P1.shipAccelerationX << " " << P1.shipAccelerationY << endl;

		P1.ship.x = P1.ship.x + (P1.shipAccelerationX * GetFrameTime());
		P1.ship.y = P1.ship.y + (P1.shipAccelerationY * GetFrameTime());

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
		P1.ship.y = 1;
	}
	else if (P1.ship.y < 0)
	{
		P1.ship.y = GetScreenHeight() - 1;
	}
}