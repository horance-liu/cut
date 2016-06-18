#ifndef H441EB5A0_2E97_4187_AA21_FAB5C70470C0
#define H441EB5A0_2E97_4187_AA21_FAB5C70470C0

#include "ccinfra/base/BaseTypes.h"
#include <ccinfra/sched/Synchronization.h>
#include <condition_variable>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <future>
#include <functional>
#include <memory>

CCINFRA_NS_BEGIN

struct Executor
{
    Executor(size_t);
    ~Executor();

    template<class F, class... Args>
    auto execute(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using ReturnType = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared< std::packaged_task<ReturnType()> >(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

        std::future<ReturnType> res = task->get_future();

        SYNCHRONIZED(tasksMutex)
        {
            tasks.emplace([task](){ (*task)(); });
        }
        condition.notify_one();

        return res;
    }

private:
    void threadRun();

private:
    std::vector< std::thread > workers;
    std::queue< std::function<void()> > tasks;

    std::mutex tasksMutex;
    std::condition_variable condition;
    bool stop;
};

CCINFRA_NS_END

#endif
