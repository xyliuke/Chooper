#include "window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace plan9
{
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        // glViewport(0, 0, width, height);
    }
    class window::window_impl {
    public:
        explicit window_impl(const std::string &title) {
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

            window = glfwCreateWindow(640, 480, title.c_str(), nullptr, nullptr);
            if (!window) {
                glfwTerminate();
                return;
            }
            glfwSetKeyCallback(window, key_callback);
            glfwMakeContextCurrent(window);
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            glfwSwapInterval(1);
        }

        void show() {
             while (!glfwWindowShouldClose(window)) {
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                if (this->callback) {
                    this->callback();
                }
                
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
        }
        void destroy() {
            // glfwDestroyWindow(window);
            glfwTerminate();
        }

        void set_loop_callback(std::function<void()> cb) {
            this->callback = std::move(cb);
        }

        void set_title(const std::string &title) {
            glfwSetWindowTitle(window, title.c_str());
        }

    private:
        GLFWwindow *window;
        std::function<void()> callback;
    };

    window::window(const std::string &title) : impl(std::make_shared<window_impl>(title)) {
        
    }
    void window::set_loop_callback(std::function<void()> callback) const {
        impl->set_loop_callback(callback);
    }
    void window::show() const {
        impl->show();
    }

    void window::set_title(const std::string &title) {
        impl->set_title(title);
    }

    void window::destroy() const {
        impl->destroy();
    }
}