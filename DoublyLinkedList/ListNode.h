#pragma once

class ListNode {
	char *data;
	ListNode *prev;
	ListNode *next;
public:
	friend class DoublyLinkedList;
	ListNode();							//default constructor
	ListNode(char *_data);
	~ListNode(void);
};
