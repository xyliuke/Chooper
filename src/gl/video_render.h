//
// Created by liuke on 2022/8/25.
//

#ifndef USOPP_VIDEO_RENDER_H
#define USOPP_VIDEO_RENDER_H

#include <memory>
#include <functional>

namespace plan9
{
    class VideoRender {
    public:
        VideoRender(const std::string &vertex_file_path, const std::string &fragment_file_path);
        void Create(float lx, float ly, float rx, float ry, int vertex_location, int texture_location);
        void Update(const std::string &path);
        void UpdateRGBData(unsigned char *data, int width, int height);
        void Render();
        void UpdateSize(float lx, float ly, float rx, float ry, int vertex_location, int texture_location);
    private:
        class video_render_impl;
        std::shared_ptr<video_render_impl> impl;
    };
}


#endif //USOPP_VIDEO_RENDER_H
