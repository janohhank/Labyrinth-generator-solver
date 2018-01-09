#pragma once

//Labyrinth project includes.
#include "../model/Labyrinth.h"

//STD includes.
#include <memory>

namespace labyrinth{

/**
** Abstract base class of labyrinth solvers.
**
** @author Kisházi "janohhank" János
**/
class LabyrinthSolverBase{
	public:
		/**
		** Simple no-args constructor.
		**/
		LabyrinthSolverBase();

		/**
		** Simple virtal NOOP destructor.
		**/
		virtual ~LabyrinthSolverBase();

		/**
		** Solves the labyrinth and the created solution map added to the given labyrinth instance.
		** @param labyrinth, the given labyrinth instance.
		**/
		virtual void solveLabyrinth(const std::unique_ptr<Labyrinth>& labyrinth) = 0;
};

}
