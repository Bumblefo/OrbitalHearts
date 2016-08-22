#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.hpp"
#include "CalcHelper.hpp"
#include "Entity.hpp"
#include "WindowManager.hpp"

class WeaponError {};

#define UP -1
#define DOWN 1
#define LEFT -1
#define RIGHT 1

class Player : public Entity
{
public:
	//Constructor/Destructor
	~Player();
	Player();
	Player(sf::Vector2f position);

	//Queries
	const sf::CircleShape& getBody() const { return body; };

	//Commands
	virtual void update(float deltaTime) override;
	virtual void draw() override;
	void handleInputs();

	void attemptMove(float deltaTime);
	virtual void shoot(float deltaTime, sf::Vector2f target_pos);

protected:
	enum Weapon { bullet, missile };

	void fireBullet(sf::Vector2f target_position);
	void fireMissile(sf::Vector2f target_position);

	void updateChildren(float deltaTime);
	void updateProjectiles(float deltaTime);

	void move(float deltaX, float deltaY) override { body.move(deltaX, deltaY); };

	sf::CircleShape body;	//delete once actual sprite drawn
	float moveSpeed = 500;
	Weapon equippedWeapon;
	
	std::vector<Bullet> bullets;
	//EntityPool<Bullet> bullets;

	sf::Vector2f cursor_pos;	

	//Keyboard bindings
	sf::Keyboard::Key upKey;
	sf::Keyboard::Key downKey;
	sf::Keyboard::Key leftKey;
	sf::Keyboard::Key rightKey;

	sf::Keyboard::Key shootKey;
};







Player::~Player()
{
}

Player::Player()
	: body(sf::CircleShape(8)), upKey{ sf::Keyboard::Up }, downKey{ sf::Keyboard::Down },
	leftKey{ sf::Keyboard::Left }, rightKey{ sf::Keyboard::Right }
{
	body.setFillColor(sf::Color(179, 130, 196));
	body.setOutlineThickness(-5);
	body.setOutlineColor(sf::Color(158, 98, 179));
	body.setOrigin(15.f, 15.f);
	body.setPosition(0, 0);
}

Player::Player(sf::Vector2f position)
	:body(sf::CircleShape(30)), upKey{ sf::Keyboard::Up }, downKey{ sf::Keyboard::Down },
	leftKey{ sf::Keyboard::Left }, rightKey{ sf::Keyboard::Right }
{
	body.setFillColor(sf::Color(179, 130, 196));
	body.setOutlineThickness(-5);
	body.setOutlineColor(sf::Color(158, 98, 179));
	body.setOrigin(15.f, 15.f);
	body.setPosition(position);
}

void Player::update(float deltaTime)
{
	attemptMove(deltaTime);
	shoot(deltaTime, cursor_pos);
	updateChildren(deltaTime);
}

void Player::updateChildren(float deltaTime)
{
	updateProjectiles(deltaTime);
}

void Player::updateProjectiles(float deltaTime)
{
	sf::FloatRect windowBounds = WindowManager::instance().getWindowBounds();
	for (auto i = bullets.begin(); i != bullets.end(); i++)
	{
		if (!i->getSprite().getGlobalBounds().intersects(windowBounds))
			bullets.erase(i);
		else
			i->update(deltaTime);
	}
}

void Player::draw()
{
	WindowManager::instance().getWindow().draw(body);

	/*for (Bullet& bullet: bullets)
	{
		window.draw(bullet.getSprite());
	}*/
}

void Player::attemptMove(float deltaTime)
{
	sf::Vector2f old_position = body.getPosition();
	sf::FloatRect windowBounds = WindowManager::instance().getWindowBounds();
	sf::FloatRect bounds = body.getGlobalBounds();
	
	int moveX = (sf::Keyboard::isKeyPressed(leftKey) ? LEFT : 0) + (sf::Keyboard::isKeyPressed(rightKey) ? RIGHT : 0);
	float deltaX = moveX * moveSpeed * deltaTime;
	if ((moveX == LEFT && bounds.left + deltaX < windowBounds.left) || 
		(moveX == RIGHT && bounds.left + bounds.width + deltaX > windowBounds.left + windowBounds.width))
	{
		deltaX = 0;
	}

	int moveY = (sf::Keyboard::isKeyPressed(upKey) ? UP : 0) + (sf::Keyboard::isKeyPressed(downKey) ? DOWN : 0);
	float deltaY = moveY * moveSpeed * deltaTime;
	if ((moveY == UP && bounds.top + deltaY < windowBounds.top) ||
		(moveY == DOWN && bounds.top + bounds.height + deltaY > windowBounds.top + windowBounds.height))
	{
		deltaY = 0;
	}

	move(deltaX, deltaY);
}

void Player::fireBullet(sf::Vector2f target_position)
{
	//fire bullet towards cursor

}

void Player::fireMissile(sf::Vector2f target_position)
{

}

void Player::shoot(float deltaTime, sf::Vector2f target_position)
{
	if (sf::Keyboard::isKeyPressed(shootKey))
	{
		switch (equippedWeapon)
		{
		case bullet:
			fireBullet(target_position);
			break;
		case missile:
			fireMissile(target_position);
			break;
		default:
			throw WeaponError();
			break;
		}
	}
}


#endif // PLAYER_HPP