#pragma once
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "object/player.h"
#include "object/asteroid.h"

using namespace std;

void Game();

void DrawGame(PLAYER P1, Texture2D ship_idle, Texture2D scope);
void PlayerMovement(PLAYER& P1);
void PlayerWallColition(PLAYER& P1);