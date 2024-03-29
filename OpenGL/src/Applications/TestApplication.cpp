#include "Applications/TestApplication.h"

#include <GL/glew.h>

#include "Utils/Profiling.h"

#include "Graphics/GLCall.h"
#include "vendor/imgui/imgui.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "Graphics/VertexArray.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

TestApplication::TestApplication()
    : m_TranslationA(0.0, 0.0, 0.5), m_TranslationB(300.0, 200.0, 1.0), m_TranslationC(600.0, 400.0, 2.0)
{
    PROFILE_FUNCTION();

    m_Name = "Texture 2D";

    float positions[] = {
        -50.0f, -50.0f, 0.0f, 0.0f, // 0
        50.0f, -50.0f, 1.0f, 0.0f,  // 1
        50.0f, 50.0f, 1.0f, 1.0f,   // 2
        -50.0f, 50.0f, 0.0f, 1.0f   // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    /* OpenGL Blending Mode */
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    m_VAO = std::make_unique<VertexArray>();

    m_VBO = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.PushFloat(2); // Push 2 Positions ()
    layout.PushFloat(2); // Push 2 TexCoords

    m_VAO->AddBuffer(*m_VBO, layout);

    m_IBO = std::make_unique<IndexBuffer>(indices, 6);

    m_proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    // m_view = glm::translate(glm::toMat4(glm::quat), glm::vec3(0, 0, 0));

    m_Shader = std::make_unique<Shader>("OpenGL/res/shaders/Basic.shader");
    m_Texture = std::make_unique<Texture>("OpenGL/res/textures/test.png");
    m_Texture->Bind();
    m_Shader->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);

    m_VAO->Unbind();
    m_VBO->Unbind();
    m_IBO->Unbind();
    m_Shader->Unbind();

    /* Application Specific */
    m_CameraTranslation = glm::vec3(0, 0, 0);
}

TestApplication::~TestApplication()
{
}

void TestApplication::OnUpdate(Timer g_timer)
{
    // m_TranslationA.x += g_timer.deltaTime() * 0.05;
    // m_TranslationB.x += g_timer.deltaTime() * 0.05;
    // m_TranslationB.y += g_timer.deltaTime() * 0.05;

    // m_CameraTranslation.x += g_timer.deltaTime() * 0.01;
    // m_view = glm::translate(glm::mat4(1.0f), m_CameraTranslation);
}

void TestApplication::OnRender()
{
    GLCall(glClearColor(0.0f, 0.05f, 0.2f, 0.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    Renderer renderer;

    m_Shader->Bind();

    {
        PROFILE_SCOPE("Set 1st Uniform Mat4");
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
        glm::mat4 mvp = m_proj * m_view * model;
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
    }

    {
        PROFILE_SCOPE("Set 2nd Uniform Mat4");
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
        glm::mat4 mvp = m_proj * m_view * model;
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
    }

    {
        PROFILE_SCOPE("Set 3rd Uniform Mat4");
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationC);
        glm::mat4 mvp = m_proj * m_view * model;
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
    }
}

// void TestApplication::OnImGuiRender()
// {
//     PROFILE_FUNCTION();
//     ImGui::SameLine();
//     ImGui::Text("Texture 2D");
//     ImGui::Separator();

//     ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
//     ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);

//     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
// }