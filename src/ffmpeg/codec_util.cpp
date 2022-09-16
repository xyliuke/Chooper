//
// Created by 刘科 on 2022/9/13.
//

#include "codec_util.h"
extern "C" {
#include <libavformat/avformat.h>
}
#include <iostream>

namespace plan9
{
    class CodecUtil::CodecUtilImpl {
    public:
        CodecUtilImpl() {
            AVFormatContext *formatContext = nullptr;
            formatContext = avformat_alloc_context();
            int ret = avformat_open_input(&formatContext, "../test/resource/1.mp4", nullptr, nullptr);
            if (ret == 0) {
                std::cout << formatContext->duration << std::endl;
                std::cout << formatContext->nb_streams << std::endl;
                std::cout << formatContext->iformat->name << std::endl;
            }
            delete formatContext;
        }
    };

    CodecUtil::CodecUtil() {
        impl_ = std::make_shared<CodecUtilImpl>();
    }
}