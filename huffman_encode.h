#ifndef _HUFFMAN_ENCODE_H
#define _HUFFMAN_ENCODE_H
#include <iostream>
#include <fstream>
#include "HuffmanTree.h"
#include "file_meta.h"

std::map<char, int> fmap;
Meta meta;

bool huffman_encode(const char* in_file_name, const char *out_file_name){
    char c;
    std::ifstream ifs(in_file_name, std::ios::binary);
    if(!ifs.is_open()){
        printf("Line15, open file [%s] failed\n", in_file_name);
        return false;
    }
    ifs.read(&c, sizeof(c));
    while(!ifs.eof()){                                  // 统计字符频率
        fmap[c]++;
        ifs.read(&c, sizeof(c));
    }

    ifs.close();
    // ifs.clear();
    HuffmanTree ht = HuffmanTree(fmap);                             // 构建哈夫曼树
    
    int sum = 0;
    for(auto i : ht.dict) {                                         // 计算最后一个字节的位数
        sum += i.second.length() * fmap.at(i.first);
        sum %= 256;
    }
    sum %= 8;

    meta.last_byte_bits = sum == 0 ? 8 : sum;           // 构建文件元数据meta
    meta.fmap_size = fmap.size();

    std::ifstream ifs2(in_file_name, std::ios::binary);  
    if(!ifs2.is_open()){
        printf("Line43, open file [%s] failed2\n", in_file_name);
        return false;
    }
    std::ofstream ofs(out_file_name, std::ios::binary);
    if(!ofs.is_open()){
        printf("open file [%s] failed\n", out_file_name);
        return false;
    }

    ofs.write((char*)&meta, sizeof(meta));              // 编码写入meta到文件
    printf("encode. last bits: %d", meta.last_byte_bits);

    for(auto i : fmap){                                 // 写入字符频率，用于解码时构建树
        MapEntry e(i);
        ofs.write((char*)&e, sizeof(MapEntry));
    }

    char ch;
    char data;
    int data_bit_idx = 0;
    ifs2.read(&ch, sizeof(ch));
    while(!ifs2.eof()){                                  // 读入字符，并根据字典，编码写入到文件
        std::string code = ht.dict.at(ch);
        for(auto i : code){
            if(i == '0'){
                CLR_BIT(data, data_bit_idx);
            }else{
                SET_BIT(data, data_bit_idx);
            }
            data_bit_idx++;
            if(data_bit_idx >= 8){
                data_bit_idx = 0;
                ofs.write(&data, sizeof(data));
            }
        }
        ifs2.read(&ch, sizeof(ch));
    }
    if(data_bit_idx) ofs.write(&data, sizeof(data));    // 写入最后的code

    ifs2.close();
    ofs.close();

    return true;
}


#endif
