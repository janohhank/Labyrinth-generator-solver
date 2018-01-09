#pragma once

//STD includes.
#include <string>
#include <stdexcept>

namespace labyrinth{

/**
** Exception class throwed when the labyrinth has no such element, at the given coordinates.
**
** @author Kisházi "janohhank" János
**/
class NoSuchLabyrinthCoordinatesExcpetion : public std::logic_error{
	public:
		explicit NoSuchLabyrinthCoordinatesExcpetion(
			const std::string& message
		) : std::logic_error(message)
		{
			//Intentionally NOOP.
		}

		explicit NoSuchLabyrinthCoordinatesExcpetion(
			const char* message
		) : std::logic_error(message)
		{
			//Intentionally NOOP.
		}
};

}
