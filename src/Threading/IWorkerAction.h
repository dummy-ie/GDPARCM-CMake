#pragma once
namespace gd
{
	class IWorkerAction
	{
	public:
		virtual void onStartTask() = 0;
	};
}

