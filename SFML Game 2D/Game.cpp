#include "Game.h"

//destructors
Game::~Game()
{
	delete this->window;
}
//constructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFood();
	this->initSnake();
	this->initfont();
	this->initscore();
}
//Accessors

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

const bool Game::intersection(const sf::CircleShape& c1, const sf::CircleShape& c2)
{
	sf::FloatRect circ1 = c1.getGlobalBounds();
	sf::FloatRect circ2 = c2.getGlobalBounds();

	return circ1.intersects(circ2);
}

int Game::sgn(float f)
{
	return f<-eps ? -1 : f>eps;
}



//public functions

void Game::spawnfood()
{
	/*
	* @return void
	* spans foods and sets their position 
	* -sets a random position
	* adds food to the vector
	* 
	*/
	this->food.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - 2*this->food.getRadius())),
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - 2*this->food.getRadius()))
	);
	//adding the food to the foodies vector
	this->foodies.push_back(this->food);


}

void Game::spawntail()
{
	/*
	@return void
	evaluate the snake motion to add the new snake tail part
	-based on movement of last tail part
	-if no tail spawned yet, consider head as first tail element
	-Eat some food = add tail to the tailys vector with position 2*radius in 
	the oposite direction from last pressed key
	-vector of positions of tailes needs to be updated
	*/
	this->Snake_tail.setRadius(20.f);
	this->Snake_tail.setFillColor(sf::Color::Yellow);

	if (tailies.empty())

	{
		//regardless of the situation tail parts have the same shape
		switch (d)
		{
		case right:
			this->Snake_tail.setPosition(this->Snake_head.getPosition().x - this->Snake_head.getRadius(),
				this->Snake_head.getPosition().y);
			break;
		case down:
			this->Snake_tail.setPosition(this->Snake_head.getPosition().x,
				this->Snake_head.getPosition().y - this->Snake_head.getRadius());
			break;
		case left:
			this->Snake_tail.setPosition(this->Snake_head.getPosition().x - this->Snake_head.getRadius(),
				this->Snake_head.getPosition().y);
			break;
		case up:
			this->Snake_tail.setPosition(this->Snake_head.getPosition().x,
				this->Snake_head.getPosition().y + this->Snake_head.getRadius());
			break;
		}

	}
	//We decide to insert new tail bones between head and first one 
	//it ensure us to know the pisition where it should spanwn
	else
	{
		switch (d)
		{
		case right:
			this->Snake_tail.setPosition(this->Snake_head.getPosition().x - this->Snake_head.getRadius(),
				this->Snake_head.getPosition().y);
			break;
		case down:
			this->Snake_tail.setPosition(this->Snake_head.getPosition().x,
				this->Snake_head.getPosition().y - this->Snake_head.getRadius());
			break;
		case left:
			this->Snake_tail.setPosition(this->Snake_head.getPosition().x - this->Snake_head.getRadius(),
				this->Snake_head.getPosition().y);
			break;
		case up:
			this->Snake_tail.setPosition(this->Snake_head.getPosition().x,
				this->Snake_head.getPosition().y + this->Snake_head.getRadius());
			break;
		}
	}
	this->tailies.push_back(this->Snake_tail);
}

void Game::pollEvents()
{
	//Event Polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this-> window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			this->window->close();
			break;
		}
	}
}


void Game::updatefood()
{
	/*
	@return void

	update timer and check if food needs to be spawned
	*/

	//Updating timer for food spawning 
	if (this->foodies.size() < this->maxfoodies)
	{
		

		if (this->foodSpawnTimer >= this->foodSpawnTimermax)
		{
			//spawnign food and reset timer	
			this->spawnfood();
			this->foodSpawnTimer = 0.f;
		}
		else
			this->foodSpawnTimer += 1.f;
	}

	// for loop over all the food sprites
	for (int i = 0; i < this->foodies.size(); i++)
	{
		bool deleted = false;
		//check if contact with Snake Head
		if (intersection(this->foodies[i], this->Snake_head))
		{
			deleted = true;
		}
		if (deleted) 
		{
			//kill the food in the vector
			this->foodies.erase(this->foodies.begin() + i);
			spawntail();
			//get points
			this->points += 1.f;
			this->foodSpawnTimermax -= 10.f;
			//this->Snake_speed += 2.f;
		}
	}
}

void Game::updatesnake()
{
	//move the snake head with the arrow pad
	if (ev.type == sf::Event::KeyPressed) 
	{
		switch (ev.key.code)
		{
		case sf::Keyboard::Up:
			this->Snake_head.move(0, -this->Snake_speed);
			this->d = up;
			break;
		case sf::Keyboard::Down:
			this->Snake_head.move(0, this->Snake_speed);
			this->d = down;
			break;
		case sf::Keyboard::Right:
			this->Snake_head.move(this->Snake_speed, 0);
			this->d = right;
			break;
		case sf::Keyboard::Left:
			this->Snake_head.move(-this->Snake_speed, 0);
			this->d = left;
			break;
		}
	}
		
	//if no direction key is pressed the snake still has to move as it was before 
	//keyboard input stopped
	else
	{
		switch (d)
		{
		case right:
			this->Snake_head.move(this->Snake_speed, 0);
			break;
		case down:
			this->Snake_head.move(0, this->Snake_speed);
			break;
		case left:
			this->Snake_head.move(-this->Snake_speed, 0);
			break;
		case up:
			this->Snake_head.move(0, -this->Snake_speed);
			break;
		}
	}
	

	//check collision with borders IMPORTANT : If condition is maybe not best ? -> look for a better code
	// positions bizarres
	if (this->Snake_head.getPosition().x <= this->Snake_head.getRadius())
	{
		//we loose the game

		this->endgame = true;
	}
	else if (this->Snake_head.getPosition().x >= (this->videoMode.width - 2*this->Snake_head.getRadius()))
	{
		//we loose the game
		this->endgame = true;
	}
	else if(this->Snake_head.getPosition().y <= this->Snake_head.getRadius())
	{
		//we loose the game
		this->endgame = true;
	}
	else if (this->Snake_head.getPosition().y >= (this->videoMode.height - 2*this->Snake_head.getRadius()))
	{
		//we loose the game
		this->endgame = true;
	}

}

void Game::updatetail()
{
	for (int i = 0; i < this->tailies.size(); i++)
	{
		if (i == 0)// cas particulier de la tete qui nest pas dans le vecteur
		{
			//check if heads moved too far
			if (!intersection(this->Snake_head, this->tailies[i]))
			{
				//problem here, if the distance betwen them is smaller than snake speed 'vibrate' around the good position
				//move towards the head
				this->tailies[i].move(sgn(this->Snake_head.getPosition().x - this->tailies[i].getPosition().x) * this->Snake_speed,
					sgn(this->Snake_head.getPosition().y - this->tailies[i].getPosition().y) * this->Snake_speed);
				//this allows diagonal moovement which we want to eliminate ?
			}
		}
		else
		{
			if (!intersection(this->tailies[i-1], this->tailies[i]))
			{
				//move towards the head
				this->tailies[i].move(sgn(this->tailies[i-1].getPosition().x - this->tailies[i].getPosition().x) * this->Snake_speed, 
					sgn(this->tailies[i-1].getPosition().y - this->tailies[i].getPosition().y) * this->Snake_speed);
			}

		}
	}
}

void Game::updatescore()
{
	std::stringstream ss;
	ss << "Score :" << this->points;	
	this->score.setString(ss.str());
}



void Game::update()
{
	this->pollEvents();
	if (!this->endgame)
	{
		this->updatefood();

		this->updatesnake();

		this->updatetail();

		this->updatescore();

		sf::sleep(sf::seconds(0.01));
	}
}

void Game::renderfood()
{
	
	for (auto& e : this->foodies)
	{
		this->window->draw(e);
	}
}

void Game::rendersnake()
{
	//render head
	this->window->draw(this->Snake_head);
	//render tail
	for (auto& e : this->tailies)
	{
		this->window->draw(e);
	}
}

void Game::renderscore()
{
	this->window->draw(this->score);
}

void Game::renderEnd()
{
	this->Endnotif.setFont(this->font);
	this->Endnotif.setCharacterSize(80);
	this->Endnotif.setFillColor(sf::Color::White);
	this->Endnotif.setString("Go home snake, you're drunk !");
	this->Endnotif.setPosition(200,250);
	this->window->draw(this->Endnotif);
}

void Game::render()
{
	/*
	* @return void
	* -clear old frame
	* -render object
	* -display object in window
	* 
	Renders the game object
	*/

	this->window->clear(sf::Color(1, 50, 32, 255)); //clear old frame -- color the screen just for fun
	//draw objects
	// 
	//Here we draw directly in the window for simplicity (unusual)
	this->rendersnake();
	this->renderfood();
	this->renderscore();
	if (endgame)
	{
		this->renderEnd();
	}
	this->window->display();

	// render is the last function to run so we pause after
	//on fait dormir une seconde entre chaque iter
	sf::sleep(sf::seconds(0.01));
}

//private functions

void Game::initVariables()
{
	this->window = nullptr;
	
	//game logic
	this -> points = 0;
	this->foodSpawnTimermax = 500.f;
	this->foodSpawnTimer = this->foodSpawnTimermax;
	this->maxfoodies = 3;
	this->Snake_speed = 5.f;
	//this->last_dir=0; //snake is stopped before game starts
	this->d = none;//snake is stopped before game starts
	this->endgame = false;
}

//Window Definition

void Game::initWindow()
{
	this->videoMode.height = 768;
	this->videoMode.width = 1366;
	//to automaticaly adapt to screen desktop diemsions this->videoMode.getDesktopMode();
    this->window = new sf::RenderWindow(this->videoMode, "2D Simple game 1", sf::Style::Titlebar | sf::Style::Close);
	//can add fullscreen option sf::Style::Fullscreen
	//lower the frame rate 
	this->window->setFramerateLimit(35);

}

void Game::initFood()
{
	this->food.setPosition(10.f,10.f);
	this->food.setRadius(15.f);
	this->food.setFillColor(sf::Color::Red);
	this->food.setOutlineColor(sf::Color::Yellow);
	this->food.setOutlineThickness(1.f);
}

void Game::initSnake()
{
	this->Snake_head.setRadius(20.f);
	this->Snake_head.setPosition((this->videoMode.width / 2) - this->Snake_head.getRadius(), (this->videoMode.height / 2) - this->Snake_head.getRadius());
	this->Snake_head.setFillColor(sf::Color::Yellow);

}


void Game::initscore()
{
	this->score.setFont(this->font);
	this->score.setCharacterSize(20);
	this->score.setFillColor(sf::Color::White);
	this->score.setString("Score : 0");
}

void Game::initfont()
{
	if (this->font.loadFromFile("font/SupermercadoOne-Regular.ttf"))
	{
		std::cerr << "Failed to load font" << std::endl;
	}

}



