#include <iostream>
#include "DoublyLinkedList.h"
#include <cstring>

using namespace std;

DoublyLinkedList::DoublyLinkedList()
{
	head = nullptr;
	tail = nullptr;
	nd_size = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
	clear();
}

int DoublyLinkedList::size()
{
	return nd_size;
}

bool DoublyLinkedList::empty()
{
	return head == nullptr;
}

void DoublyLinkedList::clear()
{
	if (head == nullptr)
		return;

	while (head->next != nullptr)
	{
		head = head->next;
		delete head->prev;
	}

	delete head;

	head = nullptr;
	tail = nullptr;
	nd_size = 0;
}

void DoublyLinkedList::push_back(const ListNode &nd)
{
	nd_size += 1;

	if (head == nullptr)
	{
		head = new ListNode(nd.data);
		tail = head;
		return;
	}

	tail->next = new ListNode(nd.data);
	tail->next->prev = tail;
	tail = tail->next;
}

void DoublyLinkedList::push_front(const ListNode &nd)
{
	ListNode *node = new ListNode(nd.data);

	nd_size += 1;

	if (head == nullptr)
	{
		head = node;
		tail = head;
		return;
	}

	head->prev = node;
	node->next = head;
	head = node;
}

void DoublyLinkedList::pop_front()
{
	ListNode *node;

	if (head == nullptr)
		return;

	nd_size -= 1;

	if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		return;
	}

	head = head->next;
	delete head->prev;
	head->prev = nullptr;
}

void DoublyLinkedList::pop_back()
{
	if (tail == nullptr)
		return;

	nd_size -= 1;

	if (tail->prev == nullptr)
	{
		delete tail;
		tail = nullptr;
		head = nullptr;
		return;
	}

	tail = tail->prev;
	delete tail->next;
	tail->next = nullptr;
}

void DoublyLinkedList::insert_ord(const ListNode &nd)
{
	ListNode *curr, *node = new ListNode(nd.data);

	if (head == nullptr || strcmp(nd.data, head->data) <= 0 )
	{
		push_front(*node);
		return;
	}

	curr = head->next;

	while (curr != nullptr)
	{
		if (strcmp(curr->data, nd.data) >= 0)
		{
			node->next = curr;
			node->prev = curr->prev;
			curr->prev->next = node;
			curr->prev = node;
			return;
		}

		curr = curr->next;
	}

	push_back(*node);
}

void DoublyLinkedList::sort()
{
	DoublyLinkedList *dl;

	if (this->head == this->tail)
		return;

	dl = new DoublyLinkedList();

	while (this->head != nullptr)
	{
		dl->insert_ord(this->head->data);
		this->pop_front();
	}

	this->operator=(*dl);
	delete dl;
}

bool DoublyLinkedList::insert_after(char *dat, const ListNode &nd)
{
	ListNode *curr = head, *node;

	if (head == nullptr)
		return false;
	
	while (curr->next != nullptr)
	{
		if (strcmp(curr->data, dat) == 0)
		{
			node = new ListNode(nd.data);
			node->prev = curr;
			node->next = curr->next;
			curr->next->prev = node;
			curr->next = node;
			return true;
		}

		curr = curr->next;
	}

	if (strcmp(tail->data, dat) == 0)
	{
		push_back(*(new ListNode(nd.data)));
		return true;
	}

	return false;
}

void DoublyLinkedList::operator=(const DoublyLinkedList &dl)
{
	ListNode *source = dl.head;

	if (this == &dl)
		return;

	this->clear();

	while (source != nullptr)
	{
		this->push_back(*(new ListNode(source->data)));
		source = source->next;
	}
}

void DoublyLinkedList::merge(DoublyLinkedList &dl)
{
	if (this == &dl)
		return;

	while (dl.head != nullptr)
	{
		this->push_back(*(new ListNode(dl.head->data)));
		dl.pop_front();
	}

	this->sort();
}

void DoublyLinkedList::erase(char *dat)
{
	ListNode *curr, *buff;

	if (head == nullptr)
		return;

	while (strcmp(dat, head->data) == 0)
	{
		pop_front();
		if (head == nullptr) return;
	}

	curr = head->next;

	while (curr->next != nullptr)
	{
		if (strcmp(dat, curr->data) == 0)
		{
			buff = curr->next;
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			delete curr;
			curr = buff;
			continue;
		}

		curr = curr->next;
	}

	if (strcmp(dat, tail->data) == 0)
		pop_back();
}

void DoublyLinkedList::unique()
{
	ListNode *curr = head, *buff;

	if (nd_size <= 1)
		return;

	while (curr->next != nullptr)
	{
		if (strcmp(curr->data, curr->next->data) == 0)
		{
			buff = curr->next->next;
			delete curr->next;
			curr->next = buff;
			if (buff != nullptr) buff->prev = curr;
			continue;
		}

		curr = curr->next;
	}
}

void DoublyLinkedList::assign(DoublyLinkedList &dl, int first, int last)
{
	int i;
	ListNode *curr = dl.head, *buff;

	if (first < 0 || last > dl.nd_size - 1)
		return;

	for (i = 0; i < first; i++)
		curr = curr->next;

	for (; i <= last; i++)
	{
		this->push_back(*(new ListNode(curr->data)));
		if (curr == dl.head)
		{
			curr = curr->next;
			dl.pop_front();
			continue;
		}
		else if (curr == dl.tail)
		{
			dl.pop_back();
			return;
		}
		
		buff = curr->next;
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		delete curr;
		curr = buff;
	}
}

void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl)
{
	ListNode *buff = this->head, *tl = this->tail, *curr = dl.head;
	int i;

	if (where < 0 || where - 1 > this->nd_size || this == &dl)
		return;

	this->tail = nullptr;

	for (i = 0; i < where; i++)
	{
		this->tail = buff;
		buff = buff->next;
	}

	if (this->tail == nullptr)
		this->head = nullptr;

	while (curr != nullptr)
	{
		this->push_back(*(new ListNode(curr->data)));
		curr = curr->next;
	}

	this->tail->next = buff;
	if (buff != nullptr) buff->prev = this->tail;
	this->tail = tl;
}

void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl, int first, int last)
{
	ListNode *buff = this->head, *tl = this->tail, *curr = dl.head;
	int i;

	if (where < 0 || where - 1 > this->nd_size || first < 0 || last - 1 > dl.nd_size || this == &dl)
		return;

	this->tail = nullptr;

	for (i = 0; i < where; i++)
	{
		this->tail = buff;
		buff = buff->next;
	}

	if (this->tail == nullptr)
		this->head = nullptr;

	for (i = 0; i < first; i++)
		curr = curr->next;

	while (curr != nullptr && i <= last)
	{
		this->push_back(*(new ListNode(curr->data)));
		curr = curr->next;
		i++;
	}

	this->tail->next = buff;
	if (buff != nullptr) buff->prev = this->tail;
	this->tail = tl;
}

void DoublyLinkedList::print()
{
	int i = 0;
	ListNode *curr;

	if (head == nullptr)
	{
		std::cout << "List is empty" << std::endl;
		return;
	}

	for (curr = head; curr != nullptr; curr = curr->next)
	{
		std::cout << "[" << i++ << "] " << curr->data << std::endl;
	}
}

void DoublyLinkedList::print_bkw()
{
	int i = nd_size - 1;
	ListNode *curr;

	if (tail == nullptr)
	{
		std::cout << "List is empty" << std::endl;
		return;
	}

	for (curr = tail; curr != nullptr; curr = curr->prev)
	{
		std::cout << "[" << i-- << "] " << curr->data << std::endl;
	}
}