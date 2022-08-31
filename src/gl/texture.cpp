//
// Created by 刘科 on 2022/8/21.
//

#include "texture.h"
#include "image/image.h"
#include <memory>
#include <GL/glew.h>

namespace plan9
{
    class texture::texture_impl {
    public:
        explicit texture_impl() : id(0) {
            initTexture();
        }

        explicit texture_impl(std::string &path) : id(0) {
            initTexture();

            auto image = plan9::image(path);
            int width;
            int height;
            unsigned char *data = image.get_data(&width, &height);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            image.destroy(data);
        }

        texture_impl(const unsigned char *data, size_t size, int width, int height) : id(0) {
            initTexture();

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void update(const std::string &path) {
            auto image = plan9::image(path);
            int width;
            int height;
            unsigned char *data = image.get_data(&width, &height);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            image.destroy(data);
        }

        void UpdateRGBData(unsigned char *data, int width, int height) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void use(int texture_id) const {
            glActiveTexture(GL_TEXTURE0 + texture_id);
            glBindTexture(GL_TEXTURE_2D, id);
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

    texture::texture() {
        impl = std::make_shared<texture_impl>();
    }

    texture::texture(std::string &path) {
        impl = std::make_shared<texture_impl>(path);
    }

    texture::texture(const unsigned char *data, size_t size, int width, int height) {
        impl = std::make_shared<texture_impl>(data, size, width, height);
    }

    void texture::use(int texture_id) const {
        impl->use(texture_id);
    }

    void texture::update(const std::string &path) {
        impl->update(path);
    }

    void texture::UpdateRGBData(unsigned char *data, int width, int height) {
        impl->UpdateRGBData(data, width, height);
    }
}