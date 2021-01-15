#include <iostream>
#include "BT.h"

int main() {

	BT t1;

	t1.PreOrder();

	int x = t1.GetNumberNodesI();

	int x1 = t1.Height();

	bool e = t1.Exist(5);

	BT::Node* tmp = t1.Search(12);

	t1.PostOrderI();

	std::vector<int> v;

	t1.GetNPair(v);

	return 0;

};
