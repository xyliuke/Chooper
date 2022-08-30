//
// Created by 刘科 on 2022/8/29.
//

#include "timer.h"
#include <thread>
#include <chrono>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>

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

        }
        void Stop() {

        }

    private:
        int interval_{1000};
        std::function<void()> callback_{nullptr};
        std::atomic<bool> active{true};
        std::shared_ptr<std::thread> thread;
        std::shared_ptr<boost::asio::io_service> io_service_;
        std::shared_ptr<boost::asio::deadline_timer> timer_;

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