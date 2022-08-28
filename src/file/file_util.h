//
// Created by 刘科 on 2022/6/25.
//

#ifndef MACOPENGLDEMO_FILE_UTIL_H
#define MACOPENGLDEMO_FILE_UTIL_H

#include <string>
#include <memory>

namespace plan9 {
    class FileUtil {
    public:
        static size_t GetSize(const std::string &path);
        static bool GetContent(const std::string &path, char *buf, size_t size);
    };
}


#endif //MACOPENGLDEMO_FILE_UTIL_H

