#include "BinTree.h"
#include <iostream>

BinTree::BinTree() {
    m_Root = nullptr;
}

void BinTree::addNode(TreeNode *node)
{
    if (m_Root == nullptr)
    {
        m_Root = node;
        return;
    }

    TreeNode* currNode = m_Root;
    TreeNode* parentNode;

    while (currNode != nullptr)
    {
        parentNode = currNode;

        if (node->getTrainNumber() < currNode->getTrainNumber())
        {
            currNode = currNode->getLeft();

            if (currNode == nullptr) {
                parentNode->setLeft(node);
            }
        }
        else if (node->getTrainNumber() > currNode->getTrainNumber())
        {
            currNode = currNode->getRight();

            if (currNode == nullptr) {
                parentNode->setRight(node);
            }
        }
        else
        {
            currNode->setDestination(node->getDestination());
            currNode->setDepartureTime(node->getDepartureTime());
            break;
        }
    }
}

bool BinTree::removeNode(int number)
{
    if (m_Root == nullptr) {
        return false;
    }

    TreeNode* current = m_Root;
    TreeNode* parent = m_Root;
    while (number != current->getTrainNumber()) {
        parent = current;
        if (number <= current->getTrainNumber()) {
            current = current->getLeft();
        }
        else {
            current = current->getRight();
        }

        if (current == nullptr) {
            return false;
        }
    }

    if (current->getLeft() == nullptr && current->getRight() == nullptr) {
        if (current == m_Root)
        {
            delete m_Root;
            m_Root = nullptr;
        }
        else if (parent->getLeft() == current)
        {
            delete parent->getLeft();
            parent->setLeft(nullptr);
        }
        else
        {
            delete parent->getRight();
            parent->setRight(nullptr);
        }
    }
    else if (current->getLeft() == nullptr)
    {
        TreeNode* temp = current;
        if (current == parent->getRight()) {
            parent->setRight(current->getRight());
        }
        else {
            parent->setLeft(current->getRight());
        }
        delete temp;
    }
    else if (current->getRight() == nullptr)
    {
        TreeNode* temp = current;
        if (current == parent->getRight()) {
            parent->setRight(current->getLeft());
        }
        else {
            parent->setLeft(current->getLeft());
        }
        delete temp;
    }
    else
    {
        TreeNode* temp = findMin(current->getRight());
        int tempNum = temp->getTrainNumber();
        removeNode(temp->getTrainNumber());
        current->setTrainNumber(tempNum);
    }

    return true;
}

void BinTree::print() {
    printNodes(m_Root);
}

void BinTree::print(std::string dest) {
    printNodes(m_Root, dest);
}

void BinTree::printNodes(TreeNode *tree)
{
    if (tree != nullptr)
    {
        printNodes(tree->getLeft());
        tree->print();
        printNodes(tree->getRight());
    }
}

void BinTree::printNodes(TreeNode *tree, std::string dest)
{
    if (tree != nullptr)
    {
        printNodes(tree->getLeft(), dest);
        if (tree->getDestination() == dest) {
            tree->print();
        }
        printNodes(tree->getRight(), dest);
    }
}

TreeNode* BinTree::find(int number)
{
    TreeNode* p = m_Root;
    if (p == nullptr) {
        return nullptr;
    }

    while (p != nullptr)
    {
        if (number == p->getTrainNumber()) {
            return p;
        }
        else if (number < p->getTrainNumber()) {
            p = p->getLeft();
        }
        else {
            p = p->getRight();
        }
    }

    return nullptr;
}

TreeNode* BinTree::findMin(TreeNode *treePtr) {

    TreeNode* p = treePtr;
    while (p->getLeft() != nullptr) {
        p = p->getLeft();
    }

    return p;
}