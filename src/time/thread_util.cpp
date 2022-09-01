//
// Created by liuke on 2022/8/31.
//

#include "thread_util.h"
#include <vector>
#include <mutex>
#include <iostream>
#include <thread>
#include <boost/assert.hpp>

namespace plan9
{
    static std::__thread_id main_thread_id;
    static std::atomic<bool> is_set_main_thread = {false};
    static std::vector<std::function<void()>> tasks;
    static std::mutex mutex;

    class ThreadUtilImpl {
    public:
        ThreadUtilImpl() {
            main_thread_id = std::this_thread::get_id();
            is_set_main_thread = true;
        }
    };
    static ThreadUtilImpl impl;//定义静态变量是为了在main函数调用之前，能够设置主线程的id

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
        BOOST_ASSERT_MSG(is_set_main_thread, "请首先调用ThreadUtil::SetMainThreadID方法");
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