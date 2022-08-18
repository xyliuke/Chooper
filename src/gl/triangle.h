#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once

#include <GL/glew.h>

namespace plan9
{
class triangle
{
public:
    triangle();
    ~triangle();
    void create();
    void render() const;
private:
    GLuint VAO;
    GLuint shaderProgram;
};
}
#endif