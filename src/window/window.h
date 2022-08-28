#include <string>
#include <memory>
#include <functional>

namespace plan9
{
    class Window {
    public:
        explicit Window(const std::string &title);
        void SetTitle(const std::string &title);
        void Show() const;
        void Close() const;
        void Destroy() const;
        void SetLoopCallback(std::function<void()> callback) const;
        void SetKeyCommandCallback(std::function<void(int key, int scancode, int action, int mods)> callback);
    private:
        class WindowImpl;
        std::shared_ptr<WindowImpl> impl_;
    };
}