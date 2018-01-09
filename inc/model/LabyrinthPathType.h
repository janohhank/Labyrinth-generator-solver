#pragma once

namespace labyrinth{

/**
** The labyrinth solution type for each labyrinth field.
**
** @author Kisházi "janohhank" János
**/
enum class LabyrinthPathType{
	GOOD_PATH,	//Good solution
	WRONG_WAY,	//Dead end
	UNKNOWN		//Not explored path
};

}
