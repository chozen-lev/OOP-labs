#include <fstream>

using namespace std;

class References
{
public:
    References();
    ~References() {};

    void rename(string);

    friend ostream& operator<<(ostream& stream, References &obj);
    friend istream& operator>>(istream& stream, References &obj);

    bool operator==(const References &obj) const;
    bool operator!=(const References &obj) const;
    bool operator<(int value) const;
private:
    char *word;
    int *pages; // pages numbers
    int _size;  // number of pages
};