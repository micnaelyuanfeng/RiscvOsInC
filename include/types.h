#ifndef __TYPES_H__
#define __TYPES_H__

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;
typedef int                 int32_t;
typedef long long           int64_t;
typedef unsigned char       bool;

#define true   1
#define false  0
#define _nullptr 0

enum PayloadSzie {
    _Byte = 0,
    _Hword = 1,
    _Word = 2,
    _DWord = 3,
};

#endif