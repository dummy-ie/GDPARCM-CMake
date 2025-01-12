#include "FPSCounter.h"

using namespace gd;

FPSCounter::FPSCounter() : GameObject("FPSCounter")
{
	fpsCounter.setCharacterSize(60);
	fpsCounter.setStyle(sf::Text::Bold);
	fpsCounter.setFillColor(sf::Color::White);
	fpsCounter.setOutlineColor(sf::Color::Black);
	fpsCounter.setOutlineThickness(2.f);
	fpsCounter.setPosition(sf::Vector2f(WindowWidth - 250.f, WindowHeight - 100.f));

	updateClock.start();
}

void FPSCounter::update(const sf::Time deltaTime)
{
	if (updateClock.getElapsedTime().asSeconds() < updateRateSeconds)
		return;

	const float fps = 1.f / deltaTime.asSeconds();
	//std::cout << floor(fps) << "\n";

	fpsCounter.setString("FPS: " + std::to_string(static_cast<int>(fps)));
	updateClock.restart();
}

void FPSCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(fpsCounter);
}