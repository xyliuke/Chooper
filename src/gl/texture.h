//
// Created by 刘科 on 2022/8/21.
//

#ifndef USOPP_TEXTURE_H
#define USOPP_TEXTURE_H

#include <string>

namespace plan9 {

    class texture {
    public:
        texture(std::string &path);

        texture(const unsigned char *data, size_t size);

    private:
        class texture_impl;

        std::shared_ptr<texture_impl> impl;
    };

}
#endif //USOPP_TEXTURE_H
