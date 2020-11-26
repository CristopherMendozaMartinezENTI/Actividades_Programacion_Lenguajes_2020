#pragma once
#include <vector>
#include "Pieza.h"
#include "Tablero.h"
#include "Movimiento.h"

#define K_MAX_PIEZAS 32
#define K_MAX_MOV 10

class Partida
{
public:
	Tablero* tablero;
	Pieza* piezas[K_MAX_PIEZAS];
	std::vector<Movimiento*> movimientos;
};

