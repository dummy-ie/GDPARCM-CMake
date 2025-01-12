#include "ScrollingBackground.h"

using namespace gd;

ScrollingBackground::ScrollingBackground() : GameObject("ScrollingBackground")
{
	//LogUtils::log("Declared as " + this->getName());

	//assign texture
	this->sprite = sf::Sprite(*texture);
	texture->setRepeated(true);
	sf::Vector2u textureSize = this->sprite.getTexture().getSize();
	//make BG height x k to emulate repeating BG.
	this->sprite.setTextureRect(sf::IntRect({ 0, 0 }, { WindowWidth, WindowHeight * 8 }));
	sprite.setPosition({ 0, -WindowHeight * 7 });
}

void ScrollingBackground::update(const sf::Time deltaTime)
{
	sf::Vector2f position = sprite.getPosition();
	position.y += speed * deltaTime.asSeconds();
	sprite.setPosition(position);

	if (const sf::Vector2f localPos = this->sprite.getPosition(); localPos.y * deltaTime.asSeconds() > 0) {
		//reset position
		sprite.setPosition({ 0, -WindowHeight * 7 });
	}
}

void ScrollingBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}
