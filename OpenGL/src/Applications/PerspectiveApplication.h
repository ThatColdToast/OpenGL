#pragma once

#include "Application.h"

#include <memory>
#include "../vendor/glm/glm.hpp"

#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

class PerspectiveApplication : public Application
{
private:
	/* Required For Rendering */
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<Texture> m_Texture;

	/* MVP */
	glm::mat4 m_proj, m_view;
	
	/* Specific to this model */
	glm::vec3 m_TranslationA, m_TranslationB, m_TranslationC, m_CameraTranslation;
	float m_rotation;
public:
	PerspectiveApplication();
	~PerspectiveApplication();

	void OnUpdate(Timer g_timer) override;
	void OnRender() override;
	// void OnImGuiRender() override;
};