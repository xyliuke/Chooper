#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once

#include <memory>

namespace plan9
{
class triangle
{
public:
    triangle();
    void create() const;
    void render() const;
private:
    class triangle_impl;
    std::shared_ptr<triangle_impl> impl;
};
}
#endif