//
// Created by 刘科 on 2022/8/26.
//

#include "player.h"
#include "window/window.h"

namespace plan9
{
    class player::player_impl {
    public:
        player_impl() {

        }

        player_impl(const std::string &path) {

        }

        void set_file(const std::string &path) {

        }

        void play() {

        }

        void pause() {

        }

        void stop() {

        }

        void seek(int ms) {

        }

        void set_process_callback(std::function<void(int, int)> callback) {
            process_callback = std::move(callback);
        }

    private://私有变量
        std::function<void(int, int)> process_callback;
        std::shared_ptr<plan9::window> window;

    private://私有函数
        void create_window() {
            window = std::make_shared<plan9::window>("Usopp");
            window->set_loop_callback([] {

            });
            window->show();
            window->destroy();
        }
    };

    player::player() {
        impl = std::make_shared<player_impl>();
    }

    player::player(const std::string &path) {
        impl = std::make_shared<player_impl>(path);
    }

    void player::set_file(const std::string &path) {
        impl->set_file(path);
    }

    void player::play() {
        impl->play();
    }

    void player::pause() {
        impl->pause();
    }

    void player::stop() {
        impl->stop();
    }

    void player::seek(int ms) {
        impl->seek(ms);
    }

    void player::set_process_callback(std::function<void(int, int)> callback) {
        impl->set_process_callback(std::move(callback));
    }

}