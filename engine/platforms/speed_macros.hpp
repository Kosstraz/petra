#pragma once

#define FastGen(ClassName)   public:    ClassName() = default;     ~ClassName() = default;

#define  DEFAULT_FILE_SIZE FILE_SIZE_16KO  // 16384      octets  |   16   Ko

#define  FILE_SIZE_4GO      0xFFFFFFFFU    // 4294967295 octets  |   4,2  Go
#define  FILE_SIZE_1GO      0x4FFFFFFFU    // 1342177279 octets  |   1,3  Go
#define  FILE_SIZE_500MO    0x1FFFFFFFU    // 536870911  octets  |   500  Mo
#define  FILE_SIZE_100MO    0x06FFFFFFU    // 117440511  octets  |   100  Mo
#define  FILE_SIZE_50MO     0x02FFFFFFU    // 50331647   octets  |   50   Mo
#define  FILE_SIZE_1MO      0x000FFFFFU    // 1048575    octets  |   1    Mo
#define  FILE_SIZE_1024KO   0x000FFFFFU    // 1048575    octets  |   1024 Ko
#define  FILE_SIZE_512KO    0x00080000U    // 524288     octets  |   512  Ko
#define  FILE_SIZE_64KO     0x0000FFFFU    // 65535      octets  |   64   Ko
#define  FILE_SIZE_16KO     0x00004000U    // 16384      octets  |   16   Ko
#define  FILE_SIZE_8KO      0x00002000U    // 8192       octets  |   8    Ko
#define  FILE_SIZE_4KO      0x00001000U    // 4096       octets  |   4    Ko
#define  FILE_SIZE_2KO      0x00000800U    // 2048       octets  |   2    Ko
#define  FILE_SIZE_1KO      0x00000400U    // 1024       octets  |   1    Ko
#define  FILE_SIZE_500O     0x00000200U    // 512        octets  |   0,5  Ko