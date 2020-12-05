/*
    Message.h
    
    SerialBridgeで扱われるデータ形式の原型をここで定義しています。

    author: Taiyou Komazawa

    データ形式宣言の例:
        //データの構造を定義
        typedef struct{
            int x;
            int y;
            int z;
        } Vector3_t;
        //データの分類番号を定義(他のメッセージ型と被らなければOK)
        #define VECTOR3_ID 0
        //データ形式をメッセージ型に入れる。
        //(名称が長いのでtypedefで改名すればよい)
        typedef Message<Vector3_t,VECTOR3_ID> Vector3;
    
    使い方(受送信データはdata.data.以下に読み書きされる):
        Vector3 msg;
        msg.data.data.x = 0;
        msg.data.data.y = 0;
        msg.data.data.z = 0;
*/

#ifndef SERIAL_BRIDGE_MESSAGE_H_
#define SERIAL_BRIDGE_MESSAGE_H_

#include <stdlib.h>

class _Message
{
public:
    typedef uint8_t msgid_t;
    virtual inline uint8_t *ptr() = 0;
    virtual inline int size() = 0;
    virtual inline msgid_t msg_id() = 0;
};

template <class DataStruct, uint8_t MESSAGE_ID>
class Message : public _Message
{
public:
    typedef union{
        uint8_t all[sizeof(DataStruct)];
        DataStruct data;
    } Data_t;

    Data_t data;

    virtual inline uint8_t *ptr()
    {
        return data.all;
    }

    virtual inline int size()
    {
        return sizeof(DataStruct);
    }

    virtual inline msgid_t msg_id()
    {
        return (msgid_t)MESSAGE_ID;
    }
};

#endif
