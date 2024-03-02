#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Vector2.hpp"
#include "Vector3.hpp"

struct Transform2D
{
    Vector2<float> position, scale, rotation;
};

struct Transform
{
    Vector3<float> position, scale, rotation;
};

#endif