#include "RedBlackTree.h"
int main(){
    RBTree<int, int> tree;
    int choice = 1, key, value;
    while (1) {
        cout << "1. Insert 2. Delete 3. Search 4. Print 0. Exit" << endl;
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
                cout << "Input the key you want to delete:" << endl;
                cin >> key;
                if (tree.contains(key))
                    tree.pop(key);
               	else
               		cout << "Error: No such key." << endl;
                break;
            case 3:
                cout << "Input the key you want to search for: " << endl;
                cin >> key;
                try {
                    int &val = tree.get(key);
                    cout << "Value: " << val << endl;
                } catch(bool) {
                    cout << "Error: No such key." << endl;
                }
                break;
            case 4:
                tree.print();
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }
    return 0;
}