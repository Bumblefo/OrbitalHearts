#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "WindowManager.hpp"
#include <iostream>
#include <fstream>

class TextureLoadError {};

class GameMap
{
/*
A GameMap(room in the game) is a container of a 2D-array of a grid of blocks. Each block can be checked for collision detection.

Saving/Loading:
Maps can be loaded and saved to a file. This file contains the layout of the grid of blocks as well as precalculated collision detection.
	ex) a row of collidable blocks will be interpreted as 1 single rectangle for unit collision to make calculations faster
*/

public:
	//Constructors/Destructors
	GameMap(int numRows = 100, int numCols = 100, std::string bgTextureFileName = "", std::string blockTextureFileName = "roguelikeCity_transparent.png");

	//Queries
	int getRows() { return rows; };
	int getCols() { return cols; };

	//Commands
	void update(float deltaTime);
	void draw();
	bool checkBlockCollision(sf::FloatRect obj_bounds);	//Checks an entity's collision with all collidable blocks

	void loadFromFile(std::string filename);
	void saveToFile(std::string filename);

	void initGrid();

private:
	int rows;
	int cols;

	std::vector<std::vector<Block>> grid;
	sf::Texture blockTexture;

	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
};





void loadTexture(sf::Texture& texture, std::string& textureFileName)
{
	if (!texture.loadFromFile(textureFileName))
	{
		throw TextureLoadError();
	}
}

void loadSprite(sf::Sprite& sprite, sf::Texture& texture, std::string textureFileName, bool setOriginCenter = true)
{
	loadTexture(texture, textureFileName);
	sprite.setTexture(texture);

	if (setOriginCenter)
	{
		sf::Vector2u textureSize = texture.getSize();
		sprite.setOrigin(textureSize.x, textureSize.y);
	}
}

GameMap::GameMap(int numRows, int numCols, std::string bgTextureFileName, std::string blockTextureFileName)
	: rows{ numRows }, cols{numCols}
{
	rows = numRows;
	cols = numCols;


	std::cout << "Start loading textures" << std::endl;
	//loadTexture(backgroundTexture, bgTextureFileName);
	loadTexture(blockTexture, "Textures/" + blockTextureFileName);
	std::cout << "Finished loading textures" << std::endl;

	initGrid();
}

void GameMap::update(float deltaTime)
{
}

void GameMap::draw()
{
	WindowManager::instance().getWindow().draw(backgroundSprite);

	for (size_t i = 0; i < grid.size(); i++)	//draw all blocks
	{
		for (size_t j = 0; j < grid[i].size(); j++)
		{
			WindowManager::instance().getWindow().draw(grid[i][j].getSprite());
		}
	}
}

bool GameMap::checkBlockCollision(sf::FloatRect obj_bounds)
{
	//CLEARLY WRONG
	return false;
}

void GameMap::loadFromFile(std::string filename)
{
	BlockType type = blank;
	for (int i = 0; i < rows; i++)
	{
		switch (i)
		{
		case 0:
			type = blank;
			break;
		case 1:
			type = bomb;
			break;
		case 8:
			type = wall1;
			break;
		case 9:
			type = wall2;
			break;
		}

		for (int j = 0; j < cols; j++)
		{
			grid[i][j] = Block(sf::Vector2f(i, j), blockTexture, type);
		}
	}
}

void GameMap::saveToFile(std::string filename)
{
	std::ofstream file;
	file.open(filename);
	for (int i = 0; i < rows; i++)
	{
		file << grid[i][0].getType();
		for (int j = 1; j < cols; j++)
		{
			file << "," << grid[i][j].getType();
		}
		file << std::endl;
	}
}

//Helper Functions

void GameMap::initGrid()
{
	//temporary
	for (int i = 0; i < rows; i++)
	{
		grid.push_back(std::vector<Block>());
		for (int j = 0; j < cols; j++)
		{
			grid[i].push_back(Block(sf::Vector2f(i * BLOCK_SIZE, j * BLOCK_SIZE), blockTexture, blank));
		}
	}
}


#endif // GAMEMAP_HPP