#include "SmokeParticle.h"

#include "../Config/Settings.h"
#include "../Controller/Singleton/GameObjectManager.h"
#include "../Controller/Singleton/TextureManager.h"
#include "../Utility/MathUtils.h"
#include "../Utility/RandomUtils.h"

gd::SmokeParticle::SmokeParticle(const sf::Vector2f spawningDirection) :
	GameObject("SmokeParticle"),
	smokeSprite(sf::Sprite(*TextureManager::getInstance()->getSmokeTextureFromList(RandomUtils::random(0, 1)))),
	spawningDirection(spawningDirection),
	rotationSpeed(RandomUtils::random(-60.f, 60.f)),
	moveSpeed(RandomUtils::random(-100.f, 100.f)),
	lifetime(RandomUtils::random(5.f, 10.f))
{
	//smokeSprite.setColor(sf::Color(255, 255, 255, 0));
	smokeSprite.setScale(RandomUtils::randomVector2(0.5f, 1.5f));
	//smokeSprite.setPosition({WindowWidth / 2.f, 10.f});
	smokeSprite.setOrigin(smokeSprite.getLocalBounds().size / 2.f);
	smokeSprite.setPosition({ RandomUtils::random(0.f, static_cast<float>(WindowWidth)), WindowHeight });
}

void gd::SmokeParticle::update(const sf::Time deltaTime)
{
	if (!isAlive)
		return;

	if (lifeClock.getElapsedTime().asSeconds() >= lifetime)
	{
		fadeOut(deltaTime);
	}

	if (isFadingIn)
	{
		fadeIn(deltaTime);
	}

	smokeSprite.move(spawningDirection * moveSpeed * deltaTime.asSeconds());
	smokeSprite.rotate(sf::degrees(rotationSpeed * deltaTime.asSeconds()));
}

void gd::SmokeParticle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!isAlive)
		return;

	target.draw(smokeSprite);
}

void gd::SmokeParticle::start()
{
	alpha = RandomUtils::random(20, 60);
	//alpha = 255;
	smokeSprite.setColor(sf::Color(255, 255, 255, 0));
	smokeSprite.setScale(RandomUtils::randomVector2(0.5f, 1.5f));
	smokeSprite.setPosition({ RandomUtils::random(0.f, static_cast<float>(WindowWidth)), WindowHeight });

	rotationSpeed = RandomUtils::random(-60, 60);
	moveSpeed = RandomUtils::random(1, 100);
	lifetime = RandomUtils::random(5.f, 10.f);

	isFadingIn = true;
	isAlive = true;
}

void gd::SmokeParticle::fadeOut(const sf::Time deltaTime)
{
	const float a = smokeSprite.getColor().a;

	smokeSprite.setColor(sf::Color(255, 255, 255, MathUtils::interpolateTowards(a, 0, deltaTime.asSeconds())));

	if (a <= 0)
	{
		LogUtils::log("Disabling smoke");
		isAlive = false;
		lifeClock.reset();
	}
}

void gd::SmokeParticle::fadeIn(const sf::Time deltaTime)
{
	const float a = smokeSprite.getColor().a;

	smokeSprite.setColor(sf::Color(255, 255, 255, MathUtils::interpolateTowards(a, alpha, 100 * deltaTime.asSeconds())));

	if (a >= alpha)
	{
		isFadingIn = false;
		LogUtils::log("Enabling smoke");
		lifeClock.start();
	}
}
