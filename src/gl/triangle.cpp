#include "triangle.h"
#include "shader.h"
#include "texture.h"
#include <GL/glew.h>
#include "image/image.h"

namespace plan9
{

class triangle::triangle_impl {
public:
    triangle_impl():VAO(0) {

    }
    void create() {
        glewInit();
        shader = std::make_shared<plan9::shader>("../resource/vertex_shader.glsl", "../resource/fragment_shader.glsl");
        shader->compile();

        float vertices[] = {
            0.5f, 0.5f, 0.0f, 1.0f, 1.f,  // 右上角
            0.5f, -0.5f, 0.0f, 1.f, 0.f,  // 右下角
            -0.5f, -0.5f, 0.0f, 0.f, 0.f,// 左下角
            -0.5f, 0.5f, 0.0f, 0.f, 1.f,   // 左上角
        };

        unsigned int indices[] = {
            // 注意索引从0开始!
            // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
            // 这样可以由下标代表顶点组合成矩形
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
        };

        GLuint VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        GLuint EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        std::string path = "../test/resource/2.jpg";
        texture = std::make_shared<plan9::texture>(path);
        shader->set_uniform_value("ourTexture", 0);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框模式
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//填充模式
    }

    void render() const {
        texture->use(0);
        shader->use();
        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
private:
    GLuint VAO;
    std::shared_ptr<plan9::shader> shader;
    std::shared_ptr<plan9::texture> texture;
};

triangle::triangle()/*:impl(std::make_shared<triangle_impl>())*/
{
    impl = std::make_shared<triangle_impl>();
}

void triangle::create() const {
    impl->create();
}

void triangle::render() const {
    impl->render();
}

} // namespace plan9

