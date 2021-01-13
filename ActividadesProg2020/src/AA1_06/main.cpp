#include <iostream>
#include "BT.h"

int main() {

	BT t1;

	t1.PreOrder();

	int x = t1.GetNumberNodesI();

	std::vector<int> v;

	t1.GetNPair(v);

	return 0;

};
