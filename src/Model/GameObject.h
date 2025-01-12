#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/System/Time.hpp"


namespace gd
{
	class GameObject
	{
	public:
		GameObject() = default;
		virtual ~GameObject() = default;

		// Disable copy operators
		GameObject(const GameObject&) = delete;
		GameObject(GameObject&&) = delete;
		GameObject& operator=(const GameObject&) = delete;
		GameObject& operator=(GameObject&&) = delete;

	public:
		virtual void update(const sf::Time deltaTime) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const = 0;
	};
}
