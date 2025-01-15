#include "TextureDisplay.h"

using namespace gd;

TextureDisplay::TextureDisplay() : GameObject("TextureDisplay")
{
	updateClock.start();
}

void TextureDisplay::update(const sf::Time deltaTime)
{
	//this->ticks += FixedDeltaTime.asMilliseconds();

	//<code here for spawning icon object periodically>
	if (updateClock.getElapsedTime().asSeconds() < updateRateSeconds
		|| iconList.size() == 480
		)
		return;

	spawnObject();
	
	updateClock.restart();
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
	TextureManager::getInstance()->loadSingleStreamAsset(this->iconList.size());

	IconObject* iconObj = new IconObject(this->iconList.size());
	this->iconList.push_back(iconObj);

	//set position
	constexpr int imgWidth = 68;
	constexpr int imgHeight = 68;
	float x = this->columnGrid * imgWidth;
	float y = this->rowGrid * imgHeight;
	iconObj->setPosition({ x, y });

	//LogUtils::log( this, "Set position: " + std::to_string(x) + " " + std::to_string(y));

	this->columnGrid++;
	if (this->columnGrid == this->maxColumn)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}

	//GameObjectManager::getInstance()->addObject(iconObj);
	//LogUtils::log( this, "Added IconObject, iconList size: " + std::to_string(iconList.size()));
}
