//
// Created by liuke on 2022/8/31.
//

#include "thread_util.h"
#include <vector>
#include <mutex>

namespace plan9
{
    static std::vector<std::function<void()>> tasks;
    static std::mutex mutex;
    void ThreadUtil::MainThreadRunLoop() {
        if (tasks.empty()) {
            return;
        }
        mutex.lock();
        auto task = tasks.front();
        tasks.erase(tasks.begin());
        mutex.unlock();
        task();
    }

    void ThreadUtil::PostOnMainThread(std::function<void()> task) {
        mutex.lock();
        tasks.push_back(std::move(task));
        mutex.unlock();
    }
}