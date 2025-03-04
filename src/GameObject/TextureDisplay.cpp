#include "TextureDisplay.h"

#include "../Threading/BaseAssetLoader.h"

using namespace gd;

TextureDisplay::TextureDisplay() : GameObject("TextureDisplay")
{
	music = sf::Music(FileUtils::getFileFromAssetsFolder("Fus Ro Dah Audio.mp3"));
	//music.setLooping(true);

	//updateClock.start();
	iconList.reserve(1457);
	loadInClock.reset();
}

void TextureDisplay::startLoading()
{
	BaseAssetLoader* loader = new BaseAssetLoader(this);
	loader->start();
}

void TextureDisplay::update(const sf::Time deltaTime)
{
	if (!isDoneLoading)
		return;

	if (loadInClock.getElapsedTime().asSeconds() <= 5.f)
		return;

	if (this->numDisplayed == 1)
	{
		music.play();
	}

	this->ticks += FixedDeltaTime.asMilliseconds();
	if (this->streamingType == StreamingType::BATCH_LOAD && !this->startedStreaming && this->ticks > this->FRAME_RATE)
	{

	}
	else if (this->streamingType == StreamingType::SINGLE_STREAM && this->ticks > this->FRAME_RATE)
	{
		this->ticks = 0.0f;

		if (displayIdx + 1 == TextureManager::getInstance()->getNumLoadedBaseTextures())
		{
			isDoneDisplaying = true;

			if (prev)
			{
				const auto prevA = prev->sprite->getColor().a;
				prev->sprite->setColor(sf::Color(255, 255, 255, MathUtils::interpolateTowards(prevA, 0, 100.f * deltaTime.asSeconds())));
			}
		}

		if (!isDoneDisplaying)
		{
			spawnObject();
		}
		this->numDisplayed++;
	}
}

void TextureDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//icons draw themselves
	for (const auto icon : iconList)
	{
		icon->draw(target, sf::RenderStates::Default);
	}
}

void TextureDisplay::spawnObject()
{
	if (prev)
		prev->sprite->setColor(sf::Color::Transparent);

	//String objectName = "Icon_" + std::to_string(this->iconList.size());
	int idx = displayIdx;

	IconObject* iconObj = new IconObject(idx);
	this->iconList.push_back(iconObj);

	//set position
	constexpr float scale = 2.f;
	constexpr int imgWidth = 640;
	constexpr int imgHeight = 352;
	float x = WindowWidth / 2.f - (imgWidth * scale) / 2.f;
	float y = WindowHeight / 2.f - (imgHeight * scale) / 2.f;
	iconObj->sprite->setColor(sf::Color(255, 255, 255, alpha));
	iconObj->setPosition({ x, y });
	iconObj->setScale({ scale, scale });

	prev = iconObj;

	if (alpha < 255)
		alpha += 2;
	else
		alpha = 255;

	displayIdx++;
}

void TextureDisplay::onFinishedExecution()
{
	loadingScreen->finishLoading();
	isDoneLoading = true;
	loadInClock.start();
}
