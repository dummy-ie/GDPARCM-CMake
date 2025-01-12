#pragma once

#include <SFML/Graphics.hpp>
#include "../Config/Settings.h"
#include "../Controller/Singleton/TextureManager.h"

#include "GameObject.h"

namespace gd
{
	class ScrollingBackground final : public GameObject
	{
	public:
		ScrollingBackground();

		// Inherited via GameObject
		void update(const sf::Time deltaTime) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Desert", 0);
		sf::Sprite sprite = sf::Sprite(*texture);

		float speed = 100.f;

	};
}