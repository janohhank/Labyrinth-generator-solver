#pragma once

//Labyrinth project includes.
#include "LabyrinthSolverBase.h"

//STD includes
#include <vector>

namespace labyrinth{

/**
** Solve labyrinth with backtracnking algorithm.
**
** @author Kisházi "janohhank" János
**/
class BacktrackerLabyrinthSolver final : public LabyrinthSolverBase{
	public:
		/**
		** Constructs a new instance.
		**/
		BacktrackerLabyrinthSolver();

		/**
		** Simple NOOP destructor.
		**/
		~BacktrackerLabyrinthSolver();

		/**
		** {@inheritDoc}
		**/
		void solveLabyrinth(const std::unique_ptr<Labyrinth>& labyrinth) override;
	private:
		/**
		** Solve the labyrinth with backtracking with recursion.
		** @param labyrinth, the given labyrinth.
		** @param coordinate, the starting coordinates.
		** @param visitedCoordinates, the already visited positions.
		**/
		void solveLabyrinthWithBacktracking(
			const std::unique_ptr<Labyrinth>& labyrinth,
			const std::pair<unsigned int, unsigned int>& coordinate,
			std::vector<std::pair<unsigned int, unsigned int>>& visitedCoordinates
		);

		/**
		** Gives the next coordinates in the soltion searching.
		** @param labyrinth, the labyrinth instance.
		** @param visitedCoordinates, the already visited coordinates.
		** @return the choosen next step coordinates.
		**/
		std::pair<unsigned int, unsigned int> getNextCoordinate(
			const std::unique_ptr<Labyrinth>& labyrinth,
			std::vector<std::pair<unsigned int, unsigned int>>& visitedCoordinates
		);

		/**
		** Gives the next coordinate pair, based on the choosed direction.
		** @param coordinate, the current position coordinates.
		** @param directionType, the orientation of the next step.
		** @return the next position coordinates.
		**/
		std::pair<unsigned int, unsigned int> getCandidatePositionAccordingToDirection(
			const std::pair<unsigned int, unsigned int>& coordinate,
			const DirectionType& directionType
		) const;

		/**
		** Gives the possible directions, which are available from the current position.
		** @param labyrinth, the labyrinth instance.
		** @param coordinate, the current position coordinates.
		** @return the possible direction where has no walls from the current location.
		**/
		std::set<DirectionType> getPossibleDirections(
			const std::unique_ptr<Labyrinth>& labyrinth,
			const std::pair<unsigned int, unsigned int>& coordinate
		) const;
};

}