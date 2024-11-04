#ifndef _HUFFMANTREE_H
#define _HUFFMANTREE_H
#include <map>
#include <queue>
#include <iostream>
#define DEBUG 0
struct Node
{
    char c;   //字符
    int freq;
    Node *left;
    Node *right;
    Node(char _c, int f, Node* l = nullptr, Node* r = nullptr): c(_c), freq(f), left(l), right(r){}
    bool operator<(const Node &node) const {return freq > node.freq;} // （小根堆）
};

bool is_leaf(const Node *n) {return n->left == nullptr && n->right == nullptr;}

class HuffmanTree
{
public:
    std::priority_queue<Node> pq;
    std::map<char, std::string> dict;
    HuffmanTree(std::map<char, int> fmap){    // 传入统计好字符频率的map
        for(auto i : fmap){
            std::cout << "Character: " << i.first << ", Frequency: " << i.second << std::endl;
            Node node(i.first,i.second);
            pq.push(node);                      // 构建优先队列
        }

        while(pq.size() > 1){                   // 构建HuffmanTree
            Node *left = new Node(pq.top());
            pq.pop();
            Node *right = new Node(pq.top());
            pq.pop();
            Node node = Node('?', left->freq + right->freq, left, right);
            pq.push(node);
        }
        
        Node root = pq.top();                   // 构建编码字典
        std::string prefix;
        _traverse_build_dict(&root, prefix);

    }

private:

    void _traverse_build_dict(Node *root, std::string &prefix){     // 深度优先
        std::string ptmp = prefix;

        if(root->left != nullptr){
            prefix += '0';
            if(is_leaf(root->left)){
                dict[root->left->c] = prefix;
            }else{
                _traverse_build_dict(root->left, prefix);
            }
        }

        if(root->right != nullptr){
            prefix = ptmp;
            prefix += '1';
            if(is_leaf(root->right)){
                dict[root->right->c] = prefix;
            }else{
                _traverse_build_dict(root->right, prefix);
            }
        }
    }
};





#endif