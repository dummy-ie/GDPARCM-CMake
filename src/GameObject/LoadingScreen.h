#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "../Utility/FileUtils.h"
#include "../Utility/MathUtils.h"

namespace gd
{
	class LoadingScreen : public GameObject
	{
	public:
		LoadingScreen();

		// Inherited via GameObject
		void update(const sf::Time deltaTime) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void finishLoading();

	private:
		void fadeAssetsOut(sf::Time deltaTime);
		void fadeAssetsIn(sf::Time deltaTime);
		void setAssetsTransparent();

		void moveSmoke(sf::Time deltaTime);

		void randomizeSprites();
		void interpSprites(sf::Time deltaTime);

		void randomizeTips();
		void splitTipsText();

		std::vector<sf::Sprite> highlights;
		std::vector<sf::Sprite> backgrounds;
		std::vector<sf::Sprite> smoke;
		sf::Sprite level;

		sf::Font font = sf::Font(FileUtils::getFileFromAssetsFolder("Futura Condensed.ttf"));
		std::vector<sf::Text> tipLines;

		int highlightIdx = 0;
		int backgroundIdx = 0;
		int tipsIdx = 0;

		sf::Clock transitionTimer;
		float transitionInterval = 5.f;

		const float fadeRate = 100.f;
		bool isFadingOut = false;
		bool isFadingIn = true;

		bool isFinishedLoading = false;

		std::string tipsText[5] =
		{
			"Daedric princes are god-like beings that inhabit the plane of Oblivion. Most are considered evil, forcing their worshippers to build their shrines far from civilized places.",
			"Agents of the high elven Aldmeri Dominion are known as Thalmor. They maintain an embassy in Skyrim, and have been known to secretly capture and imprison any Nords who question their doctrines or beliefs.",
			"When the High King dies, the Jarls of Skyrim convene a Moot to elect a new High King.",
			"Tiber Septim brought peace to Tamriel in 2E 896, by conquering all of the known world. Thus began the Third Era.",
			"The College of Winterhold is an independent organization, and thus was not affected by the dissolution of the Mages Guild at the beginning of the Fourth Era.",

		};
	};
}
