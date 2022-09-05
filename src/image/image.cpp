//
// Created by 刘科 on 2022/7/12.
//

#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace plan9
{
    class Image::image_impl {
    private:
        std::string image_file;
    public:
        explicit image_impl(const std::string &path) {
            image_file = path;
        }
        unsigned char * get_data(int *width, int *height) const {
            int nrChannels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load(image_file.c_str(), width, height, &nrChannels, 0);
            return data;
        }
        static void destroy(unsigned char *data) {
            stbi_image_free(data);
        }
    };

    Image::Image(const std::string &path) {
        impl = std::make_shared<image_impl>(path);
    }

    unsigned char *Image::GetData(int *width, int *height) const {
        return impl->get_data(width, height);
    }

    void Image::Destroy(unsigned char *data) {
        Image::image_impl::destroy(data);
    }
}