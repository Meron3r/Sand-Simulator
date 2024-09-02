/*
* 
*	Sand Simulator
* 
*/

#include "Game.h"

//using namespace sf;

int main()
{
	//Init game engine
	Game game;

	//Game Loop
	while (game.running())
	{
		//Update
		game.update();

		//Render
		game.render();

	}

	//End of App
	return 0;
}