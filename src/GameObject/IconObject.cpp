#include "IconObject.h"

using namespace gd;

IconObject::IconObject(const int textureIndex) : GameObject("IconObject " + std::to_string(textureIndex))
{
	this->textureIndex = textureIndex;

	//assign texture
	const sf::Texture* texture = TextureManager::getInstance()->getBaseTextureFromList(this->textureIndex);
	sprite = new sf::Sprite(*texture);
	sprite->setTexture(*texture);
}

void IconObject::update(const sf::Time deltaTime)
{
}

void IconObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite);
}

void IconObject::setPosition(const sf::Vector2f position) const
{
	sprite->setPosition(position);
}

void IconObject::setScale(const sf::Vector2f scale) const
{
	sprite->setScale(scale);
}

