#include "../inc/model/LabyrinthField.h"

namespace labyrinth{

LabyrinthField::LabyrinthField(){
	walls = {
		DirectionType::UP,
		DirectionType::DOWN,
		DirectionType::LEFT,
		DirectionType::RIGHT
	};

	fieldType = LabyrinthFieldType::PATH;
}

LabyrinthField::~LabyrinthField(){
	//Intentionally NOOP.
}

LabyrinthFieldType LabyrinthField::getFieldType() const{
	return fieldType;
}

std::set<DirectionType> LabyrinthField::getSorruendedWalls() const{
	return walls;
}

void LabyrinthField::setFieldType(const LabyrinthFieldType& labyrinthFieldType){
	fieldType = labyrinthFieldType;
}

void LabyrinthField::removeWall(const DirectionType& direction){
	walls.erase(direction);
}

bool LabyrinthField::isDeadEnd() const{
	if(walls.size() == 4){
		return true;
	}else{
		return false;
	}
} 

}
