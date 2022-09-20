#include "game.h"

void Game()
{
	PLAYER P1 = CreatePlayer();

	while (!WindowShouldClose())
	{
		PlayerWallColition(P1);
		PlayerMovement(P1);
		DrawGame(P1);
	}	
}

void DrawGame(PLAYER P1)
{
	BeginDrawing();
	ClearBackground(BLACK);
	//player 
	DrawRectanglePro(P1.ship, P1.origin, P1.rotation, P1.color);
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

	if (P1.shipAccelerationX > 400)
	{
		P1.shipAccelerationX = 400;
	}
	else if (P1.shipAccelerationX < -400)
	{
		P1.shipAccelerationX = -400;
	}

	if (P1.shipAccelerationY > 400)
	{
		P1.shipAccelerationY = 400;
	}
	else if (P1.shipAccelerationY < -400)
	{
		P1.shipAccelerationY = -400;
	}

		P1.ship.x = P1.ship.x + (P1.shipAccelerationX * GetFrameTime());
		P1.ship.y = P1.ship.y + (P1.shipAccelerationY * GetFrameTime());

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