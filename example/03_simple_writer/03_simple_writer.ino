/*
    03_simple_writer.ino

    データ形式の定義の例(Vector3.h)とデータの送受信の例を示します。
    受信したデータを送信元に送信する処理です。

    author: Taiyou Komazawa
*/

#include <SerialBridge.h>
#include "Vector3.h"

SerialBridge dev(&Serial);
Vector3 msg0;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.begin(115200);

    dev.wait_host("TestSimpleVect3"); //ホストの応答を待ちます。
}

void loop()
{
    msg0.data.data.x = 0.123;
    msg0.data.data.y = 0.456;
    msg0.data.data.z = 0.789;
    //  send
    dev.write(0, &msg0);

    delay(20);
}
