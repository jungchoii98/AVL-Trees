#include "bst.h"
#include <iostream>



template<typename Key, typename Value>
class rotateBST: public BinarySearchTree<Key, Value>{
	public:
		bool sameKeys(const rotateBST<Key, Value>& t2) const;
		void transform(rotateBST& t2) const;

	protected:
		void leftRotate(Node<Key, Value>* r);
		void rightRotate(Node<Key, Value>* r);
		void transformLink(rotateBST& t2, Node<Key, Value>* node) const;
		void finalPart(rotateBST& t2, Node<Key, Value>* node, Node<Key, Value>* comp) const;
};

template<typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r){
	if(r->getRight() == NULL)
	{
		return;
	}
	Node<Key, Value>* child = r->getRight();
	//if rotating on the root node
	if(r == this->mRoot)
	{
		r->setParent(child);
		child->setParent(NULL);
		this->mRoot = child;
		//if the child has a left
		if(child->getLeft() != NULL)
		{
			r->setRight(child->getLeft());
			child->getLeft()->setParent(r);
			child->setLeft(r);
		}
		//if the child does not have a left
		else
		{
			r->setRight(NULL);
			child->setLeft(r);
		}
	}
	//if not rotating on the root node
	else if(r != this->mRoot)
	{
		Node<Key, Value>* parent = r->getParent();
		child->setParent(parent);
		r->setParent(child);
		//if the child has a left
		if(child->getLeft() != NULL)
		{
			r->setRight(child->getLeft());
			child->getLeft()->setParent(r);
			child->setLeft(r);
		}
		//if the child does not have a left
		else
		{
			r->setRight(NULL);
			child->setLeft(r);
		}
		if(parent->getRight() == r)
		{
			parent->setRight(child);
		}
		else
		{
			parent->setLeft(child);
		}
	}
	return;
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r){
	if(r->getLeft() == NULL)
	{
		return;
	}
	Node<Key, Value>* child = r->getLeft();
	//if rotating on the root node
	if(r == this->mRoot)
	{
		r->setParent(child);
		child->setParent(NULL);
		this->mRoot = child;
		//if the child has a right
		if(child->getRight() != NULL)
		{
			r->setLeft(child->getRight());
			child->getRight()->setParent(r);
			child->setRight(r);
		}
		//if the child does not have a right
		else
		{
			r->setLeft(NULL);
			child->setRight(r);
		}
	}
	//if not rotating on the root node
	else if(r != this->mRoot)
	{
		Node<Key, Value>* parent = r->getParent();
		child->setParent(parent);
		r->setParent(child);
		//if the child has a right
		if(child->getRight() != NULL)
		{
			r->setLeft(child->getRight());
			child->getRight()->setParent(r);
			child->setRight(r);
		}
		//if the child does not have a right
		else
		{
			r->setLeft(NULL);
			child->setRight(r);
		}
		if(parent->getRight() == r)
		{
			parent->setRight(child);
		}
		else
		{
			parent->setLeft(child);
		}
		
	}
	return;
}

template<typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST<Key, Value>& t2) const{

	typename BinarySearchTree<Key, Value>::iterator it1;
	typename BinarySearchTree<Key, Value>::iterator it2 = t2.begin();
	//run through the iterator
	for(it1 = this->begin(); it1 != this->end(); ++it1)
	{
		if(it1->first != it2->first)
		{
			return 0;
		}
		++it2;
	}
	return 1;
}

//helper function for making a linked list
template<typename Key, typename Value>
void rotateBST<Key, Value>::transformLink(rotateBST& t2, Node<Key, Value>* node) const{
	if(node == NULL)
	{
		return;
	}
	while(node->getLeft() != NULL)
	{
		t2.rightRotate(node);
		node = node->getParent();
	}
	transformLink(t2, node->getRight());
}

//helper function for last part
template<typename Key, typename Value>
void rotateBST<Key, Value>::finalPart(rotateBST& t2, Node<Key, Value>* node, Node<Key, Value>* comp) const{
	if(!comp) return;
	//skip if they are the same
	if(node->getKey() == comp->getKey())
	{

	}
	else
	{
		//if they are not the same then do the correct rotations
		while(node->getKey() != comp->getKey())
		{
			if(node->getKey() < comp->getKey())
			{
				t2.leftRotate(node);
			}
			else if(node->getKey() > comp->getKey())
			{
				t2.rightRotate(node);
			}
			node = node->getParent();
		}
	}
	//recursive calls
	if(node->getLeft()) finalPart(t2, node->getLeft(), comp->getLeft()); 
	if(node->getRight()) finalPart(t2, node->getRight(), comp->getRight());
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const{
	if(!sameKeys(t2))
	{
		return;
	}
	//make t2 a linked list first
	Node<Key, Value>* current = t2.mRoot;
	transformLink(t2, current);
	// //get root nodes the same
	while(this->mRoot->getKey() != t2.mRoot->getKey())
	{
		current = t2.mRoot;
		t2.leftRotate(current);
		current = current->getParent();
	}
	//recursively adjust t2
	current = t2.mRoot;
	Node<Key, Value>* comp = this->mRoot;
	finalPart(t2, current, comp);
}