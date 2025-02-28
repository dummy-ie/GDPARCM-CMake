#pragma once

#include <unordered_map>
#include "SFML/Graphics.hpp"

#include "../../Utility/LogUtils.h"
#include "../../Utility/FileUtils.h"
#include "../../Threading/IETThread.h"
#include "../../Threading/IExecutionEvent.h"
#include "../../Threading/StreamAssetLoader.h"
#include "../../Threading/ThreadPool.h"

namespace gd
{
	class TextureManager
	{
	public:
		typedef std::string String;
		typedef std::vector<sf::Texture*> TextureList;
		typedef std::unordered_map<String, TextureList> HashTable;

		TextureManager();
		~TextureManager();

		// Disable copy operators
		TextureManager(const TextureManager&) = delete;
		TextureManager(TextureManager&&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;
		TextureManager& operator=(TextureManager&&) = delete;

		static TextureManager* getInstance();
		void loadFromAssetList(IExecutionEvent* executionEvent); //loading of all assets needed for startup
		void loadSingleStreamAsset(int index, IExecutionEvent* executionEvent); //loads a single streaming asset based on index in directory
		sf::Texture* getFromTextureMap(const String& assetName, int frameIndex);
		int getNumFrames(const String& assetName);

		sf::Texture* getBaseTextureFromList(int index) const;
		int getNumLoadedBaseTextures() const;

		sf::Texture* getStreamTextureFromList(const int index) const;
		int getNumLoadedStreamTextures() const;

		sf::Texture* getBackgroundTextureFromList(int index) const;
		int getNumLoadedBackgroundTextures() const;

		sf::Texture* getHighlightTextureFromList(int index) const;
		int getNumLoadedHighlightTextures() const;

		sf::Texture* getSmokeTextureFromList(int index) const;
		int getNumLoadedSmokeTextures() const;

		void instantiateAsTexture(const String& path, const String& assetName, bool isStreaming);

		void loadLoadingScreenTextures();

	private:
		static TextureManager* sharedInstance;

		ThreadPool* threadPool;
		HashTable textureMap;

		// Tex Lists
		TextureList backgroundList;
		TextureList highlightList;
		TextureList smokeList;
		TextureList baseTextureList;
		TextureList streamTextureList;

		const std::filesystem::path streamingPath = FileUtils::getFileFromAssetsFolder("StreamingFullRes/");
		const std::filesystem::path backgroundImagesPath = FileUtils::getFileFromAssetsFolder("Loading Screen Background Images/");
		const std::filesystem::path highlightImagesPath = FileUtils::getFileFromAssetsFolder("Loading Screen Highlight Images/");
		const std::filesystem::path smokeImagesPath = FileUtils::getFileFromAssetsFolder("Smoke Effects/");
		int streamingAssetCount = 0;
		int baseAssetCount = 0;

		void countStreamingAssets();
		void instantiateTextureToList(const String& path, const String& assetName, TextureList& list);
	};
}
