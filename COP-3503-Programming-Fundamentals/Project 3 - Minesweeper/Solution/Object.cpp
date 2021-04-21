#include "Object.h"

Object::Object(const char *imageName)
{
	texture.loadFromFile(imageName);
	sprite.setTexture(texture);
}

const sf::Sprite &Object::GetSprite() const
{
	return sprite;
}

void Object::SetPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

Projectile::Projectile(const char *imageName, sf::Vector2f dir, float spd) : Object(imageName)
{
	direction = dir;
	speed = spd;
}




