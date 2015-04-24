#include <queue>

class Game;

typedef void(*CallbackFunc)(Game*);

Scheduler theScheduler;

class Scheduler{
private:
	Scheduler();
	struct Task {
		CallbackFunc callback;
		int start = 0;
		int interval;
		bool operator <(Task const& t){
			return (interval - (theScheduler.currentTick%interval))
				- (t.interval - (theScheduler.currentTick%t.interval));
		}
	};
	struct TempTask :public Task{
		int calls;
	};
	std::priority_queue<Task> permaCallbacks;
	std::priority_queue<TempTask> callbacks;
	int currentTick = 0;
public:
	void tick(Game *game);
	void subscribe(CallbackFunc func, int interval, int calls);
	void subscribePermanently(CallbackFunc func, int interval);
};

