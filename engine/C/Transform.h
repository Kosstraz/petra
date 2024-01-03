#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <maths/Vector3.hpp>

typedef struct Transform 
{
    Vector3<float> position, scale, rotation;
}   Transform;

typedef struct Transform Transform;

#endif