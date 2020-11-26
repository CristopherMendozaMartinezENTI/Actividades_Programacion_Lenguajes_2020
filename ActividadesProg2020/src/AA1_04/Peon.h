#pragma once
#include "Pieza.h"
class Peon :
    public Pieza
{
public:
    void move() {
        std::cout << "Muevo Peon" << std::endl;
    };

};

