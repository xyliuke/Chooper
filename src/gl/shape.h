//
// Created by liuke on 2022/8/25.
//

#ifndef USOPP_SHAPE_H
#define USOPP_SHAPE_H

#include <memory>
namespace plan9
{
    class Shape {
    public:
        explicit Shape();
        void set_vertex_num(int num);
        void set_vertex(int index, float x, float y, float z);
        void set_vertex_color(int index, float r, float g, float b);
        void set_vertex_texture(int index, float s, float t);
        void ClearVertex();
        void set_triangle_num(int num);
        void set_vertex_index(int index, int vertex_0, int vertex_1, int vertex_2);
        void create(int vertex_location, int texture_location);
        void render() const;
    private:
        class shape_impl;
        std::shared_ptr<shape_impl> impl;
    };

}

#endif //USOPP_SHAPE_H
