#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<Key, Value>& getItem() const;
	std::pair<Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Key& getKey();
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);

protected:
	std::pair<Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{
}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the key.
*/
template<typename Key, typename Value>
Key& Node<Key, Value>::getKey()
{
	return mItem.first;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
  		virtual void insert(const std::pair<Key, Value>& keyValuePair); //TODO
        virtual void remove(const Key& key); //TODO
  		void clear(); //TODO
  		void print() const;
  		bool isBalanced() const; //TODO

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<Key,Value>& operator*() const;
				std::pair<Key,Value>* operator->() const;

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;

				friend class BinarySearchTree<Key, Value>;
		};

	public:
		iterator begin() const;
		iterator end() const;
		iterator find(const Key& key) const;

		

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	private:
		int isBalancedHelper(Node<Key, Value>* mynode, bool& bal) const;

	protected:
		Node<Key, Value>* mRoot;

	public:
		void print() {this->printRoot(this->mRoot);}

};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const
{
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	// TODO
	mRoot = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	// TODO
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	// TODO
	//if the tree is empty
	if(mRoot == NULL)
	{
		mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		mRoot->setLeft(NULL);
		mRoot->setRight(NULL);
		return;
	}
	//if its not empty
	else
	{
		Node<Key, Value>* current;
		Node<Key, Value>* parent = mRoot;
		//create a parent and current
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
		//compare the key with each node
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
		//create a new node
		if(keyValuePair.first < parent->getKey())
		{
			parent->setLeft(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent));
		}
		else if(keyValuePair.first > parent->getKey())
		{
			parent->setRight(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent));
		}
		return;
	}

}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	// TODO
	//root is null
	if(mRoot == NULL)
	{
		return;
	}
	//if you are removing just the root node
	if(mRoot->getLeft() == NULL && mRoot->getRight() == NULL)
	{
		
		mRoot->setLeft(NULL);
		mRoot->setRight(NULL);
		mRoot->setParent(NULL);
		delete mRoot;
		mRoot = NULL;
		return;
	}
	//if the key does not exist
	if(!internalFind(key))
	{
		return;
	}
	//if the key does exist
	else
	{
		Node<Key, Value>* deleted = internalFind(key);
		//if the removed node is a leaf
		if(deleted->getRight() == NULL && deleted->getLeft() == NULL)
		{
			Node<Key, Value>* temp = deleted->getParent();
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
			return;
		}
		//if it is an internal node
		else
		{
			//if it has a single child
			//if the single child is on right
			Node<Key, Value>* parent = deleted->getParent();
			if(deleted->getRight() != NULL && deleted->getLeft() == NULL)
			{
				//if the removed node is the root node
				if(deleted == mRoot)
				{
					mRoot = mRoot->getRight();
					mRoot->setParent(NULL);
					delete deleted;
					deleted = NULL;
				}
				//if the removed node is not the root node
				else
				{
					Node<Key, Value>* child = deleted->getRight();
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
			}
			//if the single child is on the left
			else if(deleted->getRight() == NULL && deleted->getLeft() != NULL)
			{
				//if the removed node is the root node
				if(deleted == mRoot)
				{
					mRoot = mRoot->getLeft();
					mRoot->setParent(NULL);
					delete deleted;
					deleted = NULL;
				}
				//if the removed node is not the root node
				else
				{
					Node<Key, Value>* child = deleted->getLeft();
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
			}
			//if it has two children
			else if(deleted->getRight() != NULL && deleted->getLeft() != NULL)
			{
				//set the predecessor 
				Node<Key, Value>* predecessor = deleted;
				if(predecessor->getLeft() != NULL) predecessor = predecessor->getLeft();
				while(predecessor->getRight() != NULL)
				{
					predecessor = predecessor->getRight();
				}
				//if the predecessor's parent is the removed node and root node
				if(predecessor->getParent() == deleted && predecessor->getParent() == mRoot)
				{
					Node<Key, Value>* temp = mRoot->getRight();
					predecessor->setRight(temp);
					temp->setParent(predecessor);
					predecessor->setParent(NULL);
					delete mRoot;
					mRoot = predecessor;
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
					return;
				}
				//if the predecessor's parent is not the removed node
				else
				{
					//if the removed node is the root node
                    if(deleted == mRoot)
                    {
                        Node<Key, Value>* temp = predecessor->getParent();
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
                        predecessor->setRight(mRoot->getRight());
                        predecessor->setLeft(mRoot->getLeft());
                        mRoot->getRight()->setParent(predecessor);
                        mRoot->getLeft()->setParent(predecessor);
                        mRoot = predecessor;
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
			}
		}
	}
}

//helper function to clear
template<typename Key, typename Value>
void clearTree(Node<Key, Value>* position)
{
	if(position->getLeft()) clearTree(position->getLeft());
	if(position->getRight()) clearTree(position->getRight());
	delete position;
}

/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	// TODO
	if(mRoot == NULL)
	{
		return;
	}
	Node<Key, Value>* current = mRoot;
	clearTree(current);
	mRoot = NULL;

}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	// TODO
	Node<Key, Value>* current = mRoot;
	while(current->getLeft() != NULL)
	{
		current = current->getLeft();
	}
	return current;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	// TODO
	if(mRoot == NULL)
	{
		return mRoot;
	}
	Node<Key, Value>* current = mRoot;
	if(current->getKey() == key)
	{
		return current;
	}
	//searches through the tree
	while(current != NULL)
	{
		if(current->getKey() == key)
		{
			return current;
		}
		else if(key < current->getKey())
		{
			current = current->getLeft();
		}
		else if(key > current->getKey())
		{
			current = current->getRight();
		}
	}
	return NULL;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value>* mynode, bool& bal) const{
	//if the tree is empty
	if(mynode == NULL)
	{
		return 0;
	}
	//if single node tree
	if(!mynode->getLeft() && !mynode->getRight())
	{
		return 0;
	}
	//recursively find the heights of each subtree
	int left = 0, right = 0;
	if(mynode->getLeft() != NULL)
	{
		left = isBalancedHelper(mynode->getLeft(), bal) + 1;
	}
	if(mynode->getRight() != NULL)
	{
		right = isBalancedHelper(mynode->getRight(), bal) + 1;
	}
	if(abs(right-left) > 1)
	{
		bal = false;
	}
	if(left > right)
	{
		return left;
	}
	else
	{
		return right;
	}
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const{
	bool bal = true;
	Node<Key, Value>* mynode = this->mRoot;
	isBalancedHelper(mynode, bal);

	return bal;
}



/**
 * Lastly, we are providing you with a print function, BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->mRoot)

   It will print up to 5 levels of the tree rooted at the passed node, in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
