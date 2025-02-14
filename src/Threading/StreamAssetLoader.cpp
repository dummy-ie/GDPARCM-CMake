#include "StreamAssetLoader.h"
#include <iostream>
#include <random>

#include "../Controller/Singleton/TextureManager.h"
#include "../Utility/StringUtils.h"
#include "IExecutionEvent.h"

using namespace gd;

StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* executionEvent)
{
	this->path = path;
	this->execEvent = executionEvent;
}

StreamAssetLoader::~StreamAssetLoader()
{
	std::cout << "Destroying stream asset loader. " << std::endl;
}

void StreamAssetLoader::run()
{
	std::cout << "Running stream asset loader " << std::endl;
	//simulate loading of very large file
	// std::random_device seeder;
	// std::mt19937 engine(seeder());
	// std::uniform_int_distribution<int> dist(100, 1000);
	IETThread::sleep(1000);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];

	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;

	this->execEvent->onFinishedExecution();
	//delete after being done
	delete this;
}
