#include "Game.h"

//Private 
void Game::initVariables()
{
	this->window = nullptr;

	//Set Vars
	this->brush = 0;

	//Setup rand
	srand(time(0));

	//Setup Font
	this->mainFont.loadFromFile("mainFont.ttf");
}

void Game::initWindow()
{
	std::cout << "Pixel Height: ";
	std::cin >> this->pixelHeight;
	std::cout << "Pixel Width: ";
	std::cin >> this->pixelWidth;
	std::cout << "Pixel Size: ";
	std::cin >> this->pixelSize;

	this->type.setCharacterSize(1.5 * this->pixelSize);
	this->type.setFillColor(sf::Color(255, 255, 255, 225));
	this->type.setFont(this->mainFont);

	for (int i = 0; i < (this->pixelHeight * this->pixelWidth); i++) 
		this->grid.push_back(0);
	for (int i = 0; i < this->pixelWidth; i++)
		this->grid[i] = 1;
	for (int i = (this->pixelHeight * this->pixelWidth) - 1; i > (this->pixelHeight * this->pixelWidth) - this->pixelWidth - 1; i--)
		this->grid[i] = 1;
	for (int i = 0; i < (this->pixelHeight * this->pixelWidth); i += this->pixelWidth)
		this->grid[i] = 1;
	for (int i = this->pixelWidth - 1; i < (this->pixelHeight * this->pixelWidth); i += this->pixelWidth)
		this->grid[i] = 1;

	this->videoMode.height = this->pixelSize * this->pixelHeight;
	this->videoMode.width = this->pixelSize * this->pixelWidth;
	this->window = new sf::RenderWindow(this->videoMode, "Sand Simulation", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

//Constructors / Destructors
Game::Game() 
{
	this->initVariables();
	this->initWindow();
}


Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

sf::Color Game::getTileColor(int tile) const
{
	if (tile == 0) return sf::Color(0, 0, 0, 255);
	if (tile == 1) return sf::Color(128, 128, 128, 255);
	if (tile == 2) return sf::Color(255, 255, 75, 255);
	if (tile == 3) return sf::Color(75, 75, 255, 255);
	if (tile == 4) return sf::Color(110, 255, 110, 255);
	if (tile == 5) return sf::Color(83, 49, 24, 255);
	if (tile == 6) return sf::Color(110, 255, 110, 130);
	if (tile == 7) return sf::Color(176, 191, 26, 255);
	if (tile == 8) return sf::Color(160, 32, 240, 255);
	else return sf::Color(255, 255, 255, 255);
}

sf::Color Game::getBrushColor()
{
	if (this->brush == 0) 
	{
		this->type.setString("Eraser");
		return sf::Color(255, 120, 120, 255);
	}
	if (this->brush == 1) 
	{
		this->type.setString("Stone");
		return sf::Color(150, 150, 150, 255);
	}
	if (this->brush == 2) 
	{
		this->type.setString("Sand");
		return sf::Color(255, 255, 150, 255);
	}
	if (this->brush == 3)
	{
		this->type.setString("Water");
		return sf::Color(120, 120, 255, 255);
	}
	if (this->brush == 4)
	{

		this->type.setString("Sead");
		return sf::Color(150, 255, 150, 255);
	}
	if (this->brush == 5) 
	{
		this->type.setString("Wood");
		return sf::Color(90, 56, 31, 255);
	}
	if (this->brush == 6) 
	{
		this->type.setString("Leaves");
		return sf::Color(150, 255, 150, 130);
	}
	if (this->brush == 7) 
	{
		this->type.setString("Acid");
		return sf::Color(176, 191, 26, 200);
	}
	if (this->brush == 8) 
	{
		this->type.setString("Coruption");
		return sf::Color(160, 32, 240, 200);
	}
	else return sf::Color(255, 255, 255, 255);
}

//Simulation Functions
void Game::simulateVirus()
{
	if (this->pastGrid[this->idx] == 8)
	{
		if (this->grid[this->idx - 1] != 8 && this->grid[this->idx - 1] != 0 && rand() % 1000 == 0)
			this->grid[this->idx - 1] = 8;
		if (this->grid[this->idx + 1] != 8 && this->grid[this->idx + 1] != 0 && rand() % 1000 == 0)
			this->grid[this->idx + 1] = 8;
		if (this->grid[this->idx + this->pixelWidth] != 8 && this->grid[this->idx + this->pixelWidth] != 0 && rand() % 1000 == 0)
			this->grid[this->idx + this->pixelWidth] = 8;
		if (this->grid[this->idx - this->pixelWidth] != 8 && this->grid[this->idx - this->pixelWidth] != 0 && rand() % 1000 == 0)
			this->grid[this->idx - this->pixelWidth] = 8;
	}
}

void Game::simulateAcid()
{
	if (this->pastGrid[this->idx] == 7)
	{
		if (this->grid[this->idx - 1] != 1 && this->grid[this->idx - 1] != 7 && rand() % 200 == 0)
			this->grid[this->idx - 1] = 0;
		if (this->grid[this->idx + 1] != 1 && this->grid[this->idx + 1] != 7 && rand() % 200 == 0)
			this->grid[this->idx + 1] = 0;
		if (this->grid[this->idx + this->pixelWidth] != 1 && this->grid[this->idx + this->pixelWidth] != 7 && rand() % 200 == 0)
			this->grid[this->idx + this->pixelWidth] = 0;
		if (this->grid[this->idx - this->pixelWidth] != 1 && this->grid[this->idx - this->pixelWidth] != 7 && rand() % 200 == 0)
			this->grid[this->idx - this->pixelWidth] = 0;

		if (this->grid[this->idx + this->pixelWidth] == 0)
		{
			this->grid[this->idx] = 0;
			this->grid[this->idx + this->pixelWidth] = 7;
		}
		else
		{
			if (this->grid[this->idx + 1] == 0 && this->grid[this->idx - 1] == 0)
			{
				if (rand() % 2 == 0)
				{
					this->grid[this->idx] = 0;
					this->grid[this->idx + 1] = 7;
				}
				else
				{
					this->grid[this->idx] = 0;
					this->grid[this->idx - 1] = 7;
				}
			}
			else
			{
				if (this->grid[this->idx + 1] == 0)
				{
					this->grid[this->idx] = 0;
					this->grid[this->idx + 1] = 7;
				}
				else if (this->grid[this->idx - 1] == 0)
				{
					this->grid[this->idx] = 0;
					this->grid[this->idx - 1] = 7;
				}
			}
		}
	}
}

void Game::simulateWood()
{
	if (this->pastGrid[this->idx] == 5)
	{
		if (this->grid[this->idx + this->pixelWidth] != 0 && this->grid[this->idx - this->pixelWidth] == 0 && rand() % 10 == 0)
		{
			for (int i = 0; i < 15; i++)
				for (int j = 0; j < 10; j++)
				{
					if (this->idx + (this->pixelWidth * j) + i >= this->pixelWidth * this->pixelHeight || this->idx + (this->pixelWidth * j) - i < 0)
						continue;
					if ((this->grid[this->idx + (this->pixelWidth * j) + i] == 3 || this->grid[this->idx + (this->pixelWidth * j) - i] == 3) && rand() % 300 == 0)
					{
						if (this->grid[this->idx + (this->pixelWidth * j) + i] == 3)
							this->grid[this->idx + (this->pixelWidth * j) + i] = 0;
						else
							this->grid[this->idx + (this->pixelWidth * j) - i] = 0;

						this->grid[this->idx - this->pixelWidth] = 5;
					}
				}
		}

		else if (this->grid[this->idx + this->pixelWidth] != 0 && this->grid[this->idx - this->pixelWidth] == 0 && this->grid[this->idx + 1] == 0 && this->grid[this->idx - 1] == 0 && rand() % 1750 == 0)
		{
			this->grid[this->idx - 1] = 6;
			this->grid[this->idx + 1] = 6;
			this->grid[this->idx - this->pixelWidth] = 6;
		}
	}
}

void Game::simulateSeed()
{
	if (this->pastGrid[this->idx] == 4)
	{
		if (this->grid[this->idx + this->pixelWidth] == 0)
		{
			this->grid[this->idx] = 0;
			this->grid[this->idx + this->pixelWidth] = 4;
		}
		else
		{
			if (this->grid[this->idx + this->pixelWidth] == 3)
				this->grid[this->idx] = 0;
		}
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (this->grid[this->idx + (this->pixelWidth * j) + i] == 3 || this->grid[this->idx + (this->pixelWidth * j) - i] == 3)
				{
					if (this->idx + (this->pixelWidth * j) + i >= this->pixelWidth * this->pixelHeight || this->idx + (this->pixelWidth * j) - i < 0)
						continue;
					if (rand() % 750 == 0)
					{
						this->grid[this->idx] = 5;
						if (this->grid[this->idx + (this->pixelWidth * j) + i] == 3)
							this->grid[this->idx + (this->pixelWidth * j) + i] = 0;
						else
							this->grid[this->idx + (this->pixelWidth * j) - i] = 0;
					}
				}
	}
}

void Game::simulateWater()
{
	if (this->pastGrid[this->idx] == 3)
	{
		if (this->grid[this->idx + this->pixelWidth] == 0)
		{
			this->grid[this->idx] = 0;
			this->grid[this->idx + this->pixelWidth] = 3;
		}
		else
		{
			if (this->grid[this->idx + 1] == 0 && this->grid[this->idx - 1] == 0)
			{
				if (rand() % 2 == 0)
				{
					this->grid[this->idx] = 0;
					this->grid[this->idx + 1] = 3;
				}
				else
				{
					this->grid[this->idx] = 0;
					this->grid[this->idx - 1] = 3;
				}
			}
			else
			{
				if (this->grid[this->idx + 1] == 0)
				{
					this->grid[this->idx] = 0;
					this->grid[this->idx + 1] = 3;
				}
				else if (this->grid[this->idx - 1] == 0)
				{
					this->grid[this->idx] = 0;
					this->grid[this->idx - 1] = 3;
				}
			}
		}
	}
}

void Game::simulateSand()
{
	if (this->pastGrid[this->idx] == 2)
	{
		if (this->grid[this->idx + this->pixelWidth] == 0 || this->grid[this->idx + this->pixelWidth] == 3 || this->grid[this->idx + this->pixelWidth] == 7)
		{
			this->grid[this->idx] = this->grid[this->idx + this->pixelWidth];
			this->grid[this->idx + this->pixelWidth] = 2;
		}
		else
		{
			if (this->grid[this->idx + this->pixelWidth + 1] == 0 && this->grid[this->idx + this->pixelWidth - 1] == 0)
			{
				if (rand() % 2 == 0)
				{
					this->grid[this->idx] = 0;
					this->grid[this->idx + this->pixelWidth + 1] = 2;
				}
				else
				{
					this->grid[this->idx] = 0;
					this->grid[this->idx + this->pixelWidth - 1] = 2;
				}
			}
			else
			{
				if (this->grid[this->idx + this->pixelWidth + 1] == 0 || this->grid[this->idx + this->pixelWidth + 1] == 3)
				{
					this->grid[this->idx] = this->grid[this->idx + this->pixelWidth + 1];
					this->grid[this->idx + this->pixelWidth + 1] = 2;
				}
				else if (this->grid[this->idx + this->pixelWidth - 1] == 0 || this->grid[this->idx + this->pixelWidth - 1] == 3)
				{
					this->grid[this->idx] = this->grid[this->idx + this->pixelWidth - 1];
					this->grid[this->idx + this->pixelWidth - 1] = 2;
				}
			}
		}
	}
}

//Functions
void Game::simulateParticles()
{
	this->pastGrid = this->grid;
	
	for (this->idx = 0; this->idx < int(this->grid.size()); this->idx++)
	{
		this->simulateVirus();
		this->simulateAcid();
		this->simulateWood();
		this->simulateSand();
		this->simulateWater();
		this->simulateSeed();
	}
}

void Game::mouseDrawing()
{
	if (this->drawing && this->gridMousePos > -1 && this->gridMousePos < int(this->grid.size()))
		this->grid[this->gridMousePos] = this->brush;
}

void Game::renderGrid()
{
	float x, y;
	x = y = 0.0f;
	sf::RectangleShape renderer;
	renderer.setSize(sf::Vector2f(float(this->pixelSize), float(this->pixelSize)));
	renderer.setPosition(sf::Vector2f(x, y));
	for (auto i : this->grid)
	{
		renderer.setFillColor(this->getTileColor(i));
		this->window->draw(renderer);
		x += this->pixelSize;
		if (x >= this->pixelWidth * this->pixelSize)
		{
			x = 0;
			y += this->pixelSize;
		}
		renderer.setPosition(sf::Vector2f(x, y));
	}

	renderer.setPosition(sf::Vector2f((this->relMouseX * this->pixelSize), (this->relMouseY * this->pixelSize)));
	renderer.setFillColor(this->getBrushColor());
	this->window->draw(renderer);
}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		case sf::Event::MouseButtonPressed:
			if (this->ev.mouseButton.button == sf::Mouse::Left)
				this->drawing = true;
			break;
		case sf::Event::MouseButtonReleased:
			if (this->ev.mouseButton.button == sf::Mouse::Left)
				this->drawing = false;
			if (this->ev.mouseButton.button == sf::Mouse::Right)
				this->brush = (this->brush + 1) % 9;
			if (this->brush == 6)
				this->brush = (this->brush + 1) % 9;
			break;
		}
	}
}

void Game::update()
{
	//Find Mouse Pos + Relitive mouse
	this->mouseX = int(sf::Mouse::getPosition(*this->window).x) * int(this->window->getDefaultView().getSize().x / this->videoMode.width);
	this->mouseY = int(sf::Mouse::getPosition(*this->window).y) * int(this->window->getDefaultView().getSize().y / this->videoMode.height);
	
	this->relMouseX = floor(this->mouseX / this->pixelSize);
	this->relMouseY = floor(this->mouseY / this->pixelSize);
	this->gridMousePos = (this->pixelWidth * this->relMouseY) + this->relMouseX;

	//Events
	this->pollEvents();
	this->mouseDrawing();
	this->simulateParticles();
}

void Game::render()
{
	/*
		@return void

		- clear old frame
		- render objects
		- display frame in window

		Renders the game objects.
		
	*/

	//Clear Old Screen
	this->window->clear(sf::Color(0, 0, 0, 255));

	//Draw All Game Objects
	this->renderGrid();
	this->window->draw(this->type);

	//Render The Window
	this->window->display();
}