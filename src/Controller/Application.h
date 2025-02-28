#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../Config/Settings.h"

#include "Singleton/TextureManager.h"
#include "Singleton/GameObjectManager.h"

#include "../GameObject/ScrollingBackground.h"
#include "../GameObject/TextureDisplay.h"
#include "../GameObject/FPSCounter.h"

namespace gd
{
	class Application
	{
	public:
		Application();
		~Application() = default;

		static Application* getInstance();
		const sf::RenderWindow& getWindow();
		void execute();

		// Disable copy operators
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;

	private:
		static Application* sharedInstance;

		sf::RenderWindow window;

		void render();
		void pollEvents();
		void update(sf::Time deltaTime);
	};
}