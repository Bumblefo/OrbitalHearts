#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameMap.hpp"
#include "World.hpp"
#include "WindowManager.hpp"

void updateGame(World& world, float deltaTime)
{
	world.update(deltaTime);
}

void drawGame(World& world)
{
	WindowManager::instance().getWindow().clear();
	world.draw();
	WindowManager::instance().getWindow().display();
}

void endGame()
{
	//save data here
	WindowManager::instance().getWindow().close();
}

void handleInputs(World& world)
{
	sf::Event event;
	while (WindowManager::instance().getWindow().pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			endGame();
			break;
		case sf::Event::MouseButtonPressed:
			break;
		case sf::Event::MouseButtonReleased:
			break;
		default:
			break;
		}
	}
}

//consider multithreading with a seperate thread for rendering

void gameLoop(World& world)
{
	sf::Clock clock;

	while (WindowManager::instance().getWindow().isOpen())
	{
		sf::Time deltaTime = clock.restart();
		handleInputs(world);
		updateGame(world, deltaTime.asSeconds());
		//physics
		//ai
		drawGame(world);

	}
}

//Mouse information
//sf::Vector2i mouseWorldCoords = sf::Mouse::getPosition(window);
//std::cout << "(" << mouseWorldCoords.x << ", " << mouseWorldCoords.y << ")" << std::endl;

int main()
{
	WindowManager::instance();
	
	World world = World();
	
	gameLoop(world);

	return 0;
}