#include <fstream>
#include <iostream>
#include <filesystem>
#include "TextureManager.h"
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
	this->countStreamingAssets();
}

void TextureManager::loadFromAssetList()
{
	LogUtils::log(this, "Reading from asset list");
	std::ifstream stream(FileUtils::getFileFromSourceFolder("Assets/assets.txt"));
	String path;

	while (std::getline(stream, path))
	{
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		this->instantiateAsTexture(path, assetName, false);
		LogUtils::log(this, "Loaded texture: " + assetName);
	}
}

void TextureManager::loadSingleStreamAsset(const int index)
{
	int fileNum = 0;

	for (const auto& entry : std::filesystem::directory_iterator(streamingPath)) {
		if (index == fileNum)
		{
			//simulate loading of very large file
			IETThread::sleep(200);

			//<code here for loading asset>
			const String path = entry.path().generic_string();
			std::vector<String> tokens = StringUtils::split(path, '/');
			String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
			instantiateAsTexture(path, assetName, true);

			LogUtils::log(this, "Loaded streaming texture: " + assetName);
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

sf::Texture* TextureManager::getStreamTextureFromList(const int index) const
{
	return this->streamTextureList[index];
}

int TextureManager::getNumLoadedStreamTextures() const
{
	return this->streamTextureList.size();
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
