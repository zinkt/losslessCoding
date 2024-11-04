#ifndef _HUFFMAN_DECODE_H
#define _HUFFMAN_DECODE_H
#include <fstream>
#include "HuffmanTree.h"
#include "file_meta.h"

Meta meta;
std::map<char,int> fmap;
std::map<std::string, char> deocde_dict;
bool huffman_decode(const char *in_file_name, const char *out_file_name){
    std::ifstream ifs(in_file_name, std::ios::binary);
    if(!ifs.is_open()){
        printf("Line8, open file [%s] failed\n", in_file_name);
        return false;
    }

    ifs.read((char*)&meta, sizeof(Meta));                       // 读入元数据
    if(strcmp(meta.tag, "zinkt")){
        printf("Wrong input file format: %s\n", in_file_name);
        return false;
    }

    MapEntry e;                                                 // 从元数据中构建字符频率表
    for(int i = 0; i < meta.fmap_size; i++){
        ifs.read((char*)&e, sizeof(MapEntry));
        fmap.insert(std::pair<char, int>(e.c, e.freq));
    }

    HuffmanTree ht(fmap);                                       // 构建哈夫曼树

    for(auto e : ht.dict) {
        deocde_dict.insert(std::pair<std::string, char>(e.second, e.first));    // 解码树
    }

    std::ofstream ofs(out_file_name, std::ios::binary);
    if(!ofs.is_open()){
        printf("Line33, open file [%s] failed\n", out_file_name);
    }

    long data_start_location = ifs.tellg();
    ifs.seekg(0, std::ios_base::end);
    long file_size = ifs.tellg();
    ifs.seekg(data_start_location, std::ios_base::beg);
    long cur_location = ifs.tellg();

    char data;
    std::string code;
    Node n = ht.pq.top();                                      // 树根
    Node *pn = &n;
    int bit_idx = 0;
    ifs.read(&data, sizeof(data));
    while(1){
        if(is_leaf(pn)){
            char ch = deocde_dict[code];
            ofs.write(&ch, sizeof(char));
            cur_location = ifs.tellg();
            if(cur_location >= file_size && bit_idx >= meta.last_byte_bits) break;
            code.clear();
            pn = &n;//重新从根开始
        }
        if(GET_BIT(data, bit_idx)){
            code += '1';
            pn = pn -> right;
        }else{
            code += '0';
            pn = pn -> left;
        }
        if(++bit_idx >= 8){
            bit_idx = 0;
            ifs.read(&data, sizeof(data));
        }
    }
    printf("decode. last bits: %d", meta.last_byte_bits);
    ifs.close();
    ofs.close();

    return true;
}






#endif

