//
// Created by 刘科 on 2022/8/26.
//

#ifndef USOPP_IMAGE_PLAYER_H
#define USOPP_IMAGE_PLAYER_H

#include <memory>
#include <functional>
#include "i_player.h"

namespace plan9
{
    class ImagePlayer : public IPlayer {
    public:
        /**
         * 播放器构造函数
         */
        ImagePlayer();
        /**
         * 播放一个本地文件
         * @param path 本地视频文件路径
         */
        ImagePlayer(const std::string &path);
        /**
         * 设置本地播放文件路径
         * @param path 本地视频文件路径
         */
        void SetFile(const std::string &path);
        /**
         * 播放
         */
        void Play();
        /**
         * 暂停
         */
        void Pause();
        /**
         * 停止播放
         */
        void Stop();
        /**
         * 跳转到指定时间，单位为毫秒
         * @param ms 指定时间
         */
        void Seek(int ms);

        /**
         * 播放进度回调，回调参数为当前播放时间和总时间
         * @param callback
         */
        void SetProcessCallback(std::function<void(int, int)> callback);

        void Show() const;

    private:
        class ImagePlayerImpl;
        std::shared_ptr<ImagePlayerImpl> impl_;
    };

}



#endif //USOPP_IMAGE_PLAYER_H
