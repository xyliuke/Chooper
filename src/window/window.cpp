#include "window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>

namespace plan9
{
    class Window::WindowImpl {
    public:
        explicit WindowImpl(const std::string &title) {
            if (!glfwInit()) {
                std::cout << "glfw init failed" << std::endl;
                return;
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

            window_ = glfwCreateWindow(640, 480, title.c_str(), nullptr, nullptr);
            if (!window_) {
                glfwTerminate();
                return;
            }
            if (map == nullptr) {
                map = std::make_shared<std::map<GLFWwindow *, Window::WindowImpl *>>();
            }
            map->insert(std::pair<GLFWwindow *, Window::WindowImpl *>(window_, this));

            glfwSetKeyCallback(window_, &WindowImpl::KeyCallback);
            glfwMakeContextCurrent(window_);
            glfwSetFramebufferSizeCallback(window_, FramebufferSizeCallback);
            glfwSwapInterval(1);
        }

        ~WindowImpl() {
            auto it = map->begin();
            while (it != map->end()) {
                if (it->second == this) {
                    map->erase(it);
                }
                it ++;
            }
        }

        void show() {
             while (!glfwWindowShouldClose(window_)) {
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                if (this->callback) {
                    this->callback();
                }
                
                glfwSwapBuffers(window_);
                glfwPollEvents();
            }
        }
        void destroy() {
            // glfwDestroyWindow(window);
            glfwTerminate();
        }

        void Close() {
            glfwSetWindowShouldClose(window_, GLFW_TRUE);
        }

        void set_loop_callback(std::function<void()> cb) {
            this->callback = std::move(cb);
        }

        void set_title(const std::string &title) {
            glfwSetWindowTitle(window_, title.c_str());
        }

        void SetKeyCommandCallback(std::function<void(int, int, int, int)> callback) {
            this->key_command_callback_ = std::move(callback);
        }

        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {

            }
            auto it = map->begin();
            while (it != map->end()) {
                if (it->first == window) {
                    if (it->second->key_command_callback_) {
                        it->second->key_command_callback_(key, scancode, action, mods);
                    }
                    break;
                }
                it ++;
            }
        }
        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {

        }


    private:
        GLFWwindow *window_;
        std::function<void()> callback;
        std::function<void(int, int, int, int)> key_command_callback_;
        static std::shared_ptr<std::map<GLFWwindow *, Window::WindowImpl *>> map;
    };

    std::shared_ptr<std::map<GLFWwindow *, Window::WindowImpl *>> Window::WindowImpl::map = nullptr;

    Window::Window(const std::string &title) : impl_(std::make_shared<WindowImpl>(title)) {
        
    }
    void Window::SetLoopCallback(std::function<void()> callback) const {
        impl_->set_loop_callback(std::move(callback));
    }
    void Window::Show() const {
        impl_->show();
    }

    void Window::SetTitle(const std::string &title) {
        impl_->set_title(title);
    }

    void Window::Destroy() const {
        impl_->destroy();
    }

    void Window::Close() const {
        impl_->Close();
    }

    void Window::SetKeyCommandCallback(std::function<void(int, int, int, int)> callback) {

    }
}