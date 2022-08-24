//
// Created by 刘科 on 2022/8/21.
//

#ifndef USOPP_TEXTURE_H
#define USOPP_TEXTURE_H

#include <string>

namespace plan9 {

    class texture {
    public:
        explicit texture(std::string &path);

        texture(const unsigned char *data, size_t size, int width, int height);
        /**
         * 使用纹理
         * @param texture_id 最小范围为0-15，表示GL_TEXTURE0-GL_TEXTURE15，至少有16个可以使用。具体参考平台定义
         */
        void use(int texture_id) const;

    private:
        class texture_impl;

        std::shared_ptr<texture_impl> impl;
    };

}
#endif //USOPP_TEXTURE_H
