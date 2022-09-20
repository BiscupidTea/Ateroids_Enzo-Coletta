#pragma once
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "object/player.h"

using namespace std;

void Game();

void DrawGame(PLAYER P1);
void PlayerMovement(PLAYER& P1);
void PlayerWallColition(PLAYER& P1);