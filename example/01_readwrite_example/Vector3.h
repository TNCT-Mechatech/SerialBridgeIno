#ifndef VECTOR_3_H_
#define VECTOR_3_H_

#include <SerialBridge.h>

typedef struct Vector3Type
{
    float x;
    float y;
    float z;
} vector3_t;

#define VECTOR3_MSG_ID 0

typedef sb::Message<vector3_t, VECTOR3_MSG_ID> Vector3;

#endif
