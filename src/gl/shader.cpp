//
// Created by 刘科 on 2022/6/25.
//

#include "shader.h"
#include <file/file_util.h>
namespace plan9 {

    class Shader::shader_impl {
    private:
        std::string vertex_file_path = {};
        std::string fragment_file_path = {};
        std::string error;
    public:
        GLuint id = {0};
        GLuint vertex_id = {0};
        GLuint fragment_id = {0};
        shader_impl(const std::string &vertex_file_path, const std::string &fragment_file_path) : 
            vertex_file_path(vertex_file_path),
            fragment_file_path(fragment_file_path) {
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

        void Use() const {
            glUseProgram(id);
        }

        void set_uniform_value(const std::string &param_name, int value) const {
            int loc = glGetUniformLocation(id, param_name.c_str());
            glUniform1i(loc, value);
        }

        void set_uniform_value(const std::string &param_name, bool value) const {
            int loc = glGetUniformLocation(id, param_name.c_str());
            glUniform1i(loc, (int)value);
        }

        void set_uniform_value(const std::string &param_name, float value) const {
            int loc = glGetUniformLocation(id, param_name.c_str());
            glUniform1f(loc, value);
        }

        void set_uniform_value(const std::string &param_name, float value1, float value2, float value3, float value4) const {
            int loc = glGetUniformLocation(id, param_name.c_str());
            glUniform4f(loc, value1, value2, value3, value4);
        }

        void set_uniform_value(const std::string &param_name, float value1, float value2, float value3) const {
            int loc = glGetUniformLocation(id, param_name.c_str());
            glUniform3f(loc, value1, value2, value3);
        }

        void set_uniform_value(const std::string &param_name, int value1, int value2, int value3, int value4) const {
            int loc = glGetUniformLocation(id, param_name.c_str());
            glUniform4d(loc, value1, value2, value3, value4);
        }

        void set_uniform_value(const std::string &param_name, int value1, int value2, int value3) const {
            int loc = glGetUniformLocation(id, param_name.c_str());
            glUniform3d(loc, value1, value2, value3);
        }

        static std::tuple<bool, GLuint, std::string> create_vertex_shader(const std::string &path) {
            size_t size = FileUtil::GetSize(path);
            auto *buf = new char[size + 1]();
            bool suc = FileUtil::GetContent(path, buf, size);
            if (!suc) {
                delete []buf;
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
                glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
                return {false, 0, std::string(infoLog)};
            }
            return {true, vertex_shader, ""};
        }

        static std::tuple<bool, GLuint, std::string> create_fragment_shader(const std::string &path) {
            size_t size = FileUtil::GetSize(path);
            auto *buf = new char[size + 1]();
            bool suc = FileUtil::GetContent(path, buf, size);
            if (!suc) {
                delete []buf;
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
                glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
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
                glGetProgramInfoLog(shader_program, 512, nullptr, infoLog);
                return {false, 0, std::string(infoLog)};
            }
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
            return {true, shader_program, ""};
        }
        std::string  get_error() const {
            return error;
        }
    };

    std::tuple<bool, GLuint, std::string> Shader::CreateVertexShader(const std::string &path) {
        return shader_impl::create_vertex_shader(path);
    }

    std::tuple<bool, GLuint, std::string> Shader::CreateVertexShaderFromContent(const char *content) {
        return shader_impl::create_vertex_shader_from_content(content);
    }

    std::tuple<bool, GLuint, std::string> Shader::CreateFragmentShader(const std::string &path) {
        return shader_impl::create_fragment_shader(path);
    }

    std::tuple<bool, GLuint, std::string> Shader::CreateFragmentShaderFromContent(const char *content) {
        return shader_impl::create_vertex_shader_from_content(content);
    }

    std::tuple<bool, GLuint, std::string>
    Shader::CompileShader(const std::string &vertex_path, const std::string &fragment_path) {
        return shader_impl::compile_shader(vertex_path, fragment_path);
    }

    std::tuple<bool, GLuint, std::string> Shader::CompileShader(GLuint vertex_shader, GLuint fragment_shader) {
        return shader_impl::compile_shader(vertex_shader, fragment_shader);
    }

    Shader::Shader(const std::string &vertex_file_path, const std::string &fragment_file_path) :
        impl(new shader_impl(vertex_file_path, fragment_file_path)) {

    }

    bool Shader::Compile() {
        return impl->compile();
    }

    GLuint Shader::get_id() {
        return impl->id;
    }

    std::string Shader::get_error() {
        return impl->get_error();
    }

    void Shader::Use() const {
        impl->Use();
    }

    void Shader::SetUniformValue(const std::string &param_name, int value) const {
        impl->set_uniform_value(param_name, value);
    }

    void Shader::SetUniformValue(const std::string &param_name, bool value) const {
        impl->set_uniform_value(param_name, value);
    }

    void Shader::SetUniformValue(const std::string &param_name, float value) const {
        impl->set_uniform_value(param_name, value);
    }

    void
    Shader::SetUniformValue(const std::string &param_name, float value1, float value2, float value3, float value4) const {
        impl->set_uniform_value(param_name, value1, value2, value3, value4);
    }

    void Shader::SetUniformValue(const std::string &param_name, int value1, int value2, int value3, int value4) const {
        impl->set_uniform_value(param_name, value1, value2, value3, value4);
    }

    void Shader::SetUniformValue(const std::string &param_name, float value1, float value2, float value3) const {
        impl->set_uniform_value(param_name, value1, value2, value3);
    }

    void Shader::SetUniformValue(const std::string &param_name, int value1, int value2, int value3) const {
        impl->set_uniform_value(param_name, value1, value2, value3);
    }
}