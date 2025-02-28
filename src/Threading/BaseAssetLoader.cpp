#include "BaseAssetLoader.h"

#include "../Controller/Singleton/TextureManager.h"

gd::BaseAssetLoader::BaseAssetLoader(IExecutionEvent* executionEvent)
{
	execEvent = executionEvent;
}

void gd::BaseAssetLoader::run()
{
	TextureManager::getInstance()->loadFromAssetList(execEvent);
}
