#pragma once
#include "IETThread.h"
#include "IExecutionEvent.h"
#include "IWorkerAction.h"
class IExecutionEvent;
namespace gd
{
	class BaseAssetLoader : public IETThread
	{
	private:
		typedef std::string String;
	public:
		BaseAssetLoader(IExecutionEvent* executionEvent);
		//virtual ~BaseAssetLoader() override = default;

	private:

		String path;
		IExecutionEvent* execEvent;

		// Inherited via IETThread
		void run() override;
	};
}

#pragma once
