#include "ccinfra/sched/Executor.h"
#include "ccinfra/algo/loop.h"

CCINFRA_NS_BEGIN

Executor::Executor(size_t threadNum) : stop(false)
{
    FOR_EACH_0(i, threadNum)
    {
        workers.emplace_back([this]{ threadRun(); });
    }
}

Executor::~Executor()
 {
     SYNCHRONIZED(tasksMutex)
     {
         stop = true;
     }
     condition.notify_all();

     for(std::thread &worker : workers)
     {
         worker.join();
     }
 }

void Executor::threadRun()
{
    ALWAYS_LOOP()
    {
        std::function<void()> task;

        SYNCHRONIZED(tasksMutex)
        {
            this->condition.wait(LOCKER(tasksMutex).getLocker(),
                [this]{ return this->stop || !this->tasks.empty(); });

            if(this->stop && this->tasks.empty()) return;
            task = std::move(this->tasks.front());
            this->tasks.pop();
        }

        task();
    }
}

CCINFRA_NS_END
