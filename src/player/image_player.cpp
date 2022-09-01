//
// Created by 刘科 on 2022/8/26.
//

#include "image_player.h"
#include "window/window.h"
#include "gl/video_render.h"
#include <iomanip>
#include <sstream>
#include "time/timer.h"
#include <iostream>
#include <chrono>
#include "time/thread_util.h"
#include "image/image.h"
#include <thread>

namespace plan9
{
    class ImagePlayer::ImagePlayerImpl {
    public:
        explicit ImagePlayerImpl() {
            create_window();
            render = std::make_shared<plan9::video_render>("../resource/vertex_shader.glsl", "../resource/fragment_shader.glsl");
            render->create(-1.f, 1.f, 1.f, -1.f, 0, 1);
            timer_ = std::make_shared<plan9::Timer>();
            timer_->SetTimerCallback(std::bind(&ImagePlayerImpl::TimerCallback, this));
            timer_->SetInterval(1000 / 24);
        }

        void SetImageList(std::shared_ptr<std::vector<std::string>> list) {
            this->list = list;
        }

        ~ImagePlayerImpl() {
            window->Close();
        }

        void SetFile(const std::string &path) {

        }

        void Play() {
            last = std::chrono::steady_clock::now();
            timer_->Start();
        }

        void Pause() {

        }

        void Stop() {
            timer_->Stop();
        }

        void Seek(int ms) {

        }

        void SetProcessCallback(std::function<void(int, int)> callback) {
            process_callback = std::move(callback);
        }

        void Show() {
            window->Show();
        }

    private://私有变量
        std::function<void(int, int)> process_callback;
        std::shared_ptr<plan9::Window> window;
        std::shared_ptr<plan9::video_render> render;
        std::shared_ptr<std::vector<std::string>> list;
        int count;
        int step;
        std::shared_ptr<plan9::Timer> timer_;
        std::chrono::steady_clock::time_point last;

        //测试数据
        int width;
        int height;
        unsigned char *data;
    private://私有函数
        void create_window() {
            window = std::make_shared<plan9::Window>("Usopp");
            count = 1;
            step = 0;
            window->SetLoopCallback([=] {
                this->render->UpdateRGBData(this->data, width, height);
                this->render->render();
            });
        }

        void TimerCallback() {
            if (this->count < this->list->size()) {
                std::string image = this->list->at(count);
                DecodeImageData(image);
                this->count += 1;
            }
            PostOnMainThread([this] {
                this->render->UpdateRGBData(this->data, width, height);
                this->render->render();
            });
        }

        void DecodeImageData(std::string &path) {
            auto image = plan9::image(path);
            int w;
            int h;
            unsigned char *d = image.get_data(&w, &h);
            this->width = w;
            this->height = h;
            plan9::image::destroy(this->data);
            this->data = d;
        }
    };

    ImagePlayer::ImagePlayer() {
        impl_ = std::make_shared<ImagePlayerImpl>();
    }

    void ImagePlayer::SetImageList(std::shared_ptr<std::vector<std::string>> list) {
        impl_->SetImageList(list);
    }

    void ImagePlayer::SetFile(const std::string &path) {
        impl_->SetFile(path);
    }

    void ImagePlayer::Play() {
        impl_->Play();
    }

    void ImagePlayer::Pause() {
        impl_->Pause();
    }

    void ImagePlayer::Stop() {
        impl_->Stop();
    }

    void ImagePlayer::Seek(int ms) {
        impl_->Seek(ms);
    }

    void ImagePlayer::SetProcessCallback(std::function<void(int, int)> callback) {
        impl_->SetProcessCallback(std::move(callback));
    }

    void ImagePlayer::Show() const {
        impl_->Show();
    }

}