#ifndef _FILE_META_H
#define _FILE_META_H
#include <map>

#define GET_BIT(vbyte, index) (((vbyte) & (1 << ((index) ^ 7))) != 0)

#define SET_BIT(vbyte, index) ((vbyte) |= (1 << ((index) ^ 7)))

#define CLR_BIT(vbyte, index) ((vbyte) &= (~(1 << ((index) ^ 7))))

struct Meta
{
    char tag[6] = "zinkt";
    short fmap_size;            // 字符种类数，(不能使用char，因为字符可能数为256)
    unsigned char last_byte_bits;
};

struct MapEntry
{
    char c;
    int freq;
    MapEntry(){}
    MapEntry(const std::pair<char,int> &e):c(e.first), freq(e.second){}
};

#endif