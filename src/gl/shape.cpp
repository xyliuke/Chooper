//
// Created by liuke on 2022/8/25.
//

#include "shape.h"
#include <GL/glew.h>

namespace plan9
{
    class Shape::shape_impl {
    public:
        shape_impl() : vao(0), vertex_num(0), vertices(nullptr), triangle_num(0), indices(nullptr) {

        }

        ~shape_impl() {
            if (vertices != nullptr) {
                delete[] vertices;
                vertices = nullptr;
            }
            if (indices != nullptr) {
                delete[] indices;
                indices = nullptr;
            }
        }

        void set_vertex_num(int num) {
            ClearVertex();
            this->vertex_num = num;
            vertices = new float[num * vertex_num_per_row]{0.f};
        }

        /**
         * 添加坐标点
         * @param index 索引值，即第几个顶点
         * @param x x坐标
         * @param y y坐标
         * @param z z坐标
         */
        void set_vertex(int index, float x, float y, float z) {
            if (index >= 0 && index < vertex_num) {
                int idx = index * vertex_num_per_row;
                vertices[idx] = x;
                vertices[idx + 1] = y;
                vertices[idx + 2] = z;
            }
        }

        void set_vertex_color(int index, float r, float g, float b) {
            if (index >= 0 && index < vertex_num) {
                float *row = vertices + index * vertex_num_per_row;
                *(row + 3) = r;
                *(row + 4) = g;
                *(row + 5) = b;
            }
        }

        void set_vertex_texture(int index, float s, float t) {
            if (index >= 0 && index < vertex_num) {
                float *row = vertices + index * vertex_num_per_row;
                *(row + 6) = s;
                *(row + 7) = t;
            }
        }

        void ClearVertex() {
            vertex_num = 0;
            delete[] vertices;
            vertices = nullptr;
        }

        void set_triangle_num(int num) {
            triangle_num = num;
            if (indices != nullptr) {
                delete[] indices;
                indices = nullptr;
            }
            indices = new unsigned int [num * index_num_per_row];
        }

        void set_vertex_index(int index, int vertex_0, int vertex_1, int vertex_2) {
            if (index >= 0 && index < triangle_num) {
                unsigned int *row = indices + index * index_num_per_row ;
                *row = vertex_0;
                *(row + 1) = vertex_1;
                *(row + 2) = vertex_2;
            }
        }

        void create(int vertex_location, int texture_location) {
            glGenVertexArrays(1, &vao);
            GLuint VBO;
            glGenBuffers(1, &VBO);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)sizeof(float) * vertex_num_per_row * vertex_num, vertices, GL_STATIC_DRAW);

            GLuint EBO;
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)sizeof(unsigned int) * triangle_num * index_num_per_row, indices, GL_STATIC_DRAW);
            GLsizeiptr i;
            glVertexAttribPointer(vertex_location, 3, GL_FLOAT, GL_FALSE, (GLsizei)(vertex_num_per_row * sizeof(float)), (void*) nullptr);
            glEnableVertexAttribArray(vertex_location);

            if (texture_location >= 0) {
                glVertexAttribPointer(texture_location, 2, GL_FLOAT, GL_FALSE, (GLsizei)(vertex_num_per_row * sizeof(float)), (void*) (6 * sizeof(float)));
                glEnableVertexAttribArray(texture_location);
            }
        }

        void render() const {
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, triangle_num * index_num_per_row, GL_UNSIGNED_INT, nullptr);
        }

    private:
        GLuint vao;
        //顶点个数，实际在vertices中存储的数据个数为vertex_num * vertex_num_per_row
        int vertex_num;
        /**
         * 顶点数组的结构如下,每行有8个数据，分别为 x,y,z 3个坐标，r,g,b 3个颜色，s,t 2个纹理坐标
         * x, y,  z, r, g, b, s,  t
         */
        float *vertices;
        //三角形索引个数，实际在indices中存储的数据个数为triangle_num * 3;
        int triangle_num;
        unsigned int *indices;
        static int vertex_num_per_row;//顶点数据数组中，每行有数据个数
        static int index_num_per_row;//索引数组中，每行有数据个数
    };
    int Shape::shape_impl::vertex_num_per_row = 8;
    int Shape::shape_impl::index_num_per_row = 3;

    Shape::Shape() {
        impl = std::make_shared<plan9::Shape::shape_impl>();
    }

    void Shape::set_vertex_num(int num) {
        impl->set_vertex_num(num);
    }

    void Shape::set_vertex(int index, float x, float y, float z) {
        impl->set_vertex(index, x, y, z);
    }

    void Shape::set_vertex_color(int index, float r, float g, float b) {
        impl->set_vertex_color(index, r, g, b);
    }

    void Shape::set_vertex_texture(int index, float s, float t) {
        impl->set_vertex_texture(index, s, t);
    }

    void Shape::ClearVertex() {
        impl->ClearVertex();
    }

    void Shape::set_triangle_num(int num) {
        impl->set_triangle_num(num);
    }

    void Shape::set_vertex_index(int index, int vertex_0, int vertex_1, int vertex_2) {
        impl->set_vertex_index(index, vertex_0, vertex_1, vertex_2);
    }

    void Shape::create(int vertex_location, int texture_location) {
        impl->create(vertex_location, texture_location);
    }

    void Shape::render() const {
        impl->render();
    }
}