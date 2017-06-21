#pragma once

#include "TreeNode.h"

class BinTree
{
public:
    BinTree();
    ~BinTree() {};

    void addNode(TreeNode *);
    bool removeNode(int);
    void print();
    void print(std::string);
    TreeNode* find(int);

private:
    TreeNode* m_Root;

    TreeNode* findMin(TreeNode*);
    void printNodes(TreeNode *);
    void printNodes(TreeNode *, std::string);
};