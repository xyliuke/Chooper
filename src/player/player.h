//
// Created by 刘科 on 2022/8/26.
//

#ifndef USOPP_PLAYER_H
#define USOPP_PLAYER_H

#include <memory>
#include <functional>

namespace plan9
{
    class player {
    public:
        /**
         * 播放器构造函数
         */
        player();
        /**
         * 播放一个本地文件
         * @param path 本地视频文件路径
         */
        player(const std::string &path);
        /**
         * 设置本地播放文件路径
         * @param path 本地视频文件路径
         */
        void set_file(const std::string &path);
        /**
         * 播放
         */
        void play();
        /**
         * 暂停
         */
        void pause();
        /**
         * 停止播放
         */
        void stop();
        /**
         * 跳转到指定时间，单位为毫秒
         * @param ms 指定时间
         */
        void seek(int ms);

        /**
         * 播放进度回调，回调参数为当前播放时间和总时间
         * @param callback
         */
        void set_process_callback(std::function<void(int, int)> callback);

    private:
        class player_impl;
        std::shared_ptr<player_impl> impl;
    };

}



#endif //USOPP_PLAYER_H
