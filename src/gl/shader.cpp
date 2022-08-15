//
// Created by 刘科 on 2022/6/25.
//

#include "shader.h"
#include "file/file_util.h"
namespace plan9 {

    class shader::shader_impl {
    private:
        std::string vertex_file_path;
        std::string fragment_file_path;
        std::string error;
    public:
        GLuint id;
        GLuint vertex_id;
        GLuint fragment_id;
        shader_impl(const std::string &vertex_file_path, const std::string &fragment_file_path) {
            id = 0;
            vertex_id = 0;
            fragment_id = 0;
            this->vertex_file_path = vertex_file_path;
            this->fragment_file_path = fragment_file_path;
        }

        bool compile() {
            auto vertex = create_vertex_shader(vertex_file_path);
            auto fragment = create_fragment_shader(fragment_file_path);
            if (std::get<0>(vertex) && std::get<0>(fragment)) {
                //创建shader成功
                vertex_id = std::get<1>(vertex);
                fragment_id = std::get<1>(fragment);
                auto ret = compile_shader(vertex_id, fragment_id);
                if (std::get<0>(ret)) {
                    id = std::get<1>(ret);
                    return true;
                } else {
                    error = std::get<2>(ret);
                }
            } else {
                if (!std::get<0>(vertex)) {
                    error = std::get<2>(vertex);
                } else if (!std::get<0>(fragment)) {
                    error = std::get<2>(fragment);
                }
            }
            return false;
        }

        static std::tuple<bool, GLuint, std::string> create_vertex_shader(const std::string &path) {
            size_t size = file_util::get_size_from_file(path);
            char *buf = new char[size + 1]();
            bool suc = file_util::get_content_from_file(path, buf, size);
            if (!suc) {
                return {false, 0, ""};
            }
            buf[size] = '\0';
            auto ret = create_vertex_shader_from_content(buf);
            delete []buf;
            return ret;
        }

        static std::tuple<bool, GLuint, std::string> create_vertex_shader_from_content(const char *context) {
            GLuint vertex_shader = 0;
            vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex_shader, 1, &context, NULL);
            glCompileShader(vertex_shader);
            int success;
            glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
                return {false, 0, std::string(infoLog)};
            }
            return {true, vertex_shader, ""};
        }

        static std::tuple<bool, GLuint, std::string> create_fragment_shader(const std::string &path) {
            size_t size = file_util::get_size_from_file(path);
            char *buf = new char[size + 1]();
            bool suc = file_util::get_content_from_file(path, buf, size);
            if (!suc) {
                return {false, 0, ""};
            }
            buf[size] = '\0';
            auto ret = create_fragment_shader_from_content(buf);
            delete []buf;
            return ret;
        }

        static std::tuple<bool, GLuint, std::string> create_fragment_shader_from_content(const char *content) {
            GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment_shader, 1, &content, NULL);
            glCompileShader(fragment_shader);
            int success;
            glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
                return {false, 0, std::string(infoLog)};
            }
            return {true, fragment_shader, ""};
        }

        static std::tuple<bool, GLuint, std::string>
        compile_shader(const std::string &vertex_path, const std::string &fragment_path) {
            auto vertex_shader = create_vertex_shader(vertex_path);
            auto fragment_shader = create_fragment_shader(fragment_path);
            if (std::get<0>(vertex_shader) && std::get<0>(fragment_shader)) {
                return compile_shader(std::get<1>(vertex_shader), std::get<1>(fragment_shader));
            }
            return {false, 0, "shader error"};
        }

        static std::tuple<bool, GLuint, std::string> compile_shader(GLuint vertex_shader, GLuint fragment_shader) {
            GLuint shader_program = glCreateProgram();
            glAttachShader(shader_program, vertex_shader);
            glAttachShader(shader_program, fragment_shader);
            glLinkProgram(shader_program);
            // check for linking errors
            int success;
            glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
                return {false, 0, std::string(infoLog)};
            }
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
            return {true, shader_program, ""};
        }
        std::string  get_error() {
            return error;
        }
    };

    std::tuple<bool, GLuint, std::string> shader::create_vertex_shader(const std::string &path) {
        return shader_impl::create_vertex_shader(path);
    }

    std::tuple<bool, GLuint, std::string> shader::create_vertex_shader_from_content(const char *content) {
        return shader_impl::create_vertex_shader_from_content(content);
    }

    std::tuple<bool, GLuint, std::string> shader::create_fragment_shader(const std::string &path) {
        return shader_impl::create_fragment_shader(path);
    }

    std::tuple<bool, GLuint, std::string> shader::create_fragment_shader_from_content(const char *content) {
        return shader_impl::create_vertex_shader_from_content(content);
    }

    std::tuple<bool, GLuint, std::string>
    shader::compile_shader(const std::string &vertex_path, const std::string &fragment_path) {
        return shader_impl::compile_shader(vertex_path, fragment_path);
    }

    std::tuple<bool, GLuint, std::string> shader::compile_shader(GLuint vertex_shader, GLuint fragment_shader) {
        return shader_impl::compile_shader(vertex_shader, fragment_shader);
    }

    shader::shader(const std::string &vertex_file_path, const std::string &fragment_file_path) :
        impl(new shader_impl(vertex_file_path, fragment_file_path)) {

    }

    bool shader::compile() {
        return impl->compile();
    }

    GLuint shader::get_id() {
        return impl->id;
    }

    std::string shader::get_error() {
        return impl->get_error();
    }
}