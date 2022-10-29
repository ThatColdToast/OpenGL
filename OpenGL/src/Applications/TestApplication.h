#pragma once

#include "Application.h"

#include <memory>
#include "../vendor/glm/glm.hpp"

#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

class TestApplication : public Application
{
private:

	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<Texture> m_Texture;

	glm::mat4 proj, view;
	glm::vec3 m_TranslationA, m_TranslationB;
public:
	TestApplication();
	~TestApplication();

	void OnUpdate(Timer g_timer) override;
	void OnRender() override;
	// void OnImGuiRender() override;
};