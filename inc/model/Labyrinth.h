#pragma once

// Labyrinth project includes.
#include "LabyrinthField.h"
#include "LabyrinthPathType.h"
#include "NoSuchLabyrinthCoordinatesExcpetion.hpp"

// STL includes.
#include <map>

namespace labyrinth{

/**
** The model of the labyrinth.
** Always an N * M sized rectangle shaped maze. (N=height, M=width)
**
** @author Kisházi "janohhank" János
**/
class Labyrinth final{
	private:
		/*
		* The labyrinth map.
		* The key is the y,x coordiantes of the field (height,width).
		* The value is the field type.
		*/
		std::map<std::pair<unsigned int, unsigned int>, LabyrinthField> labyrinthFieldMap;

		/*
		* The labyrinth solution map.
		* The key is the y,x coordiantes of the field (height,width).
		* The value is the path type.
		*/
		std::map<std::pair<unsigned int, unsigned int>, LabyrinthPathType> labyrinthPathMap;

		/*
		* Labyrinth size parameters.
		*/
		const unsigned int height;
		const unsigned int width;
	public:
		/**
		** Constructs a new instance, and constructs the labyrinth map.
		** @param height, the labyrinth height.
		** @param width, the labyrinth width.
		**/
		Labyrinth(const unsigned int& height, const unsigned int& width);

		/**
		** Simple NOOP destructor.
		**/
		~Labyrinth();

		/**
		** Gives the <code>LabyrinthField</code> of the concrete coordinates.
		** @param coordinates, the map coordinates (y,x - height,width).
		** @return the <code>LabyrinthField</code> instance.
		**/
		LabyrinthField getLabyrinthField(
			const std::pair<unsigned int, unsigned int>& coordinates
		) const;

		/**
		** Gives the <code>LabyrinthPathType</code> of the concrete coordinates.
		** @param coordinates, the map coordinates (y,x - height,width).
		** @return the <code>LabyrinthPathType</code> instance.
		**/
		LabyrinthPathType getLabyrinthPathType(
			const std::pair<unsigned int, unsigned int>& coordinates
		) const;

		/**
		** Gives the entrance field coordinates.
		** @return the coordinates pair of the entrance field (y,x - height,width).
		**/
		std::pair<unsigned int, unsigned int> getEntranceCoordinates() const;

		/**
		** Gives the exit field coordinates.
		** @return the coordinates pair of the exit field (y,x - height,width).
		**/
		std::pair<unsigned int, unsigned int> getExitCoordinates() const;

		/**
		** Add new labyrinth path to the path map.
		** @param coordinate, the coordinates of the new paht element.
		** @param labyrinthPathType, the type of the new path element.
		**/
		void addLabyrinthPathElement(
			const std::pair<unsigned int, unsigned int>& coordinate,
			const LabyrinthPathType& labyrinthPathType
		);

		/**
		** Gives the whole labyrinth field map.
		** @return the labyrinth field map.
		**/
		std::map<std::pair<unsigned int, unsigned int>, LabyrinthField> getLabyrinthFieldMap() const;

		/**
		** Gives the whole labyrinth solution map.
		** @return the labyrinth solution map.
		**/
		std::map<std::pair<unsigned int, unsigned int>, LabyrinthPathType> getLabyrinthPathMap() const;
	private:
		/**
		** Generates a random maze.
		**/
		void generateMaze();

		/**
		** Generates a random maze from a concrete position.
		** @param position, the starting position (y,x - height,width).
		**/
		void generate(
			const std::pair<unsigned int, unsigned int>& position
		);

		/**
		** Sets the labyrinth entrance and exit fields randomly.
		**/
		void setRandomEntranceAndExit();
};

}