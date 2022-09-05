//
// Created by liuke on 2022/8/25.
//

#include "video_render.h"
#include "shape.h"
#include "shader.h"
#include "texture.h"

namespace plan9
{
    class VideoRender::video_render_impl {
    public:
        video_render_impl(const std::string &vertex_file_path, const std::string &fragment_file_path) {
            glewInit();
            shape = std::make_shared<plan9::Shape>();
            shader = std::make_shared<plan9::Shader>(vertex_file_path, fragment_file_path);
            texture = std::make_shared<plan9::Texture>();
            texture_id = 0;
        }
        /**
         * 创建显示区域大小，（lx,ly)是左上角坐标,范围为[0, 1); (rx,ry)是右下角坐标,范围是(0, 1]，lx < rx, ly < ry
         * @param lx
         * @param ly
         * @param rx
         * @param ry
         */
        void create(float lx, float ly, float rx, float ry, int vertex_location, int texture_location) {
            shader->Compile();

            shape->SetVertexNum(4);
            shape->SetVertex(0, rx, ly, 0.f);
            shape->SetVertex(1, rx, ry, 0.f);
            shape->SetVertex(2, lx, ry, 0.f);
            shape->SetVertex(3, lx, ly, 0.f);

            shape->SetTriangleNum(2);
            shape->SetVertexIndex(0, 0, 1, 3);
            shape->SetVertexIndex(1, 1, 2, 3);

            shape->SetVertexTexture(0, 1.f, 1.f);
            shape->SetVertexTexture(1, 1.f, 0.f);
            shape->SetVertexTexture(2, 0.f, 0.f);
            shape->SetVertexTexture(3, 0.f, 1.f);

            shape->Create(vertex_location, texture_location);
        }

        void UpdateSize(float lx, float ly, float rx, float ry, int vertex_location, int texture_location) {

            shape->SetVertexNum(4);
            shape->SetVertex(0, rx, ly, 0.f);
            shape->SetVertex(1, rx, ry, 0.f);
            shape->SetVertex(2, lx, ry, 0.f);
            shape->SetVertex(3, lx, ly, 0.f);

            shape->SetTriangleNum(2);
            shape->SetVertexIndex(0, 0, 1, 3);
            shape->SetVertexIndex(1, 1, 2, 3);

            shape->SetVertexTexture(0, 1.f, 1.f);
            shape->SetVertexTexture(1, 1.f, 0.f);
            shape->SetVertexTexture(2, 0.f, 0.f);
            shape->SetVertexTexture(3, 0.f, 1.f);

            shape->Create(vertex_location, texture_location);
        }

        void update(const std::string &path) {
            texture->Update(path);
            shader->SetUniformValue("ourTexture", 0);
        }

        void UpdateRGBData(unsigned char *data, int width, int height) {
            texture->UpdateRGBData(data, width, height);
            shader->SetUniformValue("ourTexture", 0);
        }

        void render() {
            texture->Use(texture_id);
            shader->Use();
            shape->Render();
        }
    private:
        int texture_id;
        std::shared_ptr<plan9::Shape> shape;
        std::shared_ptr<plan9::Shader> shader;
        std::shared_ptr<plan9::Texture> texture;
    };

    VideoRender::VideoRender(const std::string &vertex_file_path, const std::string &fragment_file_path) {
        impl = std::make_shared<video_render_impl>(vertex_file_path, fragment_file_path);
    }

    void VideoRender::Create(float lx, float ly, float rx, float ry, int vertex_location, int texture_location) {
        impl->create(lx, ly, rx, ry, vertex_location, texture_location);
    }

    void VideoRender::Update(const std::string &path) {
        impl->update(path);
    }

    void VideoRender::Render() {
        impl->render();
    }

    void VideoRender::UpdateRGBData(unsigned char *data, int width, int height) {
        impl->UpdateRGBData(data, width, height);
    }

    void VideoRender::UpdateSize(float lx, float ly, float rx, float ry, int vertex_location, int texture_location) {
        impl->UpdateSize(lx, ly, rx, ry, vertex_location, texture_location);
    }
}