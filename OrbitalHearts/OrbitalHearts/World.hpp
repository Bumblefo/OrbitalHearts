#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include "GameMap.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "WindowManager.hpp"

#define NUM_ENTITIES_DEFAULT 10

class World
{
public:
	//Constructor/Destructor
	~World();
	World(int numEntities = NUM_ENTITIES_DEFAULT);

	//Queries
	Player& getPlayer() { return *_player; };
	GameMap& getGameMap() { return *_gameMap; };
	Entity** getEntities() { return _entities; };

	//Commands
	void update(float deltaTime);
	void draw();
	
private:
	GameMap* _gameMap;

	Player* _player;

	Entity** _entities;
	int _numEntities = 0;
	int _numActiveEntities = 0;
};

World::~World()
{
	delete _gameMap;
	delete _player;

	for (int i = 0; i < _numEntities; i++)
	{
		delete _entities[i];
	}

	delete[] _entities;
}

World::World(int numEntities)
	: _numEntities{numEntities}
{
	_gameMap = new GameMap();
	_player = new Player(sf::Vector2f(100.f, 100.f));
	_entities = new Entity*[_numEntities];
}

void World::update(float deltaTime)
{
	_player->update(deltaTime);

	WindowManager::instance().setWindowCenter(_player->getBody().getPosition());
	
	for (int i = 0; i < _numActiveEntities; i++)
	{
		_entities[i]->update(deltaTime);
	}
}

void World::draw()
{
	_gameMap->draw();
	
	_player->draw();

	for (int i = 0; i < _numActiveEntities; i++)
	{
		_entities[i]->draw();
	}
}


#endif //WORLD_HPP