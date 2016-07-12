#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>



void updateGame(sf::Time deltaTime)
{

}

void endGame(sf::Window& window)
{
	//save data here

	window.close();
}

//consider multithreading with a seperate thread for rendering

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Orbital Hearts", sf::Style::Default);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();

		updateGame(deltaTime);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				endGame(window);
		}

		window.clear(); // Required. Draw everything after
		
		window.draw(shape);
		
		window.display(); // Required
	}

	return 0;
}