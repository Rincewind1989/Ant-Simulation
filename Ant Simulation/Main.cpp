#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <SFML/Graphics.hpp>

#include "GameSystem.h"

//Screen Size
unsigned int WINDOW_WIDTH = 1280;
unsigned int WINDOW_HEIGHT = 680;

//Map size
int MAP_WIDTH = 160;
int MAP_HEIGHT = 160;

//Farm size
int NUMBER_ANTS = 2;
int AMOUNT_FOOD_IN_NEST = 0;

//Attributes
int AMOUND_OF_FOOD_NEEDED_FOR_NEW_ANT = 150;
float EVAPORATION_OF_PHEROMONES = 0.25;

//Forward declarations
void processInput(sf::Window &window, GameSystem &world);

int main()
{
	//Creates the world
	GameSystem world(NUMBER_ANTS, AMOUNT_FOOD_IN_NEST, MAP_WIDTH, MAP_HEIGHT, AMOUND_OF_FOOD_NEEDED_FOR_NEW_ANT, EVAPORATION_OF_PHEROMONES);

	//Initilizing the window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ant Simulation");



	//Loops the game
	while (window.isOpen())
	{

		//Process the Input
		processInput(window, world);

		//Processes the level
		world.processWorld();

		//Printing the world
		window.clear();
		world.printWorld(window);
		window.display();
	}
}

void processInput(sf::Window &window, GameSystem &world)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			// window closed
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::MouseButtonReleased:
		{
			sf::Vector2i position = sf::Mouse::getPosition(window);
			std::cout << "X-Positon is: " << position.x << " " << "Y-Position is: " << position.y << std::endl;
			break;
		}

		// key pressed
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Left:
				world.setControlerPosition('a');
				break;
			case sf::Keyboard::Right:
				world.setControlerPosition('d');
				break;
			case sf::Keyboard::Up:
				world.setControlerPosition('w');
				break;
			case sf::Keyboard::Down:
				world.setControlerPosition('s');
				break;
			default:
				break;
			}
			break;
			// we don't process other types of events
		default:
			break;
		}
	}
}