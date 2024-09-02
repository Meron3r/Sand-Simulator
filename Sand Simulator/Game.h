#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>

/*
	Class that actsas the game engine
	Wrapper class.
*/

class Game
{
private:
	//Variables
	int pixelWidth, pixelHeight;
	int pixelSize;
	int mouseX, mouseY;
	int relMouseX, relMouseY, gridMousePos;
	int brush;
	int idx;
	bool drawing;

	//Grid
	std::vector<int> grid, pastGrid;

	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Fonts and Texts
	sf::Font mainFont;
	sf::Text type;

	//Private functions
	void initVariables();
	void initWindow();
public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	sf::Color getBrushColor();
	sf::Color getTileColor(int tile) const;

	//Simulation Functions
	void simulateVirus();
	void simulateAcid();
	void simulateWood();
	void simulateSeed();
	void simulateWater();
	void simulateSand();
	void simulateParticles();

	//Functions
	void mouseDrawing();
	void renderGrid();
	void pollEvents();
	void update();
	void render();
};

