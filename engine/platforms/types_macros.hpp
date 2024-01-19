#pragma once

#define READ_ONLY

#define INT8_MAX        (0x00000000000000FF / 2)
#define INT16_MAX       (0x000000000000FFFF / 2)
#define INT32_MAX       (0x00000000FFFFFFFF / 2)
#define INT64_MAX       (0xFFFFFFFFFFFFFFFF / 2)

#define INT8_MIN       -(0x00000000000000FF / 2 + 1)
#define INT16_MIN      -(0x000000000000FFFF / 2 + 1)
#define INT32_MIN      -(0x00000000FFFFFFFF / 2 + 1)
#define INT64_MIN      -(0xFFFFFFFFFFFFFFFF / 2 + 1)

#define UINT8_MAX       (0x00000000000000FF)
#define UINT16_MAX      (0x000000000000FFFF)
#define UINT32_MAX      (0x00000000FFFFFFFF)
#define UINT64_MAX      (0xFFFFFFFFFFFFFFFF)

typedef unsigned char   ubool ;
typedef char            boolean;
typedef bool            int16b;

typedef signed char     int8  ;
typedef short           int16 ;
typedef int             int32 ;
typedef long            int64 ;
typedef long long       int128; // <=> int64

typedef unsigned char   uint8 ;
typedef unsigned short  uint16;
typedef unsigned int    uint32;
typedef unsigned long   uint64;

typedef unsigned char   uchar ;
typedef unsigned int    uint  ;
typedef unsigned long   ulong ;