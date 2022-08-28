#include <iostream>
#include "window/window.h"
#include "gl/triangle.h"
#include "gl/video_render.h"
#include <sstream>
#include <iomanip>
#include <chrono>
#include "player/image_player.h"

//将视频拆分成图片
//ffmpeg -i test.mp4 -r 30 -f image2 foo-%05d.jpeg
int main() {
//    auto *w =  new plan9::Window("Usopp");
//    auto *t = new plan9::triangle();
//    t->create();
//    w->set_loop_callback([t] {
//        t->render();
//    });


//    auto v = new plan9::video_render("../resource/vertex_shader.glsl", "../resource/fragment_shader.glsl");
//    v->create(-1.f, 1.f, 1.f, -1.f, 0, 1);
//    v->update("../test/resource/2.jpg");
//    int count = 1;
//    int ten = 0;
//    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
//    w->SetLoopCallback([=] mutable {
//        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
//        std::cout << (end - start).count() / 1000 / 1000 << ": ms" << std::endl;
//        start = std::chrono::steady_clock::now();
//        if (ten < 3) {
//            v->render();
//            ten ++;
//        } else {
//            std::stringstream ss;
//            ss << "../test/resource/image_group/foo-";
//            ss << std::setw(5) << std::setfill('0') << count;
//            ss << ".jpeg";
////            std::cout << ss.str() << std::endl;
//            v->update(ss.str());
//            v->render();
//            count += 1;
//            ten = 0;
//        }
//    });
//
//
//    w->Show();
//    w->Destroy();

//    delete t;
//    delete v;

    auto imagePlayer = new plan9::ImagePlayer();
    imagePlayer->Show();
//    delete w;
}