//
// Created by 刘科 on 2022/8/26.
//

#include "image_player.h"
#include "window/window.h"
#include "gl/video_render.h"
#include <iomanip>
#include <sstream>

namespace plan9
{
    class ImagePlayer::ImagePlayerImpl {
    public:
        explicit ImagePlayerImpl() {
            create_window();
            render = std::make_shared<plan9::video_render>("../resource/vertex_shader.glsl", "../resource/fragment_shader.glsl");
            render->create(-1.f, 1.f, 1.f, -1.f, 0, 1);
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

        }

        void Pause() {

        }

        void Stop() {

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

    private://私有函数
        void create_window() {
            window = std::make_shared<plan9::Window>("Usopp");
            count = 1;
            step = 0;
            window->SetLoopCallback([=] {
                if (step < 3) {
                    render->render();
                    step ++;
                } else {
//                    std::stringstream ss;
//                    ss << "../test/resource/image_group/foo-";
//                    ss << std::setw(5) << std::setfill('0') << count;
//                    ss << ".jpeg";
////            std::cout << ss.str() << std::endl;
                    if (count < list->size()) {
                        std::string image = list->at(count);
                        render->update(image);
                        render->render();
                        count += 1;
                        step = 0;
                    } else {
                        step = 0;
                    }
                }
            });
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