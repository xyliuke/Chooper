//
// Created by liuke on 2022/8/31.
//

#include "thread_util.h"
#include <vector>
#include <mutex>
#include <iostream>
#include <thread>

namespace plan9
{
    static std::vector<std::function<void()>> tasks;
    static std::mutex mutex;
    static std::__thread_id main_thread_id;
    void ThreadUtil::MainThreadRunLoop() {
        main_thread_id = std::this_thread::get_id();
        if (tasks.empty()) {
            return;
        }
        std::cout << "main queue size " << tasks.size() << std::endl;
        mutex.lock();
        auto task = tasks.front();
        tasks.erase(tasks.begin());
        mutex.unlock();
        task();
    }

    void ThreadUtil::PostOnMainThread(std::function<void()> task) {
        if (ThreadUtil::IsMainThread()) {
            //是主线程，直接执行
            if (task) {
                task();
            }
            return;
        }
        mutex.lock();
        tasks.push_back(std::move(task));
        mutex.unlock();
    }

    bool ThreadUtil::IsMainThread() {
        return (std::this_thread::get_id() == main_thread_id);
    }
}