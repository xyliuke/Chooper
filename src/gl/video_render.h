//
// Created by liuke on 2022/8/25.
//

#ifndef USOPP_VIDEO_RENDER_H
#define USOPP_VIDEO_RENDER_H

#include <memory>
#include <functional>

namespace plan9
{
    class video_render {
    public:
        video_render(const std::string &vertex_file_path, const std::string &fragment_file_path);
        void create(float lx, float ly, float rx, float ry, int vertex_location, int texture_location);
        void set_image_array(std::shared_ptr<std::vector<std::string&>> list);
        void set_fps(unsigned int fps);
        void update(const std::string &path);
        void render();
        void set_process_callback(std::function<void(float)> callback);
    private:
        class video_render_impl;
        std::shared_ptr<video_render_impl> impl;
    };
}


#endif //USOPP_VIDEO_RENDER_H
