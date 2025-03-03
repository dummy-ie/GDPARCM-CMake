#include "GameObjectManager.h"

#include "../../Utility/LogUtils.h"

using namespace gd;

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager::~GameObjectManager()
{
	for (const GameObject* gameObject : gameObjectList)
	{
		delete gameObject;
	}

	gameObjectList.clear();
}

GameObjectManager* GameObjectManager::getInstance()
{
	if (sharedInstance == nullptr)
		sharedInstance = new GameObjectManager();

	return sharedInstance;
}

std::vector<GameObject*> GameObjectManager::getGameObjectList()
{
	return gameObjectList;
}

void GameObjectManager::addObject(GameObject* gameObject)
{
	gameObjectList.push_back(gameObject);
}

void GameObjectManager::removeObject(GameObject* gameObject)
{
	if (const auto it = std::ranges::find(gameObjectList, gameObject); it != gameObjectList.end())
	{
		delete* it;
		gameObjectList.erase(it);
	}
}

void GameObjectManager::drawAllObjects(sf::RenderWindow* window) const
{
	for (const GameObject* gameObject : gameObjectList)
	{
		gameObject->draw(*window);
	}
}

void GameObjectManager::updateAllObjects(const sf::Time deltaTime) const
{
	for (GameObject* gameObject : gameObjectList)
	{
		//LogUtils::log(this, "updating: " + gameObject->getName());
		gameObject->update(deltaTime);
	}
}
