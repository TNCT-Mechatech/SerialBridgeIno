/*
    01_echoback_example.ino

    データ形式の定義の例(Vector3.h)とデータの送受信の例を示します。
    受信したデータを送信元に送信する処理です。

    author: Taiyou Komazawa
*/

#include <SerialBridge.h>
#include "Vector3.h"

SerialBridge dev(&Serial);
Vector3 msg0;
Vector3 msg1;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.begin(9600);

    dev.add_frame(0, &msg1);

    dev.wait_host("TestVect3"); //ホストの応答を待ちます。
}

void loop()
{

    if(dev.read() == 0){ //受信に成功すれば0を返す。
        digitalWrite(LED_BUILTIN, HIGH);
        msg0 = msg1; //受信データをエコーする
        dev.write(0, &msg0);
    }else{
        digitalWrite(LED_BUILTIN, LOW);
    }

    delay(20);
}
