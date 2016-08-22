#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "WindowManager.hpp"

class Entity
{
public:
	//Constructors/Destructor
	~Entity() {};
	Entity() {};

	//Queries
	const sf::Sprite& getSprite() const { return _sprite; };

	//Commands
	virtual void update(float deltaTime) = 0;
	virtual void draw();
	virtual void attemptMove(float deltaTime) = 0;

protected:
	virtual void move(float deltaX, float deltaY) { _sprite.move(deltaX, deltaY); };

	sf::Sprite _sprite;

};

void Entity::draw()
{
	WindowManager::instance().getWindow().draw(_sprite);
}

#endif //ENTITY_HPP