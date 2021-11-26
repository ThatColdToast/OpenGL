#pragma once

#include <glm/glm.hpp>

#include "Test.h"

namespace test
{
	class TestTextureImGui : public Test
	{
	private:
		glm::vec3 translationA; // (200, 200, 0);
		glm::vec3 translationB; // (400, 200, 0);
	public:
		TestTextureImGui();
		~TestTextureImGui();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}