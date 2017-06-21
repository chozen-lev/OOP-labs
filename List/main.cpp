#include <iostream>
#include "List.h"
#include "References.h"

int main()
{
    List<References> db;
    List<References> trash;
    List<References>::iterator it;
    int i;

    db.load("base.csv");
    cout << "Base:\n";
    for (it = db.begin(), i = 1; it != db.end(); ++it, ++i) {
        cout << " " << i << ". ";
        (*it).Print();
    }

    cout << "Trash:\n" << "\tnone\n";

    cout << "\nRemove first item:";
    db.splice(db.begin(), trash);

    cout << "\nBase:\n";
    for (it = db.begin(), i = 1; it != db.end(); ++it, ++i) {
        cout << " " << i << ". ";
        (*it).Print();
    }

    cout << "Trash:\n";
    for (it = trash.begin(), i = 1; it != trash.end(); ++it, ++i) {
        cout << " " << i << ". ";
        (*it).Print();
    }

    cout << "\nRename first item in base to \"word\" and restore first element from trash:";
    db.rename(db.begin(), "word");
    trash.splice(trash.begin(), db);

    cout << "\nBase:\n";
    for (it = db.begin(), i = 1; it != db.end(); ++it, ++i) {
        cout << " " << i << ". ";
        (*it).Print();
    }

    cout << "Trash:\n" << "\tnone\n";

    cout << "\nRemove all where size less than 5:";
    db.remove(5, trash);

    cout << "\nBase:\n";
    for (it = db.begin(), i = 1; it != db.end(); ++it, ++i) {
        cout << " " << i << ". ";
        (*it).Print();
    }

    cout << "Trash:\n";
    for (it = trash.begin(), i = 1; it != trash.end(); ++it, ++i) {
        cout << " " << i << ". ";
        (*it).Print();
    }

	return 0;
}
