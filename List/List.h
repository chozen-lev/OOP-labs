#pragma once

#include "Iterator.h"
#include <iostream>

using namespace std;

template <class T>
class List {
    
    struct ListNode
    {
        T data;
        ListNode *next;
        ListNode() {
            next = NULL;
        }
        ListNode( T dat ) {
            data = dat;
        }
        void Print() {
            cout << data << endl;
        }
    };
    
public:
    typedef ListNode node_type;
    typedef _iterator<node_type> iterator;
    // constructors/destructors
    List();
    ~List();
    
    // methods
    iterator begin();                           // Returns an iterator addressing the first element 
    iterator end();                             // Returns an iterator that addresses the location succeeding the last element

    void load(const char *filename);
    void clear();                               // Erases all the elements of a list.
    bool empty() const;                         // Tests if a list is empty.
    iterator find(const node_type &val);        // Returns an iterator to the first element in a list that match a specified value.
    void pop_front();                           // Deletes the element at the beginning of a list.
    void push_front(const node_type &val);      // Adds an element to the beginning of a list.
    void remove(const node_type val);           // Erases first element in a list that match a specified value.
        
    int size() const;                           // Returns the number of elements in a list.

    void splice(iterator _Where, List<T>& _Right);  // Removes element from //the target list and inserts it in first
                                                    // position of the argument list.
    void Print() const;                         // Dumps list into the screen
    bool rename(iterator it, string name);
    void remove(int value, List<T>& _Trash);

private:
    int _size;
    node_type *head;
    iterator *first, *last;
};

template <class T>
List<T>::List() {
    head = NULL;
    first = new iterator(NULL);
    last = new iterator(NULL);
    _size = 0;
}

template <class T>
List<T>::~List() {
    clear();
}

template <class T>
typename List<T>::iterator List<T>::begin() {
    return *first;
}

template <class T>
typename List<T>::iterator List<T>::end() {
    return *last;
}

template<class T>
void List<T>::load(const char * filename)
{
    T data;
    ifstream stream(filename);
    if (!stream)
    {
        cout << "Couldn't open file\n";
        exit(1);
    }
    while (!stream.eof())
    {
        stream >> data;
        push_front(node_type(data));
    }
    stream.close();
}

template<class T>
void List<T>::clear()
{
    node_type *temp = head;
    while (head) {
        head = head->next;
        delete temp;
        temp = head;
    }
    delete first;
    first = new iterator(NULL);
}

template<class T>
bool List<T>::empty() const {
    return _size == 0;
}

template <class T>
typename List<T>::iterator List<T>::find(const node_type& val)
{
    node_type *temp = head;
    while (temp && temp->data != val.data) {
        temp = temp->next;
    }
    return *new iterator(temp);
}

template <class T>
void List<T>::pop_front()
{
    node_type *temp;
    if (head)
    {
        ++(*first);
        temp = head;
        head = head->next;
        delete temp;
        _size--;
        delete first;
        first = new iterator(head);
    }
}

template<class T>
void List<T>::push_front(const node_type& val)
{
    node_type *temp = new node_type(val);
    temp->next = head;
    head = temp; 
    _size++;
    delete first;
    first = new iterator(head);
}

template<class T>
void List<T>::remove(const node_type val)
{
    node_type *temp = head, *tmp;
    if (!head) return;
    if (val.data == head->data)
    {
        pop_front();
        return;
    }
    while (temp->next && val.data != temp->next->data) {
        temp = temp->next;
    }
    if (temp->next)
    {
        tmp = temp->next;
        temp->next = temp->next->next;
        delete tmp;
        _size--;
    }
}

template<class T>
int List<T>::size() const {
    return _size;
}

template<class T>
void List<T>::splice(iterator _Where, List<T>& _Right)
{
    _Right.push_front(*_Where);
    this->remove(*_Where);
}

template <class T>
void List<T>::Print() const
{
    node_type *temp = head;
    while (temp)
    {
        temp->Print();
        temp = temp->next;
    }
    cout << endl;
}

template<class T>
bool List<T>::rename(iterator it, string name)
{
    if (!name.empty())
    {
        (*it).data.rename(name);
        return true;
    }
    return false;
}

template <class T>
void List<T>::remove(int value, List<T>& _Trash)
{
    node_type *temp = head, *del;
    while(temp) {
        if (temp->data < value){
            del = temp;
            temp = temp->next;
            splice(del, _Trash);
        }
        else temp = temp->next;
    }
}