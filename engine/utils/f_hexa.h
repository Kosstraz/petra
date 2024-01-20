#ifndef F_HEXA_H
#define F_HEXA_H

#ifdef __cplusplus
extern "C" {
#endif

    // Inverse le sens binaire sur du 32 bits
int inv_bin32(int val);

    // Inverse le sens binaire sur du 16 bits
short inv_bin16(short val);

    // Inverse le sens binaire sur du 8 bits
signed char inv_bin8(signed char val);

#ifdef __cplusplus
}
#endif

#endif