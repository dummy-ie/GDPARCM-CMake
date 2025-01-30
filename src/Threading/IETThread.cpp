#include "IETThread.h"

using namespace gd;

IETThread::IETThread()
= default;

IETThread::~IETThread()
= default;

void IETThread::start()
{
	std::thread(&IETThread::run, this).detach(); //detach thread for independent execution. without this, join() function must be called.
}

void IETThread::sleep(const int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
