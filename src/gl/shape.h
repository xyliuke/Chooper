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
        void SetVertexNum(int num);
        void SetVertex(int index, float x, float y, float z);
        void SetVertexColor(int index, float r, float g, float b);
        void SetVertexTexture(int index, float s, float t);
        void ClearVertex();
        void SetTriangleNum(int num);
        void SetVertexIndex(int index, int vertex_0, int vertex_1, int vertex_2);
        void Create(int vertex_location, int texture_location);
        void Render() const;
    private:
        class shape_impl;
        std::shared_ptr<shape_impl> impl;
    };

}

#endif //USOPP_SHAPE_H
