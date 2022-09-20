#pragma once
#include <string>
#include "game.h"


struct RECOPTIONS
{
	Rectangle rectangle;
	std::string name;
};

void Menu();
int CheckInput(RECOPTIONS& play, RECOPTIONS& rules, RECOPTIONS& options, RECOPTIONS& credits, RECOPTIONS& escape);
void DrawMenu(RECOPTIONS& play, RECOPTIONS& rules, RECOPTIONS& options, RECOPTIONS& credits, RECOPTIONS& escape);
void DrawOptions();
void DrawCredits();
void DrawRules();
bool PointRectangleColision(float& x, float& y, float& w, float& h);
void CreateOptions(RECOPTIONS& play, RECOPTIONS& rules, RECOPTIONS& options, RECOPTIONS& credits, RECOPTIONS& escape);
bool ExitButton();