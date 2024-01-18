#include <SFML/Graphics.hpp>

#include <iostream>

#include "gravity.h"
#include "object.h"

float getMagnitude(const sf::Vector2f& v)
{
	return std::sqrtf(std::powf(v.x, 2) + std::powf(v.y, 2));
}

float getMagnitude(const sf::Vector2f &src, const sf::Vector2f &dst)
{
	return getMagnitude(src - dst);
}

sf::Vector2f getDistance(const sf::Vector2f& src, const sf::Vector2f& dst)
{
	return (src - dst);
}

sf::Vector2f normalize(const sf::Vector2f& v, float magnitude)
{
	return v / magnitude;
}

sf::Vector2f normalize(const sf::Vector2f& v)
{
	return normalize(v, getMagnitude(v));
}

void printSfVector(const sf::Vector2f& vec)
{
	std::cout << vec.x << ", " << vec.y << '\n';
}

// Apply gravity to all the objects in the vector w.r.t the object at srcObjectIndex.
void Gravity::applyGravity(std::vector<Object*> vecObjects, size_t srcObjectIndex)
{
	if (srcObjectIndex >= vecObjects.size())
	{
		return;
	}
		
	// Get the srcObject.
	const Object* srcObject = vecObjects[srcObjectIndex];

	for (size_t i = 0; i < vecObjects.size(); ++i)
	{
		if (i != srcObjectIndex)
		{
			const sf::Vector2f distanceVector = getDistance(srcObject->getPosition(), vecObjects[i]->getPosition());
			
			const float magnitude = getMagnitude(distanceVector);

			std::cout << "Mag: " << magnitude << ", distanceVector: ";
			printSfVector(distanceVector);

			// Get the direction of the distance.
			sf::Vector2f direction = normalize(distanceVector, magnitude);
			std::cout << "DirectionVector: ";
			printSfVector(direction);

			// Get the force of gravity.
			const float force = static_cast<float>(Gravity::getGravitationalConstant() * srcObject->getMass() * vecObjects[i]->getMass()) / std::powf(magnitude, 2);
			
			const float theta = std::atan2f(distanceVector.y, distanceVector.x);

			sf::Vector2f forceVector;
			forceVector.x = std::cosf(theta) * force;
			forceVector.y = std::sinf(theta) * force;

			std::cout << "Force: " << force << ", Force Vector:";
			printSfVector(forceVector);

			vecObjects[i]->addForce(forceVector);
		}
	}
}