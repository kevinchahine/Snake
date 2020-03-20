#pragma once

#include <iostream>
#include <array>

#include "SnakeBoard.h"

class Position : public std::array<SnakeBoard::index, 2>
{
public:
	SnakeBoard::index row() const;
	void row(const SnakeBoard::index& row);
	
	SnakeBoard::index col() const;
	void col(const SnakeBoard::index& col);

};

