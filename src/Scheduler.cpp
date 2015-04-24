#include "Scheduler.h"


void Scheduler::tick(Game *theGame)
{
	std::vector<Task *> permaTasks;
	while ((currentTick - permaCallbacks.top().start) % permaCallbacks.top().interval == 0)
	{
		Task *task = &permaCallbacks.top();
		permaTasks.push_back(task);
		task->callback(theGame);
		permaCallbacks.pop();
	}
	currentTick++;
	//TODO make this work
}

void Scheduler::subscribe(CallbackFunc func, int interval, int calls)
{

}

void Scheduler::subscribePermanently(CallbackFunc func, int interval)
{

}