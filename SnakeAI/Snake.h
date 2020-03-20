#pragma once

#include <iostream>
#include <queue>

#include "Position.h"

/*				
              |-- Head is actually at the BACK of the queue
		      v 
	  T T T T H
	  ^
	  |-- Tail is at the FRONT of the queue

	  T T T T H
	    T T T T H	<-- Push back the new head and pop the old tail
*/
class Snake : public std::queue<Position>
{
public:
	const Position& peekHead() const;
	
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

};

