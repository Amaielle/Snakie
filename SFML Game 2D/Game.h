//file game.h
//date 05/02/2022
//project 2d simple game
//author julie

#pragma once
//if we dont use pragma once we have to do the usual : 
//#ifndef GAME_1_HH
//#define GAME_1_HH
//#endif // !GAME_1_HH

//includes
//#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <math.h>
#include <sstream>

#define eps 1e-9 

/*
class that acts as the game engine
wrapper class

*/




class Game
{
public:
	//destructors / constructors

	virtual ~Game();
	Game();


	//accessors

	const bool getWindowIsOpen() const;
	const bool intersection(const sf::CircleShape& c1, const sf::CircleShape& c2);
	int sgn(float f);
	//std::vector<float> FollowPrevious( sf::CircleShape& c1,  sf::CircleShape& c2);
	

	//public functions
	void spawnfood();
	void spawntail();
	void pollEvents();
	void updatefood();
	void updatesnake();
	void updatetail();
	void updatescore();
	void update();
	void renderfood();
	void rendersnake();
	void renderscore();
	void renderEnd();
	void render();
	

	//game objects
	std::vector<sf::CircleShape> foodies;
	std::vector<sf::CircleShape> tailies;
	//to create texrured object we usually use sf::sprite, but i wont use it here because i want somthg simple
	sf::CircleShape food;
	sf::CircleShape Snake_head;
	sf::CircleShape Snake_tail;
	//game logic
	float Snake_speed;

	//window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

private:

	sf::Vector2f Snake_head_last_pos; 

	//Ressources
	sf::Font font;

	//Text
	sf::Text score;
	sf::Text Endnotif;

	//game logic 

	int points;
	float foodSpawnTimer;
	float foodSpawnTimermax;
	int maxfoodies;
	bool endgame;
	enum direction 
	{
		right,
		down,
		left,
		up,
		none
	};
	direction d;

	//private functions
	void initVariables();
	void initWindow();
	void initFood();
	void initSnake();
	void initfont();	
	void initscore();
};


class  Taily : public Game
{
public:
private:
};