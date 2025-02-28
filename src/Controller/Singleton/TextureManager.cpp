#include <fstream>
#include <iostream>
#include <filesystem>
#include "TextureManager.h"

#include <random>

#include "../../Threading/IExecutionEvent.h"
#include "../../Utility/StringUtils.h"

using namespace gd;

//a singleton class
TextureManager* TextureManager::sharedInstance = nullptr;

TextureManager* TextureManager::getInstance() {
	if (sharedInstance == nullptr) {
		//initialize
		sharedInstance = new TextureManager();
	}

	return sharedInstance;
}

TextureManager::TextureManager()
{
	// this->countStreamingAssets();
	// this->threadPool = new ThreadPool("TextureManagerPool", 12);
	// this->threadPool->startScheduler();
}

TextureManager::~TextureManager()
{
	delete threadPool;
}

void TextureManager::loadFromAssetList(IExecutionEvent* executionEvent)
{
	LogUtils::log(this, "Reading from asset list");

	for (const auto& entry : std::filesystem::directory_iterator(streamingPath))
	{
		// Artificial delay
		//IETThread::sleep(1000);

		std::vector<String> tokens = StringUtils::split(entry.path().generic_string(), '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		this->instantiateAsTexture(entry.path().generic_string(), assetName, false);
		LogUtils::log(this, "Loaded texture: " + assetName);
		baseAssetCount++;
	}

	executionEvent->onFinishedExecution();
	LogUtils::log("Loaded number of base textures: " + std::to_string(getNumLoadedBaseTextures()));
}

void TextureManager::loadSingleStreamAsset(const int index, IExecutionEvent* executionEvent)
{
	int fileNum = 0;

	for (const auto& entry : std::filesystem::directory_iterator(streamingPath)) {
		if (index == fileNum)
		{
			//simulate loading of very large file
			// std::random_device seeder;
			// std::mt19937 engine(seeder());
			// std::uniform_int_distribution<int> dist(200, 600);
			// IETThread::sleep(dist(engine));

			//<code here for loading asset>
			const String path = entry.path().generic_string();
			std::vector<String> tokens = StringUtils::split(path, '/');
			String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
			// instantiateAsTexture(path, assetName, true);

			StreamAssetLoader* assetLoader = new StreamAssetLoader(path, executionEvent);
			this->threadPool->scheduleTask(assetLoader);


			// StreamAssetLoader* assetLoader = new StreamAssetLoader(path, executionEvent);
			// assetLoader->start();

			//LogUtils::log(this, "Loaded streaming texture: " + assetName);
			break;
		}

		fileNum++;
	}
}

sf::Texture* TextureManager::getFromTextureMap(const String& assetName, const int frameIndex)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName][frameIndex];
	}
	else {
		LogUtils::log(this, "No texture found for " + assetName);
		return nullptr;
	}
}

int TextureManager::getNumFrames(const String& assetName)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName].size();
	}
	else {
		LogUtils::log(this, "No texture found for " + assetName);
		return 0;
	}
}

sf::Texture* TextureManager::getBaseTextureFromList(const int index) const
{
	return this->baseTextureList[index];
}

int TextureManager::getNumLoadedBaseTextures() const
{
	return baseAssetCount;
}

sf::Texture* TextureManager::getStreamTextureFromList(const int index) const
{
	return this->streamTextureList[index];
}

int TextureManager::getNumLoadedStreamTextures() const
{
	return this->streamTextureList.size();
}

sf::Texture* TextureManager::getBackgroundTextureFromList(int index) const
{
	return backgroundList[index];
}

int TextureManager::getNumLoadedBackgroundTextures() const
{
	return backgroundList.size();
}

sf::Texture* TextureManager::getHighlightTextureFromList(int index) const
{
	return highlightList[index];
}

int TextureManager::getNumLoadedHighlightTextures() const
{
	return highlightList.size();
}

sf::Texture* TextureManager::getSmokeTextureFromList(int index) const
{
	return smokeList[index];
}

int TextureManager::getNumLoadedSmokeTextures() const
{
	return smokeList.size();
}

void TextureManager::countStreamingAssets()
{
	this->streamingAssetCount = 0;
	for (const auto& entry : std::filesystem::directory_iterator(streamingPath)) {
		//instantiateAsTexture(entry.path().string(), std::to_string(streamingAssetCount), true);
		//LogUtils::log(this, "Loaded in stream asset: " + std::to_string(this->streamingAssetCount));
		this->streamingAssetCount++;
	}

	LogUtils::log(this, "Number of streaming assets: " + std::to_string(this->streamingAssetCount));
}

void TextureManager::instantiateTextureToList(const String& path, const String& assetName, TextureList& list)
{
	sf::Texture* texture = new sf::Texture();
	LogUtils::logBool(this, texture->loadFromFile(FileUtils::getFileFromAssetsFolder(path)));
	this->textureMap[assetName].push_back(texture);

	list.push_back(texture);

}

void TextureManager::instantiateAsTexture(const String& path, const String& assetName, const bool isStreaming)
{
	sf::Texture* texture = new sf::Texture();
	LogUtils::logBool(this, texture->loadFromFile(FileUtils::getFileFromAssetsFolder(path)));
	this->textureMap[assetName].push_back(texture);

	if (isStreaming)
	{
		this->streamTextureList.push_back(texture);
	}
	else
	{
		this->baseTextureList.push_back(texture);
	}

}

void TextureManager::loadLoadingScreenTextures()
{
	for (const auto& entry : std::filesystem::directory_iterator(backgroundImagesPath))
	{
		std::vector<String> tokens = StringUtils::split(entry.path().generic_string(), '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		instantiateTextureToList(entry.path().generic_string(), assetName, backgroundList);
		LogUtils::log(this, "Loaded texture: " + assetName);
	}

	for (const auto& entry : std::filesystem::directory_iterator(highlightImagesPath))
	{
		std::vector<String> tokens = StringUtils::split(entry.path().generic_string(), '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		instantiateTextureToList(entry.path().generic_string(), assetName, highlightList);
		LogUtils::log(this, "Loaded texture: " + assetName);
	}

	for (const auto& entry : std::filesystem::directory_iterator(smokeImagesPath))
	{
		std::vector<String> tokens = StringUtils::split(entry.path().generic_string(), '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		instantiateTextureToList(entry.path().generic_string(), assetName, smokeList);
		LogUtils::log(this, "Loaded texture: " + assetName);
		LogUtils::log(this, "Smoke list size: " + std::to_string(smokeList.size()));
	}

	auto levelDisplayPath = FileUtils::getFileFromAssetsFolder("Level Display.png");
	sf::Texture* texture = new sf::Texture();
	LogUtils::logBool(this, texture->loadFromFile(levelDisplayPath));
	this->textureMap["Level Display"].push_back(texture);

}
