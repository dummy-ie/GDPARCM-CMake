#pragma once

#include <iostream>

#include "../Config/Settings.h"
#include "../Utility/LogUtils.h"
#include "../Utility/FileUtils.h"

#include "../Controller/Singleton/GameObjectManager.h"
#include "../Controller/Singleton/TextureManager.h"
#include "IconObject.h"
#include "GameObject.h"
#include "../Threading/IExecutionEvent.h"
#include "SFML/Audio/Music.hpp"

namespace gd
{
	class IconObject;
	/// <summary>
	/// Class that deals with displaying of streamed textures
	/// </summary>
	class TextureDisplay final : public GameObject, public IExecutionEvent
	{
	public:
		TextureDisplay();

		void startLoading();
		void update(const sf::Time deltaTime) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Music music;

		typedef std::vector<IconObject*> IconList;
		IconList iconList;

		enum class StreamingType : uint8_t
		{
			BATCH_LOAD = 0,
			SINGLE_STREAM = 1
		};

		const float FRAME_RATE = 29.97f; 
		const StreamingType streamingType = StreamingType::SINGLE_STREAM;
		float ticks = 0.0f;
		bool startedStreaming = false;

		int numDisplayed = 0;
		int displayIdx = 0;
		bool isDoneDisplaying = false;
		bool isDoneLoading = false;

		void spawnObject();

	public:
		void onFinishedExecution() override;
	};
}
