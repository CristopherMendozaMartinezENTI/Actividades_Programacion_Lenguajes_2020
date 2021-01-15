#include "MinHeapTree.h"

MinHeapTree::~MinHeapTree()
{
}

BT::Node* MinHeapTree::Search(int key)
{
    return nullptr;
}

bool MinHeapTree::Exist(int key)
{
    return false;
}

int MinHeapTree::Min()
{
    if (root != nullptr)
        return root->key;
    else
        return 0;
}
