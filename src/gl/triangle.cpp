#include "triangle.h"
#include "shader.h"
#include <GL/glew.h>

#include <GL/glew.h>

namespace plan9
{

class triangle::triangle_impl {
public:
    triangle_impl():VAO(0), shaderProgram(0) {

    }
    void create() {
        glewInit();
        shader = std::make_shared<plan9::shader>("../resource/vertex_shader.glsl", "../resource/fragment_shader.glsl");
        bool suc = shader->compile();

        float vertices[] = {
                -0.5f, -0.5f, -0.f, // left
                0.5f, -0.5f, 0.f, // right
                0.0f,  0.5f, -0.f  // top
        };

        GLuint VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
    }

    void render() const {
//        glUseProgram(shaderProgram);
        shader->use();
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
private:
    GLuint VAO;
    GLuint shaderProgram;
    std::shared_ptr<plan9::shader> shader;
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

