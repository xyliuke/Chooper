#include <iostream>
#include "window/window.h"

int main() {
    plan9::window w = plan9::window("");
    int count = 0;
    w.set_loop_callback([count] mutable {
        std::cout << "loop : " << count << "\n";
        count ++;
    });
    w.show();    
    w.destory();
}