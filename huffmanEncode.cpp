#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;
struct treeNode
{
    treeNode *left;
    treeNode *right;
    char ch;    //此节点储存的待编码字符
    int weight; //字符所占权重（频数）
    treeNode()
    {
        left = right = nullptr;
        ch = '\0';
        weight = 0;
    }
    treeNode(treeNode *l, treeNode *r, char c, int w) : left(l), right(r), ch(c), weight(w) {}
    bool isLeaf() { return !left && !right; }
};

struct HuffmanTree
{
    treeNode* head;
    vector<treeNode> nodeSet;//储存待生成的树节点
    HuffmanTree() {}
    HuffmanTree(map<char,int> weightMap)//以存有字符频数的vector初始化nodeSet
    {
        for(auto & i:weightMap)
        {    
            nodeSet.push_back(treeNode(nullptr,nullptr,i.first, i.second));
            sort(nodeSet.begin(), nodeSet.end(), HuffmanTree::treeNodeCmp);
        }
    }
    void HtreeTraverse(treeNode* root, string& code)//遍历H树（对输出code的操作并不美观hh）
    {
        string tempCodeL = code;
        string tempCodeR = code;
        tempCodeL += '0';
        tempCodeR += '1';
        if (root->isLeaf())
            cout << root->ch << "  " << code<<endl;
        else
        {
            HtreeTraverse(root->left,tempCodeL);
            HtreeTraverse(root->right,tempCodeR);
        }
        
    }
    static bool treeNodeCmp(treeNode t1, treeNode t2) { return t1.weight > t2.weight; }//用于sort算法
};

void HuffmanEncode(string raw_str)
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

int main()
{
    string raw_str;
    cout << "Raw string without space: ";//cin不能直接取得带空格的字符串
    cin >> raw_str;
    HuffmanEncode(raw_str);
    system("pause");
    return 0;
}