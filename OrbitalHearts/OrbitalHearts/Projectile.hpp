#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include "CalcHelper.hpp"

/*
A projectile is an entity with a direction in which it moves unless told otherwise.
*/

class Projectile abstract
{
public:
	//Constructor/Destructor
	~Projectile();
	Projectile(sf::Vector2f position, sf::Vector2f target_direction, sf::Texture texture);

	//Queries
	virtual bool checkCollision(sf::FloatRect obj_bounds) const;
	sf::Sprite getSprite() { return sprite; };
	sf::Vector2f getTargetDirection() { return targetDirection; };

	//Commands
	virtual void update(float deltaTime) = 0;
	void setDirection(sf::Vector2f new_direction);
	virtual void attemptMove(float deltaTime) = 0;
	virtual void move(float deltaX, float deltaY);

protected:
	sf::Sprite sprite;
	sf::Vector2f targetDirection;
};






Projectile::~Projectile()
{
}

Projectile::Projectile(sf::Vector2f position, sf::Vector2f target_direction, sf::Texture texture)
	: targetDirection{ toUnitVector(target_direction) }
{
	sprite.setPosition(position);
	sprite.setTexture(texture);
}

bool Projectile::checkCollision(sf::FloatRect obj_bounds) const
{
	if (sprite.getGlobalBounds().intersects(obj_bounds))
	{
		return true;
	}
	return false;
}

void Projectile::setDirection(sf::Vector2f new_direction)
{
	targetDirection = new_direction;
}

void Projectile::move(float deltaX, float deltaY)
{
	sprite.move(deltaX, deltaY);
}


#endif // PROJECTILE_HPP