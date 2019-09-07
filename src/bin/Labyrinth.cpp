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
float spanX = 0.0f;
float spanY = 0.0f;

/**
** OpenGL "glutDisplayFunc" callback implementation.
**/
void display(){
	renderer->drawLabyrinth();
}

/**
** OpenGL "glutReshapeFunc" callback implementation.
**/
void reshapeWindow(int width, int height){
	const float& x = spanX;
	const float& y = spanY;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 

	gluOrtho2D(0.0, x, y, 0.0);
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

	if(LABYRINTH_HEIGHT > 100 || LABYRINTH_WIDTH > 100){
		throw logic_error("The required labyirnth size is lower then 100 in each dimension!");
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

	const int& windowInitWidth = 500;
	const int& windowInitHeight = 500;
	const int& windowInitPositionX = 50;
	const int& windowInitPositionY = 50;
	spanX = ((static_cast<float>(LABYRINTH_WIDTH) / 10.0f) + 0.1f) * 1.1f;
	spanY = ((static_cast<float>(LABYRINTH_HEIGHT) / 10.0f) + + 0.1f) * 1.1f;

	// Initialize the OpenGL GUI.
	glutInit(&argc, argv);
	glutInitWindowSize(windowInitWidth, windowInitHeight);
	glutInitWindowPosition(windowInitPositionX, windowInitPositionY);
	glutCreateWindow("LabyrinthSolver");
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeWindow);

	glViewport(0, 0, windowInitWidth, windowInitHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutMainLoop();

	return 0;
}