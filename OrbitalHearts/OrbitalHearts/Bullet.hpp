#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include "Projectile.hpp"

class Bullet : public Projectile
{
public:
	//Constructors/Destructors
	~Bullet();
	Bullet(sf::Vector2f position, sf::Vector2f target_direction, sf::Texture& texture);

	//Queries
	//bool checkCollision(sf::FloatRect obj_bounds) const;

	//Commands
	void update(float deltaTime) override;
	void attemptMove(float deltaTime) override;

	bool operator==(const Bullet& bullet) const;
	Bullet& operator=(const Bullet& bullet);

private:
	float speed = 800;
};





Bullet::~Bullet()
{}

Bullet::Bullet(sf::Vector2f position, sf::Vector2f target_direction, sf::Texture& texture)
	: Projectile{ position, target_direction, texture}
{
}

void Bullet::update(float deltaTime)
{
	attemptMove(deltaTime);
}

void Bullet::attemptMove(float deltaTime)
{
	move(getTargetDirection().x * deltaTime * speed, getTargetDirection().y * deltaTime * speed);
}

bool Bullet::operator==(const Bullet& other) const
{
	if (speed != other.speed || targetDirection != other.targetDirection || sprite.getPosition() != other.sprite.getPosition())
		return false;
	return true;
}

Bullet& Bullet::operator=(const Bullet& other)
{
	if (other == *this)
		return *this;

	speed = other.speed;
	targetDirection = other.targetDirection;
	sprite = other.sprite;

	return *this;
}

#endif // BULLET_HPP