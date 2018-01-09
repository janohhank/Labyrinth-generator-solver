#include "../inc/model/Labyrinth.h"

//Labyrinth project includes.
#include "../inc/utility/Utility.hpp"

//STD includes.
#include <stack>
#include <vector>

namespace labyrinth{

Labyrinth::Labyrinth(const unsigned int height, unsigned int width){
	if(height < 2 || width < 2){
		throw std::logic_error("The labyrinth size must be greater then 2x2!");
	}

	//Sets the size parameters.
	this->height = height;
	this->width = width;

	//Initialize the labyrinth maps.
	for(unsigned int y = 0; y < height; ++y){
		for(unsigned int x = 0; x < width; ++x){
			labyrinthFieldMap.emplace(std::make_pair(y,x), LabyrinthField());
			labyrinthPathMap.emplace(std::make_pair(y,x), LabyrinthPathType::UNKNOWN);
		}
	}

	//Sets the entrance and the exit fields.
	setRandomEntranceAndExit();

	//Generate a random maze.
	generateMaze();
}

Labyrinth::~Labyrinth(){
	//Intentionally NOOP.
}

LabyrinthField Labyrinth::getLabyrinthField(
	const std::pair<unsigned int, unsigned int>& coordinates
) const{
	const auto&& field = labyrinthFieldMap.find(coordinates);
	if(field != labyrinthFieldMap.end()){
		return field->second;
	}

	throw NoSuchLabyrinthCoordinatesExcpetion(
		std::string("The labyrinth coordinates doesn't exists.")
		+ " y : " + std::to_string(coordinates.first)
		+ " x : " + std::to_string(coordinates.second)
	);
}

LabyrinthPathType Labyrinth::getLabyrinthPathType(
	const std::pair<unsigned int, unsigned int>& coordinates
) const{
	const auto&& field = labyrinthPathMap.find(coordinates);
	if(field != labyrinthPathMap.end()){
		return field->second;
	}

	throw NoSuchLabyrinthCoordinatesExcpetion(
		std::string("The labyrinth coordinates doesn't exists.")
		+ " y : " + std::to_string(coordinates.first)
		+ " x : " + std::to_string(coordinates.second)
	);
}

std::pair<unsigned int, unsigned int> Labyrinth::getEntranceCoordinates() const{
	for(
		auto iterator = labyrinthFieldMap.cbegin();
		iterator != labyrinthFieldMap.cend();
		++iterator
	){
		if(iterator->second.getFieldType() == LabyrinthFieldType::ENTRANCE){
			return iterator->first;
		}
	}

	throw NoSuchLabyrinthCoordinatesExcpetion(
		"The labyrinth doesn't has entrance field."
	);
}

std::pair<unsigned int, unsigned int> Labyrinth::getExitCoordinates() const{
	for(
		auto iterator = labyrinthFieldMap.cbegin();
		iterator != labyrinthFieldMap.cend();
		++iterator
	){
		if(iterator->second.getFieldType() == LabyrinthFieldType::EXIT){
			return iterator->first;
		}
	}

	throw NoSuchLabyrinthCoordinatesExcpetion(
		"The labyrinth doesn't has exit field."
	);
}

void Labyrinth::addLabyrinthPathElement(
	const std::pair<unsigned int, unsigned int>& coordinate,
	const LabyrinthPathType& labyrinthPathType
){
	labyrinthPathMap.insert_or_assign(coordinate, labyrinthPathType);
}

std::map<std::pair<unsigned int, unsigned int>, LabyrinthField> Labyrinth::getLabyrinthFieldMap() const{
	return labyrinthFieldMap;
}

std::map<std::pair<unsigned int, unsigned int>, LabyrinthPathType> Labyrinth::getLabyrinthPathMap() const{
	return labyrinthPathMap;
}

void Labyrinth::generateMaze(){
	//The generation starts from the entrance coordinates.
	generate(getEntranceCoordinates());
}

void Labyrinth::generate(
	const std::pair<unsigned int, unsigned int>& position
){
	//Already visited cells counter.
	unsigned int visitedFields = 1;
	//Total fields of the maze.
	const unsigned int totalFields = (width) * (height);
	//The possible next directions.
	std::vector<DirectionType> possibleDirections;
	//The visited fields stack.
	std::stack<std::pair<unsigned int, unsigned int>> visitedPositions;
	//Current examined field position.
	std::pair<unsigned int, unsigned int> currentPosition = {position.first, position.second};

	//Main generation loop.
	while(visitedFields < totalFields){
		const unsigned int x = currentPosition.second;
		const unsigned int y = currentPosition.first;

		auto&& currentField = labyrinthFieldMap.find({y, x})->second;

		auto&& leftField = labyrinthFieldMap.find({y, x - 1})->second;
		auto&& downField = labyrinthFieldMap.find({y + 1, x})->second;
		auto&& rightField = labyrinthFieldMap.find({y, x + 1})->second;
		auto&& upField = labyrinthFieldMap.find({y - 1, x})->second;

		//Get possible next directions.
		if(x < width - 1){
			if(rightField.isDeadEnd()){
				possibleDirections.emplace_back(DirectionType::RIGHT);
			}
		}

		if(y < height - 1){
			if(downField.isDeadEnd()){
				possibleDirections.emplace_back(DirectionType::DOWN);
			}
		}

		if(x > 0){
			if(leftField.isDeadEnd()){
				possibleDirections.emplace_back(DirectionType::LEFT);
			}
		}

		if(y > 0){
			if(upField.isDeadEnd()){
				possibleDirections.emplace_back(DirectionType::UP);
			}
		}

		//Choose a random direction and construct the maze.
		if(!possibleDirections.empty()){
			const auto& direction = possibleDirections.at(rand() % possibleDirections.size());

			switch(direction){
				case DirectionType::LEFT:
					currentField.removeWall(DirectionType::LEFT);
					leftField.removeWall(DirectionType::RIGHT);

					currentPosition.second = x - 1;
				break;
				case DirectionType::DOWN:
					currentField.removeWall(DirectionType::DOWN);
					downField.removeWall(DirectionType::UP);

					currentPosition.first = y + 1;
				break;
				case DirectionType::RIGHT:
					currentField.removeWall(DirectionType::RIGHT);
					rightField.removeWall(DirectionType::LEFT);

					currentPosition.second = x + 1;
				break;
				case DirectionType::UP:
					currentField.removeWall(DirectionType::UP);
					upField.removeWall(DirectionType::DOWN);

					currentPosition.first = y - 1;
				break;
				default:
					throw std::logic_error("Unhandled switch case!");
				break;
			}

			visitedPositions.push({y, x});

			++visitedFields;
		}else{
			currentPosition = visitedPositions.top();
			visitedPositions.pop();
		}

		possibleDirections.clear();
	}
}

void Labyrinth::setRandomEntranceAndExit(){
	std::random_device randomDevice;
	std::mt19937 rng(randomDevice());

	std::uniform_int_distribution<unsigned int> uniformDistributionWidth(1, width - 2);
	std::uniform_int_distribution<unsigned int> uniformDistributionHeigth(1, height - 2);

	const auto directions = getRandomDirections();
	switch(*directions.begin()){
		case DirectionType::UP:
			labyrinthFieldMap.find(
				{0, uniformDistributionWidth(rng)}
			)->second.setFieldType(LabyrinthFieldType::ENTRANCE);

			labyrinthFieldMap.find(
				{height - 1, uniformDistributionWidth(rng)}
			)->second.setFieldType(LabyrinthFieldType::EXIT);
		break;
		case DirectionType::DOWN:
			labyrinthFieldMap.find(
				{height - 1, uniformDistributionWidth(rng)}
			)->second.setFieldType(LabyrinthFieldType::ENTRANCE);

			labyrinthFieldMap.find(
				{0, uniformDistributionWidth(rng)}
			)->second.setFieldType(LabyrinthFieldType::EXIT);
		break;
		case DirectionType::LEFT:
			labyrinthFieldMap.find(
				{uniformDistributionHeigth(rng), 0}
			)->second.setFieldType(LabyrinthFieldType::ENTRANCE);

			labyrinthFieldMap.find(
				{uniformDistributionHeigth(rng), width - 1}
			)->second.setFieldType(LabyrinthFieldType::EXIT);
		break;
		case DirectionType::RIGHT:
			labyrinthFieldMap.find(
				{uniformDistributionHeigth(rng), width - 1}
			)->second.setFieldType(LabyrinthFieldType::ENTRANCE);

			labyrinthFieldMap.find(
				{uniformDistributionHeigth(rng), 0}
			)->second.setFieldType(LabyrinthFieldType::EXIT);
		break;
		default:
			throw std::logic_error("Unhandled switch case!");
		break;
	}
}

}
