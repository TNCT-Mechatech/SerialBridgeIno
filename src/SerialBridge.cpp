#include "SerialBridge.h"


SerialBridge::SerialBridge(HardwareSerial *dev)
{
    _dev = dev;
    _str_num = 0;
    _max_data_size = 0;
}

void SerialBridge::wait_host(String device_name)
{
    _wait_host(device_name);
}

void SerialBridge::add_msg(_Message *str)
{
    if (str != NULL && _str_num <= STRUCT_MAX_NUM){
        _str[_str_num] = str;
        if (_max_data_size < str->size())
            _max_data_size = str->size();
        _str_num++;
    }
}

int SerialBridge::read()
{
    int size = FRAME_LEN + _max_data_size;
    if (_dev->available() >= size){
        uint8_t check_sum = 0;
        int data_sum = 0;

        if (_read_once(&data_sum) != HEADER)
            return -2;

        frame_id id = _read_once(&data_sum);

        if (id >= _str_num)
            return -3;
        
        if (_read_once(&data_sum) != _str[id]->msg_id())
            return -4;

        for (int i = 0; i < _str[id]->size(); i++){
            uint8_t c;
            _str[id]->ptr()[i] = _read_once(&data_sum);
        }

        check_sum = _dev->read();

        if (_read_once(&data_sum) != END)
            return -5;

        if ((data_sum & 0xFF) == check_sum)
            return 0;
        else
            return -6;
    }
    return -1;
}

void SerialBridge::write(frame_id id, _Message *str)
{
    int data_sum = 0;
    _write_once(HEADER, &data_sum);
    _write_once(id, &data_sum);
    _write_once(str->msg_id(), &data_sum);
    for (int i = 0; i < str->size(); i++)
        _write_once(str->ptr()[i], &data_sum);

    data_sum += END;
    _dev->write((uint8_t)(data_sum & 0xFF)); //下位ビット8bitを送信
    _dev->write(END);
    _dev->flush();
}

void SerialBridge::_wait_host(String device_name)
{
    char res[3] = {};
    while (strcmp(res, "OK")){
        Serial.print(device_name);
        Serial.print("\n");
        Serial.readBytesUntil('\n', res, 3);
    }
}

inline void SerialBridge::_write_once(uint8_t c, int *data_sum){
    _dev->write(c);
    *data_sum += c;
}

inline uint8_t SerialBridge::_read_once(int *data_sum){
    uint8_t c = _dev->read();
    *data_sum += c;
    return c;
}
