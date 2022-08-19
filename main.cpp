#include <iostream>
#include "window/window.h"
#include "gl/triangle.h"

int main() {
    auto *w =  new plan9::window("Usopp");
    int count = 0;
    auto *t = new plan9::triangle();
    t->create();
    w->set_loop_callback([count, t] mutable {
        t->render();
    });
    w->show();    
    w->destory();

    delete t;
    delete w;
}