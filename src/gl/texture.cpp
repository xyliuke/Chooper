//
// Created by 刘科 on 2022/8/21.
//

#include "texture.h"
#include <memory>
#include <GL/glew.h>

namespace plan9
{
    class texture::texture_impl {
    public:
        texture_impl(std::string &path) {
            initTexture();
        }

        texture_impl(const unsigned char *data, size_t size) {
            initTexture();
        }

    private:
        GLuint id;
        void initTexture() {
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
    };

    texture::texture(std::string &path) {
        impl = std::make_shared<texture_impl>(path);
    }

    texture::texture(const unsigned char *data, size_t size) {
        impl = std::make_shared<texture_impl>(data, size);
    }
}