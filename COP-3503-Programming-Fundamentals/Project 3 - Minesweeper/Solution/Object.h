#pragma once
#include <SFML/Graphics.hpp>

class Object
{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Object(const char *imageName);
	const sf::Sprite &GetSprite() const;
	void SetPosition(float x, float y);
};

class Projectile : public Object
{
	sf::Vector2f direction;
	float speed;
public:
	Projectile(const char *imageName, sf::Vector2f dir, float spd);
	void Update();
};

