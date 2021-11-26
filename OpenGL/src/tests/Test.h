#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <functional>

namespace test
{
	class Test
	{
	public:
		const char* m_Name;

		Test() : m_Name("Empty Test") {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test
	{
	private:
		Test*& m_CurrentTest;
		std::vector < std::pair < std::string, std::function<Test* () > > > m_Tests;
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		template <typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering Test: " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	};
}