#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../Utility/FileUtility.h"

namespace gd
{
	class Application
	{
	public:
		Application();
		~Application() = default;

		void execute();

		// Disable copy operators
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;

	private:
		sf::RenderWindow window;
		

		void render();
		void pollEvents();
		void update(sf::Time deltaTime);
	};
}