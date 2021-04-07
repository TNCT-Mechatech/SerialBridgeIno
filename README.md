# SerialBridgeIno

## 状態

　version 1.0.0 

## 概要

 本ライブラリは、ArduinoマイコンとPC(ROS)とのシリアル通信を行うためのライブラリです。
 マイコンとPC間で数値データのやり取りを可能にします。
  
##  サンプルコード
[01_echoback_example.ino](example/01_echoback_example/01_echoback_example.ino) これは受信したデータ(Vector3)を送信するコードです。  
```c++
#include "Vector3.h"
```  
ここでメッセージVector3を読み込んでいます。[Vector3.h](example/01_echoback_example/Vector3.h) を見てみましょう。  
```c++
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
```  
Vector3Typeで通信するデータ構造を定義しています。ここでは、float型の変数x,y,zを通信します。  
```c++
#define VECTOR3_MSG_ID 0
```  
これはメッセージIDです。ROS側のmessage_idと合わせる必要があります。  
これらをテンプレートにカスタマイズしてみるといいでしょう。  
  
次に通信のためのソースコードを紹介します。  
```c++
#include <SerialBridge.h>
#include "Vector3.h"

SerialBridge dev(&Serial);
Vector3 msg0;
Vector3 msg1;
```
SerialBridgeとメッセージをincludeし、インスタンスを生成します。  
```c++
SerialBridge dev(&Serial);
```  
Serialのポインタを渡してください。  
```c++
Vector3 msg0;
Vector3 msg1;
```  
messageを定義します。変数msg0を送信用,変数msg1を受信用とします。  
受信を行うにはSerialBridgeにフレームを登録する必要があります。受信に使用する変数msg1を登録しましょう。  
```c++
dev.add_frame(0, &msg1);
```
最初の引数はmessage_idです。(任意の値を指定してください)  
次にpcとの接続を確立するためにノードの識別名を設定します。  
```c++
dev.wait_host("TestVect3");
```
ここでは'TestVector3'という名前になっています。(任意の名前を指定してください)  
  
送受信をしてみましょう。
```c++
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
```  
受信には```dev.read()```を使います。受信に成功した場合は0を返します。if構文でチェックしてください。  
受信したデータを参照するには、```<メッセージ>.data.data.<変数>``` このようにします。  
エコーバックするために変数msg0に代入します。  
```c++
msg0 = msg1;
```  
送信には、```dev.write(0,&msg0);```を使います。この場合、message_idを0として送信します。  
  
送受信にはdelayを入れる必要があります。極端に短い場合は受信に失敗するので、受信側のdelayを多くしたりして試行錯誤してください。  
