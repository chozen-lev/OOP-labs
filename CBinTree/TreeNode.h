#pragma once

#include <string>

class TreeNode
{
public:
    TreeNode();
    TreeNode(int, std::string, std::string);
    ~TreeNode() {};

    int getTrainNumber() const;
    std::string getDestination() const;
    std::string getDepartureTime() const;

    TreeNode* getLeft() const;
    TreeNode* getRight() const;

    void setTrainNumber(int);
    void setDestination(std::string);
    void setDepartureTime(std::string);

    void setLeft(TreeNode *);
    void setRight(TreeNode *);

    void print();

private:
    int m_TrainNumber;
    std::string m_Destination;
    std::string m_DepartureTime;

    TreeNode* m_Left;
    TreeNode* m_Right;
};