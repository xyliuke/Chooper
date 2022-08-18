#include <string>
#include <memory>

namespace plan9
{
    class window {
    public:
        explicit window(const std::string &title);
        void show() const;
        void destory() const;
        void set_loop_callback(std::function<void()> callback) const;
    private:
        class window_impl;
        std::shared_ptr<window_impl> impl;
    };
}