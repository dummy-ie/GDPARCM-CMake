#pragma once

#include <unordered_map>
#include "SFML/Graphics.hpp"

#include "../../Utility/LogUtils.h"
#include "../../Utility/FileUtils.h"
#include "../../Threading/IETThread.h"
#include "../../Threading/IExecutionEvent.h"
#include "../../Threading/StreamAssetLoader.h"

namespace gd
{
	class TextureManager
	{
	public:
		typedef std::string String;
		typedef std::vector<sf::Texture*> TextureList;
		typedef std::unordered_map<String, TextureList> HashTable;

		TextureManager();
		~TextureManager() = default;

		// Disable copy operators
		TextureManager(const TextureManager&) = delete;
		TextureManager(TextureManager&&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;
		TextureManager& operator=(TextureManager&&) = delete;

		static TextureManager* getInstance();
		void loadFromAssetList(); //loading of all assets needed for startup
		void loadSingleStreamAsset(int index, IExecutionEvent* executionEvent); //loads a single streaming asset based on index in directory
		sf::Texture* getFromTextureMap(const String& assetName, int frameIndex);
		int getNumFrames(const String& assetName);

		sf::Texture* getStreamTextureFromList(const int index) const;
		int getNumLoadedStreamTextures() const;

		void instantiateAsTexture(const String& path, const String& assetName, bool isStreaming);

	private:
		static TextureManager* sharedInstance;

		HashTable textureMap;
		TextureList baseTextureList;
		TextureList streamTextureList;

		const std::filesystem::path streamingPath = FileUtils::getFileFromAssetsFolder("Streaming/");
		int streamingAssetCount = 0;

		void countStreamingAssets();

	};
}
