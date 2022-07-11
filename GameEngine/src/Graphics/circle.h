#pragma once

#include "drawable.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "points.h"

class Circle : public Drawable
{
public:
	Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec2 centre);
	Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec3 centre);
	Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, GLfloat x, GLfloat y, GLfloat z = 0.0f);

	void init() override;
	void update(float elapsedTimeInMs) override;
	void render() override;
	void release() override;

protected:
	void draw() override;

private:
	glm::vec3		m_centre;
	GLfloat			m_radius{};
	Points			m_points;
};

Circle::Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec2 centre)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(centre, 0.0f)
	, m_points(shaderID, bOwnIt)
{}

Circle::Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec3 centre)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(centre)
	, m_points(shaderID, bOwnIt)
{}

Circle::Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, GLfloat x, GLfloat y, GLfloat z)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(x, y, z)
	, m_points(shaderID, bOwnIt)
{}

inline void Circle::init()
{
	// Create and assign points
	// r2 = x2 + y2
	// x = rcos0
	// y = rsin0
	glm::vec3 p = m_centre;
	p.x += m_radius;
	for (GLfloat i = 0; i < 360; i += 0.1f)
	{
		p.x = m_centre.x + m_radius * (GLfloat)std::cos(glm::radians(i));
		p.y = m_centre.y + m_radius * (GLfloat)std::sin(glm::radians(i));
		m_points.addPoint(p);
	}

	m_points.init();
}

inline void Circle::update(float elapsedTimeInMs)
{
	m_points.update(elapsedTimeInMs);
}

inline void Circle::render()
{
	m_points.render();
}

inline void Circle::release()
{
	Drawable::release();
}

inline void Circle::draw()
{
	;
}