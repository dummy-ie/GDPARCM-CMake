#pragma once
#include "IETThread.h"
#include "IExecutionEvent.h"
#include "IWorkerAction.h"
class IExecutionEvent;
namespace gd
{
	class StreamAssetLoader : public IWorkerAction
	{
	private:
		typedef std::string String;
	public:
		StreamAssetLoader(String path, IExecutionEvent* executionEvent);
		virtual ~StreamAssetLoader();

	private:
		void onStartTask() override;

		String path;
		IExecutionEvent* execEvent;
	};
}

