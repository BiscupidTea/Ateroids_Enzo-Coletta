#pragma once
#include "raylib.h"
#include "raymath.h"
#include "object/player.h"
#include <iostream>

using namespace std;

void Game();

void DrawGame(PLAYER P1);
void PlayerMovement(PLAYER& P1);
void PlayerWallColition(PLAYER& P1);