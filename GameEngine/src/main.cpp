#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaderProgram.h"
#include "engine.h"

#include "resourceManager.h"

#include "Common/constants.h"

#include "Graphics/point.h"
#include "Graphics/points.h"
#include "Graphics/line.h"
#include "Graphics/lines.h"
#include "Graphics/triangle.h"
#include "Graphics/rectangle.h"
#include "Graphics/circle.h"

// opengl screen
// -1,1        1,1
//	  __________
//   |			|
//   |			|
//   |			|
//	 |__________|
// -1,-1	   1,-1

// GLSL extensions
// .vert -> vertex shader
// .tesc -> Tessellation control shader
// .tese -> Tessellation evaluation shader
// .geom -> Geometry shader
// .frag -> Fragment shader
// .comp -> Compute shader

void drawPoint(Engine& e, ResourceManager& rm);
void drawPoints(Engine& e, ResourceManager& rm);
void drawLine(Engine& e, ResourceManager& rm);
void drawLines(Engine& e, ResourceManager& rm);
void drawTriangle(Engine& e, ResourceManager& rm);
void drawRectangle(Engine& e, ResourceManager& rm);
void drawCircle(Engine& e, ResourceManager& rm, bool bFilled);


int main()
{
	ResourceManager rm;

	Engine e;
	int major = OPENGL_MAJOR_VERSION;
	int minor = OPENGL_MINOR_VERSION;

	e.init(TITLE, WIDTH, HEIGHT, major, minor);

	glEnable(GL_LINE_SMOOTH);

	std::vector<std::pair<std::string, SHADER_TYPE>> shaders;
	shaders.push_back(std::make_pair(R"(.\resources\Shaders\point.vert)", SHADER_TYPE::VERT));
	shaders.push_back(std::make_pair(R"(.\resources\Shaders\point.frag)", SHADER_TYPE::FRAG));
	rm.addShader("Point_Shader", shaders);

	shaders[0] = std::make_pair(R"(.\resources\Shaders\pointWithMVP.vert)", SHADER_TYPE::VERT);
	shaders[1] = std::make_pair(R"(.\resources\Shaders\pointWithMVP.frag)", SHADER_TYPE::FRAG);
	rm.addShader("PointWithMVP_Shader", shaders);

	drawPoint(e, rm);

	drawPoints(e, rm);

	drawLine(e, rm);
	
	drawLines(e, rm);

	drawTriangle(e, rm);

	drawRectangle(e, rm);

	drawCircle(e, rm, false);		// draw circle

	drawCircle(e, rm, true);		// draw filled circle

	e.startLoop();
	return 0;
}

void drawPoint(Engine& e, ResourceManager& rm)
{
	Point *point = new Point(rm.shader("PointWithMVP_Shader"), true, glm::vec2{ -0.5f, -0.5f });
	point->init();
	e.addDrawable(point);
}

void drawPoints(Engine& e, ResourceManager& rm)
{
	Points *points = new Points(rm.shader("PointWithMVP_Shader"), false);
	float inc = 0.001f;
	glm::vec3 start(0.0f);
	for (size_t i = 0; i < 300; ++i)
	{
		points->addPoint(start);
		start.y += inc;
	}
	points->init();
	e.addDrawable(points);
}

void drawLine(Engine& e, ResourceManager& rm)
{
	Line *line = new Line(rm.shader("PointWithMVP_Shader"), false, glm::vec2(0.5f, 0.0f), glm::vec2(0.5f, 0.5f));
	line->init();
	e.addDrawable(line);
}

void drawLines(Engine& e, ResourceManager& rm)
{
	Lines *lines = new Lines(rm.shader("PointWithMVP_Shader"), false);
	lines->addine(glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, -1.0f));
	lines->addine(glm::vec2(1.0f, -1.0f), glm::vec2(0.0f, 1.0f));

	lines->setMakeLoop(true);
	lines->init();

	e.addDrawable(lines);
}

void drawTriangle(Engine& e, ResourceManager& rm)
{
	Triangle* tri = new Triangle(rm.shader("PointWithMVP_Shader"), false);
	tri->setTriangle({ 
		glm::vec2{-0.5f, 0.9f},
		glm::vec2{-0.9f, 0.5f},
		glm::vec2{-0.1f, 0.5f}
		});

	tri->init();

	e.addDrawable(tri);
}

void drawRectangle(Engine& e, ResourceManager& rm)
{
	Rectangle* rect = new Rectangle(rm.shader("PointWithMVP_Shader"), false);

	rect->setRectangle(0.2f, 0.2f, 0.4f, 0.4f);
	rect->init();

	e.addDrawable(rect);
}

void drawCircle(Engine& e, ResourceManager& rm, bool bFilled)
{
	Circle *cir = new Circle(rm.shader("PointWithMVP_Shader"), false, 0.4f, glm::vec3(0.0f));
	cir->setDrawFilled(bFilled);
	cir->init();
	e.addDrawable(cir);

}