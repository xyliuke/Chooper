//
// Created by 刘科 on 2022/6/25.
//

#include "file_util.h"
#include <fstream>
#include <iostream>

namespace plan9 {

    size_t file_util::get_size_from_file(const std::string &path) {
        std::ifstream ifstream = std::ifstream(path, std::ios::binary | std::ios::in | std::ios::ate);
        if (ifstream.is_open()) {
            std::streampos size = ifstream.tellg();
            ifstream.close();
            return (size_t)size;
        }
        return 0;
    }

    bool file_util::get_content_from_file(const std::string &path, char *buf, size_t size) {
        std::ifstream ifstream = std::ifstream(path, std::ios::binary | std::ios::in | std::ios::ate);
        if (ifstream.is_open()) {
            ifstream.seekg(0, std::ios::beg);
            ifstream.read(buf, (std::streampos)size);
            ifstream.close();
            return true;
        }
        return false;
    }


}