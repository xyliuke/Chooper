//
// Created by 刘科 on 2022/8/29.
//

#ifndef USOPP_TIMER_H
#define USOPP_TIMER_H

#include <memory>
#include <functional>

namespace plan9
{
    class Timer {
    public:
        Timer();
        void SetInterval(int ms);
        void SetTimerCallback(std::function<void()> callback);
        void Start();
        void Stop();
    private:
        class TimerImpl;
        std::shared_ptr<TimerImpl> impl_;
    };
}



#endif //USOPP_TIMER_H
