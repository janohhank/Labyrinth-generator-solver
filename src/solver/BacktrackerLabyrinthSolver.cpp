#include "../inc/solver/BacktrackerLabyrinthSolver.h"

namespace labyrinth{

BacktrackerLabyrinthSolver::BacktrackerLabyrinthSolver(){
	//Intentionally NOOP.
}

BacktrackerLabyrinthSolver::~BacktrackerLabyrinthSolver(){
	//Intentionally NOOP.
}

void BacktrackerLabyrinthSolver::solveLabyrinth(const std::unique_ptr<Labyrinth>& labyrinth){
	std::vector<std::pair<unsigned int, unsigned int>> visitedCoordinates = {};
	solveLabyrinthWithBacktracking(
		labyrinth,
		labyrinth->getEntranceCoordinates(),
		visitedCoordinates
	);
}

void BacktrackerLabyrinthSolver::solveLabyrinthWithBacktracking(
	const std::unique_ptr<Labyrinth>& labyrinth,
	const std::pair<unsigned int, unsigned int>& coordinate,
	std::vector<std::pair<unsigned int, unsigned int>>& visitedCoordinates
){
	visitedCoordinates.emplace_back(coordinate);

	labyrinth->addLabyrinthPathElement(visitedCoordinates.back(), LabyrinthPathType::GOOD_PATH);

	const auto&& filedType = labyrinth->getLabyrinthField(coordinate).getFieldType();
	switch(filedType){
		case LabyrinthFieldType::PATH:
			solveLabyrinthWithBacktracking(
				labyrinth,
				getNextCoordinate(labyrinth, visitedCoordinates),
				visitedCoordinates
			);
		break;
		case LabyrinthFieldType::ENTRANCE:
			solveLabyrinthWithBacktracking(
				labyrinth,
				getNextCoordinate(labyrinth, visitedCoordinates),
				visitedCoordinates
			);
		break;
		case LabyrinthFieldType::EXIT:
			//The labyrinth solved!
			return;
		break;
		default:
			throw std::logic_error("Unhandled switch case!");
		break;
	}
}

std::pair<unsigned int, unsigned int> BacktrackerLabyrinthSolver::getNextCoordinate(
	const std::unique_ptr<Labyrinth>& labyrinth,
	std::vector<std::pair<unsigned int, unsigned int>>& visitedCoordinates
){
	std::set<DirectionType> possibleDirections = getPossibleDirections(labyrinth, visitedCoordinates.back());
	while(!possibleDirections.empty()){
		std::set<DirectionType>::iterator direction;
		if(RANDOM_DIRECTION_CHOOSE){
			//TODO
		}else{
			direction = possibleDirections.begin();
		}

		const std::pair<unsigned int, unsigned int> candidate =
			getCandidatePositionAccordingToDirection(
				visitedCoordinates.back(),
				*direction
			)
		;

		try{
			const auto&& fieldType = labyrinth->getLabyrinthField(candidate).getFieldType();
			const auto&& pathType = labyrinth->getLabyrinthPathType(candidate);
			if(
				(fieldType == LabyrinthFieldType::EXIT || fieldType == LabyrinthFieldType::PATH)
				&& pathType == LabyrinthPathType::UNKNOWN
			){
				return candidate;
			}else{
				possibleDirections.erase(direction);
			}
		}catch(NoSuchLabyrinthCoordinatesExcpetion nslce){
			possibleDirections.erase(direction);
			continue;
		}
	}

	labyrinth->addLabyrinthPathElement(visitedCoordinates.back(), LabyrinthPathType::WRONG_WAY);

	for(
		std::vector<std::pair<unsigned int, unsigned int>>::reverse_iterator iterator = visitedCoordinates.rbegin();
		iterator != visitedCoordinates.rend();
		++iterator
	){
		if(labyrinth->getLabyrinthPathType(*iterator) != LabyrinthPathType::WRONG_WAY){
			return *iterator;
		}
	}

	throw std::logic_error("The labyrinth has no solution!");
}

std::pair<unsigned int, unsigned int> BacktrackerLabyrinthSolver::getCandidatePositionAccordingToDirection(
	const std::pair<unsigned int, unsigned int>& coordinate,
	const DirectionType& directionType
) const{
	switch(directionType){
		case DirectionType::UP:
			return {coordinate.first - 1, coordinate.second};
		break;
		case DirectionType::DOWN:
			return {coordinate.first + 1, coordinate.second};
		break;
		case DirectionType::LEFT:
			return {coordinate.first, coordinate.second - 1};
		break;
		case DirectionType::RIGHT:
			return {coordinate.first, coordinate.second + 1};
		break;
		default:
			throw std::logic_error("Unhandled switch case!");
		break;
	}
}

std::set<DirectionType> BacktrackerLabyrinthSolver::getPossibleDirections(
	const std::unique_ptr<Labyrinth>& labyrinth,
	const std::pair<unsigned int, unsigned int>& coordinate
) const{
	std::set<DirectionType> result = {DirectionType::UP, DirectionType::DOWN, DirectionType::LEFT, DirectionType::RIGHT};

	const auto&& walls = labyrinth->getLabyrinthField(coordinate).getSorruendedWalls();
	for(const auto& wall : walls){
		switch(wall){
			case DirectionType::UP:
				result.erase(DirectionType::UP);
			break;
			case DirectionType::DOWN:
				result.erase(DirectionType::DOWN);
			break;
			case DirectionType::LEFT:
				result.erase(DirectionType::LEFT);
			break;
			case DirectionType::RIGHT:
				result.erase(DirectionType::RIGHT);
			break;
			default:
				throw std::logic_error("Unhandled switch case!");
			break;
		}
	}

	return result;
}

}
