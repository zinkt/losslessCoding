#include "huffman_encode.h"
#include <iostream>
#include <string.h>
int main(int argc, char **argv)
{
    if(argc == 2){
        char out[50];
        snprintf(out, sizeof(out), "%s.cps", argv[1]);
        huffman_encode(argv[1], out);
    }else{
        printf("Parameter number error\nPlease enter infile and outfile\n");
        std::string infile, outfile;
        std::cin >> infile;
        outfile = infile + ".cps";
        huffman_encode(infile.c_str(), outfile.c_str());
    }

    return 0;
}
