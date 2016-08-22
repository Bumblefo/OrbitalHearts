#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define BLOCK_SPRITESHEET_ROWLENGTH 10

enum BlockType { blank = 0, bomb, wall1, wall2=10};
static const int BLOCK_SIZE = 16;

class Block
{
	/*
	A sprite(with transform) with a BlockType associated with it
	*/
public:
	~Block() {};
	Block(sf::Vector2f position, sf::Texture& texture, BlockType type);

	sf::Sprite& getSprite() { return _sprite; };
	BlockType getType() { return _type; };

protected:
	sf::Sprite _sprite;
	BlockType _type;
};





sf::IntRect getSpriteSheetTextureRect(BlockType type)
{
	return sf::IntRect(type % BLOCK_SPRITESHEET_ROWLENGTH, type % 100, BLOCK_SIZE, BLOCK_SIZE);
}

Block::Block(sf::Vector2f position, sf::Texture& texture, BlockType type = blank)
	: _type{ type }
{
	_sprite.setTexture(texture);
	_sprite.setTextureRect(getSpriteSheetTextureRect(type));
	_sprite.setOrigin(BLOCK_SIZE / 2, BLOCK_SIZE / 2);
	_sprite.setPosition(position);
}



#endif // BLOCK_HPP