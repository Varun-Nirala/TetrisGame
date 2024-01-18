#ifndef __HELPER_H__
#define __HELPER_H__

#include <random>
#include <chrono>
#include <vector>
#include "logger.h"

namespace Helper
{
static inline void printSfVector(std::string msg, const sf::Vector2f& vec)
{
	ns_Util::Logger::LOG_MSG(msg, vec.x, ", ", vec.y);
}

static inline int getRandomNumber(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_int_distribution<> distrib(min, max);

	return distrib(gen);
}

static inline float getRandomNumber(float min, float max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_real_distribution<> distrib(min, max);

	return static_cast<float>(distrib(gen));
}

static inline std::chrono::time_point<std::chrono::steady_clock> getCurrentTime()
{
	return std::chrono::steady_clock::now();
}

static inline int64_t getElapsedTimeInMicroseconds(const std::chrono::time_point<std::chrono::steady_clock>& previousTime)
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previousTime).count();
}

template<typename T>
static inline void printVectorOfVector(const std::vector<std::vector<T>>& mat)
{
	for (size_t i = 0; i < mat.size(); ++i)
	{
		for (size_t j = 0; j < mat[i].size(); ++j)
		{
			ns_Util::Logger::LOG_MSG(mat[i][j], ' ');
		}
		ns_Util::Logger::LOG_MSG('\n');
	}
	ns_Util::Logger::LOG_MSG('\n');
}
}
#endif //!__HELPER_H__