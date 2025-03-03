#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.h"

namespace gd
{
	class SmokeParticle : public GameObject
	{
	public:
		SmokeParticle(sf::Vector2f spawningDirection);
		void update(const sf::Time deltaTime) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void start();
		bool isAlive = false;

	private:
		void fadeOut(const sf::Time deltaTime);
		void fadeIn(const sf::Time deltaTime);

		sf::Sprite smokeSprite;

		bool isFadingIn = true;
		float alpha = 0;

		sf::Vector2f spawningDirection;
		float rotationSpeed;
		float moveSpeed;

		sf::Clock lifeClock;
		float lifetime;

	};
}
