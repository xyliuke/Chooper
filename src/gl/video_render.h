//
// Created by liuke on 2022/8/25.
//

#ifndef USOPP_VIDEO_RENDER_H
#define USOPP_VIDEO_RENDER_H

#include <memory>

namespace plan9
{
    class video_render {
    public:
        video_render(const std::string &vertex_file_path, const std::string &fragment_file_path);
        void create(float lx, float ly, float rx, float ry, int vertex_location, int texture_location);
        void update(const std::string &path);
        void render();
    private:
        class video_render_impl;
        std::shared_ptr<video_render_impl> impl;
    };
}


#endif //USOPP_VIDEO_RENDER_H
