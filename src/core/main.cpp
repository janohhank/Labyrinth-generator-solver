/**
** @brief This example generates an N*M labyirnth, and make a solution for it.
**	  Displayed with OpenGL GLUT.
**
** @author Kisházi "janohhank" János
**/

//Labyrinth project includes.
#include "../inc/model/Labyrinth.h"
#include "../inc/gui/LabyrinthRenderer.h"
#include "../inc/solver/BacktrackerLabyrinthSolver.h"

using namespace std;
using namespace labyrinth;

/*
* Program static renderer instance.
*/
unique_ptr<LabyrinthRenderer> renderer = make_unique<LabyrinthRenderer>();

/*
* OpenGL "glutDisplayFunc" callback implementation.
*/
void display(){
	renderer->drawLabyrinth();
}

/*
* Main acces point of the program.
*/
int main(int argc, char** argv){
	const unsigned int LABYRINTH_HEIGHT = 10;
	const unsigned int LABYRINTH_WIDTH = 10;

	//Initialize the labyrinth.
	const unique_ptr<Labyrinth> labyrinth = make_unique<Labyrinth>(LABYRINTH_HEIGHT, LABYRINTH_WIDTH);
	const unique_ptr<LabyrinthSolverBase> labyrinthBacktracer = make_unique<BacktrackerLabyrinthSolver>();

	//Solve labyrinth with backtracking.
	labyrinthBacktracer->solveLabyrinth(
		labyrinth
	);

	//Send labyrinth map and solution map to renderer.
	renderer->receiveLabyrinthMapAndSolution(
		labyrinth->getLabyrinthFieldMap(),
		labyrinth->getLabyrinthPathMap()
	);

	//Initialize the OpenGL GUI.
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