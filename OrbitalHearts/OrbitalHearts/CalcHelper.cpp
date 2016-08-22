#include "CalcHelper.hpp"

sf::Vector2f toUnitVector(sf::Vector2f vector)
{
	float magnitude = sqrtf(powf(vector.x, 2) + powf(vector.y, 2));
	return sf::Vector2f(vector.x / magnitude, vector.y / magnitude);
}
