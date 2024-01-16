#include <core/Core.hpp>

#include <core/SceneManager.hpp>
#include <base/Camera.hpp>
#include <base/GeometryTest.hpp>

#include <rendering/Texture.hpp>

#include <core/Chrono.hpp>

#include <sstream>

//  Todo:
//

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    IF_RARELY(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 0x01);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    Handle::window_size = {width, height};
    Camera* get = SceneManager::GetCurrentScene()->FindACTOR<Camera>("mainCamera");
    get->Perspective(width, height);
    get = nullptr;
}

int Core::Loop()
{
        // Debugage
    DEBUG(CORE_LOG, "Lancement de l'execution principale du programme.")
    Chrono c;
    c.Start();

        // Fenêtre et paramètres OpenGL
    GLFWwindow* context = glfwGetCurrentContext();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

        // Callback
    glfwSetKeyCallback(context, key_callback);
    glfwSetFramebufferSizeCallback(context, framebuffer_size_callback);

        // Scène principale
    Scene mainLevel     = Scene();
    SceneManager::SetCurrentScene(&mainLevel);

        // Personnalisation   <---
    Camera cam              =   Camera("mainCamera");
    GeometryTest player     =   GeometryTest("player");
    player.SetColor(Color3(1.f, 0.f, 1.0f));
    player.WhatBuild(DRAW_CUBE);

        // Charge la scène et tous ces éléments
    SceneManager::GetCurrentScene()->LoadThisScene();

    c.Stop();
    EXEC_TIME(c.GetTime())
    DEBUG_GL()
    while (!glfwWindowShouldClose(context))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

        player.SetColor(Color3(1.f, 0.f, 1.0f));
        player.SetPosition(Vector3f(0.0f));



            // Dessin tous les éléments de la scène
        SceneManager::GetCurrentScene()->DrawThisScene();

        glfwSwapBuffers(context);
        glfwPollEvents();
    }

    DEBUG(CORE_LOG, "Terminate memory")
    glfwTerminate();
    DEBUG(CORE_LOG, "GLFW resources terminated")
    glfwDestroyWindow(context);
    DEBUG(CORE_LOG, "Window destroyed")

    return (0);
}