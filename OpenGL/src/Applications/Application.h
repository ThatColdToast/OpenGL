#pragma once

#include "Utils/Timing.h"

class Application
{
public:
	const char* m_Name;

	Application() : m_Name("Template Application") {}
	virtual ~Application() {}

	virtual void OnUpdate(Timer g_timer) {}
	virtual void OnRender() {}
	virtual void OnImGuiRender() {}
};