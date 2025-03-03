#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

#include "SmokeParticle.h"
#include "../Utility/FileUtils.h"
#include "../Utility/MathUtils.h"
#include "SFML/Audio/Music.hpp"

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

		void randomizeSprites();
		void interpSprites(sf::Time deltaTime);

		void randomizeTips();
		void splitTipsText();

		void spawnSmoke();

		std::vector<sf::Sprite> highlights;
		std::vector<sf::Sprite> backgrounds;
		std::vector<SmokeParticle*> smoke;
		sf::Sprite level;

		sf::Font font = sf::Font(FileUtils::getFileFromAssetsFolder("Futura Condensed.ttf"));
		std::vector<sf::Text> tipLines;

		int highlightIdx = 0;
		int backgroundIdx = 0;
		int tipsIdx = 0;

		sf::Music music;

		sf::Clock smokeClock;
		float smokeInterval = 0.f;

		sf::Clock transitionClock;
		float transitionInterval = 5.f;

		const float fadeRate = 100.f;
		bool isFadingOut = false;
		bool isFadingIn = true;

		bool isFinishedLoading = false;

		std::string tipsText[16] =
		{
			"Daedric princes are god-like beings that inhabit the plane of Oblivion. Most are considered evil, forcing their worshippers to build their shrines far from civilized places.",
			"Agents of the high elven Aldmeri Dominion are known as Thalmor. They maintain an embassy in Skyrim, and have been known to secretly capture and imprison any Nords who question their doctrines or beliefs.",
			"When the High King dies, the Jarls of Skyrim convene a Moot to elect a new High King.",
			"Tiber Septim brought peace to Tamriel in 2E 896, by conquering all of the known world. Thus began the Third Era.",
			"The College of Winterhold is an independent organization, and thus was not affected by the dissolution of the Mages Guild at the beginning of the Fourth Era.",
			"Magicka is the energy used to power spells. The higher the magicka, the more spells that can be cast.",
			"Potions that restore Stamina or Magicka should be used during combat, to increase the number of available spells and power attacks.",
			"Moving while holding down Attack results in a power attack. Moving in different directions creates different power attacks.",
			"Serving jail time causes some skills to lose their accumulated progress to the next value. The longer the sentence, the more skills that are affected.",
			"The charge level of a staff is based on the corresponding skill of the mage wielding it. For example, a wizard with a high Destruction skill would get a lot of uses from a staff of Fireball.",
			"In addition to doing regular damage, Frost attacks deplete the target's Stamina, and slow them down. Use them to prevent enemies from doing as many power attacks.",
			"Once a skill reaches 100, you can make it legendary. The skill is reset to 15, and all perks are converted to perk points. Making a skill legendary allows you to level your character almost indefinitely.",
			"The School of Destruction focuses on the mastery of fire, frost and shock, and is used to cast spells like Fireball, Ice Spike, and Lightning Bolt.",
			"An Arcane Enchanter can be used to learn new enchantments from weapons and armor, but any item experimented on is destroyed in the process.",
			"Imperials are natives of Cyrodiil, the cosmopolitan heartland of the Empire. Once a day, they can use the Voice of the Emperor ability to calm an angry opponent for a short while.",
			"You can only have one Standing Stone active at a time. If you accept the bonus from a new one, it replaces any bonuses from the previously used Stone."
		};
	};
}
