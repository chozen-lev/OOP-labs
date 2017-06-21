#include "References.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <cstdlib>

References::References()
{
    word = nullptr;
    pages = nullptr;
    _size = 0;
}

void References::rename(string name)
{
    delete[] word;
    word = new char[name.length() + 1];
    strcpy(word, name.c_str());
}

ostream& operator<<(ostream& stream, References &obj)
{
    stream << obj.word << "\t";

    for (int i = 0; i < ((obj._size > 4) ? 4 : obj._size); i++) {
        cout << obj.pages[i] << " ";
    }

    if (obj._size > 4) {
        cout << ".. ";
    }
    else
    {
        for (int i = 0; i < 4 - obj._size; i++) {
            cout << "   ";
        }
    }
    stream << "\t" << obj._size;
    return stream;
}

istream& operator>>(std::istream& stream, References &obj)
{
    obj.word = nullptr;
    obj.pages = nullptr;
    obj._size = 0;

    string str;
    getline(stream, str, ';');
    obj.word = new char[str.length() + 1];
    strcpy(obj.word, str.c_str());

    int page;
    getline(stream, str);
    istringstream strStream(str);

    while (strStream >> page)
    {
        obj._size += 1;
        obj.pages = (int*)realloc(obj.pages, obj._size * sizeof(int));
        obj.pages[obj._size - 1] = page;
    }

    return stream;
}

bool References::operator==(const References &obj) const{
    return strcmp(word, obj.word) == 0;
}

bool References::operator!=(const References &obj) const{
    return strcmp(word, obj.word) != 0;
}

bool References::operator<(int value) const
{
    return _size < value;
}