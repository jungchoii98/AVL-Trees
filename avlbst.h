#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "rotateBST.h"
#include <cmath>

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
	// Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they 
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int mHeight;

};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent)
    , mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
    return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public rotateBST<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    void remove(const Key& key);

private:
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
    void insertHelper(AVLNode<Key, Value>* z);
    void updateAll(AVLNode<Key, Value>* node);
    void updateSingle(AVLNode<Key, Value>* thing);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/


template<typename Key, typename Value>
void AVLTree<Key, Value>::updateAll(AVLNode<Key, Value>* thing){
    while(thing != NULL)
    {
        if(thing->getLeft() != NULL && thing->getRight() != NULL)
        {
            if(thing->getLeft()->getHeight() > thing->getRight()->getHeight())
            {
                thing->setHeight(thing->getLeft()->getHeight()+1);
            }
            else if(thing->getLeft()->getHeight() < thing->getRight()->getHeight())
            {
                thing->setHeight(thing->getRight()->getHeight()+1);
            }
            else
            {
                thing->setHeight(thing->getLeft()->getHeight()+1);
            }
        }
        else if(thing->getLeft() != NULL && thing->getRight() == NULL)
        {
            thing->setHeight(thing->getLeft()->getHeight()+1);
        }
        else if(thing->getRight() != NULL && thing->getLeft() == NULL)
        {
            thing->setHeight(thing->getRight()->getHeight()+1);
        }
        thing = thing->getParent();
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::updateSingle(AVLNode<Key, Value>* thing){
    if(thing->getLeft() != NULL && thing->getRight() != NULL)
    {
        //choose the child of greater height or if equal choose either
        if(thing->getLeft()->getHeight() > thing->getRight()->getHeight())
        {
            thing->setHeight(thing->getLeft()->getHeight()+1);
        }
        else if(thing->getLeft()->getHeight() < thing->getRight()->getHeight())
        {
            thing->setHeight(thing->getRight()->getHeight()+1);
        }
        else
        {
            thing->setHeight(thing->getLeft()->getHeight()+1);
        }
    }
    else if(thing->getLeft() != NULL && thing->getRight() == NULL)
    {
        thing->setHeight(thing->getLeft()->getHeight()+1);
    }
    else if(thing->getRight() != NULL && thing->getLeft() == NULL)
    {
        thing->setHeight(thing->getRight()->getHeight()+1);
    }
    else
    {
        thing->setHeight(1);
    }
}

//helper function for insert
template<typename Key, typename Value>
void AVLTree<Key, Value>::insertHelper(AVLNode<Key, Value>* z){
    //exit if already balanced
    if(this->isBalanced())
    {
        return;
    }
    AVLNode<Key, Value>* y;
    AVLNode<Key, Value>* x;
    //get the y
    if(z->getLeft() != NULL && z->getRight() != NULL)
    {
        if(z->getLeft()->getHeight() > z->getRight()->getHeight())
        {
            y = z->getLeft();
        }
        else
        {
            y = z->getRight();
        }
    }
    else if(z->getLeft() != NULL && z->getRight() == NULL)
    {
        y = z->getLeft();
    }
    else if(z->getRight() != NULL && z->getLeft() == NULL)
    {
        y = z->getRight();
    }
    //gets the x
    if(y->getLeft() != NULL && y->getRight() != NULL)
    {
        if(y->getLeft()->getHeight() > y->getRight()->getHeight())
        {
            x = y->getLeft();
        }
        else if(y->getRight()->getHeight() > y->getLeft()->getHeight())
        {
            x = y->getRight();
        }
        else if(y->getLeft()->getHeight() == y->getRight()->getHeight())
        {
            if(z->getLeft() == y) x = y->getLeft();
            else if(z->getRight() == y) x = y->getRight();
        }
    }
    else if(y->getLeft() != NULL && y->getRight() == NULL)
    {
        x = y->getLeft();
    }
    else if(y->getRight() != NULL && y->getLeft() == NULL)
    {
        x = y->getRight();
    }
    //bool flag for if its zig zig or zig zag
    bool zigzig = true;
    //balances zig zig going left
    if(z->getLeft() == y && y->getLeft() == x)
    {
        this->rightRotate(z);
        zigzig = true;
    }
    //balances zig zig going right
    else if(z->getRight() == y && y->getRight() == x)
    {
        this->leftRotate(z);
        zigzig = true;
    }
    //balances zig zag going left
    else if(z->getLeft() == y && y->getRight() == x)
    {
        this->leftRotate(y);
        updateAll(y);
        this->rightRotate(z);
        updateAll(x);
        zigzig = false;
    }
    //balances zig zag going right
    else if(z->getRight() == y && y->getLeft() == x)
    {
        this->rightRotate(y);
        updateAll(y);
        this->leftRotate(z);
        updateAll(x);
        zigzig = false;
    }
    if(zigzig)
    {
        //sets the new heights for z in a zig zig
        updateSingle(z);
        //sets the new heights for y
        updateSingle(y);
        //update heights of all the parents
        AVLNode<Key, Value>* thing = y->getParent();
        updateAll(thing);
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    // TODO
    
    //if there is an empty tree
    if(this->mRoot == NULL)
    {
        this->mRoot = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        dynamic_cast<AVLNode<Key, Value>*>(this->mRoot)->setHeight(1);
        this->mRoot->setLeft(NULL);
        this->mRoot->setRight(NULL);
        return;
    }
    else
    {
        AVLNode<Key, Value>* current;
        AVLNode<Key, Value>* parent = dynamic_cast<AVLNode<Key, Value>*>(this->mRoot);
        if(keyValuePair.first < parent->getKey())
        {
            current = parent->getLeft();
        }   
        else if(keyValuePair.first > parent->getKey())
        {
            current = parent->getRight();
        }
        else
        {
            parent->setValue(keyValuePair.second);
            return;
        }
        while(current != NULL)
        {
            if(current->getKey() == keyValuePair.first)
            {
                current->setValue(keyValuePair.second);
                return;
            }
            else if(keyValuePair.first < current->getKey())
            {
                parent = current;
                current = current->getLeft();
            }
            else if(keyValuePair.first > current->getKey())
            {
                parent = current;
                current = current->getRight();
            }
        }
        if(keyValuePair.first < parent->getKey())
        {
            parent->setLeft(new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, parent));
            parent->getLeft()->setHeight(parent->getLeft()->getHeight()+1);
        }
        else if(keyValuePair.first > parent->getKey())
        {
            parent->setRight(new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, parent));
            parent->getRight()->setHeight(parent->getRight()->getHeight()+1);
        }
        AVLNode<Key, Value>* place = parent;
        updateAll(parent);
        while(this->isBalanced() == false)
        {
            //increments the height of the tree
            AVLNode<Key, Value>* thenode = NULL;
            parent = place;
            while(parent != NULL)
            {
                //parent->setHeight(parent->getHeight()+1);
                if(thenode != NULL){}
                else
                {
                    if(parent->getLeft() != NULL && parent->getRight() != NULL)
                    {
                        if(abs(parent->getLeft()->getHeight() - parent->getRight()->getHeight()) >= 2)
                        {
                            thenode = parent;
                        }
                    }
                    else if(parent->getLeft() != NULL && parent->getRight() == NULL)
                    {
                        if(parent->getLeft()->getHeight() >= 2)
                        {
                            thenode = parent;
                        }
                    }
                    else if(parent->getRight() != NULL && parent->getLeft() == NULL)
                    {
                        if(parent->getRight()->getHeight() >= 2)
                        {
                            thenode = parent;
                        }
                    }
                }
                parent = parent->getParent();
            }
            if(thenode != NULL)
            {
                insertHelper(thenode);
            }
        }
        return;
    }
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
   // TODO
    //root is null
    if(this->mRoot == NULL)
    {
        return;
    }
    //if you are removing just the root node
    if(this->mRoot->getLeft() == NULL && this->mRoot->getRight() == NULL)
    {
        
        this->mRoot->setLeft(NULL);
        this->mRoot->setRight(NULL);
        this->mRoot->setParent(NULL);
        delete this->mRoot;
        this->mRoot = NULL;
        return;
    }
    //if the key does not exist
    if(!this->internalFind(key))
    {
        return;
    }
    //if the key does exist
    else
    {
        AVLNode<Key, Value>* predecessorPar = NULL;
        AVLNode<Key, Value>* deleted = dynamic_cast<AVLNode<Key, Value>*>(this->internalFind(key));
        //if the removed node is a leaf
        if(deleted->getRight() == NULL && deleted->getLeft() == NULL)
        {
            AVLNode<Key, Value>* temp = deleted->getParent();
            if(temp->getRight() == deleted)
            {
                temp->setRight(NULL);
                delete deleted;
            }
            else if(temp->getLeft() == deleted)
            {
                temp->setLeft(NULL);
                delete deleted;
            }
            deleted = NULL;
            if(!this->isBalanced())
            {
                predecessorPar = temp;
            }
        }
        //if it is an internal node
        else
        {
            //if it has a single child
            //if the single child is on right
            AVLNode<Key, Value>* parent = deleted->getParent();
            if(deleted->getRight() != NULL && deleted->getLeft() == NULL)
            {
                //if the removed node is the root node
                if(deleted == this->mRoot)
                {
                    this->mRoot = this->mRoot->getRight();
                    this->mRoot->setParent(NULL);
                    delete deleted;
                    deleted = NULL;
                }
                //if the removed node is not the root node
                else
                {
                    AVLNode<Key, Value>* child = deleted->getRight();
                    child->setParent(parent);
                    if(parent->getLeft() == deleted)
                    {
                        parent->setLeft(child);
                    }
                    else
                    {
                        parent->setRight(child);
                    }
                    delete deleted;
                    deleted = NULL;
                }
                if(!this->isBalanced())
                {
                    predecessorPar = parent;
                }
            }
            //if the single child is on the left
            else if(deleted->getRight() == NULL && deleted->getLeft() != NULL)
            {
                //if the removed node is the root node
                if(deleted == this->mRoot)
                {
                    this->mRoot = this->mRoot->getLeft();
                    this->mRoot->setParent(NULL);
                    delete deleted;
                    deleted = NULL;
                }
                //if the removed node is not the root node
                else
                {
                    AVLNode<Key, Value>* child = deleted->getLeft();
                    child->setParent(parent);
                    if(parent->getLeft() == deleted)
                    {
                        parent->setLeft(child);
                    }
                    else
                    {
                        parent->setRight(child);
                    }
                    delete deleted;
                    deleted = NULL;
                }
                if(!this->isBalanced())
                {
                    predecessorPar = parent;
                }
            }
            //if it has two children
            else if(deleted->getRight() != NULL && deleted->getLeft() != NULL)
            {
                //set the predecessor 
                AVLNode<Key, Value>* predecessor = deleted;
                if(predecessor->getLeft() != NULL) predecessor = predecessor->getLeft();
                while(predecessor->getRight() != NULL)
                {
                    predecessor = predecessor->getRight();
                }
                //if the predecessor's parent is the removed node and root node
                if(predecessor->getParent() == deleted && predecessor->getParent() == this->mRoot)
                {
                    AVLNode<Key, Value>* temp = dynamic_cast<AVLNode<Key, Value>*>(this->mRoot->getRight());
                    predecessor->setRight(temp);
                    temp->setParent(predecessor);
                    predecessor->setParent(NULL);
                    delete this->mRoot;
                    this->mRoot = predecessor;
                    deleted = NULL;
                }
                //if the predecessor's parent is the removed node but not the root node
                else if(predecessor->getParent() == deleted)
                {
                    //if the removed node is a right child
                    if(parent->getRight() == deleted)
                    {
                        parent->setRight(predecessor);
                        predecessor->setParent(parent);
                        if(deleted->getRight() != NULL)
                        {
                            deleted->getRight()->setParent(predecessor);
                            predecessor->setRight(deleted->getRight());
                        }
                        delete deleted;
                        deleted = NULL;
                    }
                    //if the removed node is a left child
                    else
                    {
                        parent->setLeft(predecessor);
                        predecessor->setParent(parent);
                        if(deleted->getRight() != NULL)
                        {
                            deleted->getRight()->setParent(predecessor);
                            predecessor->setRight(deleted->getRight());
                        }
                        delete deleted;
                        deleted = NULL;
                    }
                }
                //if the predecessor's parent is not the removed node
                else
                {
                    //if the removed node is the root node
                    if(deleted == this->mRoot)
                    {
                        AVLNode<Key, Value>* temp = predecessor->getParent();
                        //if predecessor has a left child
                        if(predecessor->getLeft() != NULL)
                        {
                            predecessor->getLeft()->setParent(temp);
                            temp->setRight(predecessor->getLeft());
                        }
                        //if predecessor does not have a left child
                        else
                        {
                            temp->setRight(NULL);
                        }
                        predecessor->setRight(this->mRoot->getRight());
                        predecessor->setLeft(this->mRoot->getLeft());
                        this->mRoot->getRight()->setParent(predecessor);
                        this->mRoot->getLeft()->setParent(predecessor);
                        this->mRoot = predecessor;
                        predecessor->setParent(NULL);
                        delete deleted;
                        deleted = NULL;
                    }
                    //if the removed node is a right child
                    else if(parent->getRight() == deleted)
                    {
                        parent->setRight(predecessor);
                        if(predecessor->getLeft() != NULL)
                        {
                            predecessor->getParent()->setRight(predecessor->getLeft());
                            predecessor->getLeft()->setParent(predecessor->getParent());
                        }
                        else
                        {
                            predecessor->getParent()->setRight(NULL);
                        }
                        deleted->getLeft()->setParent(predecessor);
                        if(deleted->getRight() != NULL)
                        {
                            deleted->getRight()->setParent(predecessor);
                            predecessor->setRight(deleted->getRight());
                        }
                        else
                        {
                            predecessor->setRight(NULL);
                        }
                        predecessor->setLeft(deleted->getLeft());
                        predecessor->setParent(parent);
                        delete deleted;
                        deleted = NULL;
                    }
                    //if the removed node is a left child
                    else
                    {
                        parent->setLeft(predecessor);
                        if(predecessor->getLeft() != NULL)
                        {
                            predecessor->getParent()->setRight(predecessor->getLeft());
                            predecessor->getLeft()->setParent(predecessor->getParent());
                        }
                        else
                        {
                            predecessor->getParent()->setRight(NULL);
                        }
                        deleted->getLeft()->setParent(predecessor);
                        if(deleted->getRight() != NULL)
                        {
                            deleted->getRight()->setParent(predecessor);
                            predecessor->setRight(deleted->getRight());
                        }
                        else
                        {
                            predecessor->setRight(NULL);
                        }
                        predecessor->setLeft(deleted->getLeft());
                        predecessor->setParent(parent);
                        delete deleted;
                        deleted = NULL;
                    }
                }
                if(!this->isBalanced())
                {
                    predecessorPar = predecessor;
                }
            }
        }
        //keep balancing until it is balanced
        while(!this->isBalanced())
        {
            if(predecessorPar != NULL)
            {
                insertHelper(predecessorPar);
            }
            if(predecessorPar == dynamic_cast<AVLNode<Key, Value>*>(this->mRoot))
            {
            }
            else
            {
                predecessorPar = predecessorPar->getParent();
            }
        }
    }
    return;
}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
