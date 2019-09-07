#pragma once

// Labyrinth project includes.
#include "../model/LabyrinthField.h"
#include "../model/LabyrinthPathType.h"

// OpenGL includes.
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

// STL includes.
#include <map>
#include <mutex>

namespace labyrinth{

/**
** Renderers the labyrinth map, and the solution wia OpenGL GLUT.
**
** @author Kisházi "janohhank" János
**/
class LabyrinthRenderer final{
	private:
		/*
		* The stored labyrinth map.
		* The key is the y,x coordiantes of the field (height,width).
		* The value is the field type.
		*/
		std::map<std::pair<unsigned int, unsigned int>, LabyrinthField> labyrinthFieldMap;

		/*
		* The stored labyrinth solution map.
		* The key is the y,x coordiantes of the field (height,width).
		* The value is the path type.
		*/
		std::map<std::pair<unsigned int, unsigned int>, LabyrinthPathType> labyrinthPathMap;

		/*
		* Receive/draw mutex for locking.
		*/
		std::mutex dataMutex;
	public:
		/**
		** Constructs a new instance.
		**/
		LabyrinthRenderer();

		/**
		** Simple NOOP destructor.
		**/
		~LabyrinthRenderer();

		/**
		** Receives the labyrinth map and corresponding solution map.
		** @param labyrinthFieldMap, the received labyrint map.
		** @param labyrinthPathMap, the received labyrint solution map.
		**/
		void receiveLabyrinthMapAndSolution(
			const std::map<std::pair<unsigned int, unsigned int>, LabyrinthField>& labyrinthFieldMap,
			const std::map<std::pair<unsigned int, unsigned int>, LabyrinthPathType>& labyrinthPathMap
		);

		/**
		** Draws the labyrint via OpenGL, this is a callback function, which called from OpenGL main loop.
		**/
		void drawLabyrinth();
};

}