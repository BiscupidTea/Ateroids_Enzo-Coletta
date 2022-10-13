#include "menu.h"
	Texture2D Mouse_R;
	Texture2D Mouse_L;
	Texture2D title;

	Music menuMusic;

void Menu()
{
	
	background = LoadTexture("res/textures/background.png");
	ship_move = LoadTexture("res/textures/Ship_move.png");
	scope = LoadTexture("res/textures/scope.png");
	ship_stop = LoadTexture("res/textures/Ship_stop.png");
	asteroidB = LoadTexture("res/textures/asteroid (1).png");
	asteroidM = LoadTexture("res/textures/asteroid (2).png");
	asteroidS = LoadTexture("res/textures/asteroid (3).png");
	enemyB = LoadTexture("res/textures/flauta.png");
	title = LoadTexture("res/textures/titulo.png");
	playB = LoadTexture("res/textures/PLAY.png");
	rulesB = LoadTexture("res/textures/HTP.png");
	optionsB = LoadTexture("res/textures/options.png");
	creditsB = LoadTexture("res/textures/credits.png");
	escapeB = LoadTexture("res/textures/MENU.png");
	continueB = LoadTexture("res/textures/CONTINUE.png");
	Mouse_R = LoadTexture("res/textures/Mouse_R.png");
	Mouse_L = LoadTexture("res/textures/Mouse_L.png");
	disparo = LoadTexture("res/textures/disparo.png");

	asteroidSound = LoadSound("res/sounds/asteroid.wav");
	dead = LoadSound("res/sounds/dead.wav");
	shieldPiked = LoadSound("res/sounds/shieldPiked.wav");
	shoterPiked = LoadSound("res/sounds/shoterPiked.wav");
	shot1 = LoadSound("res/sounds/Shot1.wav");

	menuMusic = LoadMusicStream("res/sounds/menu_song.mp3");
	gamemusic = LoadMusicStream("res/sounds/game_song.mp3");

	RECOPTIONS play;
	RECOPTIONS rules;
	RECOPTIONS options;
	RECOPTIONS credits;
	RECOPTIONS escape;
	bool closeGame;
	float masterVolume = 0.5f;
	int maxScore = 0;

	CreateOptions(play, rules, options, credits, escape);
	closeGame = false;

		PlayMusicStream(menuMusic);
	while (closeGame == false && !WindowShouldClose())
	{
		UpdateMusicStream(menuMusic);
		ShowCursor();
		DrawMenu(play, rules, options, credits, escape);
		switch (CheckInput(play, rules, options, credits, escape))
		{
		case 1:
			StopMusicStream(menuMusic);
			closeGame = true;
			Game(closeGame, masterVolume, maxScore);
			PlayMusicStream(menuMusic);
			break;

		case 2:
			do
			{
				UpdateMusicStream(menuMusic);
				DrawRules();
			} while (!ExitButton());
			break;

		case 3:
			do
			{
				DrawOptions();
				if (IsKeyPressed(KEY_P))
				{
					ToggleFullscreen();
				}
					UpdateMusicStream(menuMusic);
			} while (!ExitButton());
			break;

		case 4:
			do
			{
				UpdateMusicStream(menuMusic);
				DrawCredits();
			} while (!ExitButton());
			break;

		case 5:
			closeGame = true;
			break;

		default:
			break;
		}

	}

	CloseWindow();
}

void CreateOptions(RECOPTIONS& play, RECOPTIONS& rules, RECOPTIONS& options, RECOPTIONS& credits, RECOPTIONS& escape)
{
	play.rectangle.x = static_cast<float>((GetScreenWidth() / 2) -(playB.width /2));
	play.rectangle.y = (200);
	play.rectangle.height = static_cast<float>(playB.height);
	play.rectangle.width = static_cast<float>(playB.width);

	rules.rectangle.x = static_cast<float>((GetScreenWidth() / 2) -(rulesB.width/2));
	rules.rectangle.y = (300);
	rules.rectangle.height = static_cast<float>(rulesB.height);
	rules.rectangle.width = static_cast<float>(rulesB.width);

	options.rectangle.x = static_cast<float>((GetScreenWidth() / 2) -(optionsB.width/2));
	options.rectangle.y = (400);
	options.rectangle.height = static_cast<float>(optionsB.height);
	options.rectangle.width = static_cast<float>(optionsB.width);

	credits.rectangle.x = static_cast<float>((GetScreenWidth() / 2) -( creditsB.width/2));
	credits.rectangle.y = (500);
	credits.rectangle.height = static_cast<float>(creditsB.height);
	credits.rectangle.width = static_cast<float>(creditsB.width);

	escape.rectangle.x = static_cast<float>((GetScreenWidth() / 2) -( escapeB.width/2));
	escape.rectangle.y = (600);
	escape.rectangle.height = static_cast<float>(escapeB.height);
	escape.rectangle.width = static_cast<float>(escapeB.width);
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
	return 6;
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
	DrawTexture(background, 0, 0, WHITE);
	DrawTexture(title, GetScreenWidth()/2 - title.width/2, -60, WHITE);
	//
	DrawRectangleRec(play.rectangle, WHITE);
	DrawTexture(playB, GetScreenWidth() / 2 - playB.width / 2, static_cast<int>(play.rectangle.y), WHITE);
	//
	DrawRectangleRec(rules.rectangle, WHITE);
	DrawTexture(rulesB, GetScreenWidth() / 2 - rulesB.width / 2, static_cast<int>(rules.rectangle.y), WHITE);
	//
	DrawRectangleRec(options.rectangle, WHITE);
	DrawTexture(optionsB, GetScreenWidth() / 2 - optionsB.width / 2, static_cast<int>(options.rectangle.y), WHITE);
	//
	DrawRectangleRec(credits.rectangle, WHITE);
	DrawTexture(creditsB, GetScreenWidth() / 2 - creditsB.width / 2, static_cast<int>(credits.rectangle.y), WHITE);
	//
	DrawRectangleRec(escape.rectangle, WHITE);
	DrawTexture(escapeB, GetScreenWidth() / 2 - escapeB.width / 2, static_cast<int>(escape.rectangle.y), WHITE);
	EndDrawing();
}

void DrawRules()
{
	BeginDrawing();
	DrawTexture(background, 0, 0, WHITE);
	DrawTexture(Mouse_L, GetScreenWidth() / 2 - Mouse_L.width, 100, WHITE);
	DrawTexture(Mouse_R, GetScreenWidth() / 2, 100, WHITE);
	DrawText("Left click to shoot", GetScreenWidth() / 2 - (MeasureText("Left click to shoot", 30) / 2), 300, 30, BLACK);
	DrawText("Right click to move", GetScreenWidth() / 2 - (MeasureText("Right click to move", 30) / 2), 400, 30, BLACK);
	DrawExitButton();
	EndDrawing();
}

void DrawOptions()
{
	BeginDrawing();
	DrawTexture(background, 0, 0, WHITE);
	DrawText("P = Fullscreen/Windowed", GetScreenWidth() / 2 - (MeasureText("P = Fullscreen/Windowed", 50) / 2), GetScreenHeight() / 2, 50, BLACK);
	DrawExitButton();
	EndDrawing();
}

void DrawCredits()
{
	BeginDrawing();
	DrawTexture(background, 0, 0, WHITE);
	DrawText("Programming and Audio", (GetScreenWidth() / 2) - (MeasureText("Programming and Audio", 50) / 2), 150, 50, BLACK);
	DrawText("Enzo Coletta", (GetScreenWidth() / 2) - (MeasureText("Enzo Coletta", 30) / 2), 225, 30, BLACK);
	DrawText("Art and Animations", (GetScreenWidth() / 2) - (MeasureText("Art and Animations", 50) / 2), 300, 50, BLACK);
	DrawText("Sara Lee", (GetScreenWidth() / 2) - (MeasureText("Sara Lee", 30) / 2), 375, 30, BLACK);
	DrawText("Anastasia Genero", (GetScreenWidth() / 2) - (MeasureText("Anastasia Genero", 30) / 2), 450, 30, BLACK);
	DrawExitButton();
	EndDrawing();
}

void DrawExitButton()
{
	DrawRectangle(GetScreenWidth() - 100, 0, 100, 55, RED);
	DrawText("EXIT", GetScreenWidth() - 75, 20, 25, BLACK);
}

bool ExitButton()
{
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		if ((GetMouseX() > (GetScreenWidth() - 100)) && (GetMouseY() < 55))
		{
			return true;
		}
	}
	return false;
}