#pragma once

#include <iostream>

namespace snake
{
	class Move
	{
		
		//friend std::ostream& operator<<(std::ostream& os, const Move& move);

	protected:
		// 'w' - up
		// 'a' - left
		// 'd' - right
		// 's' - down
		// 'z' - undo
		// 'n' - no move (don't move)
		// 'x' or any other - invalid
		char mMove;
	};
}

