#pragma once

#include <utility>
#include <glad/glad.h>

class Drawable
{
public:
	Drawable(GLuint shaderID, bool bOwnIt)
	{
		m_shader.first = shaderID;
		m_shader.second = bOwnIt;
	}

	virtual void init() = 0;
	virtual void update(float elapsedTimeInMs) = 0;
	virtual void render() = 0;
	virtual void release();

	void setShader(GLuint id, bool bOwnIt) { m_shader.first = id; m_shader.second = bOwnIt; }
	void setVAO(GLuint id, bool bOwnIt) { m_vao.first = id; m_vao.second = bOwnIt; }
	void setVBO(GLuint id, bool bOwnIt) { m_vbo.first = id; m_vbo.second = bOwnIt; }

	virtual void activateAll();
	virtual void deactivateAll();

	void activateShader() { glUseProgram(m_shader.first); }
	void activateVAO() { glBindVertexArray(m_vao.first); }
	void activateVBO() { glBindBuffer(GL_ARRAY_BUFFER, m_vbo.first); }

	void deactivateShader() { glUseProgram(0); }
	void deactivateVAO() { glBindVertexArray(0); }
	void deactivateVBO() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	static GLuint createVAO();
	static GLuint createVBO();

protected:
	virtual void draw() = 0;

protected:
	std::pair<GLuint, bool>			m_shader;
	std::pair<GLuint, bool>			m_vao;
	std::pair<GLuint, bool>			m_vbo;
};

inline void Drawable::release()
{
	if (m_shader.second && m_shader.first)
	{
		glDeleteProgram(m_shader.first);
	}

	if (m_vao.second && m_vao.first)
	{
		glDeleteVertexArrays(1, &m_vao.first);
	}

	if (m_vbo.second && m_vbo.first)
	{
		glDeleteBuffers(1, &m_vbo.first);
	}
	m_shader.first = m_vao.first = m_vbo.first = 0;
}

inline void Drawable::activateAll()
{
	activateShader();
	activateVAO();
	activateVBO();
}

inline void Drawable::deactivateAll()
{
	deactivateVBO();
	deactivateVAO();
	deactivateShader();
}

inline GLuint Drawable::createVAO()
{
	GLuint id{};
	glGenVertexArrays(1, &id);
	return id;
}

inline GLuint Drawable::createVBO()
{
	GLuint id{};
	glGenBuffers(1, &id);
	return id;
}