#pragma once
#include "Block.h"

class Map {
private:
	int grid[GRID];
	int blocks[MAX_BLOCKS];

	std::vector<Block> wall;
};
	