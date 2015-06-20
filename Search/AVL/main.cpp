#include "AVLTree.h"
using namespace std;

int main() {
    AVLTree<int, int> tree;
    int choice = 1, key, value;
    while (1) {
        cout << "1. Insert 2. Delete 3. Update 4. Search 5. Print 0. Exit" << endl;
        cin >> choice;
        if (!choice)
            break;
        switch(choice) {
            case 1:
                cout << "Input key and value: " << endl;
                cin >> key >> value;
                tree.insert(key, value);
                break;
            case 2:
                cout << "Input key: " << endl;
                cin >> key;
                tree.pop(key);
                break;
            case 3:
                cout << "Input key and value: " << endl;
                cin >> key >> value;
                tree.update(key, value);
                break;
            case 4:
                cout << "Input key: " << endl;
                cin >> key;
                if (tree.hasKey(key))
                    cout << "At: " << tree.search(key) << endl;
                else
                    cout << "Not exist." << endl;
                break;
            case 5:
                tree.print();
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }
    return 0;
}