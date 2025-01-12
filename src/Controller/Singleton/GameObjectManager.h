#pragma once

#include <vector>
#include "../../Model/GameObject.h"
#include "SFML/Graphics/RenderWindow.hpp"

namespace gd
{
	class GameObjectManager
	{
	public:
		GameObjectManager() = default;
		~GameObjectManager();

		// Disable copy operators
		GameObjectManager(const GameObjectManager&) = delete;
		GameObjectManager(GameObjectManager&&) = delete;
		GameObjectManager& operator=(const GameObjectManager&) = delete;
		GameObjectManager& operator=(GameObjectManager&&) = delete;

		static GameObjectManager* getInstance();
		std::vector<GameObject*> getGameObjectList();
		void addObject(GameObject* gameObject);

		void drawAllObjects(sf::RenderWindow* window) const;
		void updateAllObjects(const sf::Time deltaTime) const;

	private:
		static GameObjectManager* sharedInstance;
		std::vector<GameObject*> gameObjectList;
	};
}
