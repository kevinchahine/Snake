#pragma once

#include <iostream>
#include <array>

#include <boost/multi_array.hpp>

using index = boost::multi_array<uint8_t, 2>::index;

class Position : public std::array<index, 2>
{
public:
	Position();
	Position(int row, int col);
	Position(const Position&) = default;
	Position(Position&&) noexcept = default;
	~Position() noexcept = default;

	Position& operator=(const Position&) = default;
	Position& operator=(Position&&) noexcept = default;

	Position upOne() const;
	Position downOne() const;
	Position leftOne() const;
	Position rightOne() const;

	index row() const;
	void row(const index& row);
	
	index col() const;
	void col(const index& col);


};

