#pragma once

#include <iostream>

#include "../Config/Settings.h"
#include "../Utility/LogUtils.h"
#include "../Utility/FileUtils.h"

#include "../Controller/Singleton/GameObjectManager.h"
#include "../Controller/Singleton/TextureManager.h"
#include "IconObject.h"
#include "GameObject.h"

namespace gd
{
	class IconObject;
	/// <summary>
	/// Class that deals with displaying of streamed textures
	/// </summary>
	class TextureDisplay final : public GameObject
	{
	public:
		TextureDisplay();

		void update(const sf::Time deltaTime) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		typedef std::vector<IconObject*> IconList;
		IconList iconList;

		enum class StreamingType : uint8_t
		{
			BATCH_LOAD = 0,
			SINGLE_STREAM = 1
		};

		const float streamingLoadDelay = 4000.0f;
		const StreamingType streamingType = StreamingType::SINGLE_STREAM;
		//float ticks = 0.0f;
		bool startedStreaming = false;

		int columnGrid = 0; int rowGrid = 0;

		const int maxColumn = 28;
		const int maxRow = 22;

		sf::Clock updateClock;
		float updateRateSeconds = .25f;

		void spawnObject();
	};
}
