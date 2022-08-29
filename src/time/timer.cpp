//
// Created by 刘科 on 2022/8/29.
//

#include "timer.h"
#include <thread>
#include <chrono>

namespace plan9
{
    class Timer::TimerImpl {
    public:
        TimerImpl() {

        }
        void SetInterval(int ms) {
            interval_ = ms;
        }
        void SetTimerCallback(std::function<void()> callback) {
            callback_ = std::move(callback);
        }
        void Start() {
            active = true;
            thread = std::make_shared<std::thread>([=]() {
                if(!active.load()) return;
                std::this_thread::sleep_for(std::chrono::milliseconds(interval_));
                if(!active.load()) return;
                RunCallback();
            });
            thread->detach();
        }
        void Stop() {
            active = false;
        }

    private:
        int interval_{1000};
        std::function<void()> callback_{nullptr};
        std::atomic<bool> active{true};
        std::shared_ptr<std::thread> thread;

    private:
        void RunCallback() {
            if (callback_) {
                callback_();
            }
        }
    };

    Timer::Timer() {
        impl_ = std::make_shared<plan9::Timer::TimerImpl>();
    }

    void Timer::SetInterval(int ms) {
        impl_->SetInterval(ms);
    }

    void Timer::SetTimerCallback(std::function<void()> callback) {
        impl_->SetTimerCallback(std::move(callback));
    }

    void Timer::Start() {
        impl_->Start();
    }

    void Timer::Stop() {
        impl_->Stop();
    }
}