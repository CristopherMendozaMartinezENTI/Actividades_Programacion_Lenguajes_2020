#pragma once
#include <vector>
#include "Pieza.h"
#include "Tablero.h"
#include "Movimiento.h"
#include "Constants.h"

class Partida
{
public:
	Tablero* tablero;
	Pieza* piezas[K_MAX_PIEZAS];
	std::vector<Movimiento*> *movimientos;
};

