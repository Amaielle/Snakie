	//file main.cpp
//date 05/02/2022
//project 2d simple game
//author julie


//includes

#include "Game.h"

int main()

{
	//Init random seed
	std::srand(static_cast<unsigned>(time(NULL)));

	//Init game Engine

	Game game;


	//Game Loop
	while (game.getWindowIsOpen())
	{

		//Update
		game.update();

		//Render
		game.render();
		//window.clear(sf::Color(16,94,38,255)); //clear old frame -- color the screen just for fun

	   
	}
	//End of Application 

	return 0;

}