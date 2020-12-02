#include <iostream>
using namespace std;
#include "encode_decode.h"
int main()
{
    string rawStr;

    cout << "----------------------This is a demostration of my lossless coding functions----------------------\n"
         << "\n********Run-length code********\n"
         << "Input raw string without space:\n";
    cin >> rawStr;
    //runlength
    string RLcode = encode_decode::run_lengthEncode(rawStr);
    cout << "Encode: \n" << RLcode << "\n"
         << "Decode: \n" << encode_decode::run_lengthDecode(RLcode)<<'\n';

    //shannon-fano
    cout << "\n********Shannon-Fano code********\n";
    //encode_decode::shannon_fanoEncode(rawStr);

    //LZW code
    cout<<"\n********LZW code********\n"
         << "Input raw string:\n";
    rawStr.clear();
    cin >> rawStr;
    string LZWcode = encode_decode::LZWEncode(rawStr);
    cout<<"Encode:\n"<<LZWcode<<endl;
    cout << "Decode:\n"
         << encode_decode::LZWDecode(LZWcode) << endl;
    
    //LZW code
    cout<<"\n********Arithmatic code********\n"
         << "Input raw string and '#' to terminate:\n";
    rawStr.clear();
    cin >> rawStr;
    double code = encode_decode::arithmeticEncode(rawStr);
    string arithmaticCode = to_string(code);
    cout << "Encode:\n" << arithmaticCode << endl;
    //绘制概率区域表
    map<char, int> count;
    for(auto & i:rawStr)   
        count[i]++;
    map<char, range> p_table;
    double lowlevel = 0.0, highlevel = 0.0;
    int charNum = rawStr.size();
    for(auto & i:count)
    {
        lowlevel = highlevel;
        highlevel = lowlevel + i.second /(double)charNum;
        p_table[i.first] = range(lowlevel, highlevel);
    }
    string decode = encode_decode::arithmeticDecode(code, p_table);
    cout << "Decode:\n" << decode << endl;

    system("pause");
    return 0;
}