#pragma once

#include "Test.h"

namespace test
{
	class TestTemplate : public Test
	{
	private:
	public:
		TestTemplate();
		~TestTemplate();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}