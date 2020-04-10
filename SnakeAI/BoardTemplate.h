#pragma once

#include <iostream>
#include <sstream>

#include <boost/multi_array.hpp>

template<typename T>
class BoardTemplate : public boost::multi_array<T, 2>
{
public:
	BoardTemplate(const size_t& nRows, const size_t& nCols);

	void print(std::ostream& os = std::cout) const;

	size_t getNRows() const;
	size_t getNCols() const;
	size_t getNCells() const;
};

template<typename T>
BoardTemplate<T>::BoardTemplate(
	const size_t& nRows, 
	const size_t& nCols) :
	boost::multi_array<T, 2>(boost::extents[nRows][nCols])
{
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
