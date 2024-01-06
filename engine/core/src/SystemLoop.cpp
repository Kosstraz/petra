#include "../Core.hpp"

#include <base/Camera.hpp>
#include <base/GeometryTest.hpp>

#include <core/Chrono.hpp>

#include <core/SceneManager.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Core::Loop()
{
        // Debugage
    DEBUG(CORE_LOG, "Lancement de l'execution principale du programme.")
    Chrono c;
    c.Start();

        // Fenêtre et paramètres OpenGL
    GLFWwindow* context = glfwGetCurrentContext();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_MULTISAMPLE);

        // Callback
    glfwSetKeyCallback(context, key_callback);

        // Scène principale
    Scene* mainLevel     = new Scene();
    SceneManager::SetCurrentScene(mainLevel);

        // Personnalisation   <---
    Camera*       cam = new Camera("mainCamera");
    GeometryTest* geo = new GeometryTest("geo" );
    geo->WhatBuild(DRAW_CUBE);

        // Charge la scène et tous ces éléments
    SceneManager::GetCurrentScene()->LoadThisScene();





        // Modifications de la Personnalisation





    c.Stop();
    EXEC_TIME(c.GetTime())
    DEBUG_GL()
    while (!glfwWindowShouldClose(context))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);












            // Dessin tous les éléments de la scène
        SceneManager::GetCurrentScene()->DrawThisScene();

        glfwSwapBuffers(context);
        glfwPollEvents();
    }

    DEBUG(CORE_LOG, "Suppression de la memoire, fin de programme.")
    delete mainLevel;
}