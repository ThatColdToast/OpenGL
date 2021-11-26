#pragma once

#include "Test.h"

#include <memory>
#include "vendor/glm/glm.hpp"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace test
{
	class TestTexture2D : public Test
	{
	private:
		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 proj;
		glm::mat4 view;

	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}