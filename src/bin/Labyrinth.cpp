/**
** @brief This example generates an N*M labyirnth, and make a solution for it.
**	  Displayed with OpenGL GLUT.
**
** @author Kisházi "janohhank" János
**/

// Labyrinth project includes.
#include "../inc/model/Labyrinth.h"
#include "../inc/gui/LabyrinthRenderer.h"
#include "../inc/solver/BacktrackerLabyrinthSolver.h"

// STL include.
#include <iostream>

using namespace std;
using namespace labyrinth;

/*
* Program static renderer instance.
*/
unique_ptr<LabyrinthRenderer> renderer = make_unique<LabyrinthRenderer>();

/**
** OpenGL "glutDisplayFunc" callback implementation.
**/
void display(){
	renderer->drawLabyrinth();
}

/**
** Standard output log helper function.
** @param file is the source file path, usually the __FILE__
** @param type is the type of the log message, for example INFO or ERROR
** @param message the log message in a string
**/
void print(
	const string& file,
	const string& type,
	const string& message
){
	cout << "[" << file << "]" << "[" << type << "]" << " " << message << endl;
}

/**
** Example usage information.
**/
void usage(char *argv[]){
	cout << "[" << argv[0] << "]" << " Requires the following arguments:" << " LABYRiNTH_HEIGHT" << " LABYRiNTH_WIDTH" << endl
	<< "	Where: " << endl
	<< "		LABYRiNTH_HEIGHT is the required labyrinth discrete height size. It can be [4,10]." << endl
	<< "		LABYRiNTH_WIDTH is the required labyrinth discrete width size. It can be [4,10]." << endl;
}

/*
* Main acces point of the program.
*/
int main(int argc, char** argv){
	if(argc < 3){
		usage(argv);
		return 1;
	}

	const unsigned int LABYRINTH_HEIGHT = stoi(argv[1]);
	const unsigned int LABYRINTH_WIDTH = stoi(argv[2]);

	if(LABYRINTH_HEIGHT > 10 || LABYRINTH_WIDTH > 10){
		throw logic_error("The required labyirnth size is lower then 10 in each dimension!");
	}

	print(__FILE__,"INFO","The required labyrinth size is: " + to_string(LABYRINTH_HEIGHT) + "x" + to_string(LABYRINTH_WIDTH) + ".");

	print(__FILE__,"INFO","Initializing and generating the labyirnth.");
	const unique_ptr<Labyrinth> labyrinth = make_unique<Labyrinth>(LABYRINTH_HEIGHT, LABYRINTH_WIDTH);
	const unique_ptr<LabyrinthSolverBase> labyrinthBacktracer = make_unique<BacktrackerLabyrinthSolver>();

	print(__FILE__,"INFO","Solving the labyirnth.");
	labyrinthBacktracer->solveLabyrinth(
		labyrinth
	);

	print(__FILE__,"INFO","Display the solution.");
	renderer->receiveLabyrinthMapAndSolution(
		labyrinth->getLabyrinthFieldMap(),
		labyrinth->getLabyrinthPathMap()
	);

	// Initialize the OpenGL GUI.
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("LabyrinthSolver");
	glutDisplayFunc(display);
	gluOrtho2D(0, 1.5, 1.5, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutMainLoop();

	return 0;
}