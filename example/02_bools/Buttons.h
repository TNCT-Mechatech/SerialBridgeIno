#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <SerialBridge.h>
#include <Bools.h>

typedef struct ButtonsType
{
    bools8_t::bit_field sw0;
    bools8_t::bit_field sw1;
} buttons_t;

#define BUTTONS_MSG_ID 1

typedef sb::Message<buttons_t, BUTTONS_MSG_ID> Buttons;

#endif