#pragma once
#include "IETThread.h"
#include "IExecutionEvent.h"
class IExecutionEvent;
namespace gd
{
	class StreamAssetLoader : public IETThread
	{
	private:
		typedef std::string String;
	public:
		StreamAssetLoader(String path, IExecutionEvent* executionEvent);
		~StreamAssetLoader();

	private:
		void run() override;

		String path;
		IExecutionEvent* execEvent;
	};
}

