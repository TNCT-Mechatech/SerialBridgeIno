#ifndef VECTOR_3_H_
#define VECTOR_3_H_

#include <SerialBridge.h>

typedef struct Vector3Type //データの中身を定義
{
    float x;
    float y;
    float z;
} vector3_t;

//メッセージID(被りのない限り好きな数字でOK)
#define VECTOR3_MSG_ID 0

//先程の定義を渡してメッセージ型を作成。今回は型名をVector3にしました。
typedef sb::Message<vector3_t, VECTOR3_MSG_ID> Vector3;

//これだけで送るデータを自作できます。

#endif
