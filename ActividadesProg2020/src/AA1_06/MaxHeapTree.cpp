#include "MaxHeapTree.h"
MaxHeapTree::MaxHeapTree()
{
}


MaxHeapTree::~MaxHeapTree()
{
}

BT::Node* MaxHeapTree::Search(int key)
{
	return nullptr;
}

bool MaxHeapTree::Exist(int key)
{
	return false;
}

int MaxHeapTree::Max()
{
    if (root != nullptr)
        return root->key;
    else

        return 0;
}

