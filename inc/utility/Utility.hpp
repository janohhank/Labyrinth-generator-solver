#pragma once

//Labyrinth project includes.
#include "DirectionType.h"

//STD includes.
#include <random>
#include <algorithm>

namespace labyrinth{

/**
** Gives random (shuffled) directions in a vector (four directions).
** @return the <code>DirectionType</code>s in a vector.
**/
inline std::vector<DirectionType> getRandomDirections(){
	std::random_device randomDevice;
	std::mt19937 rng(randomDevice());

	std::vector<DirectionType> directions =
		{
			DirectionType::UP,
			DirectionType::DOWN,
			DirectionType::LEFT,
			DirectionType::RIGHT
		}
	;

	std::shuffle(directions.begin(), directions.end(), rng);
	return directions;
}

}