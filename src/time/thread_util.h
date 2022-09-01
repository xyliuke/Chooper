//
// Created by liuke on 2022/8/31.
//

#ifndef USOPP_THREAD_UTIL_H
#define USOPP_THREAD_UTIL_H

#include <functional>

namespace plan9
{
    void MainThreadRunLoop();
    void PostOnMainThread(std::function<void()> task);
    bool IsMainThread();
    void PostIdleTaskOnMainThread(std::function<void()> task);
}



#endif //USOPP_THREAD_UTIL_H
