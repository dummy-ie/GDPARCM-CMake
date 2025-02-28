#pragma once

#include "GameObject.h"

#include <iostream>
#include "../Config/Settings.h"
#include "../Utility/FileUtils.h"
#include "../Controller/Singleton/TextureManager.h"

namespace gd
{
	class IconObject final : public GameObject
	{
	public:
		explicit IconObject(int textureIndex);
		void update(const sf::Time deltaTime) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void setPosition(sf::Vector2f position) const;
		void setScale(sf::Vector2f scale) const;

	private:
		int textureIndex = 0;
		sf::Sprite* sprite;

		friend class TextureDisplay;
	};
}

