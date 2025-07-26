#include "huffmantree.h"
#include <queue>

// 构建哈夫曼树的函数
Node* buildHuffmanTree(std::vector<Node>& nodes)
{
    if (nodes.empty())
        return nullptr;

    // 1. 创建优先队列（最小堆）
    auto cmp = [](Node* left, Node* right) {
        return left->freq > right->freq; // 注意是>，构造最小堆
    };

    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> minHeap(cmp);

    // 2. 将所有节点指针加入堆
    for (auto& node : nodes)
        minHeap.push(new Node(node.val, node.freq));

    // 3. 构建哈夫曼树
    while (minHeap.size() > 1) {
        // 取出两个最小频率的节点
        Node* left = minHeap.top();
        minHeap.pop();

        Node* right = minHeap.top();
        minHeap.pop();

        // 创建新内部节点（字符用'\0'表示）
        Node* internal = new Node('\0', left->freq + right->freq);
        internal->left = left;
        internal->right = right;

        minHeap.push(internal);
    }

    // 4. 返回根节点
    return minHeap.empty() ? nullptr : minHeap.top();
}

// 释放哈夫曼树内存
void deleteTree(Node* root)
{
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

// 递归生成编码
void generateCodes (Node* node, std::string code, std::map<char, std::string> &huffmanCodes)
{
    if (!node)
        return;

    // 叶子节点存储编码
    if (!node->left && !node->right) {
        if (node->val != '\0') { // 确保是有效字符节点
            huffmanCodes[node->val] = code;
        }
        return;
    }

    // 左子树编码追加"0"，右子树追加"1"
    generateCodes(node->left, code + "0", huffmanCodes);
    generateCodes(node->right, code + "1", huffmanCodes);
};

// 递归生成哈夫曼编码
std::map<char, std::string> generateHuffmanCodes(Node* root, std::map<char, std::string> &huffmanCodes)
{
    if (!root)
        return huffmanCodes;

    generateCodes(root, "", huffmanCodes);
    return huffmanCodes;
}
