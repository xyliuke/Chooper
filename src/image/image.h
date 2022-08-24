//
// Created by 刘科 on 2022/7/12.
//

#ifndef MACOPENGLDEMO_IMAGE_H
#define MACOPENGLDEMO_IMAGE_H

#include <string>

namespace plan9
{
    class image {
    public:
        explicit image(const std::string &path);
        unsigned char * get_data(int *width, int *height) const;
        void destroy(unsigned char *data) const;
    private:
        class image_impl;
        std::shared_ptr<image_impl> impl;
    };
}



#endif //MACOPENGLDEMO_IMAGE_H
