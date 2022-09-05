//
// Created by 刘科 on 2022/8/29.
//

#include "timer.h"
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
namespace plan9
{
    class Timer::TimerImpl {
    public:
        TimerImpl() {
            timer_ = std::make_shared<boost::asio::steady_timer>(io_service_, boost::asio::chrono::microseconds (interval_));
            strand_ = std::make_shared<boost::asio::strand<boost::asio::io_context::executor_type>>(boost::asio::make_strand(io_service_));
        }
        void SetInterval(int ms) {
            interval_ = ms;
        }
        void SetTimerCallback(std::function<void()> callback) {
            callback_ = std::move(callback);
//            timer_->async_wait(std::bind(&Timer::TimerImpl::RunCallback, this));
            timer_->async_wait(boost::asio::bind_executor(*strand_,
                                                          boost::bind(&Timer::TimerImpl::RunCallback, this)));
        }
        void Start() {
            timer_ = std::make_shared<boost::asio::steady_timer>(io_service_, boost::asio::chrono::milliseconds (interval_));
            thread_ = std::make_shared<boost::thread>(boost::bind(&boost::asio::io_context::run, &io_service_));
            thread_->detach();
        }
        void Stop() {
            io_service_.stop();
        }

    private:
        int interval_{1000};
        std::function<void()> callback_{nullptr};
        boost::asio::io_context io_service_;
        std::shared_ptr<boost::asio::steady_timer> timer_;
        std::shared_ptr<boost::asio::strand<boost::asio::io_context::executor_type>> strand_;
        std::shared_ptr<boost::thread> thread_;
    private:
        void RunCallback() {
            if (callback_) {
                callback_();
            }
            timer_->expires_at(timer_->expiry() + boost::asio::chrono::milliseconds(interval_));
            timer_->async_wait(std::bind(&Timer::TimerImpl::RunCallback, this));
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