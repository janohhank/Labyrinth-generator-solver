#include "../inc/gui/LabyrinthRenderer.h"

namespace labyrinth{

LabyrinthRenderer::LabyrinthRenderer(){
	//Intentionally NOOP.
}

LabyrinthRenderer::~LabyrinthRenderer(){
	//Intentionally NOOP.
}

void LabyrinthRenderer::receiveLabyrinthMapAndSolution(
	const std::map<std::pair<unsigned int, unsigned int>, LabyrinthField>& labyrinthFieldMap,
	const std::map<std::pair<unsigned int, unsigned int>, LabyrinthPathType>& labyrinthPathMap
){
	std::lock_guard<std::mutex> lock(dataMutex);

	this->labyrinthFieldMap = labyrinthFieldMap;
	this->labyrinthPathMap = labyrinthPathMap;
}

void LabyrinthRenderer::drawLabyrinth(){
	std::lock_guard<std::mutex> lock(dataMutex);

	//Clear the color buffer (background).
	glClear(GL_COLOR_BUFFER_BIT);

	//
	const float scaleFactor = 10.0f;
	const float offsetRectangle = 0.1f;
	const float offsetRectangleWidth = 0.002;

	//
	std::tuple<float,float,float> rgb;

	glPushMatrix();
	glTranslatef(0.1f, 0.1f, 0);
	for(
		auto iterator = labyrinthFieldMap.cbegin();
		iterator != labyrinthFieldMap.cend();
		++iterator
	){
		const float y = static_cast<float>(iterator->first.first) / scaleFactor;
		const float x = static_cast<float>(iterator->first.second) / scaleFactor;

		if(iterator->second.getFieldType() == LabyrinthFieldType::ENTRANCE){
			rgb = {0.0f,0.0,1.0f};
		}else if(iterator->second.getFieldType() == LabyrinthFieldType::EXIT){
			rgb = {0.0f,1.0,0.0f};
		}else{
			rgb = {1.0f,0.0,0.0f};
		}

		for(const auto& wall : iterator->second.getSorruendedWalls()){
			switch(wall){
				case DirectionType::UP:
					glPushMatrix();
					glTranslatef(x, y, 0);
					glBegin(GL_QUADS);
						glColor3f(std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb));
						glVertex2f(offsetRectangle, offsetRectangleWidth);
						glVertex2f(0, offsetRectangleWidth);
						glVertex2f(0, 0);
						glVertex2f(offsetRectangle, 0);
					glEnd();
					glPopMatrix();
					
				break;
				case DirectionType::DOWN:
					glPushMatrix();
					glTranslatef(x, y + (offsetRectangle - offsetRectangleWidth), 0);
					glBegin(GL_QUADS);
						glColor3f(std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb));
						glVertex2f(offsetRectangle, offsetRectangleWidth);
						glVertex2f(0, offsetRectangleWidth);
						glVertex2f(0, 0);
						glVertex2f(offsetRectangle, 0);
					glEnd();
					glPopMatrix();
					
				break;
				case DirectionType::LEFT:
					glPushMatrix();
					glTranslatef(x, y, 0);
					glBegin(GL_QUADS);
						glColor3f(std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb));
						glVertex2f(offsetRectangleWidth, offsetRectangle);
						glVertex2f(0, offsetRectangle);
						glVertex2f(0, 0);
						glVertex2f(offsetRectangleWidth, 0);
					glEnd();
					glPopMatrix();
				break;
				case DirectionType::RIGHT:
					glPushMatrix();
					glTranslatef(x + (offsetRectangle - offsetRectangleWidth), y, 0);
					glBegin(GL_QUADS);
						glColor3f(std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb));
						glVertex2f(offsetRectangleWidth, offsetRectangle);
						glVertex2f(0, offsetRectangle);
						glVertex2f(0, 0);
						glVertex2f(offsetRectangleWidth, 0);
					glEnd();
					glPopMatrix();
				break;
				default:
					throw std::logic_error("Unhandled switch case!");
				break;
			}
		}
	}

	for(
		auto iterator = labyrinthPathMap.cbegin();
		iterator != labyrinthPathMap.cend();
		++iterator
	){
		const float y = static_cast<float>(iterator->first.first) / scaleFactor;
		const float x = static_cast<float>(iterator->first.second) / scaleFactor;

		if(iterator->second == LabyrinthPathType::GOOD_PATH){
			rgb = {0.0f,1.0,0.0f};
		}else if(iterator->second == LabyrinthPathType::WRONG_WAY){
			rgb = {1.0f,0.0,0.0f};
		}

		if(
			iterator->second == LabyrinthPathType::GOOD_PATH
			|| iterator->second == LabyrinthPathType::WRONG_WAY
		){
			glPushMatrix();
			glTranslatef(x + 0.025, y + 0.025, 0);
			glBegin(GL_POLYGON);
				glColor3f(std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb));
				glVertex2f(0.016f, 0.0f);
				glVertex2f(0.033f, 0.0f);
				glVertex2f(0.05f, 0.025f);
				glVertex2f(0.033f, 0.05f);
				glVertex2f(0.016f, 0.05f);
				glVertex2f(0.0f, 0.025f);
			glEnd();
			glPopMatrix();
		}
	}
	glPopMatrix();

	glFlush();
}

}
