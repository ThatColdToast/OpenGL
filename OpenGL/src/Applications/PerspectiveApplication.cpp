#include "Applications/PerspectiveApplication.h"

#include <iostream>
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

PerspectiveApplication::PerspectiveApplication()
    : m_TranslationA(0.0, 0.0, 0.5), m_TranslationB(300.0, 200.0, 0.5f), m_TranslationC(600.0, 400.0, 50.0), m_rotation(0.0f)
{
    PROFILE_FUNCTION();

    m_Name = "3D Perspective";

    float positions[] = {
        /* POS X, Y, Z   | TexCoord X, Y */
        // -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, // 0 BLF
        //  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, // 1 BRF
        //  1.0f,  1.0f, -1.0f, 1.0f, 1.0f, // 2 TRF
        // -1.0f,  1.0f, -1.0f, 0.0f, 1.0f, // 3 TLF
        // -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // 4 BLB
        //  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, // 5 BRB
        //  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, // 6 TRB
        // -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, // 7 TLB

        // Front
        -0.5f, -0.5f, -0.5f, 0.0, 0.0, // 0 BLF
         0.5f, -0.5f, -0.5f, 1.0, 0.0, // 1 BRF
         0.5f,  0.5f, -0.5f, 1.0, 1.0, // 2 TRF
        -0.5f,  0.5f, -0.5f, 0.0, 1.0, // 3 TLF

        // Right
         0.5f, -0.5f, -0.5f, 0.0, 0.0, // 4 BRF
         0.5f, -0.5f,  0.5f, 1.0, 0.0, // 5 BRB
         0.5f,  0.5f,  0.5f, 1.0, 1.0, // 6 TRB
         0.5f,  0.5f, -0.5f, 0.0, 1.0, // 7 TRF

         // Back
         0.5f, -0.5f, 0.5f, 0.0, 0.0, // 8 BRB
        -0.5f, -0.5f, 0.5f, 1.0, 0.0, // 9 BLB
        -0.5f,  0.5f, 0.5f, 1.0, 1.0, // 10 TLB
         0.5f,  0.5f, 0.5f, 0.0, 1.0, // 11 TRB

        // Left
        -0.5f, -0.5f,  0.5f, 0.0, 0.0, // 12 BLB
        -0.5f, -0.5f, -0.5f, 1.0, 0.0, // 13 BLF
        -0.5f,  0.5f, -0.5f, 1.0, 1.0, // 14 TLF
        -0.5f,  0.5f,  0.5f, 0.0, 1.0, // 15 TLB

        // Top
        -0.5f,  0.5f, -0.5f, 0.0, 0.0, // 16 TLF
         0.5f,  0.5f, -0.5f, 1.0, 0.0, // 17 TRF
         0.5f,  0.5f,  0.5f, 1.0, 1.0, // 18 TRB
        -0.5f,  0.5f,  0.5f, 0.0, 1.0, // 19 TLB

        // Bottom
        -0.5f, -0.5f,  0.5f, 0.0, 0.0, // 20 BLB
         0.5f, -0.5f,  0.5f, 1.0, 0.0, // 21 BRB
        -0.5f, -0.5f, -0.5f, 1.0, 1.0, // 22 BLF
         0.5f, -0.5f, -0.5f, 0.0, 1.0, // 23 BRF
    };

    unsigned int indices[] = {
        // 0, 1, 2,
        // 2, 3, 0,

        // 1, 5, 6,
        // 6, 2, 1,

        // 5, 4, 7,
        // 7, 6, 5,

        // 4, 0, 2,
        // 2, 7, 4,

        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20,
    };

    /* OpenGL Blending Mode */
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    /* OpenGL Face Culling */
    GLCall(glEnable(GL_CULL_FACE));
    GLCall(glCullFace(GL_BACK));
    GLCall(glFrontFace(GL_CCW));

    m_VAO = std::make_unique<VertexArray>();

    m_VBO = std::make_unique<VertexBuffer>(positions, 5 * 4 * 6 * sizeof(float));

    VertexBufferLayout layout;
    layout.PushFloat(3); // Push 3 Positions
    layout.PushFloat(2); // Push 2 TexCoords

    m_VAO->AddBuffer(*m_VBO, layout);

    m_IBO = std::make_unique<IndexBuffer>(indices, 3 * 2 * 6);

    m_proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1000.0f);
    // m_proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, 0.01f, 1.0f);
    // m_proj = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
    // m_proj = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, -1.0f, 100.0f);
    // m_proj = glm::perspectiveFov(90.0f, 1920.0f, 1080.0f, 0.01f, 100.0f);
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

PerspectiveApplication::~PerspectiveApplication()
{
}

void PerspectiveApplication::OnUpdate(Timer g_timer)
{
    // m_TranslationA.x += g_timer.deltaTime() * 0.05;
    // m_TranslationB.x += g_timer.deltaTime() * 0.05;o
    // m_TranslationB.y += g_timer.deltaTime() * 0.05;

    m_rotation += g_timer.deltaTime() * 0.05;
    if (m_rotation >= 360) m_rotation -= 360.0f;
    std::cout << "Rotation: " << m_rotation << std::endl;

    // m_CameraTranslation.x += g_timer.deltaTime() * 0.01;
    // m_view = glm::translate(glm::mat4(1.0f), m_CameraTranslation);
}

void PerspectiveApplication::OnRender()
{
    const float scalar = 100.0f;
    GLCall(glClearColor(0.0f, 0.05f, 0.2f, 0.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    Renderer renderer;

    m_Shader->Bind();

    // {
    //     PROFILE_SCOPE("Set 1st Uniform Mat4");
    //     glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
    //     model = glm::scale(glm::rotate(model, glm::radians(m_rotation), glm::vec3(1.0f, 1.0f, 0.0f)), glm::vec3(scalar, scalar, scalar));
    //     // glm::mat4 model = glm::rotate(glm::translate(glm::mat4(1.0f), m_TranslationA), glm::radians(m_rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    //     glm::mat4 mvp = m_proj * m_view * model;
    //     m_Shader->SetUniformMat4f("u_MVP", mvp);

    //     renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
    // }

    // {
    //     PROFILE_SCOPE("Set 2nd Uniform Mat4");
    //     glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
    //     model = glm::scale(glm::rotate(model, glm::radians(m_rotation), glm::vec3(1.0f, 1.0f, 0.0f)), glm::vec3(scalar, scalar, scalar));
    //     // glm::mat4 model = glm::rotate(glm::translate(glm::mat4(1.0f), m_TranslationB), glm::radians(m_rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    //     glm::mat4 mvp = m_proj * m_view * model;
    //     m_Shader->SetUniformMat4f("u_MVP", mvp);

    //     renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
    // }

    // {
    //     PROFILE_SCOPE("Set 3rd Uniform Mat4");
    //     // glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationC);
    //     // model = glm::scale(glm::rotate(model, glm::radians(m_rotation), glm::vec3(1.0f, 1.0f, 0.0f)), glm::vec3(scalar, scalar, scalar));

    //     // glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(scalar));

    //     // glm::mat4 model = glm::rotate(glm::translate(glm::mat4(1.0f), m_TranslationC), glm::radians(m_rotation), glm::vec3(0.0f, 1.0f, 0.0f));

    //     // glm::mat4 model =
    //     //     glm::scale(
    //     //         glm::translate(
    //     //             glm::rotate(
    //     //                 glm::mat4(1.0f),
    //     //                 glm::radians(m_rotation),
    //     //                 glm::vec3(1.0f)
    //     //             ),
    //     //             glm::vec3(300.0f, 300.0f, 0.0f)
    //     //         ),
    //     //     glm::vec3(scalar)
    //     //     );

    //     glm::mat4 mvp = m_proj * m_view * model;
    //     m_Shader->SetUniformMat4f("u_MVP", mvp);

    //     renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
    // }

    {
        // Cube 1
        glm::mat4 model = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(scalar)), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 mvp = m_proj * m_view * model;
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
    }

    {
        // Cube 2
        glm::mat4 model = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(scalar)), glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 mvp = m_proj * m_view * model;
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
    }
}

// void PerspectiveApplication::OnImGuiRender()
// {
//     PROFILE_FUNCTION();
//     ImGui::SameLine();
//     ImGui::Text("Texture 2D");
//     ImGui::Separator();

//     ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
//     ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);

//     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
// }