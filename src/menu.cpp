#include "menu.h"

void Menu()
{
	RECOPTIONS play;
	RECOPTIONS rules;
	RECOPTIONS options;
	RECOPTIONS credits;
	RECOPTIONS escape;
	bool closeGame = false;
	CreateOptions(play, rules, options, credits, escape);
	do
	{
		DrawMenu(play, rules, options, credits, escape);
		switch (CheckInput(play, rules, options, credits, escape))
		{
		case 1:
			Game();
			break;

		case 2:
			do
			{
				DrawRules();
			} while (ExitButton() == false);
			break;

		case 3:
			do
			{
				DrawOptions();
				if (IsKeyPressed(KEY_P))
				{
					ToggleFullscreen();
				}
			} while (ExitButton() == false);
			break;

		case 4:
			do
			{
				DrawCredits();
			} while (ExitButton() == false);

			break;


		case 5:
			closeGame = true;
			break;

		default:
			break;
		}

	} while (closeGame == false);

	CloseWindow();
}

void CreateOptions(RECOPTIONS& play, RECOPTIONS& rules, RECOPTIONS& options, RECOPTIONS& credits, RECOPTIONS& escape)
{
	play.rectangle.x = ((GetScreenWidth() / 2) - (200 / 2));
	play.rectangle.y = (200);
	play.rectangle.height = 40;
	play.rectangle.width = 200;
	play.name = "play";

	rules.rectangle.x = ((GetScreenWidth() / 2) - (200 / 2));
	rules.rectangle.y = (300);
	rules.rectangle.height = 40;
	rules.rectangle.width = 200;
	rules.name = "rules";

	options.rectangle.x = ((GetScreenWidth() / 2) - (200 / 2));
	options.rectangle.y = (400);
	options.rectangle.height = 40;
	options.rectangle.width = 200;
	options.name = "options";

	credits.rectangle.x = ((GetScreenWidth() / 2) - (200 / 2));
	credits.rectangle.y = (500);
	credits.rectangle.height = 40;
	credits.rectangle.width = 200;
	credits.name = "credits";

	escape.rectangle.x = ((GetScreenWidth() / 2) - (200 / 2));
	escape.rectangle.y = (600);
	escape.rectangle.height = 40;
	escape.rectangle.width = 200;
	escape.name = "exit";
}

int CheckInput(RECOPTIONS& play, RECOPTIONS& rules, RECOPTIONS& options, RECOPTIONS& credits, RECOPTIONS& escape)
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (PointRectangleColision(play.rectangle.x, play.rectangle.y, play.rectangle.width, play.rectangle.height))
		{
			return 1;
		}
		else if (PointRectangleColision(rules.rectangle.x, rules.rectangle.y, rules.rectangle.width, rules.rectangle.height))
		{
			return 2;
		}
		else if (PointRectangleColision(options.rectangle.x, options.rectangle.y, options.rectangle.width, options.rectangle.height))
		{
			return 3;
		}
		else if (PointRectangleColision(credits.rectangle.x, credits.rectangle.y, credits.rectangle.width, credits.rectangle.height))
		{
			return 4;
		}
		else if (PointRectangleColision(escape.rectangle.x, escape.rectangle.y, escape.rectangle.width, escape.rectangle.height))
		{
			return 5;
		}
	}
}

bool PointRectangleColision(float& x, float& y, float& w, float& h)
{
	if (GetMouseX() >= x &&
		GetMouseX() <= x + w &&
		GetMouseY() >= y &&
		GetMouseY() <= y + h)
	{
		return true;
	}
	return false;
}

void DrawMenu(RECOPTIONS& play, RECOPTIONS& rules, RECOPTIONS& options, RECOPTIONS& credits, RECOPTIONS& escape)
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawText("Menu en espera", (GetScreenWidth() / 2) - (MeasureText("Menu en espera", 50) / 2), 50, 50, WHITE);
	DrawRectangleRec(play.rectangle, WHITE);
	DrawText(play.name.c_str(), (GetScreenWidth() / 2) - (MeasureText(play.name.c_str(), 20) / 2), 205, 20, BLACK);
	DrawRectangleRec(rules.rectangle, WHITE);
	DrawText(rules.name.c_str(), (GetScreenWidth() / 2) - (MeasureText(rules.name.c_str(), 20) / 2), 305, 20, BLACK);
	DrawRectangleRec(options.rectangle, WHITE);
	DrawText(options.name.c_str(), (GetScreenWidth() / 2) - (MeasureText(options.name.c_str(), 20) / 2), 405, 20, BLACK);
	DrawRectangleRec(credits.rectangle, WHITE);
	DrawText(credits.name.c_str(), (GetScreenWidth() / 2) - (MeasureText(credits.name.c_str(), 20) / 2), 505, 20, BLACK);
	DrawRectangleRec(escape.rectangle, WHITE);
	DrawText(escape.name.c_str(), (GetScreenWidth() / 2) - (MeasureText(escape.name.c_str(), 20) / 2), 605, 20, BLACK);
	EndDrawing();
}

void DrawRules()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawText("Pong is a 2d game between two players. The objective is to score in ", 0, 55, 50, WHITE);
	DrawText("the opposite zone to add 1 point whoever reaches 10 points first", 0, 205, 50, WHITE);
	DrawText("will be the winner. This mod also adds power up.", 0, 305, 50, WHITE);
	DrawText("Pressing SPACE pauses the game.", 0, 405, 50, WHITE);
	DrawText("Player 1 will handle the left pad with the W and S arrows.", 0, 505, 50, WHITE);
	DrawText("Player 2 controls the paddle with the UP and DOWN arrows.", 0, 650, 50, WHITE);
	DrawText("There is also an AI option for those who don't want to play against another person.", 0, 750, 50, WHITE);
	DrawRectangle(GetScreenWidth() - 100, 0, 100, 55, RED);
	DrawText("Esc", GetScreenWidth() - 75, 25, 30, BLACK);
	EndDrawing();
}

void DrawOptions()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawRectangle(GetScreenWidth() / 2 - (MeasureText("Fullscreen/Windowed", 50) / 2), (GetScreenHeight() / 2), 700, 50, WHITE);
	DrawText("P = Fullscreen/Windowed", GetScreenWidth() / 2 - (MeasureText("Fullscreen/Windowed", 50) / 2) + 50, GetScreenHeight() / 2, 50, BLACK);
	DrawRectangle(GetScreenWidth() - 100, 0, 100, 55, RED);
	DrawText("Esc", GetScreenWidth() - 75, 25, 30, BLACK);
	EndDrawing();
}

void DrawCredits()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawText("Game Made by Enzo Coletta", (GetScreenWidth() / 2) - (MeasureText("Game Made by Enzo Coletta", 50) / 2), GetScreenHeight() / 2, 50, WHITE);
	DrawRectangle(GetScreenWidth() - 100, 0, 100, 55, RED);
	DrawText("Esc", GetScreenWidth() - 75, 25, 30, BLACK);
	EndDrawing();
}

bool ExitButton()
{
	return true;
}