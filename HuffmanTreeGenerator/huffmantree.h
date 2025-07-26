#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <vector>
#include <map>
#include <string>

struct Node{
    char val; // 字符的值
    int freq; // 字符的频率
    Node *left, *right;

    Node(char data, int freq)
        : val(data), freq(freq), left(nullptr), right(nullptr) {}
};

// 用于优先队列的比较函数
struct compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

Node* buildHuffmanTree(std::vector<Node>& nodes);
std::map<char, std::string> generateHuffmanCodes(Node* root, std::map<char, std::string> &huffmanCodes);
void deleteTree(Node* root);
#endif // HUFFMANTREE_H
