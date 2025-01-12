#include "Application.h"

#include <iostream>

#include "../Config/Settings.h"
#include "../Model/FPSCounter.h"
#include "Singleton/GameObjectManager.h"

using namespace gd;

Application::Application()
{
	window = sf::RenderWindow(
		sf::VideoMode({WindowWidth, WindowHeight}), "[LEOCARIO] GDPARCM");

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);

	window.setFramerateLimit(FramerateCap);
}

void Application::execute()
{
	const sf::Clock clock = sf::Clock::Clock();
	sf::Time previousDeltaTime = sf::Time::Zero;

	while (this->window.isOpen())
	{
		const sf::Time currentDeltaTime = clock.getElapsedTime();
		const sf::Time deltaTime = currentDeltaTime - previousDeltaTime;

		window.clear();

		pollEvents();
		update(deltaTime);

		render();

		window.display();

		previousDeltaTime = currentDeltaTime;
	}
}

void Application::render()
{
	GameObjectManager::getInstance()->drawAllObjects(&window);
}

void Application::pollEvents()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
	}
}

void Application::update(const sf::Time deltaTime)
{
	GameObjectManager::getInstance()->updateAllObjects(deltaTime);
}
