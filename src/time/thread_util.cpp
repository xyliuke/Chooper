//
// Created by liuke on 2022/8/31.
//

#include "thread_util.h"
#include <vector>
#include <mutex>
#include <chrono>
#include <thread>
#include <boost/assert.hpp>

namespace plan9
{
    static std::__thread_id main_thread_id;
    static std::atomic<bool> is_set_main_thread = {false};
    static std::vector<std::function<void()>> tasks;
    static std::vector<std::function<void()>> idle_tasks;
    static std::mutex mutex;
    static std::mutex idle_mutex;

    class ThreadUtilImpl {
    public:
        ThreadUtilImpl() {
            main_thread_id = std::this_thread::get_id();
            is_set_main_thread = true;
        }
    };
    static ThreadUtilImpl impl;//定义静态变量是为了在main函数调用之前，能够设置主线程的id

    //返回值为函数执行消耗的时间，单位为微秒，1毫秒=1000微秒
    long MainThreadRunLoopTask() {
        mutex.lock();
        bool empty = tasks.empty();
        mutex.unlock();
        if (empty) {
            return -1;
        }

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        mutex.lock();
        auto task = tasks.front();
        tasks.erase(tasks.begin());
        mutex.unlock();
        task();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        return (end - start).count() / 1000;
    }

    void RunIdleTask() {
        idle_mutex.lock();
        if (idle_tasks.empty()) {
            idle_mutex.unlock();
            return;
        }
        auto task = idle_tasks.front();
        idle_tasks.erase(idle_tasks.begin());
        idle_mutex.unlock();
        task();
    }

    void MainThreadRunLoop() {
        long total = 0;
        while (true) {
            long cost = MainThreadRunLoopTask();
            if (cost < 0) {
                //已经没有任务,可以执行idle任务
                if (total == 0) {
                    RunIdleTask();
                }
                break;
            }
            total += cost;
            if (total > 3000) {
                break;
            }
        }
    }

    void PostOnMainThread(std::function<void()> task) {
        BOOST_ASSERT_MSG(is_set_main_thread, "请首先调用ThreadUtil::SetMainThreadID方法");
        if (IsMainThread()) {
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

    bool IsMainThread() {
        return (std::this_thread::get_id() == main_thread_id);
    }

    void PostIdleTaskOnMainThread(std::function<void()> task) {
        idle_mutex.lock();
        idle_tasks.push_back(std::move(task));
        idle_mutex.unlock();
    }
}