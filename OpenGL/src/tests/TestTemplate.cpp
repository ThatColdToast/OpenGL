#include "tests/TestTemplate.h"

#include <GL/glew.h>
#include "Utils/Profiling.h"
#include "Graphics/GLCall.h"
#include "vendor/imgui/imgui.h"

namespace test
{
	TestTemplate::TestTemplate()
	{
		PROFILE_FUNCTION();
		m_Name = "Test Template";
	}

	TestTemplate::~TestTemplate()
	{
	}

	void TestTemplate::OnUpdate(float deltaTime)
	{
	}

	void TestTemplate::OnRender()
	{
	}

	void TestTemplate::OnImGuiRender()
	{
	}
}