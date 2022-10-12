#include "menu.h"

int main()
{
	InitWindow(1024, 768, "Asteroids");
	InitAudioDevice();
	Menu();
	CloseAudioDevice();
	return 0;
}