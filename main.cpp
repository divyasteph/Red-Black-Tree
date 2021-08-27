//#include "/home/dvya/Documents/ADSLAb/src/RBT.cpp"
#include "/home/dvya/Documents/RED/include/RBT.h"
#include <iostream>

using namespace std;
int main()
{
    RBT* tree= new RBT();

    tree->insert(72);
    tree->insert(63);
    tree->insert(25);
    tree->insert(41);
    tree->insert(53);
    tree->insert(23);
    tree->insert(12);

    cout << "______RED BLACK TREE______\n\n";
    cout << "Inoder Traversal\n";
    tree->inorder();

    cout << "\n\nLevel Order Traversal\n";
    tree->levelorder();

    cout<< "\n\nSearch Results...";
    tree->Search(53);

    cout<< "\n\nDeleting Key: 41\n";
    tree->Delete(41);

    cout<<"\nUpdated Tree...\n";
    cout << "Inoder Traversal\n";
    tree->inorder();


    cout << "\n\nLevel Order Traversal\n";
    tree->levelorder();


std::cout<<std::endl;
}

