/*
    01_readwrite_example.ino

    データ形式の定義の例(Vector3.h)とデータの送受信の例を示します。

    author: Taiyou Komazawa
*/

#include <SerialBridge.h>
#include "Vector3.h"

SerialBridge dev(&Serial);
Vector3 msg0;
Vector3 msg1;

void setup()
{
    Serial.begin(9600);

    dev.add_frame(0, &msg1);

    dev.wait_host("TestVect3"); //ホストの応答を待ちます。
}

void loop()
{
    msg0.data.data.x = 0.123;
    msg0.data.data.y = 0.456;
    msg0.data.data.z = 0.321;

    dev.write(0, &msg0);

    dev.read();

    delay(20);
}