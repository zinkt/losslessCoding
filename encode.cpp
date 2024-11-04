#include "huffman_encode.h"
#include <iostream>

int main(int argc, char **argv)
{
    if(argc == 3){
        huffman_encode(argv[1], argv[2]);
    }else{
        printf("Parameter number error\nPlease enter infile and outfile\n");
        std::string infile, outfile;
        std::cin >> infile;
        std::cin >> outfile;
        huffman_encode(infile.c_str(), outfile.c_str());
    }

    return 0;
}
