/*
    02_bools.ino

    データ形式の定義の例(Buttons.h)とデータの送受信の例を示します。

    author: Taiyou Komazawa
*/

#include <SerialBridge.h>
#include "Buttons.h"

SerialBridge dev(&Serial);
Buttons msg0;
Buttons msg1;

bools8_t swh0;
bools8_t swh1;

void setup()
{
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    Serial.begin(9600);

    dev.add_frame(0, &msg1);

    dev.wait_host("TestBools"); //ホストの応答を待ちます。
}

void loop()
{
    bool bool_array[bools8_t::len] = {
        0, 1, 1, 0, 0, 1, 0, 0
    };
    swh0 = new bool[bools8_t::len]{0,1,1,0,0,1,0};
    swh1 = bool_array;
    msg0.data.data.sw0 = swh0;
    msg0.data.data.sw1 = swh1;

    dev.write(0, &msg0);

    if (dev.read() == 0) //受信に成功すれば0を返す。
        digitalWrite(13, HIGH);

    delay(20);
}
