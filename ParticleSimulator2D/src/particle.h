#pragma once

#include <glm/glm.hpp>

enum class PARTICLE_TYPE
{
	SAND,
	WATER,
	FIRE
};

struct Transformations
{
	glm::vec2		size{};
	glm::vec2		position{};
	glm::vec2		scale{ 1.0f };
	glm::vec3		rotationVec{ 0.0f, 0.0f, 1.0f };
	float			rotationInDeg{};
};

class Particle
{
public:
	Particle(glm::vec2 pos, glm::vec2 size = glm::vec2{ 2.0f, 2.0f }, PARTICLE_TYPE type = PARTICLE_TYPE::SAND);

	void update(float elapsedDeltaTimeInSec);
	void render();

private:
	bool				m_bisActive{ true };
	bool				m_bIsStatic{ false };
	PARTICLE_TYPE		m_type{};
	Transformations		m_transformations{};
};