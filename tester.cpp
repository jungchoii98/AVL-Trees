#include "avlbst.h"
#include <iostream>

using namespace std;

int main() {

AVLTree<int,int>* avl = new AVLTree<int,int>;

cout << "1: Remove from empty tree" << endl;
avl->remove(0);
avl->print();
cout << "Tree is balanced: " << avl->isBalanced() << endl;
cout << "should be an empty tree" << endl;
cout << endl;
cout << endl;
cout << endl;
cout << endl;

cout << "2: Remove root with no children" << endl;
avl->insert(std::pair<int,int> (9,9));

avl->remove(9);
avl->print();
cout << "Tree is balanced: " << avl->isBalanced() << endl;
cout << "should be empty tree" << endl;
cout << endl;
cout << endl;
cout << endl;
cout << endl;

cout << "3: Remove root with left child" << endl;
avl->insert(std::pair<int,int> (9,9));
avl->insert(std::pair<int,int> (1,1)); //new root

avl->remove(9);
avl->print();
cout << "Tree is balanced: " << avl->isBalanced() << endl;
cout << "Root should be 1" << endl;
cout << endl;
cout << endl;
cout << endl;
cout << endl;

cout << "4: Remove root with right child" << endl;

avl->insert(std::pair<int,int> (9,9)); //right child of 1

avl->remove(1);
avl->print();
cout << "Tree is balanced: " << avl->isBalanced() << endl;
cout << "Root should be 9" << endl;
cout << endl;
cout << endl;
cout << endl;
cout << endl;

cout << "5: Remove root with 2 children" << endl;

avl->insert(std::pair<int,int> (8,8)); //LC
avl->insert(std::pair<int,int> (10,10)); //RC

avl->remove(9);
avl->print();
cout << "Tree is balanced: " << avl->isBalanced() << endl;
cout << "root should now be 8" << endl;
cout << endl;
cout << endl;
cout << endl;
cout << endl;

cout << "7: Remove Internal Node with 1 child -> casue L-L rotation" << endl;

avl->insert(std::pair<int,int>(5,5));
avl->insert(std::pair<int,int> (30,30));
avl->insert(std::pair<int,int> (4,4));
avl->insert(std::pair<int,int> (6,6));
avl->insert(std::pair<int,int> (1,1));

avl->remove(10);
avl->print();
cout << "Tree is balanced: " << avl->isBalanced() << endl;

cout << "root should be 5 (6 nodes)" << endl;
cout << endl;
cout << endl;
cout << endl;
cout << endl;


cout << "8: Remove Internal Node with 1 child -> R-R rotation" << endl;
avl->insert(std::pair<int,int>(50,50));

avl->remove(4);
avl->print();
cout << "Tree is balanced: " << avl->isBalanced() << endl;

cout << "new root should be 8 (6 nodes)" << endl;
cout << endl;
cout << endl;
cout << endl;
cout << endl;


cout << "9: Remove Interanl Node with 2 children -> L-L rotation" << endl;
avl->insert(std::pair<int,int> (7,7));

avl->remove(5);

avl->print();
cout << avl->isBalanced() << endl;

cout << "root is still 8, but left child of 8 is 6" << endl;
cout << endl;
cout << endl;
cout << endl;
cout << endl;


cout << "10: Remove Internal Node with 2 children -> R-R rotation" << endl;

avl->insert(std::pair<int,int> (25,25));
avl->insert(std::pair<int,int> (40,40));
avl->insert(std::pair<int,int> (27,27));
avl->insert(std::pair<int,int> (0,0));
avl->insert(std::pair<int,int> (70,70));
avl->insert(std::pair<int,int> (90,90));

avl->remove(30);
avl->print();
cout << "Tree is balanced: " << avl->isBalanced() << endl;

cout << "root is still 8, but right child of 8 is 50" << endl;
cout << endl;
cout << endl;
cout << endl;
cout << endl;

delete avl;

AVLTree<int,int>* yuhyuhyuh = new AVLTree<int,int>;

cout << "11: Remove Internal Node with 1 child -> L-R Rotation" << endl;
yuhyuhyuh->insert(std::pair<int,int>(15,15));
yuhyuhyuh->insert(std::pair<int,int>(10,10));
yuhyuhyuh->insert(std::pair<int,int>(20,20));
yuhyuhyuh->insert(std::pair<int,int>(7,7));
yuhyuhyuh->insert(std::pair<int,int>(11,11));
yuhyuhyuh->insert(std::pair<int,int>(89,89));
yuhyuhyuh->insert(std::pair<int,int>(13,13));

yuhyuhyuh->remove(20);
yuhyuhyuh->print();
cout << "Tree is balanced: " << yuhyuhyuh->isBalanced() << endl;

cout << "root should be 11" << endl;
cout << endl;
cout << endl;
cout << endl;
cout << endl;


cout << "12: Remove Internal Node with 1 child -> R-L Rotation" << endl;
yuhyuhyuh->insert(std::pair<int,int>(14,14));

yuhyuhyuh->remove(10);
yuhyuhyuh->print();
cout << "Tree is balanced: " << yuhyuhyuh->isBalanced() << endl;

cout << "root should be 13" << endl;
cout << endl;
cout << endl;
cout << endl;
cout << endl;

 

delete yuhyuhyuh;

 

cout << "Test Cases made by John Tanner and Asheesh Chopra" << endl;
cout << "Good luck everyone, and remember that AVL trees DO NOT define who you are" << endl;

return 0;
}