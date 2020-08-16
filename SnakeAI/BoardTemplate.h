#pragma once

#include <iostream>
#include <sstream>

#include <boost/multi_array.hpp>

#include "Snake.h"

template<typename T>
class BoardTemplate : public boost::multi_array<T, 2>
{
public:
	BoardTemplate(const size_t& nRows, const size_t& nCols);

	BoardTemplate(const size_t& nRows, const size_t& nCols, const T& value);

	void print(std::ostream& os = std::cout) const;

	void paste(const Snake& snake);

	size_t getNRows() const;
	size_t getNCols() const;
	size_t getNCells() const;
	bool isInBound(const Position& pos) const;
};

template<typename T>
BoardTemplate<T>::BoardTemplate(
	const size_t& nRows, 
	const size_t& nCols) :
	boost::multi_array<T, 2>(boost::extents[nRows][nCols])
{
}

template<typename T>
BoardTemplate<T>::BoardTemplate(
	const size_t& nRows, 
	const size_t& nCols,
	const T& value) :
	boost::multi_array<T, 2>(boost::extents[nRows][nCols])
{
	const size_t NROWS = this->getNRows();
	const size_t NCOLS = this->getNCols();

	for (size_t row = 0; row < NROWS; row++) {
		for (size_t col = 0; col < NCOLS; col++) {
			(*this)[row][col] = value;
		}
	}
}

template<typename T>
void BoardTemplate<T>::print(std::ostream& os) const
{
	const size_t NROWS = this->getNRows();
	const size_t NCOLS = this->getNCols();

	for (size_t row = 0; row < NROWS; row++) {
		for (size_t col = 0; col < NCOLS; col++) {
			os << (*this)[row][col] << ' ';
		}
		os << '\n';
	}
	os << '\n';
}

template<typename T>
void BoardTemplate<T>::paste(const Snake& snake)
{
	for (const auto& positionOnSnake : snake)
	{
		(*this)(positionOnSnake) = true;
	}
}

template<typename T>
inline size_t BoardTemplate<T>::getNRows() const
{
	return this->shape()[0];
}

template<typename T>
inline size_t BoardTemplate<T>::getNCols() const
{
	return this->shape()[1];
}

template<typename T>
inline size_t BoardTemplate<T>::getNCells() const
{
	return this->num_elements();
}

template<typename T>
bool BoardTemplate<T>::isInBound(const Position& pos) const
{
	const size_t N_ROWS = getNRows();
	const size_t N_COLS = getNCols();

	return
		pos.row() >= 0 && 
		pos.col() >= 0 && 
		pos.row() < N_ROWS &&
		pos.col() < N_COLS;
}
