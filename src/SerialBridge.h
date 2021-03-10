/*
    SerialBridge.h
    
    SerialBridgeの処理をここで定義しています。

    author: Taiyou Komazawa
*/

#ifndef SERIAL_BRIDGE_H_
#define SERIAL_BRIDGE_H_

#include <Arduino.h>

#include <Message.h>

class SerialBridge
{
public:
    typedef uint8_t frame_id;

    SerialBridge(Stream *dev);

    void wait_host(String device_name);

    void add_frame(frame_id id, sb::_Message *str);
    int read();
    void write(frame_id id, sb::_Message *str);

protected:
    enum
    {
        FRAME_LEN = 4,
        STRUCT_MAX_NUM = 10,
    };

    typedef enum ControlCharType
    {
        HEADER = ':',
        END = '\n',
    } ctrl_char_t;

private:
    sb::_Message *_str[STRUCT_MAX_NUM];
    uint8_t _max_data_size;

    Stream *_dev;

    void _wait_host(String device_name);
    inline void _write_once(uint8_t c, int *data_sum);
    inline uint8_t _read_once(int *data_sum);
};

#endif
