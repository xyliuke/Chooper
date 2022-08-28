//
// Created by 刘科 on 2022/8/28.
//

#ifndef USOPP_IPLAYER_H
#define USOPP_IPLAYER_H

#include <memory>
#include <functional>

namespace plan9
{
    class IPlayer {
    public:
        /**
         * 设置本地播放文件路径
         * @param path 本地视频文件路径
         */
        virtual void SetFile(const std::string &path) = 0;
        /**
         * 播放
         */
        virtual void Play() = 0;
        /**
         * 暂停
         */
        virtual void Pause() = 0;
        /**
         * 停止播放
         */
        virtual void Stop() = 0;
        /**
         * 跳转到指定时间，单位为毫秒
         * @param ms 指定时间
         */
        virtual void Seek(int ms) = 0;

        /**
         * 播放进度回调，回调参数为当前播放时间和总时间
         * @param callback
         */
        virtual void SetProcessCallback(std::function<void(int, int)> callback) = 0;
    };
}



#endif //USOPP_IPLAYER_H
