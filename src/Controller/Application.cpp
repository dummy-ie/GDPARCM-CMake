#include "Application.h"

#include "../GameObject/LoadingScreen.h"

using namespace gd;

Application* Application::sharedInstance = nullptr;

Application::Application()
{
	window = sf::RenderWindow(
		sf::VideoMode({ WindowWidth, WindowHeight }),
		"[LEOCARIO] GDPARCM",
		sf::Style::Default,
		sf::State::Windowed
	);

	// ScrollingBackground* scrollingBackground = new ScrollingBackground();
	// GameObjectManager::getInstance()->addObject(scrollingBackground);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);

	TextureManager::getInstance()->loadLoadingScreenTextures();

	LoadingScreen* loadingScreen = new LoadingScreen();
	GameObjectManager::getInstance()->addObject(loadingScreen);

	TextureDisplay* textureDisplay = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(textureDisplay);

	textureDisplay->loadingScreen = loadingScreen;
	textureDisplay->startLoading();

	window.setFramerateLimit(FramerateCap);
}

Application* Application::getInstance()
{
	if (sharedInstance == nullptr) {
		//initialize
		sharedInstance = new Application();
	}

	return sharedInstance;
}

const sf::RenderWindow& Application::getWindow()
{
	return window;
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
