#include <iostream>
#include "window/window.h"
#include "gl/triangle.h"

int main() {
    plan9::window *w =  new plan9::window("");
    int count = 0;
    plan9::triangle *t = new plan9::triangle();
    t->create();
    w->set_loop_callback([count, t] mutable {
        t->render();
    });
    w->show();    
    w->destory();

    delete t;
    delete w;
}