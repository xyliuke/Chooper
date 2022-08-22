//
// Created by 刘科 on 2022/6/25.
//

#ifndef MACOPENGLDEMO_SHADER_H
#define MACOPENGLDEMO_SHADER_H

#include <GL/glew.h>
#include <string>
#include <tuple>

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
        /**
         * 编译shader文件，编译后才能使用get_id
         * @return true表示编译成功
         */
        bool compile();
        /**
         * 获取编译后的shader的id
         * @return
         */
        GLuint get_id();
        /**
         * 使用shader有两种方式，一种是使用get_id返回shader的id，调用glUseProgram(id)
         * 另一种是直接调用use()
         */
        void use() const;

        std::string  get_error();

        void set_uniform_value(const std::string &param_name, bool value) const;
        void set_uniform_value(const std::string &param_name, int value) const;
        void set_uniform_value(const std::string &param_name, float value) const;
        void set_uniform_value(const std::string &param_name, float value1, float value2, float value3, float value4) const;
        void set_uniform_value(const std::string &param_name, int value1, int value2, int value3, int value4) const;
        void set_uniform_value(const std::string &param_name, float value1, float value2, float value3) const;
        void set_uniform_value(const std::string &param_name, int value1, int value2, int value3) const;
    private:
        class shader_impl;
        std::shared_ptr<shader_impl> impl;
    };
}



#endif //MACOPENGLDEMO_SHADER_H
