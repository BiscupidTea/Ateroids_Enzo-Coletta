#include "menu.h"

int main()
{
	InitWindow(1200, 900, "Asteroids");
	InitAudioDevice();
	Menu();
	CloseAudioDevice();
	return 0;
}