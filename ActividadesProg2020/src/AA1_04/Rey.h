#pragma once
#include "Pieza.h"
class Rey :
    public Pieza
{
public:
    void move() {
        std::cout << "Muevo Rey" << std::endl;
    };

};

