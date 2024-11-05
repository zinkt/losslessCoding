#include "huffman_decode.h"
#include <iostream>

int main(int argc, char **argv)
{
    if(argc == 2){
        char out[50];
        snprintf(out, sizeof(out), "%s.dcps", argv[1]);
        huffman_decode(argv[1], out);
    }else{
        printf("Parameter number error\nPlease enter infile and outfile\n");
        std::string infile, outfile;
        std::cin >> infile;
        outfile = infile + ".dcps";
        huffman_decode(infile.c_str(), outfile.c_str());
    }
    return 0;
}
