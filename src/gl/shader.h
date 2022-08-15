//
// Created by 刘科 on 2022/6/25.
//

#ifndef MACOPENGLDEMO_SHADER_H
#define MACOPENGLDEMO_SHADER_H

#include <GL/glew.h>
#include <string>

namespace plan9 {
    class shader {
    public:
        /**
         * 创建一个顶点shader
         * @param path shader文件路径
         * @return 返回一个三元组，分别表示GLuint，是否创建成功，和如果创建失败的错误信息
         */
        static std::tuple<bool, GLuint, std::string> create_vertex_shader(const std::string &path);

        static std::tuple<bool, GLuint, std::string> create_vertex_shader_from_content(const char * content);

        static std::tuple<bool, GLuint, std::string> create_fragment_shader(const std::string &path);

        static std::tuple<bool, GLuint, std::string> create_fragment_shader_from_content(const char * content);

        static std::tuple<bool, GLuint, std::string> compile_shader(const std::string &vertex_path, const std::string &fragment_path);

        static std::tuple<bool, GLuint, std::string> compile_shader(GLuint vertex_shader, GLuint fragment_shader);

        shader(const std::string &vertex_file_path, const std::string &fragment_file_path);

        bool compile();

        GLuint get_id();

        std::string  get_error();
    private:
        class shader_impl;
        std::shared_ptr<shader_impl> impl;
    };
}



#endif //MACOPENGLDEMO_SHADER_H
