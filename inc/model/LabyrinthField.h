#pragma once

// Labyrinth project includes.
#include "LabyrinthFieldType.h"
#include "../utility/DirectionType.h"

// STL includes.
#include <set>

namespace labyrinth{

/**
** Labyrinth field representation. This fields are simple squares.
** Includes the field type and the sorruended walls (in four directions).
**
** @author Kisházi "janohhank" János
**/
class LabyrinthField final{
	private:
		/*
		* This field concrete type.
		* The default type is PATH.
		*/
		LabyrinthFieldType fieldType;

		/*
		* The sorruended walls, the direction type denotes the location of the wall.
		* The default state is - all sides.
		*/
		std::set<DirectionType> walls;
	public:
		/**
		** Constructs a new default instance.
		**/
		LabyrinthField();

		/**
		** Simple NOOP destructor.
		**/
		~LabyrinthField();
		/**
		** Gives the field type.
		** @return the field type.
		**/
		LabyrinthFieldType getFieldType() const;

		/**
		** Gives the walls in the current field.
		** @return the set of walls, the direction type denotes the location of the wall.
		**/
		std::set<DirectionType> getSorruendedWalls() const;

		/**
		** Sets the current field new type.
		** @param labyrinthFieldType, the new field type.
		**/
		void setFieldType(const LabyrinthFieldType& labyrinthFieldType);

		/**
		** Removes a selected wall.
		** @param direction, the selected wall in this direction.
		**/
		void removeWall(const DirectionType& direction);

		/**
		** Examines a field walls.
		** @return true if the field has walls all sides, otherwise false.
		**/
		bool isDeadEnd() const;
};

}