#include "ListNode.h"
#include <cstring>

ListNode::ListNode()
{
	prev = nullptr;
	next = nullptr;
	data = nullptr;
}

ListNode::ListNode(char *_data)
{
	prev = nullptr;
	next = nullptr;

	if (_data == nullptr)
	{
		data = nullptr;
		return;
	}

	data = new char[strlen(_data) + 1];
	strcpy(data, _data);
}

ListNode::~ListNode(void)
{
	delete[] data;
}