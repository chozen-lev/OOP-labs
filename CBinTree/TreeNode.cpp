#include "TreeNode.h"
#include <iostream>

TreeNode::TreeNode()
{
    m_TrainNumber = 0;
    m_Destination = "";
    m_DepartureTime = "";

    m_Left = nullptr;
    m_Right = nullptr;
}

TreeNode::TreeNode(int number, std::string dest, std::string time)
{
    m_TrainNumber = number;
    m_Destination = dest;
    m_DepartureTime = time;

    m_Left = nullptr;
    m_Right = nullptr;
}

int TreeNode::getTrainNumber() const {
    return m_TrainNumber;
}

std::string TreeNode::getDestination() const {
    return m_Destination;
}

std::string TreeNode::getDepartureTime() const {
    return m_DepartureTime;
}

TreeNode* TreeNode::getLeft() const {
    return m_Left;
}

TreeNode* TreeNode::getRight() const {
    return m_Right;
}

void TreeNode::setTrainNumber(int number) {
    m_TrainNumber = number;
}

void TreeNode::setDestination(std::string dest) {
    m_Destination = dest;
}

void TreeNode::setDepartureTime(std::string time) {
    m_DepartureTime = time;
}

void TreeNode::setLeft(TreeNode *node) {
    m_Left = node;
}

void TreeNode::setRight(TreeNode *node) {
    m_Right = node;
}

void TreeNode::print()
{
    std::cout << "Train number: " << m_TrainNumber << std::endl;
    std::cout << "Destination: " << m_Destination << std::endl;
    std::cout << "Arrival time: " << m_DepartureTime << std::endl << std::endl;
}