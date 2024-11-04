#ifndef _FILE_META_H
#define _FILE_META_H
#include <map>
//得到index位的值，若index位为0，则GET_BYTE值为假，否则为真
#define GET_BIT(vbyte, index) (((vbyte) & (1 << ((index) ^ 7))) != 0)
//index位置1
#define SET_BIT(vbyte, index) ((vbyte) |= (1 << ((index) ^ 7)))
//index位置0
#define CLR_BIT(vbyte, index) ((vbyte) &= (~(1 << ((index) ^ 7))))

struct Meta
{
    char tag[6] = "zinkt";
    unsigned char fmap_size;            // 字符种类数，记录了后续
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