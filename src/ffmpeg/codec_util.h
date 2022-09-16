//
// Created by 刘科 on 2022/9/13.
//

#ifndef USOPP_CODEC_UTIL_H
#define USOPP_CODEC_UTIL_H
#include <memory>

namespace plan9
{
    class CodecUtil {
    public:
        CodecUtil();

    private:
        class CodecUtilImpl;
        std::shared_ptr<CodecUtilImpl> impl_;
    };

}



#endif //USOPP_CODEC_UTIL_H
