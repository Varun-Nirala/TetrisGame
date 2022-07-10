#pragma once

#include <memory>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

class DisplayWindow;
class Drawable;

class Engine
{
public:
	Engine();
	~Engine();

	bool init(const char* title, int width, int height, int& hintOpenGlMajorVersion, int& hintOpenGlMinorVersion);

	void addDrawable(Drawable* pdrawable);

	void startLoop();

	void onKeyInput(int key, int scancode, int action, int mods);
	void onMouseMove(double posX, double posY);
	void onMouseScroll(double offsetX, double offsetY);
	void onMouseButton(int button, int action, int mods);

	void enableDepthTest();
	void enableStencilTest();
	void enableBlendFunc();

	bool isDepthTestEnable() const;
	bool isStencilTestEnable() const;
	bool isBlendFuncEnable() const;

private:
	void gameLoop();
	void update(float elapsedDeltaTimeInMs);
	
	void render();
	void preRender();
	void postRender();
private:
	std::unique_ptr<DisplayWindow>			m_pWindow;
	glm::vec4								m_clearColor{ 0.2f, 0.3f, 0.3f, 1.0f };
	GLuint									m_enabledBits{};

	std::vector<Drawable*>					m_drawables;
};