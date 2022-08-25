#include <iostream>
#include "window/window.h"
#include "gl/triangle.h"
#include "gl/video_render.h"

int main() {
    auto *w =  new plan9::window("Usopp");
//    auto *t = new plan9::triangle();
//    t->create();
//    w->set_loop_callback([t] {
//        t->render();
//    });


    auto v = new plan9::video_render("../resource/vertex_shader.glsl", "../resource/fragment_shader.glsl");
    v->create(-0.5f, 0.5f, 0.5f, -0.5f, 0, 1);
    v->update("../test/resource/2.jpg");
    w->set_loop_callback([=] {
        v->render();
    });


    w->show();
    w->destory();

//    delete t;
//    delete v;
    delete w;
}