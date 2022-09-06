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
#include "state/state.h"
#include <thread>

namespace plan9
{
    //状态
    class ImagePlayerInitState : public state {

    };

    class ImagePlayerPlayingState : public state {

    };

    class ImagePlayerStateMachine : public state_machine {
    public:
        ImagePlayerStateMachine() {
            STATE_MACHINE_ADD_ROW(this, ImagePlayerInitState, PLAY, ImagePlayerPlayingState, [=](state_machine* fsm) -> bool {
                return !(fsm->is_current_state<ImagePlayerPlayingState>());
            });
        }

    public:
        //事件
        static const std::string PLAY;
        static const std::string STOP;
        static const std::string PAUSE;
        static const std::string RESUME;
    };

    class ImagePlayer::ImagePlayerImpl {
    public:
        explicit ImagePlayerImpl() {
            create_window();
            render = std::make_shared<plan9::VideoRender>("../resource/vertex_shader.glsl", "../resource/fragment_shader.glsl");
            render->Create(-1.f, 1.f, 1.f, -1.f, 0, 1);
            timer_ = std::make_shared<plan9::Timer>();
            timer_->SetTimerCallback(std::bind(&ImagePlayerImpl::TimerCallback, this));
            timer_->SetInterval(1000 / 24);
        }

        void SetImageList(std::shared_ptr<std::vector<std::string>> list) {
            this->list = std::move(list);
        }

        ~ImagePlayerImpl() {
            window->Close();
        }

        void SetFile(const std::string &path) {

        }

        void Play() {
            isPlay = true;
            last = std::chrono::steady_clock::now();
            timer_->Start();
        }

        void Pause() {
            isPlay = false;
            timer_->Stop();
        }

        void Stop() {
            timer_->Stop();
            count = 0;
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
        std::shared_ptr<plan9::VideoRender> render;
        std::shared_ptr<std::vector<std::string>> list;
        int count;
        int step;
        std::shared_ptr<plan9::Timer> timer_;
        std::chrono::steady_clock::time_point last;

        //测试数据
        int width = {0};
        int height = {0};
        unsigned char *data;

        bool isFirstRender = {false};
        bool isPlay = {false};
    private://私有函数
        void create_window() {
            window = std::make_shared<plan9::Window>("Usopp");
            count = 1;
            step = 0;
            window->SetLoopCallback([=] {
                Render();
            });

            window->SetWindowSizeChangedCallback([=](int width, int height){
                ResizeTexture(width, height);
            });

            window->SetKeyCommandCallback([this] (int key, int scancode, int action, int mods) {
                if (key == 32/*GLFW_KEY_SPACE*/ && action == 1 /*GLFW_PRESS*/) {
                    if (this->isPlay) {
                        this->Pause();
                    } else {
                        this->Play();
                    }

//                    this->window->Close();
//                    plan9::Window::Destroy();
                }
            });
        }

        void TimerCallback() {
            if (this->count < this->list->size()) {
                std::string image = this->list->at(count);
                DecodeImageData(image);
                this->count += 1;
            }
            PostOnMainThread([this] {
                Render();
            });
        }

        void DecodeImageData(std::string &path) {
            auto image = plan9::Image(path);
            int w;
            int h;
            unsigned char *d = image.GetData(&w, &h);
            this->width = w;
            this->height = h;
            plan9::Image::Destroy(this->data);
            this->data = d;
        }

        void Render() {
            if (width > 0 && height > 0) {
                if (!isFirstRender) {
                    BeforeFirstRender();
                }
                this->render->UpdateRGBData(this->data, width, height);
                this->render->Render();
                if (!isFirstRender) {
                    AfterFirstRender();
                    isFirstRender = true;
                }
            }
        }

        void BeforeFirstRender() {
            ResizeTexture(window->GetWidth(), window->GetHeight());
        }

        void AfterFirstRender() {

        }

        void ResizeTexture(int window_width, int window_height) {
            if (height > 0 && width > 0) {
                float ly = 1.f;
                float ry = -1.f;
                int should_height = int(float(height * window_width) / float(width));
                ly = float(should_height) / float(window_height);
                ry = -ly;
                render->UpdateSize(-1.f, ly, 1.f, ry, 0, 1);
            }
        }
    };

    ImagePlayer::ImagePlayer() {
        impl_ = std::make_shared<ImagePlayerImpl>();
    }

    void ImagePlayer::SetImageList(std::shared_ptr<std::vector<std::string>> list) {
        impl_->SetImageList(std::move(list));
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