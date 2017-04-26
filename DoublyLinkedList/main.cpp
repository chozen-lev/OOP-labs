#include <iostream>
#include "DoublyLinkedList.h"

int main()
{
	DoublyLinkedList *node = new DoublyLinkedList(), *node2 = new DoublyLinkedList();
	node->push_back(*(new ListNode("1")));
	node->push_back(*(new ListNode("2")));
	node->push_back(*(new ListNode("3")));
	node->print();
	std::cout << "-------------------\n";
	node->push_front(*(new ListNode("0")));
	node->pop_back();
	node->print();
	std::cout << "-------------------\n";
	node->push_back(*(new ListNode("5")));
	node->push_back(*(new ListNode("2")));
	node->push_back(*(new ListNode("0")));
	node->sort();
	node->insert_after("0", *(new ListNode("5")));
	node->print();
	std::cout << "-------------------\n";
	node2->push_back(*(new ListNode("12")));
	node2->push_back(*(new ListNode("22")));
	node2->push_back(*(new ListNode("32")));
	node->print();
	std::cout << "-------------------\n";
	node2->print();
	std::cout << "-------------------\n";
	node->assign(*node2, 0, 0);
	node->print();
	std::cout << "-------------------\n";
	node2->print_bkw();
	std::cout << "-------------------\n";
	node->splice(0, *node2);
	node->print();
	std::cout << "-------------------\n";
	node->sort();
	node->print();
	std::cout << "-------------------\n";
	
	return 0;
}