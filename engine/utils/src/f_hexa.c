#include "../f_hexa.h"

#include <string.h>

int inv_bin32(int hexa)
{
    return (
        ((hexa & 0x000000FF) << 24) |
        ((hexa & 0x0000FF00) << 8 ) |
        ((hexa & 0x00FF0000) >> 8 ) |
        ((hexa & 0xFF000000) >> 24));
}

short inv_bin16(short hexa)
{
    return (
        ((hexa & 0x000F) << 12) |
        ((hexa & 0x00F0) << 4 ) |
        ((hexa & 0x0F00) >> 4 ) |
        ((hexa & 0xF000) >> 12));
}

signed char inv_bin8(signed char hexa)
{
    return (
        ((hexa & 0x0F) << 4) |
        ((hexa & 0xF0) >> 4 ));
}