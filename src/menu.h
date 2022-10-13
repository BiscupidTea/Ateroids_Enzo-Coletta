#pragma once
#include <string>
#include "game.h"

extern Texture2D ship_move;
extern Texture2D scope;
extern Texture2D AsteroidTipe_1;
extern Texture2D background;
extern Texture2D ship_stop;
extern Texture2D asteroidB;
extern Texture2D asteroidM;
extern Texture2D asteroidS;
extern Texture2D enemyB;
extern Texture2D playB;
extern Texture2D rulesB;
extern Texture2D optionsB;
extern Texture2D creditsB;
extern Texture2D escapeB;
extern Texture2D continueB;
extern Texture2D disparo;

extern Sound asteroidSound;
extern Sound dead;
extern Sound shieldPiked;
extern Sound shoterPiked;
extern Sound shot1;
extern Music gamemusic;

struct RECOPTIONS
{
	Rectangle rectangle={};
};

void Menu();
int CheckInput(
	RECOPTIONS& play, 
	RECOPTIONS& rules, 
	RECOPTIONS& options, 
	RECOPTIONS& credits, 
	RECOPTIONS& escape
);

void DrawMenu(
	RECOPTIONS& play, 
	RECOPTIONS& rules, 
	RECOPTIONS& options, 
	RECOPTIONS& credits,
	RECOPTIONS& escape
);

void DrawOptions();

void DrawCredits();

void DrawRules();

void DrawExitButton();

bool PointRectangleColision(
	float& x, 
	float& y, 
	float& w, 
	float& h
);

void CreateOptions(
	RECOPTIONS& play, 
	RECOPTIONS& rules,
	RECOPTIONS& options, 
	RECOPTIONS& credits, 
	RECOPTIONS& escape
);

bool ExitButton();