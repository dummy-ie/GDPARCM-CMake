#pragma once

#include <SFML/Graphics.hpp>

#include "../Config/Settings.h"
#include "../Utility/FileUtils.h"

#include "GameObject.h"

namespace gd
{
	class FPSCounter final : public GameObject
	{
	public:
		FPSCounter();

		void update(const sf::Time deltaTime) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Font fpsCounterFont = sf::Font(FileUtils::getFileFromAssetsFolder("Futura Condensed.ttf"));
		sf::Text fpsCounter = fpsCounterFont;

		sf::Clock updateClock;
		float updateRateSeconds = 0.5f;
	};
}