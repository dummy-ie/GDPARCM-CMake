#include "TextureDisplay.h"

#include "../Threading/BaseAssetLoader.h"

using namespace gd;

TextureDisplay::TextureDisplay() : GameObject("TextureDisplay")
{
	music = sf::Music(FileUtils::getFileFromAssetsFolder("Fus Ro Dah Audio.mp3"));
	//music.setLooping(true);

	//updateClock.start();
	iconList.reserve(1457);
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

	if (this->numDisplayed == 1)
	{
		music.play();
	}

	this->ticks += FixedDeltaTime.asMilliseconds();
	if (this->streamingType == StreamingType::BATCH_LOAD && !this->startedStreaming && this->ticks > this->FRAME_RATE)
	{
		// this->startedStreaming = true;
		// this->ticks = 0.0f;
		// TextureManager::getInstance()->loadStreamingAssets();
	}
	else if (this->streamingType == StreamingType::SINGLE_STREAM && this->ticks > this->FRAME_RATE)
	{
		this->ticks = 0.0f;

		if (displayIdx + 1 == TextureManager::getInstance()->getNumLoadedBaseTextures())
		{
			displayIdx = 0;
			isDoneDisplaying = true;
			for (IconObject* iconObject : this->iconList)
			{
				iconObject->sprite->setColor(sf::Color(255, 255, 255, 0));
			}
		}

		if (!isDoneDisplaying)
			spawnObject();
		// else
		// 	this->iconList.at(displayIdx)->sprite->setColor(sf::Color::White);

		//TextureManager::getInstance()->loadSingleStreamAsset(this->numDisplayed, this);
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
	iconObj->setPosition({ x, y });
	iconObj->setScale({ scale, scale });

	//LogUtils::log( this, "Set position: " + std::to_string(x) + " " + std::to_string(y));

	// this->columnGrid++;
	// if (this->columnGrid == this->maxColumn)
	// {
	// 	this->columnGrid = 0;
	// 	this->rowGrid++;
	// }

	//GameObjectManager::getInstance()->addObject(iconObj);
	//LogUtils::log( this, "Added IconObject, iconList size: " + std::to_string(iconList.size()));
	displayIdx++;
}

void TextureDisplay::onFinishedExecution()
{
	isDoneLoading = true;
}
