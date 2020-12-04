#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;
struct sigleCode_3digits
{
    int init = 0;
    short fst = 0;
    short snd = 0;
    short trd = 0;
    string sigleCode_to_String() { return to_string(fst) + to_string(snd) + to_string(trd); }
    sigleCode_3digits() {}
    sigleCode_3digits(int i) : init(i)
    {
        trd = i % 10;
        i /= 10;
        snd = i % 10;
        i /= 10;
        fst = i % 10;
    }
};
struct range
{
    double range_low = 0.0;
    double range_high = 1.0;
    range() {}
    range(double low, double high) : range_low(low), range_high(high) {}
};
struct treeNode
{
    treeNode *left;
    treeNode *right;
    char ch;    //此节点储存的待编码字符
    int weight; //字符所占权重（频数）
    treeNode()
    {
        left = nullptr;
        right = nullptr;
        ch = '\0';
        weight = 0;
    }
    treeNode(treeNode *l, treeNode *r, char c, int w) : left(l), right(r), ch(c), weight(w) {}
    bool isLeaf() { return !left && !right; }
};
struct HuffmanTree
{
    treeNode *head;
    vector<treeNode> nodeSet; //储存待生成的树节点
    HuffmanTree() {}
    HuffmanTree(map<char, int> weightMap) //以存有字符频数的vector初始化nodeSet
    {
        for (auto &i : weightMap)
            nodeSet.push_back(treeNode(nullptr, nullptr, i.first, i.second));
    }
    void HtreeTraverse(treeNode *root, string &code) //遍历H树（对输出code的操作并不美观hh）
    {
        string tempCodeL = code;
        string tempCodeR = code;
        tempCodeL += '0';
        tempCodeR += '1';
        if (root->isLeaf())
            cout << root->ch << "  " << code << endl;
        else
        {
            HtreeTraverse(root->left, tempCodeL);
            HtreeTraverse(root->right, tempCodeR);
        }
    }
    static bool treeNodeCmp(treeNode t1, treeNode t2) { return t1.weight > t2.weight; } //用于sort算法
};
struct SFTree
{
    treeNode *head;
    vector<treeNode> nodeSet; //储存待生成的树节点
    SFTree() {}
    SFTree(map<char, int> weightMap) //以存有字符频数的vector初始化nodeSet
    {
        head = new treeNode();
        for (auto &i : weightMap)
            nodeSet.push_back(treeNode(nullptr, nullptr, i.first, i.second));
        sort(nodeSet.begin(), nodeSet.end(), SFTree::treeNodeCmp);
    }
    static bool treeNodeCmp(treeNode t1, treeNode t2) { return t1.weight > t2.weight; } //用于sort算法
    static vector<treeNode>::iterator Optimize_split(vector<treeNode>::iterator tempSet_begin, vector<treeNode>::iterator tempSet_end)
    {

        double sum = 0.0, half = 0.0;
        for (auto itr = tempSet_begin; itr != tempSet_end; itr++)
            sum += itr->weight;
        half = sum / 2.0;
        sum = 0.0;
        for (auto itr = tempSet_begin; itr != tempSet_end; itr++)
        {
            sum += itr->weight;
            if (sum > half)
                return itr;
        }
        return tempSet_end;
    }
    void SFtreeCreate(treeNode *parent, vector<treeNode>::iterator tempSet_begin, vector<treeNode>::iterator tempSet_end)
    {
        if (tempSet_begin + 1 == tempSet_end)
        {
            parent->ch = tempSet_begin->ch;
            parent->weight = tempSet_begin->weight;
        }
        else if (tempSet_begin + 2 == tempSet_end)
        {
            parent->left = new treeNode(nullptr, nullptr, tempSet_begin->ch, tempSet_begin->weight);
            parent->right = new treeNode(nullptr, nullptr, (tempSet_end - 1)->ch, tempSet_begin->weight);
        }
        else
        {
            vector<treeNode>::iterator tempOptimize = Optimize_split(tempSet_begin, tempSet_end);
            treeNode *nodeLeft = new treeNode;
            treeNode *nodeRight = new treeNode;
            parent->left = nodeLeft;
            parent->right = nodeRight;
            SFtreeCreate(nodeLeft, tempSet_begin, tempOptimize);
            SFtreeCreate(nodeRight, tempOptimize, tempSet_end);
        }
    }
    void SFtreeTraverse(treeNode *root, string &code) //遍历H树（对输出code的操作并不美观hh）
    {
        string tempCodeL = code;
        string tempCodeR = code;
        tempCodeL += '0';
        tempCodeR += '1';
        if (root->isLeaf())
            cout << root->ch << "  " << code << endl;
        else
        {
            SFtreeTraverse(root->left, tempCodeL);
            SFtreeTraverse(root->right, tempCodeR);
        }
    }
};
class encode_decode
{
public:
    static string run_lengthEncode(string);
    static string run_lengthDecode(string);

    //SF func
    static void shannon_fanoEncode(string);
    static bool nodeCmp(treeNode t1, treeNode t2) { return t1.weight > t2.weight; }
    //Huffman
    static void HuffmanEncode(string);
    //LZW func
    static string LZWEncode(string);
    static string LZWDecode(string);
    //Arithmatic func
    static double arithmeticEncode(string);
    static string arithmeticDecode(double, map<char, range>);
};
//run_lengthCode 编码------三位一组
string encode_decode::run_lengthEncode(string raw_str)
{
    char c;
    string res;              //结果
    if (raw_str.size() <= 1) //如果原字符串太短
        return raw_str;
    else
    {
        res = raw_str[0];
        unsigned count = 1;
        for (unsigned i = 1; i < raw_str.size(); i++) //编码
        {
            c = raw_str[i];
            if (c == res[res.size() - 1] && count == 99)
            {
                res += to_string(99);
                res += c;
                count = 1;
            }
            else if (c == res[res.size() - 1])
                count++;
            else
            {
                if (count > 9)
                    res += to_string(count);
                else
                    res += (to_string(0) + to_string(count));
                res += c;
                count = 1;
            }
        }
        if (count > 9) //结尾处理
            res += to_string(count);
        else
            res += (to_string(0) + to_string(count));
    }
    if (res.size() % 3 == 0)
        return res;
    else
        return "encode error";
}
//run_lengthCode 解码
string encode_decode::run_lengthDecode(string code)
{
    string ori;
    unsigned count = 0;
    for (unsigned i = 0; i < code.size(); i += 3)
    {
        char c = code[i];
        count = ((code[i + 1] - '0') * 10) + (code[i + 2] - '0');
        for (; count != 0; count--)
            ori += c;
    }
    return ori;
}
//shannon_fanoCode 编码
void encode_decode::shannon_fanoEncode(string raw_str)
{
    //统计字符并排序
    map<char, int> count;
    for (auto &i : raw_str)
        count[i]++;
    SFTree sftree(count);
    sftree.SFtreeCreate(sftree.head, sftree.nodeSet.begin(), sftree.nodeSet.end());
    string str = " ";
    sftree.SFtreeTraverse(sftree.head, str);

    /*vector<pair<char, double>> charVec;
    for (map<char,int>::iterator cur = count.begin(); cur != count.end(); cur++)
    {
        charVec.push_back(pair<char, double>(cur->first, (cur->second)/size));
    }
    sort(charVec.begin(), charVec.end(), encode_decode::pairCmp);
    */
}
//Huffman 编码
void encode_decode::HuffmanEncode(string raw_str)
{
    //统计字符
    map<char, int> count;
    for (auto &i : raw_str)
        count[i]++;
    //构造Huffman tree
    HuffmanTree Htree(count);
    //当待生成的节点大于1时
    while (Htree.nodeSet.size() > 1)
    {
        treeNode *tempLeft = new treeNode((Htree.nodeSet.end() - 1)->left, (Htree.nodeSet.end() - 1)->right, (Htree.nodeSet.end() - 1)->ch, (Htree.nodeSet.end() - 1)->weight);
        treeNode *tempRight = new treeNode((Htree.nodeSet.end() - 2)->left, (Htree.nodeSet.end() - 2)->right, (Htree.nodeSet.end() - 2)->ch, (Htree.nodeSet.end() - 2)->weight);
        //更新head
        Htree.head = new treeNode(tempLeft, tempRight, '\0', (Htree.nodeSet.end() - 1)->weight + (Htree.nodeSet.end() - 2)->weight);
        Htree.nodeSet.pop_back(); //弹出已编码的节点
        Htree.nodeSet.pop_back();
        Htree.nodeSet.push_back(*Htree.head); //推入新生成节点
        sort(Htree.nodeSet.begin(), Htree.nodeSet.end(), HuffmanTree::treeNodeCmp);
    }
    //遍历树并输出结果
    string str = " ";
    Htree.HtreeTraverse(Htree.head, str);
}
//LZW 编码------ASCII为初始字典
string encode_decode::LZWEncode(string raw_str)
{
    vector<sigleCode_3digits> code;
    map<string, int> dic;
    //default dictionary
    string temp = "t";
    for (int i = 0; i < 128; i++)
    {
        temp[0] = (char)i;
        dic[temp] = i;
    }
    string p = "\0";
    char c;
    //encode
    for (auto &i : raw_str) //对于string的每个字符
    {
        c = i;
        string tempStr = p + c;
        map<string, int>::iterator itrF = dic.find(tempStr);
        if (itrF != dic.end()) //找到了
            p = tempStr;
        else //没找到
        {
            code.push_back(sigleCode_3digits(dic[p])); //储存编码
            dic[tempStr] = dic.size();
            p = c;
        }
    }
    code.push_back(sigleCode_3digits(dic[p])); //结尾处理
    string outputCode;
    for (auto &i : code)
    {
        outputCode += i.sigleCode_to_String();
    }
    return outputCode;
}
//LZW 解码
string encode_decode::LZWDecode(string oriCode)
{
    //default dictionary
    map<int, string> revdic;
    for (int i = 0; i < 128; i++)
    {
        revdic[i] = (char)i;
    }
    //转储在vector中
    vector<sigleCode_3digits> codeSave;
    for (unsigned i = 0; i < oriCode.size(); i += 3)
    {
        codeSave.push_back(sigleCode_3digits((oriCode[i] - '0') * 100 + (oriCode[i + 1] - '0') * 10 + oriCode[i + 2] - '0'));
    }
    //解码
    string res = "\0";
    int pW, cW;
    cW = codeSave[0].init;
    res += revdic[cW];
    for (unsigned i = 1; i < codeSave.size(); i++)
    {
        pW = cW;
        cW = codeSave[i].init;
        map<int, string>::iterator itr = revdic.find(cW);
        if (itr != revdic.end()) //找到了
        {
            res += itr->second;
            revdic[revdic.size()] = revdic[pW] + revdic[cW][0];
        }
        else
        {
            revdic[revdic.size()] = revdic[pW] + revdic[pW][0];
            res += revdic[revdic.size() - 1];
        }
    }
    return res;
}
//arithmetic 编码------编码较少字段，因为精度问题还未解决
double encode_decode::arithmeticEncode(string raw_str)
{
    //计数
    map<char, int> count;
    for (auto &i : raw_str)
        count[i]++;
    //绘制概率区域表
    map<char, range> p_table;
    double lowlevel = 0.0, highlevel = 0.0;
    int charNum = raw_str.size();
    for (auto &i : count)
    {
        lowlevel = highlevel;
        highlevel = lowlevel + i.second / (double)charNum;
        p_table[i.first] = range(lowlevel, highlevel);
    }
    //开始编码
    long double lowRange = 0.0, highRange = 1.0;
    for (auto &i : raw_str)
    {
        long double delta = highRange - lowRange;
        highRange = lowRange + delta * p_table[i].range_high;
        lowRange = lowRange + delta * p_table[i].range_low;
    }
    return (highRange + lowRange) / 2;
}
//arithmatic 解码
string encode_decode::arithmeticDecode(double code, map<char, range> p_table)
{
    double low = 0.0, high = 1.0, delta = 1.0;
    string str = "";
    char t = '\0';
    while (t != '#')
    {
        for (auto &i : p_table)
        {
            if (code > (low + delta * i.second.range_low) && code < (low + delta * i.second.range_high))
            {
                str += i.first;
                high = low + delta * i.second.range_high;
                low = low + delta * i.second.range_low;
                delta = high - low;
                t = i.first;
                break;
            }
        }
    }
    return str;
}
